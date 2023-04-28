#! /usr/bin/env python

import sys
import os
import argparse
import time
from math import exp, log
import random
from treeswift import *
import treeswift
import json
import numpy as np
from tripVote.placement_lib import complete_gene_trees

def __label_tree__(tree_obj):
	is_labeled = True
	i = 0
	labels = set()
	for node in tree_obj.traverse_preorder():
		if not node.is_leaf() and (not node.label or node.label in labels):
			is_labeled = False
			node.label = 'I' + str(i)
			i += 1        
		labels.add(node.label)
	return is_labeled

def compare_trees(true_trees, new_tree_file, output_dir):
	total_FN = 0
	for i in range(len(true_trees)):
		os.system("compareTrees/compareTrees.missingBranch " + output_dir + "/true_tree_" + str(i) + ".trees" + " " + new_tree_file + " > " + output_dir + "/log.txt")
		with open(output_dir + "/log.txt", 'r') as f:
			lines = f.readlines()
			FN = float(lines[0].split()[-1])
			total_FN += FN
	total_FN /= len(true_trees)
	return total_FN

def get_clade_leaves(clade_dict, node):
	if node.is_leaf():
		if node.label not in clade_dict:
			clade_dict[node.label] = [node.label]
		return

	leaves = []
	for child in node.child_nodes():
		if child.label in clade_dict:
			leaves += clade_dict[child.label]
		else:
			get_clade_leaves(clade_dict, child)
			leaves += clade_dict[child.label]
	clade_dict[node.label] = leaves

def cal_nodal_dist(u, v):
	u_ancestors = {}
	v_ancestors = {}
	u_ancestors[u.label] = 0
	v_ancestors[v.label] = 0

	node = u
	while not node.is_root():
		parent = node.parent
		u_ancestors[parent.label] = u_ancestors[node.label] + 1
		node = parent

	node = v
	while node.label not in u_ancestors:
		parent = node.parent
		v_ancestors[parent.label] = v_ancestors[node.label] + 1
		node = parent

	lca = node
	dist = u_ancestors[lca.label] + v_ancestors[lca.label]
	return dist

def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument('-i', '--input', required=True, help="Input tree to be completed")
	parser.add_argument('-r', '--refs', required=True, help="Reference trees that are used to complete input trees.")
	parser.add_argument('-o', '--output_file', required=True, help="Output file")
	parser.add_argument('-l', '--log_dir', required=True, help="Log Directory")
	parser.add_argument('-m', '--min_thresh', required=True, help="Minimum Clade Size")
	parser.add_argument('-x', '--max_thresh', required=True, help="Maximum Clade Size")



	args = parser.parse_args()

	random.seed(a=1105)

	start = time.time()

	with open(args.input,'r') as f:
		inputTree = f.read().strip().split("\n")[0]

	with open(args.refs,'r') as f:
		refTrees = f.read().strip().split("\n")

	log_dir = args.log_dir
	if not os.path.isdir(log_dir):
		os.mkdir(log_dir)
	scores_dir = os.path.join(log_dir, "scores")
	if not os.path.isdir(scores_dir):
		os.mkdir(scores_dir)

	with open(args.output_file, 'w') as f:
		f.write("cldae taxa" + "\t" + "clade sizde" + "\t" + "label" + "\t" + "runtime" + "\t" + "nodal dist" + "\n")

	inputTree_obj = read_tree_newick(inputTree)
	is_labeled = __label_tree__(inputTree_obj)
	# print(inputTree_obj.newick())
	for node in inputTree_obj.traverse_preorder():
		node.edge_length = None

	dataset = []
	num_leaves = inputTree_obj.num_nodes(leaves=True, internal=False)

	nodes = []
	tree_root = None
	for node in inputTree_obj.traverse_preorder():
		if node.is_root():
			tree_root = node
		else:
			nodes.append(node)
	nodes = np.random.permutation(nodes)

	if tree_root is None:
		print("No root???")

	clade_dict = {}
	get_clade_leaves(clade_dict, tree_root)

	for n in nodes:
		label = n.label
		print("label: ", label)
		new_tree = treeswift.read_tree_newick(inputTree_obj.newick())
		clade_root = new_tree.label_to_node([label])[label]
		parent = clade_root.parent
		# print("parent: ", parent)
		parent.remove_child(clade_root)
		other_child = parent.child_nodes()[0]
		before_placement = other_child.label
		# print("other child: ", other_child)
		if parent.is_root():
			other_child.parent = None
			new_tree.root = other_child
			# new_tree.reroot(other_child)
			# other_child.remove_child(parent)
		else:
			grand_parent = parent.parent
			# print("grand parent: ", grand_parent)
			grand_parent.remove_child(parent)
			grand_parent.add_child(other_child)

		if new_tree.num_nodes(internal = False) < 3:
			continue

		placement_set = clade_dict[label]
		if len(placement_set) < int(args.min_thresh) or len(placement_set) > int(args.max_thresh):
			continue

		outputTrees, total_scores, spr_runtime = complete_gene_trees([new_tree.newick()], refTrees=refTrees , placement_taxa=placement_set, sample_size = 0 ,nsample = 0)
		after_placement = max(total_scores, key=total_scores.get)
		if total_scores[before_placement] == total_scores[after_placement]:
			after_placement = before_placement

		with open(os.path.join(scores_dir, label + ".txt"), 'w') as f:
			f.write(json.dumps(total_scores))

		before_node = inputTree_obj.label_to_node([before_placement])[before_placement]
		after_node = inputTree_obj.label_to_node([after_placement])[after_placement]
		nodal_dist = cal_nodal_dist(before_node, after_node)
		# quartet_dist = total_scores[after_placement] - total_scores[before_placement]

		record = []
		placement_string = ",".join(placement_set)
		record.append(placement_string)
		record.append(str(len(placement_set)))
		if is_labeled:
			record.append(label)
		else:
			record.append("-")

		record.append(str(spr_runtime))
		record.append(str(nodal_dist))
		# record.append(str(quartet_dist))
		# n = num_leaves - len(placement_set)
		# n_choose_three = (n * (n-1) * (n-2)) / 6
		# record.append(str(n_choose_three))
		# dataset.append(record)


		with open(args.output_file, 'a') as f:
			# f.write("clade taxa" + "\t" + "label" + "\t" + "nodal dist" + "\t" + "quartet score diff" + "\t" + "remaining taxa choose 3" + "\n")
			f.write("\t".join(record) + "\n")

	end = time.time()
	print("Runtime: ", end - start) 


if __name__ == "__main__":
	main()  







