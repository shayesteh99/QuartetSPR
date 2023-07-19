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
from operator import itemgetter
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
	for node in inputTree_obj.traverse_preorder():
		node.edge_length = None
	is_labeled = __label_tree__(inputTree_obj)

	if not is_labeled:
		with open(os.path.join(output_dir, "labeled_input_tree.trees"), 'w') as f:
			f.write(inputTree_obj.newick() + '\n')

	improved_tree = inputTree_obj.newick()

	print("Initial tree:")
	print(improved_tree)
	tree_improved = True

	all_leaves = inputTree_obj.traverse_leaves()
	all_leaves = [l.label for l in all_leaves]

	rounds_data = []
	prev_source = "-"
	prev_dest = "-"
	header = ["round", "size:children", "size:sibling", "score_before", "score_after", "nodal dist", "dist from previous source", "dist from previous dest", "label:soure", "label:dest"]
	n_round = 0
	while tree_improved:
		all_improvements = []
		n_round += 1
		print('=' * 200)
		print("Round: ", n_round)
		print('=' * 200)
		tree_improved = False
		tree_obj = read_tree_newick(improved_tree)

		nodes = []
		tree_root = None
		for node in tree_obj.traverse_preorder():
			if node.is_root():
				tree_root = node
			nodes.append(node)
		nodes = np.random.permutation(nodes)

		clade_dict = {}
		get_clade_leaves(clade_dict, tree_root)

		for n in nodes:
			label = n.label
			for child in n.child_nodes():
				new_tree = treeswift.read_tree_newick(tree_obj.newick())
				clade_root = new_tree.label_to_node([child.label])[child.label]
				parent = clade_root.parent
				parent_label = parent.label
				grand_parent = parent.parent

				children_sizes = ""
				for c in child.child_nodes():
					children_sizes += str(len(clade_dict[c.label])) + ","

				parent.remove_child(clade_root)

				sibling_sizes = ""
				for c in parent.child_nodes():
					sibling_sizes += str(len(clade_dict[c.label])) + ","

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

				outputTrees, total_scores, _ = complete_gene_trees([new_tree.newick()], refTrees=refTrees , placement_taxa=placement_set, sample_size =0 ,nsample = 0)
				after_placement = max(total_scores, key=total_scores.get)
				if total_scores[before_placement] == total_scores[after_placement]:
					after_placement = before_placement

				before_node = tree_obj.label_to_node([before_placement])[before_placement]
				after_node = tree_obj.label_to_node([after_placement])[after_placement]
				nodal_dist = cal_nodal_dist(before_node, after_node)
				if prev_dest != '-':
					prev_source_node = tree_obj.label_to_node([prev_source])[prev_source]
					prev_dest_node = tree_obj.label_to_node([prev_dest])[prev_dest]
					dist_from_prev_source = str(cal_nodal_dist(before_node, prev_source_node))
					dist_from_prev_dest = str(cal_nodal_dist(before_node, prev_dest_node))
				else:
					dist_from_prev_source = '-'
					dist_from_prev_dest = '-'

				quartet_dist = total_scores[after_placement] - total_scores[before_placement]
				record = [n_round, children_sizes, sibling_sizes, total_scores[before_placement], total_scores[after_placement], nodal_dist, dist_from_prev_source, dist_from_prev_dest, 
							before_placement, after_placement]
				rounds_data.append(record)

				if total_scores[after_placement] > total_scores[before_placement]:				
					tree_improved = True
					all_improvements.append([new_tree.newick(), tree_obj.newick(), child.label, parent_label, after_placement, before_placement, 0, total_scores[after_placement]])

			if not n.is_root():
				if len(clade_dict[n.label]) >= 3:
					new_tree = treeswift.read_tree_newick(tree_obj.newick())
					new_root = new_tree.label_to_node([n.label])[n.label]
					before_placement = new_root.label
					parent = new_root.parent

					sibling_sizes = str(len(clade_dict[n.label])) + ","

					children_sizes = ""
					children_sizes += str(len(all_leaves) - len(clade_dict[parent.label])) + ","

					parent.remove_child(new_root)

					for c in parent.child_nodes():
						children_sizes += str(len(clade_dict[c.label])) + ","

					if parent.parent is None:
						placement_label = parent.child_nodes()[0].label
					else:
						placement_label = parent.label

					new_root.parent = None
					new_tree.root = new_root
					placement_set = list(set(all_leaves) - set(clade_dict[n.label]))

					outputTrees, total_scores, _ = complete_gene_trees([new_tree.newick()], refTrees=refTrees , placement_taxa=placement_set, sample_size =0 ,nsample = 0)
					after_placement = max(total_scores, key=total_scores.get)
					if total_scores[before_placement] == total_scores[after_placement]:
						after_placement = before_placement

					before_node = tree_obj.label_to_node([before_placement])[before_placement]
					after_node = tree_obj.label_to_node([after_placement])[after_placement]
					nodal_dist = cal_nodal_dist(before_node, after_node)
					if prev_dest != '-':
						prev_source_node = tree_obj.label_to_node([prev_source])[prev_source]
						prev_dest_node = tree_obj.label_to_node([prev_dest])[prev_dest]
						dist_from_prev_source = str(cal_nodal_dist(before_node, prev_source_node))
						dist_from_prev_dest = str(cal_nodal_dist(before_node, prev_dest_node))
					else:
						dist_from_prev_source = '-'
						dist_from_prev_dest = '-'

					record = [n_round, children_sizes, sibling_sizes, total_scores[before_placement], total_scores[after_placement], nodal_dist, dist_from_prev_source, dist_from_prev_dest, 
							before_placement, after_placement]
					rounds_data.append(record)

					if total_scores[after_placement] > total_scores[before_placement]:					
						tree_improved = True
						all_improvements.append([new_tree.newick(), tree_obj.newick(), n.label, placement_label, after_placement, before_placement, 1, total_scores[after_placement]])

		if not tree_improved:
			break

		best_imprv = max(all_improvements, key=itemgetter(-1))
		new_tree = treeswift.read_tree_newick(best_imprv[0])
		full_tree = treeswift.read_tree_newick(best_imprv[1])
		after_placement = best_imprv[4]
		before_placement = best_imprv[5]
		prev_source = before_placement
		prev_dest = after_placement

		if best_imprv[-2] == 0:
			child_label = best_imprv[2]
			clade_root = full_tree.label_to_node([child_label])[child_label]
			parent = clade_root.parent
			parent.remove_child(clade_root)

			parent_label = best_imprv[3]
			best_node = new_tree.label_to_node([after_placement])[after_placement]
			if best_node.is_root():
				new_root = Node()
				new_root.label = parent_label
				new_root.add_child(best_node)
				new_root.add_child(clade_root)
				new_tree.root = new_root
			else:
				v = best_node
				u = v.parent
				u.remove_child(v)
				w = Node()
				w.label = parent_label
				u.add_child(w)
				w.add_child(v)
				w.add_child(clade_root)

		else:
			parent_label = full_tree.root.label
			n_label = best_imprv[2]
			root_node = full_tree.label_to_node([n_label])[n_label]
			full_tree.reroot(root_node)
			full_tree.suppress_unifurcations()
			placement_label = best_imprv[3]
			placement_clade = full_tree.label_to_node([placement_label])[placement_label]
			root_node.remove_child(placement_clade)

			best_node = new_tree.label_to_node([after_placement])[after_placement]
			if best_node.is_root():
				new_root = Node()
				new_root.label = parent_label
				new_root.add_child(best_node)
				new_root.add_child(placement_clade)
				new_tree.root = new_root
			else:
				v = best_node
				u = v.parent
				u.remove_child(v)
				w = Node()
				w.label = parent_label
				u.add_child(w)
				w.add_child(v)
				w.add_child(placement_clade)

		improved_tree = new_tree.newick()
		print("improved tree: ", improved_tree)
		with open(os.path.join(output_dir, "rounds", "improved_tree_" + str(n_round) + ".trees"), 'w') as f:
			f.write(improved_tree + '\n')

	end = time.time()
	runtime = end - start
	print("Runtime: ", runtime) 

	with open(os.path.join(output_dir, "rounds", "improved_tree_" + str(n_round) + ".trees"), 'w') as f:
		f.write(improved_tree + '\n')
	with open(os.path.join(output_dir, "improved_tree.trees"), 'w') as f:
		f.write(improved_tree + '\n')
	with open(os.path.join(output_dir, "rounds_info.txt"), 'w') as f:
		f.write('\t'.join(header) + '\n')
		for r in rounds_data:
			r = [str(i) for i in r]
			f.write('\t'.join(r) + '\n')
	with open(os.path.join(output_dir, "log.txt"), 'w') as f:
		f.write("runtime" + "\t" + str(runtime) + "\n")


if __name__ == "__main__":
	main()    
