#include <cstdlib> // for exit
#include "hdt.h"
#include "rooted_tree.h"
#include "hdt_factory.h"
#include "counting_linked_list.h"

void HDT::handleG()
{
	// Not a leaf, i.e. a GG->G
	HDT *g1 = this->left;
	HDT *g2 = this->right;
	
	if (!g1->up2date) g1->updateCounters();
	if (!g2->up2date) g2->updateCounters();

	// reset counters
    this->resetCounters();
    
    // n_i is just the sum of the 2 children, thus n_circ is also just the sum of the 2 children
	n_circ = g1->n_circ + g2->n_circ;

    // // n_parent_zero_circ
    // n_parent_zero_circ = g1->n_parent_zero_circ + g2->n_parent_zero_circ;

    //n_paren_circ_minus_one
    n_paren_circ_minus_one = g1->n_paren_circ_minus_one + g2->n_paren_circ_minus_one;

    // n_paren_circ_square
    n_paren_circ_square = g1->n_paren_circ_square + g2->n_paren_circ_square;

    //n_paren_circ_circ
    n_paren_circ_circ = g1->n_paren_circ_circ + g2->n_paren_circ_circ;

    //n_minus_one
    n_minus_one = g1->n_minus_one + g2->n_minus_one;

    // //n_paren_zero_minus_one
    // n_paren_zero_minus_one = g1->n_paren_zero_minus_one + g2->n_paren_zero_minus_one;

    //n_paren_minus_one_paren_circ_square
    n_paren_minus_one_paren_circ_square = g1->n_paren_minus_one_paren_circ_square + g2->n_paren_minus_one_paren_circ_square;

    //n_paren_zero_paren_circ_square
    n_paren_zero_paren_circ_square = g1->n_paren_zero_paren_circ_square + g2->n_paren_zero_paren_circ_square;

    // //n_paren_zero_paren_circ_circ
    // n_paren_zero_paren_circ_circ = g1->n_paren_zero_paren_circ_circ + g2->n_paren_zero_paren_circ_circ;

    //n_paren_circ_paren_square_square
    n_paren_circ_paren_square_square = g1->n_paren_circ_paren_square_square + g2->n_paren_circ_paren_square_square;

    
    // compute n_i, n_i_circ, n_parent_ii, and n_circ_square
    CountingArray *ourCount = &this->countingVars;
    CountingArray *g1Count = &g1->countingVars;
    CountingArray *g2Count = &g2->countingVars;

    for (int i = 0; i < this->degree; i++){
        if (i == 0) {
            ourCount->set_n_bracket_circ_paren_ii(i, g1Count->get_n_bracket_circ_paren_ii(i) + g2Count->get_n_bracket_circ_paren_ii(i) +
                                                    g1->n_circ * g2Count->get_n_paren_ii(i) +
                                                    g2->n_circ * g1Count->get_n_paren_ii(i));
            ourCount->set_n_bracket_circ_paren_i_minus_one(i, g1Count->get_n_bracket_circ_paren_i_minus_one(i) + g2Count->get_n_bracket_circ_paren_i_minus_one(i) +
                                                            g1Count->get_n_paren_i_minus_one(i) * g2->n_circ +
                                                            g2Count->get_n_paren_i_minus_one(i) * g1->n_circ);
            ourCount->set_n_bracket_i_paren_circ_minus_one(i, g1Count->get_n_bracket_i_paren_circ_minus_one(i) + g2Count->get_n_bracket_i_paren_circ_minus_one(i) +
                                                            g1Count->get_n_i(i) * g2->n_paren_circ_minus_one +
                                                            g2Count->get_n_i(i) * g1->n_paren_circ_minus_one);
            ourCount->set_n_bracket_i_paren_circ_circ(i, g1Count->get_n_bracket_i_paren_circ_circ(i) + g2Count->get_n_bracket_i_paren_circ_circ(i) +
                                                            g1Count->get_n_i(i) * g2->n_paren_circ_circ +
                                                            g2Count->get_n_i(i) * g1->n_paren_circ_circ);
        }

        else {
            ourCount->set_n_bracket_circ_paren_ii(i, g1Count->get_n_bracket_circ_paren_ii(i) + g2Count->get_n_bracket_circ_paren_ii(i) +
                                                    (g1->n_circ - g1Count->get_n_i(i)) * g2Count->get_n_paren_ii(i) +
                                                    (g2->n_circ - g2Count->get_n_i(i)) * g1Count->get_n_paren_ii(i));
            ourCount->set_n_bracket_circ_paren_i_minus_one(i, g1Count->get_n_bracket_circ_paren_i_minus_one(i) + g2Count->get_n_bracket_circ_paren_i_minus_one(i) +
                                                            g1Count->get_n_paren_i_minus_one(i) * (g2->n_circ - g2Count->get_n_i(i)) +
                                                            g2Count->get_n_paren_i_minus_one(i) * (g1->n_circ - g1Count->get_n_i(i)));
            ourCount->set_n_bracket_i_paren_circ_minus_one(i, g1Count->get_n_bracket_i_paren_circ_minus_one(i) + g2Count->get_n_bracket_i_paren_circ_minus_one(i) +
                                                            g1Count->get_n_i(i) * (g2->n_paren_circ_minus_one - g2Count->get_n_paren_i_minus_one(i)) +
                                                            g2Count->get_n_i(i) * (g1->n_paren_circ_minus_one - g1Count->get_n_paren_i_minus_one(i)));
            ourCount->set_n_bracket_i_paren_circ_circ(i, g1Count->get_n_bracket_i_paren_circ_circ(i) + g2Count->get_n_bracket_i_paren_circ_circ(i) +
                                                            g1Count->get_n_i(i) * (g2->n_paren_circ_circ - g2Count->get_n_paren_ii(i)) +
                                                            g2Count->get_n_i(i) * (g1->n_paren_circ_circ - g1Count->get_n_paren_ii(i)));
        }

        ourCount->set_n_i(i,g1Count->get_n_i(i) + g2Count->get_n_i(i));
        // ourCount->set_n_i_circ(i, g1Count->get_n_i_circ(i) + g2Count->get_n_i_circ(i) +
        //                             g1Count->get_n_i(i) * (g2->n_circ - g2Count->get_n_i(i)) + 
        //                             g2Count->get_n_i(i) * (g1->n_circ - g1Count->get_n_i(i)));
        ourCount->set_n_paren_ii(i,g1Count->get_n_paren_ii(i) + g2Count->get_n_paren_ii(i));
        ourCount->set_n_paren_i_circ(i, g1Count->get_n_paren_i_circ(i) + g2Count->get_n_paren_i_circ(i));
        ourCount->set_n_bracket_minus_one_paren_ii(i, g1Count->get_n_bracket_minus_one_paren_ii(i) + g2Count->get_n_bracket_minus_one_paren_ii(i) +
                                                    g1->n_minus_one * g2Count->get_n_paren_ii(i) + 
                                                    g2->n_minus_one * g1Count->get_n_paren_ii(i));
        // ourCount->set_n_bracket_zero_paren_ii(i, g1Count->get_n_bracket_zero_paren_ii(i) + g2Count->get_n_bracket_zero_paren_ii(i) +
        //                                             g1Count->get_n_i(0) * g2Count->get_n_paren_ii(i) + 
        //                                             g2Count->get_n_i(0) * g1Count->get_n_paren_ii(i));
        ourCount->set_n_paren_minus_one_paren_ii(i, g1Count->get_n_paren_minus_one_paren_ii(i) + g2Count->get_n_paren_minus_one_paren_ii(i));
        // ourCount->set_n_paren_zero_paren_ii(i, g1Count->get_n_paren_zero_paren_ii(i) + g2Count->get_n_paren_zero_paren_ii(i));
        // ourCount->set_n_paren_zero_i(i, g1Count->get_n_paren_zero_i(i) + g2Count->get_n_paren_zero_i(i));
        ourCount->set_n_paren_i_minus_one(i, g1Count->get_n_paren_i_minus_one(i) + g2Count->get_n_paren_i_minus_one(i));
        ourCount->set_n_paren_circ_paren_ii(i, g1Count->get_n_paren_circ_paren_ii(i) + g2Count->get_n_paren_circ_paren_ii(i));
        ourCount->set_n_bracket_minus_one_paren_i_circ(i, g1Count->get_n_bracket_minus_one_paren_i_circ(i) + g2Count->get_n_bracket_minus_one_paren_i_circ(i) +
                                                            g1->n_minus_one * g2Count->get_n_paren_i_circ(i) + g2->n_minus_one * g1Count->get_n_paren_i_circ(i));
        ourCount->set_n_bracket_zero_paren_i_circ(i, g1Count->get_n_bracket_zero_paren_i_circ(i) + g2Count->get_n_bracket_zero_paren_i_circ(i) +
                                                            g1Count->get_n_i(0) * g2Count->get_n_paren_i_circ(i) + g2Count->get_n_i(0) * g1Count->get_n_paren_i_circ(i));
        ourCount->set_n_paren_zero_paren_i_circ(i, g1Count->get_n_paren_zero_paren_i_circ(i) + g2Count->get_n_paren_zero_paren_i_circ(i));
        ourCount->set_n_paren_circ_paren_i_minus_one(i, g1Count->get_n_paren_circ_paren_i_minus_one(i) + g2Count->get_n_paren_circ_paren_i_minus_one(i));
        ourCount->set_n_paren_i_paren_circ_minus_one(i, g1Count->get_n_paren_i_paren_circ_minus_one(i) + g2Count->get_n_paren_i_paren_circ_minus_one(i));
        ourCount->set_n_paren_i_paren_circ_circ(i, g1Count->get_n_paren_i_paren_circ_circ(i) + g2Count->get_n_paren_i_paren_circ_circ(i));
        ourCount->set_n_paren_minus_one_paren_i_circ(i, g1Count->get_n_paren_minus_one_paren_i_circ(i) + g2Count->get_n_paren_minus_one_paren_i_circ(i));

    }

    //for summed counters
    // Initialize sum to 0 so we can increment it in the loop
    // n_circ_square = 0;
    n_bracket_minus_one_paren_circ_circ = 0;
    n_paren_minus_one_paren_circ_circ = 0;
    n_bracket_minus_one_paren_circ_square = 0;
    // n_bracket_zero_paren_circ_circ = 0;
    n_bracket_zero_paren_circ_square = 0;
    n_bracket_circ_circ = 0;
    n_bracket_circ_paren_square_square = 0;
    for (int i = 1; i < this->degree; i++){
        n_bracket_minus_one_paren_circ_circ += ourCount->get_n_bracket_minus_one_paren_ii(i);
        n_paren_minus_one_paren_circ_circ += ourCount->get_n_paren_minus_one_paren_ii(i);
        n_bracket_minus_one_paren_circ_square += ourCount->get_n_bracket_minus_one_paren_i_circ(i);
        // n_bracket_zero_paren_circ_circ += ourCount->get_n_bracket_zero_paren_ii(i);
        n_bracket_zero_paren_circ_square += ourCount->get_n_bracket_zero_paren_i_circ(i);
        // n_circ_square += ourCount->get_n_i_circ(i);
        n_bracket_circ_circ += Util::binom2(ourCount->get_n_i(i));
        n_bracket_circ_paren_square_square += ourCount->get_n_bracket_circ_paren_ii(i);
    }

    // n_circ_square /= 2;
    n_bracket_minus_one_paren_circ_square /= 2;
    n_bracket_zero_paren_circ_square /= 2;

    // compute n_i_j
    //for (int j = 0; j < this->degree-1; j++){
    //    for (int i = j+1; i < this->degree; i++){
    for (int i = 1; i < this->degree; i++){
        for (int j = 0; j < i; j++){
            ourCount->set_n_ij(i,j, g1Count->get_n_ij(i,j) + g2Count->get_n_ij(i,j) +
                                    g1Count->get_n_i(i) * g2Count->get_n_i(j) + 
                                    g2Count->get_n_i(i) * g1Count->get_n_i(j));
        }
    }

    for (unsigned int i = 0; i < this->degree; i++){
        for (unsigned int j = 0; j < this->degree; j++){
            if (i != j){
                ourCount->set_n_bracket_i_paren_j_minus_one(i, j, g1Count->get_n_bracket_i_paren_j_minus_one(i, j) + g2Count->get_n_bracket_i_paren_j_minus_one(i, j) +
                                                                    g1Count->get_n_i(i) * g2Count->get_n_paren_i_minus_one(j) +
                                                                    g2Count->get_n_i(i) * g1Count->get_n_paren_i_minus_one(j));
                ourCount->set_n_paren_i_paren_j_minus_one(i, j, g1Count->get_n_paren_i_paren_j_minus_one(i, j) + g2Count->get_n_paren_i_paren_j_minus_one(i, j));
                ourCount->set_n_bracket_i_paren_jj(i, j, g1Count->get_n_bracket_i_paren_jj(i, j) + g2Count->get_n_bracket_i_paren_jj(i, j) +
                                                            g1Count->get_n_i(i) * g2Count->get_n_paren_ii(j) +
                                                            g2Count->get_n_i(i) * g1Count->get_n_paren_ii(j));
                ourCount->set_n_paren_i_paren_jj(i, j , g1Count->get_n_paren_i_paren_jj(i, j) + g2Count->get_n_paren_i_paren_jj(i, j));
            }
        }
    }

    // Note: n_i_arrow_j is not defined for G

    
    /* Computing tripResolved, tripUnresolved and tripResolved_root */

	// Fetch the childrens "result counting data"
	// for (int i = 0; i < this->degree; i++){
    //     tripResolved[i] = g1->tripResolved[i] + g2->tripResolved[i];
	//     tripUnresolved[i] = g1->tripUnresolved[i] + g2->tripUnresolved[i];
    // }

    
    // for (int j = 0; j < this->degree; j++){
    //     for (int i = 0; i < this->degree; i++){
    //         if (i != j){ // leave j out
    //             if (i == 0) {
    //                tripResolved[j] += g1Count->get_n_paren_ii(i) * (g2->n_circ - g2Count->get_n_i(j)); 
    //                 tripResolved[j] += g2Count->get_n_paren_ii(i) * (g1->n_circ - g1Count->get_n_i(j));  
    //             }
    //             else if (j == 0) {
    //                 tripResolved[j] += g1Count->get_n_paren_ii(i) * (g2->n_circ - g2Count->get_n_i(i)); 
    //                 tripResolved[j] += g2Count->get_n_paren_ii(i) * (g1->n_circ - g1Count->get_n_i(i));  
    //             }
    //             else {
    //                 tripResolved[j] += g1Count->get_n_paren_ii(i) * (g2->n_circ - g2Count->get_n_i(j) - g2Count->get_n_i(i)); 
    //                 tripResolved[j] += g2Count->get_n_paren_ii(i) * (g1->n_circ - g1Count->get_n_i(j) - g1Count->get_n_i(i)); 
    //             }
                
    //             tripUnresolved[j] += g1Count->get_n_i(i) * ( g2->n_circ_square - g2Count->get_n_i_circ(j) - g2Count->get_n_i_circ(i)  + g2Count->get_n_ij(i,j) );
    //             tripUnresolved[j] += g2Count->get_n_i(i) * ( g1->n_circ_square - g1Count->get_n_i_circ(j) - g1Count->get_n_i_circ(i)  + g1Count->get_n_ij(i,j) );
    //         }
    //     }
    // }
    
    // tripResolved_root = g1->tripResolved_root + g2->tripResolved_root;
    // tripResolved_root += g1Count->get_n_paren_ii(0) * (g2->n_circ /* - g2Count->get_n_i(0)*/) + (g1->n_paren_circ_square /*- g1->n_parent_zero_circ*/) * g2Count->get_n_i(0);
    // tripResolved_root += g2Count->get_n_paren_ii(0) * (g1->n_circ /* - g1Count->get_n_i(0)*/) + (g2->n_paren_circ_square /*- g2->n_parent_zero_circ*/) * g1Count->get_n_i(0);


    //computing rho and pi
    rho = g1->rho + g2-> rho;

    //Case 1
    rho += g1Count->get_n_paren_i_minus_one(0) * (g2->n_paren_circ_square + g2->n_paren_circ_circ);
    rho += g2Count->get_n_paren_i_minus_one(0) * (g1->n_paren_circ_square + g1->n_paren_circ_circ);

    // Case 2
    rho += g1Count->get_n_i(0) * (g2->n_bracket_minus_one_paren_circ_square + g2->n_bracket_minus_one_paren_circ_circ);
    rho += g2Count->get_n_i(0) * (g1->n_bracket_minus_one_paren_circ_square + g1->n_bracket_minus_one_paren_circ_circ);

    //Case 2'
    rho += g1->n_minus_one * (g2Count->get_n_bracket_i_paren_circ_circ(0) + g2->n_bracket_zero_paren_circ_square);
    rho += g2->n_minus_one * (g1Count->get_n_bracket_i_paren_circ_circ(0) + g1->n_bracket_zero_paren_circ_square);

    // //Case 3
    // rho += g1Count->get_n_i(0) * (g2->n_paren_circ_square + g2->n_paren_circ_circ) * (n_minus_one_total - n_minus_one);
    // rho += g2Count->get_n_i(0) * (g1->n_paren_circ_square + g1->n_paren_circ_circ) * (n_minus_one_total - n_minus_one);

    //Case 4
    rho += g1Count->get_n_paren_ii(0) * g2->n_paren_circ_minus_one;
    rho += g2Count->get_n_paren_ii(0) * g1->n_paren_circ_minus_one;

    //Case 5
    rho += g1Count->get_n_bracket_minus_one_paren_ii(0) * g2->n_circ;
    rho += g2Count->get_n_bracket_minus_one_paren_ii(0) * g1->n_circ;

    //Case 5'
    rho += g1Count->get_n_bracket_circ_paren_ii(0) * g2->n_minus_one;
    rho += g2Count->get_n_bracket_circ_paren_ii(0) * g1->n_minus_one;

    // //Case 6
    // rho += g1Count->get_n_paren_ii(0) * g2->n_circ * (n_minus_one_total - n_minus_one);
    // rho += g2Count->get_n_paren_ii(0) * g1->n_circ * (n_minus_one_total - n_minus_one);

    //Case 7
    rho += g1Count->get_n_bracket_circ_paren_i_minus_one(0) * g2->n_circ;
    rho += g2Count->get_n_bracket_circ_paren_i_minus_one(0) * g1->n_circ;

    //Case 8
    rho += g1Count->get_n_i(0) * g2Count->get_n_bracket_i_paren_circ_minus_one(0);
    rho += g2Count->get_n_i(0) * g1Count->get_n_bracket_i_paren_circ_minus_one(0);

    //Pi
    for (int i = 0; i < this->degree; i++){
        pi[i] = g1->pi[i] + g2->pi[i];
    }

    for (int j = 0; j < this->degree; j++){
        for (int i = 0; i < this->degree; i++){
            if (i != j){ // leave j out
                if (i == 0) {
                    //Case 4
                    pi[j] += g1Count->get_n_i(i) * (g2Count->get_n_bracket_i_paren_circ_minus_one(i) - g2Count->get_n_bracket_i_paren_j_minus_one(i, j));
                    pi[j] += g2Count->get_n_i(i) * (g1Count->get_n_bracket_i_paren_circ_minus_one(i) - g1Count->get_n_bracket_i_paren_j_minus_one(i, j));
                }
                else {
                    //Case 4
                    pi[j] += g1Count->get_n_i(i) * (g2Count->get_n_bracket_i_paren_circ_minus_one(i) + g2Count->get_n_bracket_i_paren_j_minus_one(i, 0) - g2Count->get_n_bracket_i_paren_j_minus_one(i, j));
                    pi[j] += g2Count->get_n_i(i) * (g1Count->get_n_bracket_i_paren_circ_minus_one(i) + g1Count->get_n_bracket_i_paren_j_minus_one(i, 0) - g1Count->get_n_bracket_i_paren_j_minus_one(i, j));
                }
                //Case 1
                pi[j] += g1Count->get_n_bracket_minus_one_paren_ii(i) * (g2->n_circ + g2Count->get_n_i(0) - g2Count->get_n_i(i) - g2Count->get_n_i(j));
                pi[j] += g2Count->get_n_bracket_minus_one_paren_ii(i) * (g1->n_circ + g1Count->get_n_i(0) - g1Count->get_n_i(i) - g1Count->get_n_i(j));

                //Case 2
                pi[j] += g1Count->get_n_paren_ii(i) * (g2->n_paren_circ_minus_one + g2Count->get_n_paren_i_minus_one(0) - g2Count->get_n_paren_i_minus_one(i) - g2Count->get_n_paren_i_minus_one(j));
                pi[j] += g2Count->get_n_paren_ii(i) * (g1->n_paren_circ_minus_one + g1Count->get_n_paren_i_minus_one(0) - g1Count->get_n_paren_i_minus_one(i) - g1Count->get_n_paren_i_minus_one(j));

                // //Case 3
                // pi[j] += g1Count->get_n_paren_ii(i) * (g2->n_circ + g2Count->get_n_i(0) - g2Count->get_n_i(i) - g2Count->get_n_i(j)) * (n_minus_one_total - n_minus_one);
                // pi[j] += g2Count->get_n_paren_ii(i) * (g1->n_circ + g1Count->get_n_i(0) - g1Count->get_n_i(i) - g1Count->get_n_i(j)) * (n_minus_one_total - n_minus_one);

            }
        }
        if (j == 0) {
            //Case 1'
            pi[j] += g2->n_minus_one * (g1->n_bracket_circ_paren_square_square + g1Count->get_n_bracket_i_paren_circ_circ(0) + g1Count->get_n_bracket_circ_paren_ii(0)
                    - g1Count->get_n_bracket_i_paren_circ_circ(j) - g1Count->get_n_bracket_circ_paren_ii(j));
            pi[j] += g1->n_minus_one * (g2->n_bracket_circ_paren_square_square + g2Count->get_n_bracket_i_paren_circ_circ(0) + g2Count->get_n_bracket_circ_paren_ii(0)
                    - g2Count->get_n_bracket_i_paren_circ_circ(j) - g2Count->get_n_bracket_circ_paren_ii(j));

        }
        else {
            //Case 1'
            pi[j] += g2->n_minus_one * (g1->n_bracket_circ_paren_square_square + g1Count->get_n_bracket_i_paren_circ_circ(0) + g1Count->get_n_bracket_circ_paren_ii(0)
                     - g1Count->get_n_bracket_i_paren_circ_circ(j) - g1Count->get_n_bracket_i_paren_jj(j, 0)
                     - g1Count->get_n_bracket_circ_paren_ii(j) - g1Count->get_n_bracket_i_paren_jj(0, j));
            pi[j] += g1->n_minus_one * (g2->n_bracket_circ_paren_square_square + g2Count->get_n_bracket_i_paren_circ_circ(0) + g2Count->get_n_bracket_circ_paren_ii(0)
                     - g2Count->get_n_bracket_i_paren_circ_circ(j) - g2Count->get_n_bracket_i_paren_jj(j, 0)
                     - g2Count->get_n_bracket_circ_paren_ii(j) - g2Count->get_n_bracket_i_paren_jj(0, j));

        }
    }

}
