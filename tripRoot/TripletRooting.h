#ifndef TRIPLET_ROOTING_H
#define TRIPLET_ROOTING_H

#include "int_stuff.h"
#include "triplet_calc.h"
#include "quartet_calc.h"
#include "hdt.h"
#include "TripletCounter.h"
#include "rooted_tree_factory.h"
#include <vector>
#include <unordered_map>

using namespace std;

#ifndef CONTRACT_MAX_EXTRA_SIZE
#define CONTRACT_MAX_EXTRA_SIZE 20000
#endif

class TripletRooting {
 public:
  TripletRooting();
  virtual bool initialize(RootedTree *ref, RootedTree *tree, string m_one_str);
  ~TripletRooting();
  
  virtual bool pairing();
  void countChildren(RootedTree *t);
  void count(RootedTree *v);
  void update_tI(unsigned int nodeIdx, bool count_unresolved=false);
  void update_tO(unsigned int nodeIdx, unsigned int color, bool count_unresolved=false);
  void update_tR(unsigned int nodeIdx);
  INTTYPE_REST compute_root_tripScore();
  virtual bool find_optimal_root();
  bool compute_tripScore();

  // shayesteh99 added
  void fill_minus_one_leaves(string m_one_str);
  void color_minus_one_leaves(RootedTree *t);
  void print_all_leaves_colors(RootedTree *t);
  void print_all_nodes_info(RootedTree *t);

  HDTFactory *dummyHDTFactory;
  RootedTreeFactory *factory;
  RootedTree *myRef, *myTree;
  HDT *hdt;
  TripletCounter *tripCount;
  INTTYPE_REST optimalTripScore;
  unsigned int ambiguity;
  //TemplatedLinkedList<RootedTree*> *optimaltripRoots; // the nodes that have optimal tripScore
  vector<RootedTree*> optimaltripRoots; // the nodes that have optimal tripScore
  RootedTree *optimalRoot; // the node in myTree where the optimal root placed above

  //shayesteh99 added
  // vector<string> minus_one_leaves;
  unordered_map<string, bool> minus_one_leaves;



private:
  INTTYPE_REST __compute_root_tripScore__(RootedTree *v);       
  void __downroot__(RootedTree *v, INTTYPE_REST parent_score, bool parent_active);      
};

#endif
