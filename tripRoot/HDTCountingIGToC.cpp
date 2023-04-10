#include <cstdlib> // for exit
#include "hdt.h"
#include "rooted_tree.h"
#include "hdt_factory.h"
#include "counting_array.h"

void HDT::handleIGToC()
{
	// NOTE: We generate this with left being I and right being G!

	if (!right->up2date) right->updateCounters();
	
    // reset counters
    this->resetCounters();
    
    // These are just inherited from the G node
	n_circ = right->n_circ;
	// n_circ_square = right->n_circ_square;
    // n_parent_zero_circ = right->n_parent_zero_circ;
    n_paren_circ_minus_one = right->n_paren_circ_minus_one;
    n_paren_circ_square = right->n_paren_circ_square;

    n_paren_circ_circ = right->n_paren_circ_circ;
    n_minus_one = right->n_minus_one;
    // n_paren_zero_minus_one = right->n_paren_zero_minus_one;
    n_bracket_minus_one_paren_circ_circ = right->n_bracket_minus_one_paren_circ_circ;
    n_paren_minus_one_paren_circ_circ = right->n_paren_minus_one_paren_circ_circ;
    // n_paren_zero_paren_circ_circ = right->n_paren_zero_paren_circ_circ;
    n_bracket_minus_one_paren_circ_square = right->n_bracket_minus_one_paren_circ_square;
    n_paren_minus_one_paren_circ_square = right->n_paren_minus_one_paren_circ_square;
    n_paren_zero_paren_circ_square = right->n_paren_zero_paren_circ_square;
    // n_bracket_zero_paren_circ_circ = right->n_bracket_zero_paren_circ_circ;
    n_bracket_zero_paren_circ_square = right->n_bracket_zero_paren_circ_square;
    n_paren_circ_paren_square_square = right->n_paren_circ_paren_square_square;
    n_circ_arrow_minus_one = 0;
    n_minus_one_arrow_paren_circ_square = 0;
    n_minus_one_arrow_paren_circ_circ = 0;
    n_paren_circ_square_arrow_zero = 0;
    n_paren_circ_circ_arrow_minus_one = 0;
    n_paren_circ_square_arrow_minus_one = 0;
    n_minus_one_arrow_circ = 0;
    n_minus_one_arrow_circ_arrow_circ = 0;
    // n_zero_arrow_circ_arrow_circ = 0;
    n_minus_one_arrow_circ_arrow_square = 0;
    n_zero_arrow_circ_arrow_square = 0;
    n_circ_arrow_circ = 0;
    n_circ_arrow_square = 0;
    n_bracket_circ_circ = right->n_bracket_circ_circ;
    n_paren_circ_circ_arrow_square = 0;
    n_bracket_circ_paren_square_square = right->n_bracket_circ_paren_square_square;
    n_circ_arrow_paren_square_square = 0;
    n_circ_arrow_square_arrow_square = 0;


    // tripResolved_root = right->tripResolved_root;
    rho = right->rho;

    // copy tripResolved and tripUnresolved and countingVars from the G component
    CountingArray *rCV = &right->countingVars;
    
    for (int i = 0; i < this->degree; i++){
        // tripResolved[i] = right->tripResolved[i];
        // tripUnresolved[i] = right->tripUnresolved[i];
        pi[i] = right->pi[i];
        countingVars.set_n_i(i, rCV->get_n_i(i));
        // countingVars.set_n_i_circ(i, rCV->get_n_i_circ(i));
        countingVars.set_n_i_arrow_circ(i, 0);
        countingVars.set_n_circ_arrow_i(i, 0);
        countingVars.set_n_paren_ii(i, rCV->get_n_paren_ii(i));
        countingVars.set_n_paren_i_circ(i, rCV->get_n_paren_i_circ(i));
        countingVars.set_n_i_arrow_minus_one(i, 0);
        countingVars.set_n_minus_one_arrow_i(i, 0);
        // countingVars.set_n_i_arrow_zero(i, 0);
        countingVars.set_n_minus_one_arrow_paren_ii(i, 0);
        countingVars.set_n_i_arrow_paren_circ_square(i, 0);
        countingVars.set_n_i_arrow_paren_circ_circ(i, 0);
        countingVars.set_n_circ_arrow_paren_i_minus_one(i, 0);
        countingVars.set_n_circ_arrow_minus_one_arrow_i(i, 0);
        countingVars.set_n_paren_circ_circ_arrow_i(i, 0);
        // countingVars.set_n_paren_i_circ_arrow_i(i, 0);
        countingVars.set_n_paren_i_circ_arrow_zero(i, 0);
        countingVars.set_n_circ_arrow_i_arrow_minus_one(i, 0);
        // countingVars.set_n_paren_i_circ_arrow_minus_one(i, 0);
        countingVars.set_n_i_arrow_paren_circ_minus_one(i, 0);
        countingVars.set_n_i_arrow_minus_one_arrow_circ(i, 0);
        countingVars.set_n_circ_arrow_paren_ii(i, 0);
        countingVars.set_n_paren_ii_arrow_circ(i, 0);
        countingVars.set_n_i_arrow_circ_arrow_minus_one(i, 0);
        countingVars.set_n_paren_ii_arrow_minus_one(i, 0);
        countingVars.set_n_minus_one_arrow_i_arrow_i(i, 0);
        // countingVars.set_n_zero_arrow_i_arrow_i(i, 0);
        countingVars.set_n_i_arrow_i(i, 0);
        // countingVars.set_n_zero_arrow_i(i, 0);
        countingVars.set_n_minus_one_arrow_i_arrow_circ(i, 0);
        countingVars.set_n_zero_arrow_i_arrow_circ(i, 0);
        countingVars.set_n_paren_i_minus_one_arrow_circ(i, 0);
        countingVars.set_n_circ_arrow_i_arrow_i(i, 0);
        countingVars.set_n_paren_circ_minus_one_arrow_i(i, 0);
        countingVars.set_n_i_arrow_circ_arrow_circ(i, 0);
        countingVars.set_n_bracket_minus_one_paren_ii(i, rCV->get_n_bracket_minus_one_paren_ii(i));
        // countingVars.set_n_bracket_zero_paren_ii(i, rCV->get_n_bracket_zero_paren_ii(i));
        countingVars.set_n_bracket_circ_paren_ii(i, rCV->get_n_bracket_circ_paren_ii(i));
        countingVars.set_n_paren_minus_one_paren_ii(i, rCV->get_n_paren_minus_one_paren_ii(i));
        // countingVars.set_n_paren_zero_paren_ii(i, rCV->get_n_paren_zero_paren_ii(i));
        // countingVars.set_n_paren_zero_i(i, rCV->get_n_paren_zero_i(i));
        countingVars.set_n_paren_i_minus_one(i, rCV->get_n_paren_i_minus_one(i));
        countingVars.set_n_paren_circ_paren_ii(i, rCV->get_n_paren_circ_paren_ii(i));
        countingVars.set_n_bracket_minus_one_paren_i_circ(i, rCV->get_n_bracket_minus_one_paren_i_circ(i));
        countingVars.set_n_bracket_zero_paren_i_circ(i, rCV->get_n_bracket_zero_paren_i_circ(i));
        countingVars.set_n_paren_zero_paren_i_circ(i, rCV->get_n_paren_zero_paren_i_circ(i));
        countingVars.set_n_bracket_circ_paren_i_minus_one(i, rCV->get_n_bracket_circ_paren_i_minus_one(i));
        countingVars.set_n_paren_circ_paren_i_minus_one(i, rCV->get_n_paren_circ_paren_i_minus_one(i));
        countingVars.set_n_bracket_i_paren_circ_minus_one(i, rCV->get_n_bracket_i_paren_circ_minus_one(i));
        countingVars.set_n_paren_i_paren_circ_minus_one(i, rCV->get_n_paren_i_paren_circ_minus_one(i));
        countingVars.set_n_bracket_i_paren_circ_circ(i, rCV->get_n_bracket_i_paren_circ_circ(i));
        countingVars.set_n_paren_i_paren_circ_circ(i, rCV->get_n_paren_i_paren_circ_circ(i));
        countingVars.set_n_paren_minus_one_paren_i_circ(i, rCV->get_n_paren_minus_one_paren_i_circ(i));
    }

    // copy n_ij from G component
    //for (int j = 0; j < this->degree-1; j++) {
    //    for (int i = j + 1; i < this->degree; i++){
    for (int i = 1; i < this->degree; i++){
        for (int j = 0; j < i; j++){
            countingVars.set_n_ij(i,j,rCV->get_n_ij(i,j));
        }
    }

    for (unsigned int i = 0; i < this->degree; i++){
        for (unsigned int j = 0; j < this->degree; j++){
            if (i != j){
                countingVars.set_n_bracket_i_paren_j_minus_one(i, j, rCV->get_n_bracket_i_paren_j_minus_one(i, j));
                countingVars.set_n_paren_i_paren_j_minus_one(i, j, rCV->get_n_paren_i_paren_j_minus_one(i, j));
                countingVars.set_n_bracket_i_paren_jj(i, j, rCV->get_n_bracket_i_paren_jj(i, j));
                countingVars.set_n_paren_i_paren_jj(i, j , rCV->get_n_paren_i_paren_jj(i, j));
                countingVars.set_n_i_arrow_minus_one_arrow_j(i, j, 0);
                countingVars.set_n_i_arrow_j_arrow_minus_one(i, j, 0);
                countingVars.set_n_i_arrow_paren_j_minus_one(i, j, 0);
                countingVars.set_n_paren_i_minus_one_arrow_j(i, j, 0);
                countingVars.set_n_paren_ii_arrow_j(i, j, 0);
                countingVars.set_n_i_arrow_paren_jj(i, j, 0);
                countingVars.set_n_i_arrow_j_arrow_j(i, j, 0);
            }
        }
    }

    //quartet counters
    n_paren_circ_circ = right->n_paren_circ_circ;
    
    // n_i_arrow_j should have gotten the correct values from constructor of countingArray
}
