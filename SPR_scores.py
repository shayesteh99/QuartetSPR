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
		if node.is_leaf():
			continue
		if not node.label or node.label in labels or node.label[0] != 'I': 
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

def cal_nodal_dist(u, v, branch_length = False):
	u_ancestors = {}
	v_ancestors = {}
	u_ancestors[u.label] = 0
	v_ancestors[v.label] = 0

	node = u
	while not node.is_root():
		parent = node.parent
		d = 1
		if branch_length:
			d = node.get_edge_length()
		u_ancestors[parent.label] = u_ancestors[node.label] + d
		node = parent

	node = v
	while node.label not in u_ancestors:
		parent = node.parent
		d = 1
		if branch_length:
			d = node.get_edge_length()
		v_ancestors[parent.label] = v_ancestors[node.label] + d
		node = parent

	lca = node
	dist = u_ancestors[lca.label] + v_ancestors[lca.label]
	return dist

def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument('-i', '--input', required=True, help="Input tree to be completed")
	parser.add_argument('-r', '--refs', required=True, help="Reference trees that are used to complete input trees.")
	parser.add_argument('-o', '--output_file', required=True, help="Output file")

	args = parser.parse_args()

	random.seed(a=1105)

	start = time.time()

	with open(args.input,'r') as f:
		inputTree = f.read().strip().split("\n")[0]

	with open(args.refs,'r') as f:
		refTrees = f.read().strip().split("\n")

	inputTree_obj = read_tree_newick(inputTree)
	is_labeled = __label_tree__(inputTree_obj)
	# print(inputTree_obj.newick())
	# for node in inputTree_obj.traverse_preorder():
	# 	node.edge_length = None
	print(inputTree_obj.newick())

	dataset = []
	qspr_input_list = []
	# num_leaves = inputTree_obj.num_nodes(leaves=True, internal=False)
	all_leaves = inputTree_obj.traverse_leaves()
	all_leaves = [l.label for l in all_leaves]

	nodes = []
	tree_root = None
	for node in inputTree_obj.traverse_preorder():
		if node.is_root():
			tree_root = node
		nodes.append(node)

	clade_dict = {}
	get_clade_leaves(clade_dict, tree_root)

	for n in nodes:
		label = n.label
		for child in n.child_nodes():
			new_tree = treeswift.read_tree_newick(inputTree_obj.newick())
			clade_root = new_tree.label_to_node([child.label])[child.label]
			parent = clade_root.parent
			grand_parent = parent.parent

			parent.remove_child(clade_root)
			before_placement = parent.child_nodes()[0].label

			if grand_parent is None:
				if len(parent.child_nodes()) == 1:
					other_child = parent.child_nodes()[0]
					other_child.parent = None
					new_tree.root = other_child
			else:
				grand_parent.remove_child(parent)
				for c in parent.child_nodes():
					grand_parent.add_child(c)

			if new_tree.num_nodes(internal = False) < 3:
				continue

			placement_set = clade_dict[child.label]
			qspr_input_list.append((clade_root.label, placement_set, new_tree.newick(), before_placement))

		if not n.is_root():
			if len(clade_dict[n.label]) >= 3:
				new_tree = treeswift.read_tree_newick(inputTree_obj.newick())
				new_root = new_tree.label_to_node([n.label])[n.label]
				before_placement = new_root.label

				new_root.parent = None
				new_tree.root = new_root
				placement_set = list(set(all_leaves) - set(clade_dict[n.label]))
				qspr_input_list.append((clade_root.label, placement_set, new_tree.newick(), before_placement))


	for record in qspr_input_list:
		label = record[0]
		placement_set = record[1]
		input_tree_str = record[2]
		before_placement = record[3]

		outputTrees, total_scores, _ = complete_gene_trees([input_tree_str], refTrees=refTrees , placement_taxa=placement_set, sample_size =0 ,nsample = 0)
		after_placement = max(total_scores, key=total_scores.get)
		if total_scores[before_placement] == total_scores[after_placement]:
			after_placement = before_placement

		before_node = inputTree_obj.label_to_node([before_placement])[before_placement]
		after_node = inputTree_obj.label_to_node([after_placement])[after_placement]
		nodal_dist = cal_nodal_dist(before_node, after_node)
		branch_dist = cal_nodal_dist(before_node, after_node, branch_length = True)
		# print("branch dist: ", branch_dist)
		before_root_dist = cal_nodal_dist(before_node, tree_root)
		after_root_dist = cal_nodal_dist(after_node, tree_root)

		quartet_dist = total_scores[after_placement] - total_scores[before_placement]

		spr_record = []

		#clade taxa
		placement_string = ",".join(placement_set)
		spr_record.append(placement_string)

		#label
		if is_labeled:
			spr_record.append(label)
		else:
			spr_record.append("-")

		#placement label
		if is_labeled:
			spr_record.append(after_placement)
		else:
			spr_record.append("-")

		# nodal dist
		spr_record.append(str(nodal_dist))

		# branch dist
		spr_record.append(str(branch_dist))

		# dist to root (before)
		spr_record.append(str(before_root_dist))

		# dist to root (after)
		spr_record.append(str(after_root_dist))

		#quartet score diff
		spr_record.append(str(quartet_dist))
		n = len(all_leaves) - len(placement_set)
		n_choose_three = (n * (n-1) * (n-2)) / 6
		spr_record.append(str(n_choose_three * len(placement_set) * len(refTrees)))
		dataset.append(spr_record)

	with open(args.output_file, 'w') as f:
		f.write("clade taxa" + "\t" + "label" + "\t" + "placement label" + "\t" + "nodal dist" + "\t" + "branch dist" + "\t" + "dist to root (before)" + "\t" + "dist to root (after)" + "\t" 
			+ "quartet score diff" + "\t" + "n-m choose 3 * m" + "\n")
		for r in dataset:
			f.write("\t".join(r) + "\n")

	end = time.time()
	print("Runtime: ", end - start) 


if __name__ == "__main__":
	main()  







