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

def main():
	parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.ArgumentDefaultsHelpFormatter)
	parser.add_argument('-i', '--input', required=True, help="Input tree to be completed")
	parser.add_argument('-r', '--refs', required=False, help="Reference trees that are used to complete input trees.")
	parser.add_argument('-o', '--output_dir', required=True, help="Output path")

	args = parser.parse_args()

	random.seed(a=1105)

	start = time.time()

	output_dir = args.output_dir
	if not os.path.isdir(output_dir):
		os.makedirs(output_dir)
	if not os.path.isdir(os.path.join(output_dir, "rounds")):
		os.makedirs(os.path.join(output_dir, "rounds"))

	with open(args.input,'r') as f:
		inputTree = f.read().strip().split("\n")[0]

	with open(args.refs,'r') as f:
		refTrees = f.read().strip().split("\n")
    
	inputTree_obj = read_tree_newick(inputTree)
	is_labeled = __label_tree__(inputTree_obj)
	for node in inputTree_obj.traverse_preorder():
		node.edge_length = None

	if not is_labeled:
		with open(os.path.join(output_dir, "labeled_input_tree.trees"), 'w') as f:
			f.write(inputTree_obj.newick() + '\n')

	improved_tree = inputTree_obj.newick()

	# initial_FN = compare_trees(trueTrees, output_dir + "/improved_tree.trees", output_dir)
	# print("Initial FN: ", initial_FN)

	print("Initial tree:")
	print(improved_tree)
	tree_improved = True

	rounds_data = {}
	n_round = 0
	while tree_improved:
		rnd = []
		n_round += 1
		print('=' * 200)
		print("Round: ", n_round)
		print('=' * 200)
		tree_improved = False
		tree_obj = read_tree_newick(improved_tree)
		# print("tree obj: ")
		# print(tree_obj.newick())

		nodes = []
		tree_root = None
		for node in tree_obj.traverse_preorder():
			if node.is_root():
				tree_root = node
			else:
				nodes.append(node)
		nodes = np.random.permutation(nodes)

		clade_dict = {}
		get_clade_leaves(clade_dict, tree_root)
		# print(clade_dict)

		if tree_root is None:
			print("No root???")

		for n in nodes:
			label = n.label
			print("label: ", label)
			new_tree = treeswift.read_tree_newick(improved_tree)
			# print("new_tree")
			# print(new_tree)
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
			# print(placement_set)

			# info = {"node": label, "parent": label, "sibling": label}
			# info = {'node': label, 'parent': parent.label, 'sibling': other_child.label}
			# with open(output_dir + "/info_"+ label +".txt", 'w') as f:
			# 	f.write(json.dumps(info))

			# tree_dir = output_dir + '/input_' + label + ".trees"
			# input_tree.write_tree_newick(tree_dir)

			# print("Tree Without Clade")
			# print(new_tree.newick())

			outputTrees, total_scores, spr_runtime = complete_gene_trees([new_tree.newick()], refTrees=refTrees , placement_taxa=placement_set, sample_size = 0 ,nsample = 0)
			after_placement = max(total_scores, key=total_scores.get)
			if total_scores[before_placement] == total_scores[after_placement]:
				after_placement = before_placement


			before_node = tree_obj.label_to_node([before_placement])[before_placement]
			after_node = tree_obj.label_to_node([after_placement])[after_placement]
			nodal_dist = cal_nodal_dist(before_node, after_node)
			quartet_dist = total_scores[after_placement] - total_scores[before_placement]
			record = [label, len(placement_set), before_placement, after_placement, nodal_dist, quartet_dist]
			rnd.append(record)
			# print(total_scores)
			# print(record)
			# print(record)
			if after_placement == before_placement:
				continue

			print("An improvement found")
			best_node = new_tree.label_to_node([after_placement])[after_placement]
			if best_node.is_root():
				new_root = Node()
				new_root.label = parent
				new_root.add_child(best_node)
				new_root.add_child(n)
				new_tree.root = new_root
			else:
				v = best_node
				u = v.parent
				u.remove_child(v)
				w = Node()
				w.label = parent
				u.add_child(w)
				w.add_child(v)
				w.add_child(n)

			improved_tree = new_tree.newick()
			# print("Tree after placement:")
			# print(improved_tree)
			with open(os.path.join(output_dir, "rounds", "improved_tree_" + str(n_round) + ".trees"), 'w') as f:
				f.write(improved_tree + '\n')
			tree_improved = True

			break
		rounds_data[n_round] = rnd

	end = time.time()
	runtime = end - start
	print("Runtime: ", runtime) 

	with open(os.path.join(output_dir, "improved_tree.trees"), 'w') as f:
		f.write(improved_tree + '\n')
	with open(os.path.join(output_dir, "rounds_info.txt"), 'w') as f:
		f.write(json.dumps(rounds_data))
	with open(os.path.join(output_dir, "log.txt"), 'w') as f:
		f.write("runtime" + "\t" + str(runtime) + "\n")


if __name__ == "__main__":
	main()    
