#include <cstdlib> // for exit
#include "hdt.h"
#include "rooted_tree.h"
#include "hdt_factory.h"
#include "counting_array.h"

void HDT::handleCTransform()
{    
	// Triplets (sum, n_i_circ has been set to 0, i.e. n_circ_square is also 0!; n_circ is unchanged)
	// n_circ_square = 0;
    // n_parent_zero_circ = countingVars.get_n_i(0) * (n_circ /* - countingVars.get_n_i(0)*/);
    n_paren_circ_minus_one = n_minus_one * (n_circ);

    // //n_paren_zero_minus_one
    // n_paren_zero_minus_one = countingVars.get_n_i(0) * n_minus_one;

    //n_paren_minus_one_paren_circ_square
    // n_paren_minus_one_paren_circ_square = n_bracket_minus_one_paren_circ_square;

    for (int i = 0; i < this->degree; i++){
        INTTYPE_REST n_i = countingVars.get_n_i(i);
        // n_i_circ
        // countingVars.set_n_i_circ(i,0);
        // n_paren_ii
        countingVars.set_n_paren_ii(i,Util::binom2(n_i));
        countingVars.set_n_paren_minus_one_paren_ii(i, countingVars.get_n_bracket_minus_one_paren_ii(i));
        // countingVars.set_n_paren_zero_paren_ii(i, countingVars.get_n_bracket_zero_paren_ii(i));
        countingVars.set_n_paren_circ_paren_ii(i, countingVars.get_n_bracket_circ_paren_ii(i));
        countingVars.set_n_paren_zero_paren_i_circ(i, countingVars.get_n_bracket_zero_paren_i_circ(i));
        // countingVars.set_n_paren_zero_i(i, countingVars.get_n_i(0) * countingVars.get_n_i(i));
        countingVars.set_n_paren_i_minus_one(i, n_minus_one * countingVars.get_n_i(i));
        countingVars.set_n_paren_circ_paren_i_minus_one(i, countingVars.get_n_bracket_circ_paren_i_minus_one(i));
        countingVars.set_n_paren_i_paren_circ_minus_one(i, countingVars.get_n_bracket_i_paren_circ_minus_one(i));
        countingVars.set_n_paren_i_paren_circ_circ(i, countingVars.get_n_bracket_i_paren_circ_circ(i));
        countingVars.set_n_paren_minus_one_paren_i_circ(i, countingVars.get_n_bracket_minus_one_paren_i_circ(i));
        // n_i is unchanged by this transform!
        // n_i_arrow_circ is not defined for G
        // countingVars.set_n_i_arrow_circ(i,0);

        if (i > 0) {
            //n_paren_i_circ
            countingVars.set_n_paren_i_circ(i, n_i * (n_circ - n_i));
        }
        else {
            //n_paren_i_circ
            countingVars.set_n_paren_i_circ(i, n_i * n_circ);
        }

    }

    //for summed counters
    n_paren_zero_paren_circ_square = 0;
    // n_paren_zero_paren_circ_circ = 0;
    n_paren_circ_square = 0;
    n_paren_circ_circ = 0;
    n_paren_minus_one_paren_circ_square = 0;
    n_paren_minus_one_paren_circ_circ = 0;
    n_paren_circ_paren_square_square = 0;
    for (int i = 1; i < this->degree; i++){
        n_paren_zero_paren_circ_square += countingVars.get_n_paren_zero_paren_i_circ(i);
        // n_paren_zero_paren_circ_circ += countingVars.get_n_paren_zero_paren_ii(i);
        n_paren_circ_square += countingVars.get_n_paren_i_circ(i);
        n_paren_circ_circ += countingVars.get_n_paren_ii(i);
        n_paren_circ_paren_square_square += countingVars.get_n_paren_circ_paren_ii(i);
        n_paren_minus_one_paren_circ_square += countingVars.get_n_paren_minus_one_paren_i_circ(i);
        n_paren_minus_one_paren_circ_circ += countingVars.get_n_paren_minus_one_paren_ii(i);
    }

    n_paren_circ_square /= 2;
    n_paren_zero_paren_circ_square /= 2;
    n_paren_minus_one_paren_circ_square /= 2;

    // n_i_j
    for (int i = 1; i < degree; i++){
        for (int j = 0; j < i; j++){
            countingVars.set_n_ij(i,j,0);
        }
    }

    // n_i_arrow_j are not defined for G
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j != i)
                countingVars.set_n_i_arrow_j(i,j,0);
                countingVars.set_n_paren_i_paren_j_minus_one(i, j, countingVars.get_n_bracket_i_paren_j_minus_one(i, j));
                countingVars.set_n_paren_i_paren_jj(i, j, countingVars.get_n_bracket_i_paren_jj(i, j));
        }
    }
}
