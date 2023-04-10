#include <cstdlib> // for exit
#include "hdt.h"
#include "rooted_tree.h"
#include "hdt_factory.h"
#include "counting_array.h"


void HDT::handleLeaf()
{
	// This is a leaf!
    
    // Reset counters
    this->resetCounters();
    n_circ = 1;

	if (link == NULL)
	{
		countingVars.set_n_i(0,numZeroes);
	}
	else
	{
		if (this->link->color == -1) {
			n_minus_one = 1;
			n_circ = 0;
		}
		else {
			if (this->link->color == 0) {
				n_circ = 0;
			}
			countingVars.set_n_i(this->link->color, 1);
	    	
	    }
	}
	
    // Sums and stuff (triplets)
    
}
