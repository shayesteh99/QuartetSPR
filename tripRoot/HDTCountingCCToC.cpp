#include <cstdlib> // for exit
#include "hdt.h"
#include "rooted_tree.h"
#include "hdt_factory.h"
#include "counting_array.h"

void HDT::handleCCToC()
{
	// Recurse (if not I child) (we really _should_ have both children!)
	if (!left->up2date) left->updateCounters();
	if (!right->up2date) right->updateCounters();

    // reset counters for this node
    this->resetCounters();

	// NOTE: We generate this with c2 (the higher one) being the left child and c1 (the lower one) being the right child
	HDT *c1 = this->right;
	HDT *c2 = this->left;

	// n_i is just the sum of the 2 children, thus n_circ is also just the sum of the 2 children
	n_circ = c1->n_circ + c2->n_circ;

    // // n_parent_zero_circ 
    // n_parent_zero_circ = c1->n_parent_zero_circ + c2->n_parent_zero_circ;

    //n_paren_circ_minus_one
    n_paren_circ_minus_one = c1->n_paren_circ_minus_one + c2->n_paren_circ_minus_one;

    //n_paren_circ_square
    n_paren_circ_square = c1->n_paren_circ_square + c2->n_paren_circ_square;

    //n_paren_circ_circ
    n_paren_circ_circ = c1->n_paren_circ_circ + c2->n_paren_circ_circ;

    //n_minus_one
    n_minus_one = c1->n_minus_one + c2->n_minus_one;

    // //n_paren_zero_minus_one
    // n_paren_zero_minus_one = c1->n_paren_zero_minus_one + c2->n_paren_zero_minus_one;

    //n_circ_arrow_minus_one
    n_circ_arrow_minus_one = c1->n_circ_arrow_minus_one + c2->n_circ_arrow_minus_one + c1->n_circ * c2->n_minus_one;

    //n_paren_minus_one_paren_circ_square
    n_paren_minus_one_paren_circ_square = c1->n_paren_minus_one_paren_circ_square + c2->n_paren_minus_one_paren_circ_square;

    //n_paren_zero_paren_circ_square
    n_paren_zero_paren_circ_square = c1->n_paren_zero_paren_circ_square + c2->n_paren_zero_paren_circ_square;

    // //n_paren_zero_paren_circ_circ
    // n_paren_zero_paren_circ_circ = c1->n_paren_zero_paren_circ_circ + c2->n_paren_zero_paren_circ_circ;

    //n_minus_one_arrow_paren_circ_square
    n_minus_one_arrow_paren_circ_square = c1->n_minus_one_arrow_paren_circ_square + c2->n_minus_one_arrow_paren_circ_square +
                                            c1->n_minus_one * c2->n_paren_circ_square;

    //n_paren_circ_circ_arrow_minus_one
    n_paren_circ_circ_arrow_minus_one = c1->n_paren_circ_circ_arrow_minus_one + c2->n_paren_circ_circ_arrow_minus_one +
                                        c1->n_paren_circ_circ * c2->n_minus_one;

    //n_paren_circ_square_arrow_minus_one
    n_paren_circ_square_arrow_minus_one = c1->n_paren_circ_square_arrow_minus_one + c2->n_paren_circ_square_arrow_minus_one +
                                            c1->n_paren_circ_square * c2->n_minus_one;

    //n_minus_one_arrow_circ
    n_minus_one_arrow_circ = c1->n_minus_one_arrow_circ + c2->n_minus_one_arrow_circ + c1->n_minus_one * c2->n_circ; 

    //n_paren_circ_paren_square_square
    n_paren_circ_paren_square_square = c1->n_paren_circ_paren_square_square + c2->n_paren_circ_paren_square_square;

    // compute n_i,n_parent_ii, n_i_circ, n_i_arrow_circ, and n_circ_square
    CountingArray *ourCount = &this->countingVars;
    CountingArray *c1Count = &c1->countingVars;
    CountingArray *c2Count = &c2->countingVars;

    for (int i = 0; i < this->degree; i++){
        ourCount->set_n_i(i,c1Count->get_n_i(i) + c2Count->get_n_i(i));
        // ourCount->set_n_i_circ(i,c1Count->get_n_i_circ(i) + c2Count->get_n_i_circ(i));
        if (i == 0) {
            ourCount->set_n_i_arrow_circ(i, c1Count->get_n_i_arrow_circ(i) + c2Count->get_n_i_arrow_circ(i) +
                                        c1Count->get_n_i(i) * c2->n_circ);
            ourCount->set_n_circ_arrow_i(i, c1Count->get_n_circ_arrow_i(i) + c2Count->get_n_circ_arrow_i(i) +
                                        c2Count->get_n_i(i) * c1->n_circ);
            ourCount->set_n_bracket_minus_one_paren_i_circ(i, c1Count->get_n_bracket_minus_one_paren_i_circ(i) + c2Count->get_n_bracket_minus_one_paren_i_circ(i) +
                                                            c1Count->get_n_i(i) * c1->n_circ * c2->n_minus_one +
                                                            c1->n_circ * c2Count->get_n_i_arrow_minus_one(i) +
                                                            c1->n_minus_one * c2Count->get_n_paren_i_circ(i));
            ourCount->set_n_bracket_zero_paren_i_circ(i, c1Count->get_n_bracket_zero_paren_i_circ(i) + c2Count->get_n_bracket_zero_paren_i_circ(i) +
                                                            c1Count->get_n_i(i) * c1->n_circ * c2Count->get_n_i(0) +
                                                            c1->n_circ * c2Count->get_n_i_arrow_j(i, 0) +
                                                            c1Count->get_n_i(0) * c2Count->get_n_paren_i_circ(i));
            ourCount->set_n_bracket_circ_paren_ii(i, c1Count->get_n_bracket_circ_paren_ii(i) + c2Count->get_n_bracket_circ_paren_ii(i) +
                                                        Util::binom2(c1Count->get_n_i(i)) * c2->n_circ +
                                                        c1->n_circ * c2Count->get_n_paren_ii(i) +
                                                        c1Count->get_n_i(i) * c2Count->get_n_i_arrow_circ(i));
            ourCount->set_n_bracket_i_paren_circ_circ(i, c1Count->get_n_bracket_i_paren_circ_circ(i) + c2Count->get_n_bracket_i_paren_circ_circ(i) +
                                                            c1->n_bracket_circ_circ * c2Count->get_n_i(i) + 
                                                            c1Count->get_n_i(i) * c2->n_paren_circ_circ);
            ourCount->set_n_bracket_circ_paren_i_minus_one(i, c1Count->get_n_bracket_circ_paren_i_minus_one(i) + c2Count->get_n_bracket_circ_paren_i_minus_one(i) +
                                                            c1Count->get_n_i(i) * c1->n_minus_one * c2->n_circ + 
                                                            c1->n_circ * c2Count->get_n_paren_i_minus_one(i) +
                                                            c1Count->get_n_i(i) * c2->n_minus_one_arrow_circ +
                                                            c1->n_minus_one * c2Count->get_n_i_arrow_circ(i));
            ourCount->set_n_bracket_i_paren_circ_minus_one(i, c1Count->get_n_bracket_i_paren_circ_minus_one(i) + c2Count->get_n_bracket_i_paren_circ_minus_one(i) +
                                                            c1->n_minus_one * c1->n_circ * c2Count->get_n_i(i) +
                                                            c1Count->get_n_i(i) * c2->n_paren_circ_minus_one +
                                                            c1->n_minus_one * c2Count->get_n_circ_arrow_i(i) +
                                                            c1->n_circ * c2Count->get_n_minus_one_arrow_i(i));
            ourCount->set_n_i_arrow_paren_circ_square(i, c1Count->get_n_i_arrow_paren_circ_square(i) + c2Count->get_n_i_arrow_paren_circ_square(i) +
                                                        c1Count->get_n_i(i) * c2->n_paren_circ_square);
            ourCount->set_n_i_arrow_paren_circ_circ(i, c1Count->get_n_i_arrow_paren_circ_circ(i) + c2Count->get_n_i_arrow_paren_circ_circ(i) +
                                                        c1Count->get_n_i(i) * c2->n_paren_circ_circ);
            ourCount->set_n_circ_arrow_paren_i_minus_one(i, c1Count->get_n_circ_arrow_paren_i_minus_one(i) + c2Count->get_n_circ_arrow_paren_i_minus_one(i) +
                                                        c1->n_circ * c2Count->get_n_paren_i_minus_one(i));
            ourCount->set_n_circ_arrow_minus_one_arrow_i(i, c1Count->get_n_circ_arrow_minus_one_arrow_i(i) + c2Count->get_n_circ_arrow_minus_one_arrow_i(i) +
                                                        c1->n_circ_arrow_minus_one * c2Count->get_n_i(i) +
                                                        c1->n_circ * c2Count->get_n_minus_one_arrow_i(i));
            ourCount->set_n_paren_circ_circ_arrow_i(i, c1Count->get_n_paren_circ_circ_arrow_i(i) + c2Count->get_n_paren_circ_circ_arrow_i(i) +
                                                    c1->n_paren_circ_circ * c2Count->get_n_i(i));
            ourCount->set_n_circ_arrow_i_arrow_minus_one(i, c1Count->get_n_circ_arrow_i_arrow_minus_one(i) + c2Count->get_n_circ_arrow_i_arrow_minus_one(i) +
                                                        c1Count->get_n_circ_arrow_i(i) * c2->n_minus_one +
                                                        c1->n_circ * c2Count->get_n_i_arrow_minus_one(i));
            ourCount->set_n_circ_arrow_paren_ii(i, c1Count->get_n_circ_arrow_paren_ii(i) + c2Count->get_n_circ_arrow_paren_ii(i) + 
                                                c1->n_circ * c2Count->get_n_paren_ii(i));
            ourCount->set_n_i_arrow_minus_one_arrow_circ(i, c1Count->get_n_i_arrow_minus_one_arrow_circ(i) + c2Count->get_n_i_arrow_minus_one_arrow_circ(i) +
                                                        c1Count->get_n_i(i) * c2->n_minus_one_arrow_circ +
                                                        c1Count->get_n_i_arrow_minus_one(i) * c2->n_circ);
            ourCount->set_n_paren_ii_arrow_circ(i, c1Count->get_n_paren_ii_arrow_circ(i) + c2Count->get_n_paren_ii_arrow_circ(i) +
                                                c1Count->get_n_paren_ii(i) * c2->n_circ);
            ourCount->set_n_i_arrow_circ_arrow_minus_one(i, c1Count->get_n_i_arrow_circ_arrow_minus_one(i) + c2Count->get_n_i_arrow_circ_arrow_minus_one(i) +
                                                        c1Count->get_n_i(i) * c2->n_circ_arrow_minus_one + 
                                                        c1Count->get_n_i_arrow_circ(i) * c2->n_minus_one);
            ourCount->set_n_minus_one_arrow_i_arrow_circ(i, c1Count->get_n_minus_one_arrow_i_arrow_circ(i) + c2Count->get_n_minus_one_arrow_i_arrow_circ(i) +
                                                        c1->n_minus_one * c2Count->get_n_i_arrow_circ(i) +
                                                        c1Count->get_n_minus_one_arrow_i(i) * c2->n_circ);
            ourCount->set_n_zero_arrow_i_arrow_circ(i, c1Count->get_n_zero_arrow_i_arrow_circ(i) + c2Count->get_n_zero_arrow_i_arrow_circ(i) +
                                                        c1Count->get_n_i(0) * c2Count->get_n_i_arrow_circ(i) +
                                                        c1Count->get_n_i_arrow_j(0, i) * c2->n_circ);
            ourCount->set_n_paren_i_minus_one_arrow_circ(i, c1Count->get_n_paren_i_minus_one_arrow_circ(i) + c2Count->get_n_paren_i_minus_one_arrow_circ(i) +
                                                        c1Count->get_n_paren_i_minus_one(i) * c2->n_circ);
            ourCount->set_n_circ_arrow_i_arrow_i(i, c1Count->get_n_circ_arrow_i_arrow_i(i) + c2Count->get_n_circ_arrow_i_arrow_i(i) +
                                                c1->n_circ * c2Count->get_n_i_arrow_i(i) +
                                                c1Count->get_n_circ_arrow_i(i) * c2Count->get_n_i(i));
            ourCount->set_n_paren_circ_minus_one_arrow_i(i, c1Count->get_n_paren_circ_minus_one_arrow_i(i) + c2Count->get_n_paren_circ_minus_one_arrow_i(i) +
                                                            c1->n_paren_circ_minus_one * c2Count->get_n_i(i));
            ourCount->set_n_i_arrow_circ_arrow_circ(i, c1Count->get_n_i_arrow_circ_arrow_circ(i) + c2Count->get_n_i_arrow_circ_arrow_circ(i) +
                                                    c1Count->get_n_i(i) * c2->n_circ_arrow_circ);
            ourCount->set_n_i_arrow_paren_circ_minus_one(i, c1Count->get_n_i_arrow_paren_circ_minus_one(i) + c2Count->get_n_i_arrow_paren_circ_minus_one(i) +
                                                        c1Count->get_n_i(i) * c2->n_paren_circ_minus_one);

        }
        else {
            ourCount->set_n_i_arrow_circ(i, c1Count->get_n_i_arrow_circ(i) + c2Count->get_n_i_arrow_circ(i) +
                                        c1Count->get_n_i(i) * (c2->n_circ - c2Count->get_n_i(i)));
            ourCount->set_n_circ_arrow_i(i, c1Count->get_n_circ_arrow_i(i) + c2Count->get_n_circ_arrow_i(i) +
                                        c2Count->get_n_i(i) * (c1->n_circ - c1Count->get_n_i(i)));
            ourCount->set_n_bracket_minus_one_paren_i_circ(i, c1Count->get_n_bracket_minus_one_paren_i_circ(i) + c2Count->get_n_bracket_minus_one_paren_i_circ(i) +
                                                            c1Count->get_n_i(i) * (c1->n_circ - c1Count->get_n_i(i)) * c2->n_minus_one +
                                                            (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_i_arrow_minus_one(i) +
                                                            c1->n_minus_one * c2Count->get_n_paren_i_circ(i));
            ourCount->set_n_bracket_zero_paren_i_circ(i, c1Count->get_n_bracket_zero_paren_i_circ(i) + c2Count->get_n_bracket_zero_paren_i_circ(i) +
                                                            c1Count->get_n_i(i) * (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_i(0) +
                                                            (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_i_arrow_j(i, 0) +
                                                            c1Count->get_n_i(0) * c2Count->get_n_paren_i_circ(i));
            ourCount->set_n_bracket_circ_paren_ii(i, c1Count->get_n_bracket_circ_paren_ii(i) + c2Count->get_n_bracket_circ_paren_ii(i) +
                                                        Util::binom2(c1Count->get_n_i(i)) * (c2->n_circ - c2Count->get_n_i(i)) +
                                                        (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_paren_ii(i) +
                                                        c1Count->get_n_i(i) * c2Count->get_n_i_arrow_circ(i));
            ourCount->set_n_bracket_i_paren_circ_circ(i, c1Count->get_n_bracket_i_paren_circ_circ(i) + c2Count->get_n_bracket_i_paren_circ_circ(i) +
                                                            (c1->n_bracket_circ_circ - Util::binom2(c1Count->get_n_i(i))) * c2Count->get_n_i(i) + 
                                                            c1Count->get_n_i(i) * (c2->n_paren_circ_circ - c2Count->get_n_paren_ii(i)));
            ourCount->set_n_bracket_circ_paren_i_minus_one(i, c1Count->get_n_bracket_circ_paren_i_minus_one(i) + c2Count->get_n_bracket_circ_paren_i_minus_one(i) +
                                                            c1Count->get_n_i(i) * c1->n_minus_one * (c2->n_circ - c2Count->get_n_i(i)) + 
                                                            (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_paren_i_minus_one(i) +
                                                            c1Count->get_n_i(i) * (c2->n_minus_one_arrow_circ - c2Count->get_n_minus_one_arrow_i(i)) +
                                                            c1->n_minus_one * c2Count->get_n_i_arrow_circ(i));
            ourCount->set_n_bracket_i_paren_circ_minus_one(i, c1Count->get_n_bracket_i_paren_circ_minus_one(i) + c2Count->get_n_bracket_i_paren_circ_minus_one(i) +
                                                            c1->n_minus_one * (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_i(i) +
                                                            c1Count->get_n_i(i) * (c2->n_paren_circ_minus_one - c2Count->get_n_paren_i_minus_one(i)) +
                                                            c1->n_minus_one * c2Count->get_n_circ_arrow_i(i) +
                                                            (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_minus_one_arrow_i(i));
            ourCount->set_n_i_arrow_paren_circ_square(i, c1Count->get_n_i_arrow_paren_circ_square(i) + c2Count->get_n_i_arrow_paren_circ_square(i) +
                                                        c1Count->get_n_i(i) * (c2->n_paren_circ_square - c2Count->get_n_paren_i_circ(i)));
            ourCount->set_n_i_arrow_paren_circ_circ(i, c1Count->get_n_i_arrow_paren_circ_circ(i) + c2Count->get_n_i_arrow_paren_circ_circ(i) +
                                                        c1Count->get_n_i(i) * (c2->n_paren_circ_circ - c2Count->get_n_paren_ii(i)));
            ourCount->set_n_circ_arrow_paren_i_minus_one(i, c1Count->get_n_circ_arrow_paren_i_minus_one(i) + c2Count->get_n_circ_arrow_paren_i_minus_one(i) +
                                                        (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_paren_i_minus_one(i));
            ourCount->set_n_circ_arrow_minus_one_arrow_i(i, c1Count->get_n_circ_arrow_minus_one_arrow_i(i) + c2Count->get_n_circ_arrow_minus_one_arrow_i(i) +
                                                        (c1->n_circ_arrow_minus_one - c1Count->get_n_i_arrow_minus_one(i)) * c2Count->get_n_i(i) +
                                                        (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_minus_one_arrow_i(i));
            ourCount->set_n_paren_circ_circ_arrow_i(i, c1Count->get_n_paren_circ_circ_arrow_i(i) + c2Count->get_n_paren_circ_circ_arrow_i(i) +
                                                    (c1->n_paren_circ_circ - c1Count->get_n_paren_ii(i)) * c2Count->get_n_i(i));
            ourCount->set_n_circ_arrow_i_arrow_minus_one(i, c1Count->get_n_circ_arrow_i_arrow_minus_one(i) + c2Count->get_n_circ_arrow_i_arrow_minus_one(i) +
                                                        c1Count->get_n_circ_arrow_i(i) * c2->n_minus_one +
                                                        (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_i_arrow_minus_one(i));
            ourCount->set_n_circ_arrow_paren_ii(i, c1Count->get_n_circ_arrow_paren_ii(i) + c2Count->get_n_circ_arrow_paren_ii(i) + 
                                                (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_paren_ii(i));
            ourCount->set_n_i_arrow_minus_one_arrow_circ(i, c1Count->get_n_i_arrow_minus_one_arrow_circ(i) + c2Count->get_n_i_arrow_minus_one_arrow_circ(i) +
                                                        c1Count->get_n_i(i) * (c2->n_minus_one_arrow_circ - c2Count->get_n_minus_one_arrow_i(i)) +
                                                        c1Count->get_n_i_arrow_minus_one(i) * (c2->n_circ - c2Count->get_n_i(i)));
            ourCount->set_n_paren_ii_arrow_circ(i, c1Count->get_n_paren_ii_arrow_circ(i) + c2Count->get_n_paren_ii_arrow_circ(i) +
                                                c1Count->get_n_paren_ii(i) * (c2->n_circ - c2Count->get_n_i(i)));
            ourCount->set_n_i_arrow_circ_arrow_minus_one(i, c1Count->get_n_i_arrow_circ_arrow_minus_one(i) + c2Count->get_n_i_arrow_circ_arrow_minus_one(i) +
                                                        c1Count->get_n_i(i) * (c2->n_circ_arrow_minus_one - c2Count->get_n_i_arrow_minus_one(i)) + 
                                                        c1Count->get_n_i_arrow_circ(i) * c2->n_minus_one);
            ourCount->set_n_minus_one_arrow_i_arrow_circ(i, c1Count->get_n_minus_one_arrow_i_arrow_circ(i) + c2Count->get_n_minus_one_arrow_i_arrow_circ(i) +
                                                        c1->n_minus_one * c2Count->get_n_i_arrow_circ(i) +
                                                        c1Count->get_n_minus_one_arrow_i(i) * (c2->n_circ - c2Count->get_n_i(i)));
            ourCount->set_n_zero_arrow_i_arrow_circ(i, c1Count->get_n_zero_arrow_i_arrow_circ(i) + c2Count->get_n_zero_arrow_i_arrow_circ(i) +
                                                        c1Count->get_n_i(0) * c2Count->get_n_i_arrow_circ(i) +
                                                        c1Count->get_n_i_arrow_j(0, i) * (c2->n_circ - c2Count->get_n_i(i)));
            ourCount->set_n_paren_i_minus_one_arrow_circ(i, c1Count->get_n_paren_i_minus_one_arrow_circ(i) + c2Count->get_n_paren_i_minus_one_arrow_circ(i) +
                                                        c1Count->get_n_paren_i_minus_one(i) * (c2->n_circ - c2Count->get_n_i(i)));
            ourCount->set_n_circ_arrow_i_arrow_i(i, c1Count->get_n_circ_arrow_i_arrow_i(i) + c2Count->get_n_circ_arrow_i_arrow_i(i) +
                                                (c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_i_arrow_i(i) +
                                                c1Count->get_n_circ_arrow_i(i) * c2Count->get_n_i(i));
            ourCount->set_n_paren_circ_minus_one_arrow_i(i, c1Count->get_n_paren_circ_minus_one_arrow_i(i) + c2Count->get_n_paren_circ_minus_one_arrow_i(i) +
                                                            (c1->n_paren_circ_minus_one - c1Count->get_n_paren_i_minus_one(i)) * c2Count->get_n_i(i));
            ourCount->set_n_i_arrow_circ_arrow_circ(i, c1Count->get_n_i_arrow_circ_arrow_circ(i) + c2Count->get_n_i_arrow_circ_arrow_circ(i) +
                                                    c1Count->get_n_i(i) * (c2->n_circ_arrow_circ - c2Count->get_n_i_arrow_i(i)));
            ourCount->set_n_i_arrow_paren_circ_minus_one(i, c1Count->get_n_i_arrow_paren_circ_minus_one(i) + c2Count->get_n_i_arrow_paren_circ_minus_one(i) +
                                                        c1Count->get_n_i(i) * (c2->n_paren_circ_minus_one - c2Count->get_n_paren_i_minus_one(i)));

        }
        ourCount->set_n_paren_ii(i,c1Count->get_n_paren_ii(i) + c2Count->get_n_paren_ii(i));
        ourCount->set_n_paren_i_circ(i, c1Count->get_n_paren_i_circ(i) + c2Count->get_n_paren_i_circ(i));
        ourCount->set_n_i_arrow_minus_one(i, c1Count->get_n_i_arrow_minus_one(i) + c2Count->get_n_i_arrow_minus_one(i) + c1Count->get_n_i(i) * c2->n_minus_one);
        ourCount->set_n_minus_one_arrow_i(i, c1Count->get_n_minus_one_arrow_i(i) + c2Count->get_n_minus_one_arrow_i(i) + c2Count->get_n_i(i) * c1->n_minus_one);
        // ourCount->set_n_i_arrow_zero(i, c1Count->get_n_i_arrow_zero(i) + c2Count->get_n_i_arrow_zero(i) + c1Count->get_n_i(i) * c2Count->get_n_i(0));
        ourCount->set_n_bracket_minus_one_paren_ii(i, c1Count->get_n_bracket_minus_one_paren_ii(i) + c2Count->get_n_bracket_minus_one_paren_ii(i) +
                                                    Util::binom2(c1Count->get_n_i(i)) * c2->n_minus_one + 
                                                    c1->n_minus_one * c2Count->get_n_paren_ii(i) +
                                                    c1Count->get_n_i(i) * c2Count->get_n_i_arrow_minus_one(i));
        // ourCount->set_n_bracket_zero_paren_ii(i, c1Count->get_n_bracket_zero_paren_ii(i) + c2Count->get_n_bracket_zero_paren_ii(i) +
        //                                             Util::binom2(c1Count->get_n_i(i)) * c2Count->get_n_i(0) + 
        //                                             c1Count->get_n_i(0) * c2Count->get_n_paren_ii(i) +
        //                                             c1Count->get_n_i(i) * c2Count->get_n_i_arrow_j(i, 0));
        ourCount->set_n_paren_minus_one_paren_ii(i,c1Count->get_n_paren_minus_one_paren_ii(i) + c2Count->get_n_paren_minus_one_paren_ii(i));
        // ourCount->set_n_paren_zero_paren_ii(i,c1Count->get_n_paren_zero_paren_ii(i) + c2Count->get_n_paren_zero_paren_ii(i));
        // ourCount->set_n_paren_zero_i(i,c1Count->get_n_paren_zero_i(i) + c2Count->get_n_paren_zero_i(i));
        ourCount->set_n_paren_i_minus_one(i,c1Count->get_n_paren_i_minus_one(i) + c2Count->get_n_paren_i_minus_one(i));
        ourCount->set_n_paren_circ_paren_ii(i,c1Count->get_n_paren_circ_paren_ii(i) + c2Count->get_n_paren_circ_paren_ii(i));
        ourCount->set_n_paren_zero_paren_i_circ(i,c1Count->get_n_paren_zero_paren_i_circ(i) + c2Count->get_n_paren_zero_paren_i_circ(i));
        ourCount->set_n_paren_circ_paren_i_minus_one(i, c1Count->get_n_paren_circ_paren_i_minus_one(i) + c2Count->get_n_paren_circ_paren_i_minus_one(i));
        ourCount->set_n_paren_i_paren_circ_minus_one(i, c1Count->get_n_paren_i_paren_circ_minus_one(i) + c2Count->get_n_paren_i_paren_circ_minus_one(i));
        ourCount->set_n_minus_one_arrow_paren_ii(i, c1Count->get_n_minus_one_arrow_paren_ii(i) + c2Count->get_n_minus_one_arrow_paren_ii(i) +
                                                    c1->n_minus_one * c2Count->get_n_paren_ii(i));
        // ourCount->set_n_paren_i_circ_arrow_i(i, c1Count->get_n_paren_i_circ_arrow_i(i) + c2Count->get_n_paren_i_circ_arrow_i(i) +
        //                                         c1Count->get_n_paren_i_circ(i) * c2Count->get_n_i(i));
        ourCount->set_n_paren_i_circ_arrow_zero(i, c1Count->get_n_paren_i_circ_arrow_zero(i) + c2Count->get_n_paren_i_circ_arrow_zero(i) +
                                                    c1Count->get_n_paren_i_circ(i) * c2Count->get_n_i(0));
        // ourCount->set_n_paren_i_circ_arrow_minus_one(i, c1Count->get_n_paren_i_circ_arrow_minus_one(i) + c2Count->get_n_paren_i_circ_arrow_minus_one(i) + 
        //                                                 c1Count->get_n_paren_i_circ(i) * c2->n_minus_one);
        ourCount->set_n_paren_ii_arrow_minus_one(i, c1Count->get_n_paren_ii_arrow_minus_one(i) + c2Count->get_n_paren_ii_arrow_minus_one(i) +
                                                    c1Count->get_n_paren_ii(i) * c2->n_minus_one);
        ourCount->set_n_minus_one_arrow_i_arrow_i(i, c1Count->get_n_minus_one_arrow_i_arrow_i(i) + c2Count->get_n_minus_one_arrow_i_arrow_i(i) +
                                                        c1->n_minus_one * c2Count->get_n_i_arrow_i(i) +
                                                        c1Count->get_n_minus_one_arrow_i(i) * c2Count->get_n_i(i));
        // ourCount->set_n_zero_arrow_i_arrow_i(i, c1Count->get_n_zero_arrow_i_arrow_i(i) + c2Count->get_n_zero_arrow_i_arrow_i(i) +
        //                                                 c1Count->get_n_i(0) * c2Count->get_n_i_arrow_i(i) +
        //                                                 c1Count->get_n_i_arrow_j(0, i) * c2Count->get_n_i(i));
        ourCount->set_n_i_arrow_i(i, c1Count->get_n_i_arrow_i(i) + c2Count->get_n_i_arrow_i(i) + c1Count->get_n_i(i) * c2Count->get_n_i(i));
        // ourCount->set_n_zero_arrow_i(i, c1Count->get_n_i_arrow_j(0, i) + c2Count->get_get_n_i_arrow_j(0, i) + c1Count->get_n_i(0) * c2Count->get_n_i(i));
        ourCount->set_n_paren_i_paren_circ_circ(i, c1Count->get_n_paren_i_paren_circ_circ(i) + c2Count->get_n_paren_i_paren_circ_circ(i));
        ourCount->set_n_paren_minus_one_paren_i_circ(i, c1Count->get_n_paren_minus_one_paren_i_circ(i) + c2Count->get_n_paren_minus_one_paren_i_circ(i));

        for (unsigned int j = 1; j < this->degree; j++){
            if (i != j){
                ourCount->set_n_i_arrow_circ_arrow_circ(i, ourCount->get_n_i_arrow_circ_arrow_circ(i) +
                                                            c1Count->get_n_i_arrow_j(i, j) * c2Count->get_n_i(j));
                ourCount->set_n_bracket_i_paren_circ_circ(i, ourCount->get_n_bracket_i_paren_circ_circ(i) +
                                                            c1Count->get_n_i(j) * c2Count->get_n_i_arrow_j(j, i));
            }
        }

    }

    //for summed counters
    // Initialize sum to 0 so we can increment it in the loop
    // n_circ_square = 0;
    n_bracket_minus_one_paren_circ_circ = 0;
    n_paren_minus_one_paren_circ_circ = 0;
    n_bracket_minus_one_paren_circ_square = 0;
    n_minus_one_arrow_paren_circ_circ = 0;
    n_paren_circ_square_arrow_zero = 0;
    // n_bracket_zero_paren_circ_circ = 0;
    n_bracket_zero_paren_circ_square = 0;
    n_minus_one_arrow_circ_arrow_circ = 0;
    // n_zero_arrow_circ_arrow_circ = 0;
    n_minus_one_arrow_circ_arrow_square = 0;
    n_zero_arrow_circ_arrow_square = 0;
    n_circ_arrow_circ = 0;
    n_circ_arrow_square = 0;
    n_bracket_circ_circ = 0;
    n_paren_circ_circ_arrow_square = 0;
    n_bracket_circ_paren_square_square = 0;
    n_circ_arrow_paren_square_square = 0;
    n_circ_arrow_square_arrow_square = 0;
    for (int i = 1; i < this->degree; i++){
        n_bracket_minus_one_paren_circ_circ += ourCount->get_n_bracket_minus_one_paren_ii(i);
        n_paren_minus_one_paren_circ_circ += ourCount->get_n_paren_minus_one_paren_ii(i);
        n_bracket_minus_one_paren_circ_square += ourCount->get_n_bracket_minus_one_paren_i_circ(i);
        n_minus_one_arrow_paren_circ_circ += ourCount->get_n_minus_one_arrow_paren_ii(i);
        n_paren_circ_square_arrow_zero += ourCount->get_n_paren_i_circ_arrow_zero(i);
        // n_bracket_zero_paren_circ_circ += ourCount->get_n_bracket_zero_paren_ii(i);
        n_bracket_zero_paren_circ_square += ourCount->get_n_bracket_zero_paren_i_circ(i);
        // n_circ_square += ourCount->get_n_i_circ(i);
        n_minus_one_arrow_circ_arrow_circ += ourCount->get_n_minus_one_arrow_i_arrow_i(i);
        // n_zero_arrow_circ_arrow_circ += ourCount->get_n_zero_arrow_i_arrow_i(i);
        n_minus_one_arrow_circ_arrow_square += ourCount->get_n_minus_one_arrow_i_arrow_circ(i);
        n_zero_arrow_circ_arrow_square += ourCount->get_n_zero_arrow_i_arrow_circ(i);
        n_circ_arrow_circ += ourCount->get_n_i_arrow_i(i);
        n_circ_arrow_square += ourCount->get_n_i_arrow_circ(i);
        n_bracket_circ_circ += Util::binom2(ourCount->get_n_i(i));
        n_paren_circ_circ_arrow_square += ourCount->get_n_paren_ii_arrow_circ(i);
        n_bracket_circ_paren_square_square += ourCount->get_n_bracket_circ_paren_ii(i);
        n_circ_arrow_paren_square_square += ourCount->get_n_circ_arrow_paren_ii(i);
        n_circ_arrow_square_arrow_square += ourCount->get_n_circ_arrow_i_arrow_i(i);
    }
    n_bracket_zero_paren_circ_square /= 2;
    n_paren_circ_square_arrow_zero /= 2;
    n_bracket_minus_one_paren_circ_square /= 2;
    // n_circ_square /= 2;

    // compute n_i_j
    //for (int j = 0; j < this->degree-1; j++){
    //    for (int i = j+1; i < this->degree; i++){
    for (int i = 1; i < this->degree; i++){
        for (int j = 0; j < i; j++) { 
            ourCount->set_n_ij(i,j, c1Count->get_n_ij(i,j) + c2Count->get_n_ij(i,j));
        }
    }

    // compute n_i_arrow_j
    for (unsigned int i = 0; i < this->degree; i++){
        for (unsigned int j = 0; j < this->degree; j++){
            if (i != j){
                ourCount->set_n_i_arrow_j(i,j, c1Count->get_n_i_arrow_j(i,j) + c2Count->get_n_i_arrow_j(i,j) +
                                              c1Count->get_n_i(i) * c2Count->get_n_i(j));
                ourCount->set_n_bracket_i_paren_j_minus_one(i, j, c1Count->get_n_bracket_i_paren_j_minus_one(i, j) + c2Count->get_n_bracket_i_paren_j_minus_one(i, j) +
                                                                    c1->n_minus_one * c1Count->get_n_i(j) * c2Count->get_n_i(i) +
                                                                    c1Count->get_n_i(i) * c2Count->get_n_paren_i_minus_one(j) +
                                                                    c1->n_minus_one * c2Count->get_n_i_arrow_j(j, i) +
                                                                    c1Count->get_n_i(j) * c2Count->get_n_minus_one_arrow_i(i));
                ourCount->set_n_paren_i_paren_j_minus_one(i, j, c1Count->get_n_paren_i_paren_j_minus_one(i, j) + c2Count->get_n_paren_i_paren_j_minus_one(i, j));
                ourCount->set_n_i_arrow_minus_one_arrow_j(i, j, c1Count->get_n_i_arrow_minus_one_arrow_j(i, j) + c2Count->get_n_i_arrow_minus_one_arrow_j(i, j) +
                                                                c1Count->get_n_i(i) * c2Count->get_n_minus_one_arrow_i(j) +
                                                                c1Count->get_n_i_arrow_minus_one(i) * c2Count->get_n_i(j));
                ourCount->set_n_i_arrow_j_arrow_minus_one(i, j, c1Count->get_n_i_arrow_j_arrow_minus_one(i, j) + c2Count->get_n_i_arrow_j_arrow_minus_one(i, j) +
                                                                c1Count->get_n_i_arrow_j(i, j) * c2->n_minus_one +
                                                                c1Count->get_n_i(i) * c2Count->get_n_i_arrow_minus_one(j));
                ourCount->set_n_i_arrow_paren_j_minus_one(i, j, c1Count->get_n_i_arrow_paren_j_minus_one(i, j) + c2Count->get_n_i_arrow_paren_j_minus_one(i, j) +
                                                                c1Count->get_n_i(i) * c2Count->get_n_paren_i_minus_one(j));
                ourCount->set_n_paren_i_minus_one_arrow_j(i, j, c1Count->get_n_paren_i_minus_one_arrow_j(i, j) + c2Count->get_n_paren_i_minus_one_arrow_j(i, j) +
                                                                c1Count->get_n_paren_i_minus_one(i) * c2Count->get_n_i(j));
                ourCount->set_n_paren_ii_arrow_j(i, j, c1Count->get_n_paren_ii_arrow_j(i, j) + c2Count->get_n_paren_ii_arrow_j(i, j) +
                                                        c1Count->get_n_paren_ii(i) * c2Count->get_n_i(j));
                ourCount->set_n_i_arrow_paren_jj(i, j, c1Count->get_n_i_arrow_paren_jj(i, j) + c2Count->get_n_i_arrow_paren_jj(i, j) +
                                                        c1Count->get_n_i(i) * c2Count->get_n_paren_ii(j));
                ourCount->set_n_i_arrow_j_arrow_j(i, j, c1Count->get_n_i_arrow_j_arrow_j(i, j) + c2Count->get_n_i_arrow_j_arrow_j(i, j) +
                                                        c1Count->get_n_i(i) * c2Count->get_n_i_arrow_i(j) +
                                                        c1Count->get_n_i_arrow_j(i, j) * c2Count->get_n_i(j));
                ourCount->set_n_bracket_i_paren_jj(i, j, c1Count->get_n_bracket_i_paren_jj(i, j) + c2Count->get_n_bracket_i_paren_jj(i, j) +
                                                        Util::binom2(c1Count->get_n_i(j)) * c2Count->get_n_i(i) +
                                                        c1Count->get_n_i(i) * c2Count->get_n_paren_ii(j) +
                                                        c1Count->get_n_i(j) * c2Count->get_n_i_arrow_j(j, i));
                ourCount->set_n_paren_i_paren_jj(i, j, c1Count->get_n_paren_i_paren_jj(i, j) + c2Count->get_n_paren_i_paren_jj(i, j));
            }
        }
    }

    /* Computing tripResolved, tripUnresolved and tripResolved_root */

	// Fetch the childrens "result counting data"
    // tripResolved_root = c1->tripResolved_root + c2->tripResolved_root + c1Count->get_n_i(0) * c2Count->get_n_i_arrow_circ(0); 

    // for (int i = 0; i < this->degree; i++){
    //     tripResolved[i] = c1->tripResolved[i] + c2->tripResolved[i];
	//     tripUnresolved[i] = c1->tripUnresolved[i] + c2->tripUnresolved[i];
    //     if (i != 0)
    //         tripResolved_root += (c1->n_circ /*- c1Count->get_n_i(0)*/) * c2Count->get_n_i_arrow_j(i,0);
    // }
    
    // tripResolved_root += Util::binom2(c1Count->get_n_i(0)) * (c2->n_circ /* - c2Count->get_n_i(0)*/) + Util::binom2(c1->n_circ /* - c1Count->get_n_i(0) */) * c2Count->get_n_i(0);
    // tripResolved_root += (c1->n_circ /* - c1Count->get_n_i(0)*/) * c2Count->get_n_paren_ii(0) + c1Count->get_n_i(0) * (c2->n_paren_circ_square - c2->n_parent_zero_circ);

    
    // for (int j = 0; j < this->degree; j++){
    //     for (int i = 0; i < this->degree; i++){
    //         if (i != j){ // leave j out
    //             tripResolved[j] += c1Count->get_n_i(i) * ( c2Count->get_n_i_arrow_circ(i) - c2Count->get_n_i_arrow_j(i,j) );
    //             tripUnresolved[j] += c1Count->get_n_i(i) * ( c2->n_circ_square - c2Count->get_n_i_circ(j) - c2Count->get_n_i_circ(i) + c2Count->get_n_ij(i,j) );
    //             if (i == 0 && j > 0) {
    //                 tripResolved[j] += Util::binom2(c1Count->get_n_i(i)) * ( c2->n_circ - c2Count->get_n_i(j));
    //                 tripResolved[j] += ( c1->n_circ - c1Count->get_n_i(j)) * c2Count->get_n_paren_ii(i);
    //             }
    //             else if (i > 0 && j == 0) {
    //                 tripResolved[j] += Util::binom2(c1Count->get_n_i(i)) * ( c2->n_circ - c2Count->get_n_i(i));
    //                 tripResolved[j] += ( c1->n_circ - c1Count->get_n_i(i)) * c2Count->get_n_paren_ii(i);
    //             }
    //             else {
    //                 tripResolved[j] += Util::binom2(c1Count->get_n_i(i)) * ( c2->n_circ - c2Count->get_n_i(j) - c2Count->get_n_i(i));
    //                 tripResolved[j] += ( c1->n_circ - c1Count->get_n_i(j) - c1Count->get_n_i(i)) * c2Count->get_n_paren_ii(i);
    //             }
                
    //         }
    //     }
    // }

    //computing rho and pi
    rho = c1->rho + c2-> rho;

    //Case 1
    rho += c1Count->get_n_i(0) * (c2->n_minus_one_arrow_paren_circ_square + c2->n_minus_one_arrow_paren_circ_circ);
    rho += c1->n_minus_one * (c2Count->get_n_i_arrow_paren_circ_square(0) + c2Count->get_n_i_arrow_paren_circ_circ(0));
    rho += c1->n_circ * c2Count->get_n_circ_arrow_paren_i_minus_one(0);
    rho += c1Count->get_n_i(0) * c1->n_minus_one * (c2->n_paren_circ_square + c2->n_paren_circ_circ);
    rho += c2Count->get_n_paren_i_minus_one(0) * Util::binom2(c1->n_circ);

    //Case 2
    rho += c1->n_circ * c2Count->get_n_circ_arrow_minus_one_arrow_i(0);
    rho += Util::binom2(c1->n_circ) * c2Count->get_n_minus_one_arrow_i(0);
    rho += (c1->n_bracket_minus_one_paren_circ_circ + c1->n_bracket_minus_one_paren_circ_square) * c2Count->get_n_i(0);
    rho += c1Count->get_n_i(0) * (c2->n_paren_minus_one_paren_circ_square + c2->n_paren_minus_one_paren_circ_circ);
    rho += c1->n_minus_one * (c2->n_paren_circ_square_arrow_zero + c2Count->get_n_paren_circ_circ_arrow_i(0));

    //Case 2'
    rho += c1->n_circ * c2Count->get_n_circ_arrow_i_arrow_minus_one(0);
    rho += Util::binom2(c1->n_circ) * c2Count->get_n_i_arrow_minus_one(0);
    rho += (c1Count->get_n_bracket_i_paren_circ_circ(0) + c1->n_bracket_zero_paren_circ_square) * c2->n_minus_one;
    rho += c1->n_minus_one * (c2Count->get_n_paren_i_paren_circ_circ(0) + c2->n_paren_zero_paren_circ_square);
    rho += c1Count->get_n_i(0) * (c2->n_paren_circ_circ_arrow_minus_one + c2->n_paren_circ_square_arrow_minus_one);

    // //Case 3
    // rho += c1->n_circ * c2Count->get_n_circ_arrow_i(0) * (n_minus_one_total - n_minus_one);
    // rho += Util::binom2(c1->n_circ) * c2Count->get_n_i(0) * (n_minus_one_total - n_minus_one);
    // rho += c1Count->get_n_i(0) * (c2->n_paren_circ_square + c2->n_paren_circ_circ) * (n_minus_one_total - n_minus_one);

    // Case 4
    rho += c1Count->get_n_i(0) * c2Count->get_n_i_arrow_paren_circ_minus_one(0);
    rho += c1->n_minus_one * c2Count->get_n_circ_arrow_paren_ii(0);
    rho += c1->n_circ * c2Count->get_n_minus_one_arrow_paren_ii(0);
    rho += Util::binom2(c1Count->get_n_i(0)) * c2->n_paren_circ_minus_one;
    rho += c1->n_minus_one * c1->n_circ * c2Count->get_n_paren_ii(0);

    //Case 5
    rho += c1Count->get_n_i(0) * c2Count->get_n_i_arrow_minus_one_arrow_circ(0);
    rho += Util::binom2(c1Count->get_n_i(0)) * c2->n_minus_one_arrow_circ;
    rho += c1->n_minus_one * c2Count->get_n_paren_ii_arrow_circ(0);
    rho += c1Count->get_n_bracket_minus_one_paren_ii(0) * c2->n_circ;
    rho += c1->n_circ * c2Count->get_n_paren_minus_one_paren_ii(0);

    //Case 5'
    rho += c1Count->get_n_i(0) * c2Count->get_n_i_arrow_circ_arrow_minus_one(0);
    rho += Util::binom2(c1Count->get_n_i(0)) * c2->n_circ_arrow_minus_one;
    rho += c1->n_circ * c2Count->get_n_paren_ii_arrow_minus_one(0);
    rho += c1Count->get_n_bracket_circ_paren_ii(0) * c2->n_minus_one;
    rho += c1->n_minus_one * c2Count->get_n_paren_circ_paren_ii(0);

    // //Case 6
    // rho += c1Count->get_n_i(0) * c2Count->get_n_i_arrow_circ(0) * (n_minus_one_total - n_minus_one);
    // rho += Util::binom2(c1Count->get_n_i(0)) * c2->n_circ * (n_minus_one_total - n_minus_one);
    // rho += c1->n_circ * c2Count->get_n_paren_ii(0) * (n_minus_one_total - n_minus_one);

    //Case 7
    rho += c1Count->get_n_i(0) * (c2->n_minus_one_arrow_circ_arrow_circ + c2->n_minus_one_arrow_circ_arrow_square);
    rho += c1->n_minus_one * (c2Count->get_n_i_arrow_circ_arrow_circ(0) + c2->n_zero_arrow_circ_arrow_square);
    rho += c1Count->get_n_i(0) * c1->n_minus_one * (c2->n_circ_arrow_circ + c2->n_circ_arrow_square);
    rho += c1->n_circ * c2Count->get_n_paren_i_minus_one_arrow_circ(0);
    rho += c1Count->get_n_bracket_circ_paren_i_minus_one(0) * c2->n_circ;
    rho += c1->n_circ * c2Count->get_n_paren_circ_paren_i_minus_one(0);

    //Case 8
    rho += c1->n_circ * c2Count->get_n_minus_one_arrow_i_arrow_i(0);
    rho += c1->n_minus_one * c2Count->get_n_circ_arrow_i_arrow_i(0);
    rho += c1->n_circ * c1->n_minus_one * c2Count->get_n_i_arrow_i(0);
    rho += c1Count->get_n_i(0) * c2Count->get_n_paren_circ_minus_one_arrow_i(0);
    rho += c1Count->get_n_bracket_i_paren_circ_minus_one(0) * c2Count->get_n_i(0);
    rho += c1Count->get_n_i(0) * c2Count->get_n_paren_i_paren_circ_minus_one(0);

    //Pi
    for (int i = 0; i < this->degree; i++){
        pi[i] = c1->pi[i] + c2->pi[i];
    }

    for (int j = 0; j < this->degree; j++){
        for (int i = 0; i < this->degree; i++){
            if (i != j){ // leave j out
                if (i == 0) {
                    //Case 1
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_i_arrow_minus_one_arrow_circ(i) - c2Count->get_n_i_arrow_minus_one_arrow_j(i, j));

                    //Case 1'
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_i_arrow_circ_arrow_minus_one(i) - c2Count->get_n_i_arrow_j_arrow_minus_one(i, j));

                    //Case 2
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_i_arrow_paren_circ_minus_one(i) - c2Count->get_n_i_arrow_paren_j_minus_one(i, j));

                    // //Case 3
                    // pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_i_arrow_circ(i) - c2Count->get_n_i_arrow_j(i, j)) * (n_minus_one_total - n_minus_one);
                    // pi[j] += Util::binom2(c1Count->get_n_i(i)) * (c2->n_circ + c2Count->get_n_i(0) - c2Count->get_n_i(i) - c2Count->get_n_i(j)) * (n_minus_one_total - n_minus_one);
                    // pi[j] += c1Count->get_n_i(i) * (c2->n_paren_circ_circ + c2Count->get_n_paren_ii(0) - c2Count->get_n_paren_ii(i) - c2Count->get_n_paren_ii(j)) * (n_minus_one_total - n_minus_one);

                    //Case 4
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_paren_circ_minus_one_arrow_i(i) - c2Count->get_n_paren_i_minus_one_arrow_j(j, i));
                    pi[j] += (c1Count->get_n_bracket_i_paren_circ_minus_one(i) - c1Count->get_n_bracket_i_paren_j_minus_one(i, j)) * c2Count->get_n_i(i);
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_paren_i_paren_circ_minus_one(i) - c2Count->get_n_paren_i_paren_j_minus_one(i, j));

                }
                else {
                    // Case 1
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_i_arrow_minus_one_arrow_circ(i) + c2Count->get_n_i_arrow_minus_one_arrow_j(i, 0) - c2Count->get_n_i_arrow_minus_one_arrow_j(i, j));

                    //Case 1'
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_i_arrow_circ_arrow_minus_one(i) + c2Count->get_n_i_arrow_j_arrow_minus_one(i, 0) 
                            - c2Count->get_n_i_arrow_j_arrow_minus_one(i, j));

                    //Case 2
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_i_arrow_paren_circ_minus_one(i) + c2Count->get_n_i_arrow_paren_j_minus_one(i, 0) - c2Count->get_n_i_arrow_paren_j_minus_one(i, j));

                    // //Case 3
                    // pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_i_arrow_circ(i) + c2Count->get_n_i_arrow_j(i, 0) - c2Count->get_n_i_arrow_j(i, j)) * (n_minus_one_total - n_minus_one);
                    // pi[j] += Util::binom2(c1Count->get_n_i(i)) * (c2->n_circ + c2Count->get_n_i(0) - c2Count->get_n_i(i) - c2Count->get_n_i(j)) * (n_minus_one_total - n_minus_one);
                    // pi[j] += c1Count->get_n_i(i) * (c2->n_paren_circ_circ + c2Count->get_n_paren_ii(0) - c2Count->get_n_paren_ii(i) - c2Count->get_n_paren_ii(j)) * (n_minus_one_total - n_minus_one);

                    //Case 4
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_paren_circ_minus_one_arrow_i(i) + c2Count->get_n_paren_i_minus_one_arrow_j(0, i) - c2Count->get_n_paren_i_minus_one_arrow_j(j, i));
                    pi[j] += (c1Count->get_n_bracket_i_paren_circ_minus_one(i) + c1Count->get_n_bracket_i_paren_j_minus_one(i, 0) - c1Count->get_n_bracket_i_paren_j_minus_one(i, j)) * c2Count->get_n_i(i);
                    pi[j] += c1Count->get_n_i(i) * (c2Count->get_n_paren_i_paren_circ_minus_one(i) + c2Count->get_n_paren_i_paren_j_minus_one(i, 0) - c2Count->get_n_paren_i_paren_j_minus_one(i, j));

                }

                // Case 1
                pi[j] += Util::binom2(c1Count->get_n_i(i)) * (c2->n_minus_one_arrow_circ + c2Count->get_n_minus_one_arrow_i(0) - c2Count->get_n_minus_one_arrow_i(i) - c2Count->get_n_minus_one_arrow_i(j));
                pi[j] += c1Count->get_n_bracket_minus_one_paren_ii(i) * (c2->n_circ + c2Count->get_n_i(0) - c2Count->get_n_i(i) - c2Count->get_n_i(j));
                pi[j] += c1Count->get_n_i(i) * (c2->n_paren_minus_one_paren_circ_circ + c2Count->get_n_paren_minus_one_paren_ii(0) - c2Count->get_n_paren_minus_one_paren_ii(i) - c2Count->get_n_paren_minus_one_paren_ii(j));

                //Case 1'
                pi[j] += Util::binom2(c1Count->get_n_i(i)) * (c2->n_circ_arrow_minus_one + c2Count->get_n_i_arrow_minus_one(0)
                        - c2Count->get_n_i_arrow_minus_one(i) - c2Count->get_n_i_arrow_minus_one(j));
                pi[j] += c1Count->get_n_i(i) * (c2->n_paren_circ_circ_arrow_minus_one + c2Count->get_n_paren_ii_arrow_minus_one(0)
                        - c2Count->get_n_paren_ii_arrow_minus_one(i) - c2Count->get_n_paren_ii_arrow_minus_one(j));

                // Case 2
                pi[j] += c1Count->get_n_i(i) * (c2->n_minus_one_arrow_paren_circ_circ + c2Count->get_n_minus_one_arrow_paren_ii(0) - c2Count->get_n_minus_one_arrow_paren_ii(i) - c2Count->get_n_minus_one_arrow_paren_ii(j));
                pi[j] += Util::binom2(c1Count->get_n_i(i)) * (c2->n_paren_circ_minus_one + c2Count->get_n_paren_i_minus_one(0) - c2Count->get_n_paren_i_minus_one(i) - c2Count->get_n_paren_i_minus_one(j));
                pi[j] += c1Count->get_n_i(i) * c1->n_minus_one * (c2->n_paren_circ_circ + c2Count->get_n_paren_ii(0) - c2Count->get_n_paren_ii(i) - c2Count->get_n_paren_ii(j));

                //Case 4
                pi[j] += c1Count->get_n_i(i) * (c2->n_minus_one_arrow_circ_arrow_circ + c2Count->get_n_minus_one_arrow_i_arrow_i(0) - c2Count->get_n_minus_one_arrow_i_arrow_i(i) - c2Count->get_n_minus_one_arrow_i_arrow_i(j));
                pi[j] += c1Count->get_n_i(i) * c1->n_minus_one * (c2->n_circ_arrow_circ + c2Count->get_n_i_arrow_i(0) - c2Count->get_n_i_arrow_i(i) - c2Count->get_n_i_arrow_i(j));

            }
        }

        if (j == 0) {

            //Case 1
            pi[j] += c1->n_minus_one * (c2->n_paren_circ_circ_arrow_square + c2Count->get_n_paren_ii_arrow_circ(0) + c2Count->get_n_paren_circ_circ_arrow_i(0)
                                        - c2Count->get_n_paren_ii_arrow_circ(j) - c2Count->get_n_paren_circ_circ_arrow_i(j));

            //Case 1'
            pi[j] += (c1->n_bracket_circ_paren_square_square + c1Count->get_n_bracket_i_paren_circ_circ(0) + c1Count->get_n_bracket_circ_paren_ii(0) 
                    - c1Count->get_n_bracket_i_paren_circ_circ(j) - c1Count->get_n_bracket_circ_paren_ii(j)) * c2->n_minus_one;
            pi[j] += c1->n_minus_one * (c2->n_paren_circ_paren_square_square + c2Count->get_n_paren_i_paren_circ_circ(0) + c2Count->get_n_paren_circ_paren_ii(0) 
                    - c2Count->get_n_paren_i_paren_circ_circ(j) - c2Count->get_n_paren_circ_paren_ii(j));

            //Case 2
            pi[j] += c1->n_minus_one * (c2->n_circ_arrow_paren_square_square + c2Count->get_n_circ_arrow_paren_ii(0) + c2Count->get_n_i_arrow_paren_circ_circ(0) +
                                        - c2Count->get_n_i_arrow_paren_circ_circ(j) - c2Count->get_n_circ_arrow_paren_ii(j));

            //Case 4
            pi[j] += c1->n_minus_one * (c2->n_circ_arrow_square_arrow_square + c2Count->get_n_i_arrow_circ_arrow_circ(0) + c2Count->get_n_circ_arrow_i_arrow_i(0)
                                        - c2Count->get_n_i_arrow_circ_arrow_circ(j) - c2Count->get_n_circ_arrow_i_arrow_i(j));
        }

        else {

            //Case 1
            pi[j] += c1->n_minus_one * (c2->n_paren_circ_circ_arrow_square + c2Count->get_n_paren_ii_arrow_circ(0) + c2Count->get_n_paren_circ_circ_arrow_i(0)
                                        - c2Count->get_n_paren_ii_arrow_circ(j) - c2Count->get_n_paren_ii_arrow_j(j, 0)
                                        - c2Count->get_n_paren_circ_circ_arrow_i(j) - c2Count->get_n_paren_ii_arrow_j(0, j));

            //Case 1'
            pi[j] += (c1->n_bracket_circ_paren_square_square + c1Count->get_n_bracket_i_paren_circ_circ(0) + c1Count->get_n_bracket_circ_paren_ii(0) 
                    - c1Count->get_n_bracket_i_paren_circ_circ(j) - c1Count->get_n_bracket_i_paren_jj(j, 0)
                    - c1Count->get_n_bracket_circ_paren_ii(j) - c1Count->get_n_bracket_i_paren_jj(0, j)) * c2->n_minus_one;
            pi[j] += c1->n_minus_one * (c2->n_paren_circ_paren_square_square + c2Count->get_n_paren_i_paren_circ_circ(0) + c2Count->get_n_paren_circ_paren_ii(0) 
                    - c2Count->get_n_paren_i_paren_circ_circ(j) - c2Count->get_n_paren_i_paren_jj(j, 0)
                    - c2Count->get_n_paren_circ_paren_ii(j) - c2Count->get_n_paren_i_paren_jj(0, j));

            //Case 2
            pi[j] += c1->n_minus_one * (c2->n_circ_arrow_paren_square_square + c2Count->get_n_circ_arrow_paren_ii(0) + c2Count->get_n_i_arrow_paren_circ_circ(0) +
                                        - c2Count->get_n_i_arrow_paren_circ_circ(j) - c2Count->get_n_i_arrow_paren_jj(j, 0)
                                        - c2Count->get_n_circ_arrow_paren_ii(j) - c2Count->get_n_i_arrow_paren_jj(0, j));

            //Case 4
            pi[j] += c1->n_minus_one * (c2->n_circ_arrow_square_arrow_square + c2Count->get_n_i_arrow_circ_arrow_circ(0) + c2Count->get_n_circ_arrow_i_arrow_i(0)
                                        - c2Count->get_n_i_arrow_circ_arrow_circ(j) - c2Count->get_n_i_arrow_j_arrow_j(j, 0)
                                        - c2Count->get_n_circ_arrow_i_arrow_i(j) - c2Count->get_n_i_arrow_j_arrow_j(0, j));

        }

    }
    
}
