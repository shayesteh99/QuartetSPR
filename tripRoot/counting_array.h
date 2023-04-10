#ifndef COUNTING_ARRAY_H
#define COUNTING_ARRAY_H

#include "int_stuff.h"

class CountingArray
{
    private:
        unsigned int degree;
        INTTYPE_REST *n_i, *n_i_arrow_circ;
        INTTYPE_REST **n_i_j, **n_i_arrow_j;

        //shayesteh99 added
        INTTYPE_REST *n_paren_ii, *n_paren_i_circ, *n_i_arrow_minus_one, *n_bracket_minus_one_paren_ii,
                    *n_paren_minus_one_paren_ii, *n_bracket_minus_one_paren_i_circ, *n_bracket_zero_paren_i_circ, 
                    *n_paren_zero_paren_i_circ, *n_bracket_circ_paren_ii, *n_paren_circ_paren_ii, *n_paren_i_minus_one,
                    *n_bracket_circ_paren_i_minus_one, *n_paren_circ_paren_i_minus_one, *n_minus_one_arrow_i, *n_circ_arrow_i, 
                    *n_bracket_i_paren_circ_minus_one, *n_paren_i_paren_circ_minus_one, *n_minus_one_arrow_paren_ii, *n_i_arrow_paren_circ_square, 
                    *n_i_arrow_paren_circ_circ, *n_circ_arrow_paren_i_minus_one, *n_circ_arrow_minus_one_arrow_i, *n_paren_circ_circ_arrow_i, 
                    *n_paren_i_circ_arrow_zero, *n_circ_arrow_i_arrow_minus_one,
                    *n_i_arrow_paren_circ_minus_one, *n_circ_arrow_paren_ii, *n_i_arrow_minus_one_arrow_circ, *n_paren_ii_arrow_circ,
                    *n_i_arrow_circ_arrow_minus_one, *n_paren_ii_arrow_minus_one, *n_minus_one_arrow_i_arrow_i,
                    *n_i_arrow_i, *n_zero_arrow_i_arrow_circ, *n_minus_one_arrow_i_arrow_circ, *n_paren_i_minus_one_arrow_circ,
                    *n_circ_arrow_i_arrow_i, *n_paren_circ_minus_one_arrow_i, *n_bracket_i_paren_circ_circ, *n_paren_i_paren_circ_circ,
                    *n_i_arrow_circ_arrow_circ, *n_paren_minus_one_paren_i_circ;

        INTTYPE_REST **n_paren_i_paren_j_minus_one, **n_bracket_i_paren_j_minus_one, **n_i_arrow_minus_one_arrow_j, **n_i_arrow_j_arrow_minus_one,
                    **n_i_arrow_paren_j_minus_one, **n_paren_i_minus_one_arrow_j, **n_paren_ii_arrow_j, **n_i_arrow_paren_jj, **n_i_arrow_j_arrow_j,
                    **n_bracket_i_paren_jj, **n_paren_i_paren_jj;

	public:
		void initialize(unsigned int degree);
        CountingArray();
        ~CountingArray();
        INTTYPE_REST get_n_ij(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_i_arrow_j(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_i(unsigned int i);
        // INTTYPE_REST get_n_i_circ(unsigned int i);
        INTTYPE_REST get_n_i_arrow_circ(unsigned int i);
        
        bool set_n_ij(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_i_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_i(unsigned int i, INTTYPE_REST v);
        // bool set_n_i_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_circ(unsigned int i, INTTYPE_REST v);
        

        //shayesteh99 added
        INTTYPE_REST get_n_paren_ii(unsigned int i);
        INTTYPE_REST get_n_paren_i_circ(unsigned int i);
        // INTTYPE_REST get_n_paren_zero_i(unsigned int i);
        INTTYPE_REST get_n_paren_i_minus_one(unsigned int i);
        INTTYPE_REST get_n_i_arrow_minus_one(unsigned int i);
        INTTYPE_REST get_n_minus_one_arrow_i(unsigned int i);
        // INTTYPE_REST get_n_i_arrow_zero(unsigned int i);
        INTTYPE_REST get_n_bracket_minus_one_paren_ii(unsigned int i);
        // INTTYPE_REST get_n_bracket_zero_paren_ii(unsigned int i);
        INTTYPE_REST get_n_bracket_circ_paren_ii(unsigned int i);
        INTTYPE_REST get_n_paren_minus_one_paren_ii(unsigned int i);
        // INTTYPE_REST get_n_paren_zero_paren_ii(unsigned int i);
        INTTYPE_REST get_n_paren_circ_paren_ii(unsigned int i);
        INTTYPE_REST get_n_bracket_minus_one_paren_i_circ(unsigned int i);
        INTTYPE_REST get_n_bracket_zero_paren_i_circ(unsigned int i);
        INTTYPE_REST get_n_paren_zero_paren_i_circ(unsigned int i);
        INTTYPE_REST get_n_bracket_circ_paren_i_minus_one(unsigned int i);
        INTTYPE_REST get_n_paren_circ_paren_i_minus_one(unsigned int i);
        INTTYPE_REST get_n_circ_arrow_i(unsigned int i);
        INTTYPE_REST get_n_bracket_i_paren_circ_minus_one(unsigned int i);
        INTTYPE_REST get_n_paren_i_paren_circ_minus_one(unsigned int i);
        INTTYPE_REST get_n_minus_one_arrow_paren_ii(unsigned int i);
        INTTYPE_REST get_n_i_arrow_paren_circ_square(unsigned int i);
        INTTYPE_REST get_n_i_arrow_paren_circ_circ(unsigned int i);
        INTTYPE_REST get_n_circ_arrow_paren_i_minus_one(unsigned int i);
        INTTYPE_REST get_n_circ_arrow_minus_one_arrow_i(unsigned int i);
        INTTYPE_REST get_n_paren_i_circ_arrow_zero(unsigned int i);
        // INTTYPE_REST get_n_paren_i_circ_arrow_minus_one(unsigned int i);
        INTTYPE_REST get_n_circ_arrow_i_arrow_minus_one(unsigned int i);
        INTTYPE_REST get_n_i_arrow_paren_circ_minus_one(unsigned int i);
        INTTYPE_REST get_n_circ_arrow_paren_ii(unsigned int i);
        INTTYPE_REST get_n_i_arrow_minus_one_arrow_circ(unsigned int i);
        INTTYPE_REST get_n_paren_ii_arrow_circ(unsigned int i);
        INTTYPE_REST get_n_paren_ii_arrow_minus_one(unsigned int i);
        INTTYPE_REST get_n_i_arrow_i(unsigned int i);
        // INTTYPE_REST get_n_zero_arrow_i(unsigned int i);
        INTTYPE_REST get_n_minus_one_arrow_i_arrow_i(unsigned int i);
        // INTTYPE_REST get_n_zero_arrow_i_arrow_i(unsigned int i);
        INTTYPE_REST get_n_circ_arrow_i_arrow_i(unsigned int i);
        INTTYPE_REST get_n_i_arrow_circ_arrow_minus_one(unsigned int i);
        // INTTYPE_REST get_n_paren_i_circ_arrow_i(unsigned int i);
        INTTYPE_REST get_n_paren_circ_circ_arrow_i(unsigned int i);
        INTTYPE_REST get_n_minus_one_arrow_i_arrow_circ(unsigned int i);
        INTTYPE_REST get_n_paren_i_minus_one_arrow_circ(unsigned int i);
        INTTYPE_REST get_n_paren_circ_minus_one_arrow_i(unsigned int i);
        INTTYPE_REST get_n_bracket_i_paren_circ_circ(unsigned int i);
        INTTYPE_REST get_n_paren_i_paren_circ_circ(unsigned int i);
        INTTYPE_REST get_n_i_arrow_circ_arrow_circ(unsigned int i);
        INTTYPE_REST get_n_paren_minus_one_paren_i_circ(unsigned int i);
        INTTYPE_REST get_n_zero_arrow_i_arrow_circ(unsigned int i);

        INTTYPE_REST get_n_paren_i_paren_j_minus_one(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_bracket_i_paren_j_minus_one(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_i_arrow_minus_one_arrow_j(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_i_arrow_j_arrow_minus_one(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_i_arrow_paren_j_minus_one(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_paren_i_minus_one_arrow_j(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_paren_ii_arrow_j(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_i_arrow_j_arrow_j(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_bracket_i_paren_jj(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_paren_i_paren_jj(unsigned int i, unsigned int j);
        INTTYPE_REST get_n_i_arrow_paren_jj(unsigned int i, unsigned int j);

        bool set_n_paren_ii(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_i_circ(unsigned int i, INTTYPE_REST v);
        // bool set_n_paren_zero_i(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_i_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_minus_one_arrow_i(unsigned int i, INTTYPE_REST v);
        // bool set_n_i_arrow_zero(unsigned int i, INTTYPE_REST v);
        bool set_n_bracket_minus_one_paren_ii(unsigned int i, INTTYPE_REST v);
        // bool set_n_bracket_zero_paren_ii(unsigned int i, INTTYPE_REST v);
        bool set_n_bracket_circ_paren_ii(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_minus_one_paren_ii(unsigned int i, INTTYPE_REST v);
        // bool set_n_paren_zero_paren_ii(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_circ_paren_ii(unsigned int i, INTTYPE_REST v);
        bool set_n_bracket_minus_one_paren_i_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_bracket_zero_paren_i_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_zero_paren_i_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_bracket_circ_paren_i_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_circ_paren_i_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_circ_arrow_i(unsigned int i, INTTYPE_REST v);
        bool set_n_bracket_i_paren_circ_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_i_paren_circ_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_minus_one_arrow_paren_ii(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_paren_circ_square(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_paren_circ_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_circ_arrow_paren_i_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_circ_arrow_minus_one_arrow_i(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_i_circ_arrow_zero(unsigned int i, INTTYPE_REST v);
        // bool set_n_paren_i_circ_arrow_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_circ_arrow_i_arrow_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_paren_circ_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_circ_arrow_paren_ii(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_minus_one_arrow_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_ii_arrow_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_ii_arrow_minus_one(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_i(unsigned int i, INTTYPE_REST v);
        // bool set_n_zero_arrow_i(unsigned int i, INTTYPE_REST v);
        bool set_n_minus_one_arrow_i_arrow_i(unsigned int i, INTTYPE_REST v);
        // bool set_n_zero_arrow_i_arrow_i(unsigned int i, INTTYPE_REST v);
        bool set_n_circ_arrow_i_arrow_i(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_circ_arrow_minus_one(unsigned int i, INTTYPE_REST v);
        // bool set_n_paren_i_circ_arrow_i(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_circ_circ_arrow_i(unsigned int i, INTTYPE_REST v);
        bool set_n_minus_one_arrow_i_arrow_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_i_minus_one_arrow_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_circ_minus_one_arrow_i(unsigned int i, INTTYPE_REST v);
        bool set_n_bracket_i_paren_circ_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_i_paren_circ_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_i_arrow_circ_arrow_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_paren_minus_one_paren_i_circ(unsigned int i, INTTYPE_REST v);
        bool set_n_zero_arrow_i_arrow_circ(unsigned int i, INTTYPE_REST v);

        bool set_n_paren_i_paren_j_minus_one(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_bracket_i_paren_j_minus_one(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_i_arrow_minus_one_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_i_arrow_j_arrow_minus_one(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_i_arrow_paren_j_minus_one(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_paren_i_minus_one_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_paren_ii_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_i_arrow_j_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_bracket_i_paren_jj(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_paren_i_paren_jj(unsigned int i, unsigned int j, INTTYPE_REST v);
        bool set_n_i_arrow_paren_jj(unsigned int i, unsigned int j, INTTYPE_REST v);

};  

#endif
