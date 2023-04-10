#include "counting_array.h"
#include <iostream>


void CountingArray::initialize(unsigned int degree){
    this->degree = degree;
    
    if (this->n_i == NULL)
        this->n_i = new INTTYPE_REST[degree];
    
    // if(this->n_i_circ == NULL)
    //     this->n_i_circ = new INTTYPE_REST[degree];
    
    if (this->n_paren_ii == NULL)
        this->n_paren_ii = new INTTYPE_REST[degree];
    
    if (this->n_i_arrow_circ == NULL)
        this->n_i_arrow_circ = new INTTYPE_REST[degree];

    if (this->n_circ_arrow_i == NULL)
        this->n_circ_arrow_i = new INTTYPE_REST[degree];

    if (this->n_paren_i_circ == NULL)
        this->n_paren_i_circ = new INTTYPE_REST[degree];

    // if (this->n_paren_zero_i == NULL)
    //     this->n_paren_zero_i = new INTTYPE_REST[degree];

    if (this->n_paren_i_minus_one == NULL)
        this->n_paren_i_minus_one = new INTTYPE_REST[degree];

    if (this->n_i_arrow_minus_one == NULL)
        this->n_i_arrow_minus_one = new INTTYPE_REST[degree];

    if (this->n_minus_one_arrow_i == NULL)
        this->n_minus_one_arrow_i = new INTTYPE_REST[degree];

    // if (this->n_i_arrow_zero == NULL)
    //     this->n_i_arrow_zero = new INTTYPE_REST[degree];

    if (this->n_bracket_minus_one_paren_ii == NULL)
        this->n_bracket_minus_one_paren_ii = new INTTYPE_REST[degree];

    if (this->n_minus_one_arrow_paren_ii == NULL)
        this->n_minus_one_arrow_paren_ii = new INTTYPE_REST[degree];

    if (this->n_i_arrow_paren_circ_square == NULL)
        this->n_i_arrow_paren_circ_square = new INTTYPE_REST[degree];

    if (this->n_i_arrow_paren_circ_circ == NULL)
        this->n_i_arrow_paren_circ_circ = new INTTYPE_REST[degree];

    if (this->n_circ_arrow_paren_i_minus_one == NULL)
        this->n_circ_arrow_paren_i_minus_one = new INTTYPE_REST[degree];

    if (this->n_circ_arrow_minus_one_arrow_i == NULL)
        this->n_circ_arrow_minus_one_arrow_i = new INTTYPE_REST[degree];

    if (this->n_paren_i_circ_arrow_zero == NULL)
        this->n_paren_i_circ_arrow_zero = new INTTYPE_REST[degree];

    // if (this->n_paren_i_circ_arrow_minus_one == NULL)
    //     this->n_paren_i_circ_arrow_minus_one = new INTTYPE_REST[degree];

    if (this->n_circ_arrow_i_arrow_minus_one == NULL)
        this->n_circ_arrow_i_arrow_minus_one = new INTTYPE_REST[degree];

    if (this->n_i_arrow_paren_circ_minus_one == NULL)
        this->n_i_arrow_paren_circ_minus_one = new INTTYPE_REST[degree];

    if (this->n_circ_arrow_paren_ii == NULL)
        this->n_circ_arrow_paren_ii = new INTTYPE_REST[degree];

    if (this->n_i_arrow_minus_one_arrow_circ == NULL)
        this->n_i_arrow_minus_one_arrow_circ = new INTTYPE_REST[degree];

    if (this->n_paren_ii_arrow_circ == NULL)
        this->n_paren_ii_arrow_circ = new INTTYPE_REST[degree];

    if (this->n_paren_ii_arrow_minus_one == NULL)
        this->n_paren_ii_arrow_minus_one = new INTTYPE_REST[degree];

    if (this->n_i_arrow_i == NULL)
        this->n_i_arrow_i = new INTTYPE_REST[degree];

    // if (this->n_zero_arrow_i == NULL)
    //     this->n_zero_arrow_i = new INTTYPE_REST[degree];

    if (this->n_minus_one_arrow_i_arrow_i == NULL)
        this->n_minus_one_arrow_i_arrow_i = new INTTYPE_REST[degree];

    // if (this->n_zero_arrow_i_arrow_i == NULL)
    //     this->n_zero_arrow_i_arrow_i = new INTTYPE_REST[degree];

    if (this->n_circ_arrow_i_arrow_i == NULL)
        this->n_circ_arrow_i_arrow_i = new INTTYPE_REST[degree];

    if (this->n_i_arrow_circ_arrow_minus_one == NULL)
        this->n_i_arrow_circ_arrow_minus_one = new INTTYPE_REST[degree];

    // if (this->n_paren_i_circ_arrow_i == NULL)
    //     this->n_paren_i_circ_arrow_i = new INTTYPE_REST[degree];

    if (this->n_paren_circ_circ_arrow_i == NULL)
        this->n_paren_circ_circ_arrow_i = new INTTYPE_REST[degree];

    if (this->n_minus_one_arrow_i_arrow_circ == NULL)
        this->n_minus_one_arrow_i_arrow_circ = new INTTYPE_REST[degree];

    if (this->n_paren_i_minus_one_arrow_circ == NULL)
        this->n_paren_i_minus_one_arrow_circ = new INTTYPE_REST[degree];

    if (this->n_paren_circ_minus_one_arrow_i == NULL)
        this->n_paren_circ_minus_one_arrow_i = new INTTYPE_REST[degree];

    if (this->n_bracket_i_paren_circ_circ == NULL)
        this->n_bracket_i_paren_circ_circ = new INTTYPE_REST[degree];

    if (this->n_paren_i_paren_circ_circ == NULL)
        this->n_paren_i_paren_circ_circ = new INTTYPE_REST[degree];

    if (this->n_i_arrow_circ_arrow_circ == NULL)
        this->n_i_arrow_circ_arrow_circ = new INTTYPE_REST[degree];

    if (this->n_bracket_minus_one_paren_i_circ == NULL)
        this->n_bracket_minus_one_paren_i_circ = new INTTYPE_REST[degree];

    if (this->n_paren_minus_one_paren_i_circ == NULL)
        this->n_paren_minus_one_paren_i_circ = new INTTYPE_REST[degree];

    if (this->n_zero_arrow_i_arrow_circ == NULL)
        this->n_zero_arrow_i_arrow_circ = new INTTYPE_REST[degree];

    // if (this->n_bracket_zero_paren_ii == NULL)
    //     this->n_bracket_zero_paren_ii = new INTTYPE_REST[degree];

    if (this->n_bracket_circ_paren_ii == NULL)
        this->n_bracket_circ_paren_ii = new INTTYPE_REST[degree];

    if (this->n_paren_minus_one_paren_ii == NULL)
        this->n_paren_minus_one_paren_ii = new INTTYPE_REST[degree];

    // if (this->n_paren_zero_paren_ii == NULL)
    //     this->n_paren_zero_paren_ii = new INTTYPE_REST[degree];

    if (this->n_paren_circ_paren_ii == NULL)
        this->n_paren_circ_paren_ii = new INTTYPE_REST[degree];

    if (this->n_bracket_zero_paren_i_circ == NULL)
        this->n_bracket_zero_paren_i_circ = new INTTYPE_REST[degree];

    if (this->n_paren_zero_paren_i_circ == NULL)
        this->n_paren_zero_paren_i_circ = new INTTYPE_REST[degree];

    if (this->n_bracket_circ_paren_i_minus_one == NULL)
        this->n_bracket_circ_paren_i_minus_one = new INTTYPE_REST[degree];

    if (this->n_paren_circ_paren_i_minus_one == NULL)
        this->n_paren_circ_paren_i_minus_one = new INTTYPE_REST[degree];

    if (this->n_bracket_i_paren_circ_minus_one == NULL)
        this->n_bracket_i_paren_circ_minus_one = new INTTYPE_REST[degree];

    if (this->n_paren_i_paren_circ_minus_one == NULL)
        this->n_paren_i_paren_circ_minus_one = new INTTYPE_REST[degree];

    for (int i = 0; i < degree; i++){
        this->n_i[i] = 0;
        // this->n_i_circ[i] = 0;
        this->n_i_arrow_circ[i] = 0;
        this->n_circ_arrow_i[i] = 0;
        this->n_paren_ii[i] = 0;
        this->n_paren_i_circ[i] = 0;
        // this->n_paren_zero_i[i] = 0;
        this->n_paren_i_minus_one[i] = 0;
        this->n_i_arrow_minus_one[i] = 0;
        this->n_minus_one_arrow_i[i] = 0;
        // this->n_i_arrow_zero[i] = 0;
        this->n_bracket_minus_one_paren_ii[i] = 0;
        this->n_minus_one_arrow_paren_ii[i] = 0;
        this->n_i_arrow_paren_circ_square[i] = 0;
        this->n_i_arrow_paren_circ_circ[i] = 0;
        this->n_circ_arrow_paren_i_minus_one[i] = 0;
        this->n_circ_arrow_minus_one_arrow_i[i] = 0;
        this->n_paren_i_circ_arrow_zero[i] = 0;
        // this->n_paren_i_circ_arrow_minus_one[i] = 0;
        this->n_circ_arrow_i_arrow_minus_one[i] = 0;
        this->n_i_arrow_paren_circ_minus_one[i] = 0;
        this->n_circ_arrow_paren_ii[i] = 0;
        this->n_i_arrow_minus_one_arrow_circ[i] = 0;
        this->n_paren_ii_arrow_circ[i] = 0;
        this->n_paren_ii_arrow_minus_one[i] = 0;
        this->n_i_arrow_i[i] = 0;
        // this->n_zero_arrow_i[i] = 0;
        // this->n_zero_arrow_i_arrow_i[i] = 0;
        this->n_circ_arrow_i_arrow_i[i] = 0;
        this->n_minus_one_arrow_i_arrow_i[i] = 0;
        this->n_i_arrow_circ_arrow_minus_one[i] = 0;
        // this->n_paren_i_circ_arrow_i[i] = 0;
        this->n_paren_circ_circ_arrow_i[i] = 0;
        this->n_minus_one_arrow_i_arrow_circ[i] = 0;
        this->n_paren_i_minus_one_arrow_circ[i] = 0;
        this->n_paren_circ_minus_one_arrow_i[i] = 0;
        this->n_bracket_i_paren_circ_circ[i] = 0;
        this->n_paren_i_paren_circ_circ[i] = 0;
        this->n_i_arrow_circ_arrow_circ[i] = 0;
        this->n_bracket_minus_one_paren_i_circ[i] = 0;
        this->n_paren_minus_one_paren_i_circ[i] = 0;
        this->n_zero_arrow_i_arrow_circ[i] = 0;
        // this->n_bracket_zero_paren_ii[i] = 0;
        this->n_bracket_circ_paren_ii[i] = 0;
        this->n_paren_minus_one_paren_ii[i] = 0;
        // this->n_paren_zero_paren_ii[i] = 0;
        this->n_paren_circ_paren_ii[i] = 0;
        this->n_bracket_zero_paren_i_circ[i] = 0;
        this->n_paren_zero_paren_i_circ[i] = 0;
        this->n_bracket_circ_paren_i_minus_one[i] = 0;
        this->n_paren_circ_paren_i_minus_one[i] = 0;
        this->n_bracket_i_paren_circ_minus_one[i] = 0;
        this->n_paren_i_paren_circ_minus_one[i] = 0;
    }

    // for n_i_j, create lower triangular matrices; for easy indexing, create an empty pointer for index 0 and ignore it
    if (this->n_i_j == NULL) {
        this->n_i_j = new INTTYPE_REST*[degree];
        this->n_i_j[0] = NULL;
        for (int i = 1; i < degree; i++)
            this->n_i_j[i] = new INTTYPE_REST[i];
    }

    for (int i = 1; i < degree; i++){
        for (int j = 0; j < i; j++){
            this->n_i_j[i][j] = 0;
        }
    }

    // for n_i_arrow_j, we need to maintain a full matrix because it is not symmetric
    if (this->n_i_arrow_j == NULL){
        this->n_i_arrow_j = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_i_arrow_j[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_i_arrow_j[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_i_arrow_j[i][j] = 0;
        }
    }

    if (this->n_paren_i_paren_j_minus_one == NULL){
        this->n_paren_i_paren_j_minus_one = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_paren_i_paren_j_minus_one[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_paren_i_paren_j_minus_one[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_paren_i_paren_j_minus_one[i][j] = 0;
        }
    }

    if (this->n_bracket_i_paren_j_minus_one == NULL){
        this->n_bracket_i_paren_j_minus_one = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_bracket_i_paren_j_minus_one[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_bracket_i_paren_j_minus_one[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_bracket_i_paren_j_minus_one[i][j] = 0;
        }
    }

    if (this->n_i_arrow_minus_one_arrow_j == NULL){
        this->n_i_arrow_minus_one_arrow_j = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_i_arrow_minus_one_arrow_j[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_i_arrow_minus_one_arrow_j[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_i_arrow_minus_one_arrow_j[i][j] = 0;
        }
    }

    if (this->n_i_arrow_j_arrow_minus_one == NULL){
        this->n_i_arrow_j_arrow_minus_one = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_i_arrow_j_arrow_minus_one[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_i_arrow_j_arrow_minus_one[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_i_arrow_j_arrow_minus_one[i][j] = 0;
        }
    }

    if (this->n_i_arrow_paren_j_minus_one == NULL){
        this->n_i_arrow_paren_j_minus_one = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_i_arrow_paren_j_minus_one[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_i_arrow_paren_j_minus_one[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_i_arrow_paren_j_minus_one[i][j] = 0;
        }
    }

    if (this->n_paren_i_minus_one_arrow_j == NULL){
        this->n_paren_i_minus_one_arrow_j = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_paren_i_minus_one_arrow_j[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_paren_i_minus_one_arrow_j[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_paren_i_minus_one_arrow_j[i][j] = 0;
        }
    }

    if (this->n_paren_ii_arrow_j == NULL){
        this->n_paren_ii_arrow_j = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_paren_ii_arrow_j[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_paren_ii_arrow_j[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_paren_ii_arrow_j[i][j] = 0;
        }
    }

    if (this->n_i_arrow_j_arrow_j == NULL){
        this->n_i_arrow_j_arrow_j = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_i_arrow_j_arrow_j[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_i_arrow_j_arrow_j[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_i_arrow_j_arrow_j[i][j] = 0;
            }
        }

    if (this->n_bracket_i_paren_jj == NULL){
        this->n_bracket_i_paren_jj = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_bracket_i_paren_jj[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_bracket_i_paren_jj[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_bracket_i_paren_jj[i][j] = 0;
            }
        }

    if (this->n_paren_i_paren_jj == NULL){
        this->n_paren_i_paren_jj = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_paren_i_paren_jj[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_paren_i_paren_jj[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_paren_i_paren_jj[i][j] = 0;
            }
        }
        

    if (this->n_i_arrow_paren_jj == NULL){
        this->n_i_arrow_paren_jj = new INTTYPE_REST*[degree];
        for (int i = 0; i < degree; i++)
            this->n_i_arrow_paren_jj[i] = new INTTYPE_REST[degree];
    }
    
    for (int i = 0; i < degree; i++){
        for (int j = 0; j < degree; j++){
            if (j == i)
                this->n_i_arrow_paren_jj[i][j] = -1; // insist that the value is only valid if i != j
            else    
                this->n_i_arrow_paren_jj[i][j] = 0;
        }
    }
}

CountingArray::~CountingArray(){
    //std::cout << "Calling CountingArray destructor" << std::endl;
    delete [] this->n_i;
    // delete [] this->n_i_circ;
    delete [] this->n_i_arrow_circ;
    delete [] this->n_circ_arrow_i;
    delete [] this->n_paren_ii;
    delete [] this->n_paren_i_circ;
    // delete [] this->n_paren_zero_i;
    delete [] this->n_paren_i_minus_one;
    delete [] this->n_i_arrow_minus_one;
    delete [] this->n_minus_one_arrow_i;
    // delete [] this->n_i_arrow_zero;
    delete [] this->n_bracket_minus_one_paren_ii;
    delete [] this->n_minus_one_arrow_paren_ii;
    delete [] this->n_i_arrow_paren_circ_square;
    delete [] this->n_i_arrow_paren_circ_circ;
    delete [] this->n_circ_arrow_paren_i_minus_one;
    delete [] this->n_circ_arrow_minus_one_arrow_i;
    delete [] this->n_paren_i_circ_arrow_zero;
    // delete [] this->n_paren_i_circ_arrow_minus_one;
    delete [] this->n_circ_arrow_i_arrow_minus_one;
    delete [] this->n_i_arrow_paren_circ_minus_one;
    delete [] this->n_circ_arrow_paren_ii;
    delete [] this->n_i_arrow_minus_one_arrow_circ;
    delete [] this->n_paren_ii_arrow_circ;
    delete [] this->n_paren_ii_arrow_minus_one;
    delete [] this->n_i_arrow_i;
    // delete [] this->n_zero_arrow_i;
    delete [] this->n_minus_one_arrow_i_arrow_i;
    // delete [] this->n_zero_arrow_i_arrow_i;
    delete [] this->n_circ_arrow_i_arrow_i;
    delete [] this->n_i_arrow_circ_arrow_minus_one;
    // delete [] this->n_paren_i_circ_arrow_i;
    delete [] this->n_paren_circ_circ_arrow_i;
    delete [] this->n_minus_one_arrow_i_arrow_circ;
    delete [] this->n_paren_i_minus_one_arrow_circ;
    delete [] this->n_paren_circ_minus_one_arrow_i;
    delete [] this->n_bracket_i_paren_circ_circ;
    delete [] this->n_paren_i_paren_circ_circ;
    delete [] this->n_i_arrow_circ_arrow_circ;
    delete [] this->n_bracket_minus_one_paren_i_circ;
    delete [] this->n_paren_minus_one_paren_i_circ;
    delete [] this->n_zero_arrow_i_arrow_circ;
    // delete [] this->n_bracket_zero_paren_ii;
    delete [] this->n_bracket_circ_paren_ii;
    delete [] this->n_paren_minus_one_paren_ii;
    // delete [] this->n_paren_zero_paren_ii;
    delete [] this->n_paren_circ_paren_ii;
    delete [] this->n_bracket_zero_paren_i_circ;
    delete [] this->n_paren_zero_paren_i_circ;
    delete [] this->n_bracket_circ_paren_i_minus_one;
    delete [] this->n_paren_circ_paren_i_minus_one;
    delete [] this->n_bracket_i_paren_circ_minus_one;
    delete [] this->n_paren_i_paren_circ_minus_one;

    delete [] this->n_i_arrow_j[0];
    delete [] this->n_paren_i_paren_j_minus_one[0];
    delete [] this->n_bracket_i_paren_j_minus_one[0];
    delete [] this->n_i_arrow_minus_one_arrow_j[0];
    delete [] this->n_i_arrow_j_arrow_minus_one[0];
    delete [] this->n_i_arrow_paren_j_minus_one[0];
    delete [] this->n_paren_i_minus_one_arrow_j[0];
    delete [] this->n_paren_ii_arrow_j[0];
    delete [] this->n_i_arrow_j_arrow_j[0];
    delete [] this->n_bracket_i_paren_jj[0];
    delete [] this->n_paren_i_paren_jj[0];
    delete [] this->n_i_arrow_paren_jj[0];

    for (int i = 1; i < this->degree; i++){
        delete [] this->n_i_j[i];
        delete [] this->n_i_arrow_j[i];
        delete [] this->n_paren_i_paren_j_minus_one[i];
        delete [] this->n_bracket_i_paren_j_minus_one[i];
        delete [] this->n_i_arrow_minus_one_arrow_j[i];
        delete [] this->n_i_arrow_j_arrow_minus_one[i];
        delete [] this->n_i_arrow_paren_j_minus_one[i];
        delete [] this->n_paren_i_minus_one_arrow_j[i];
        delete [] this->n_paren_ii_arrow_j[i];
        delete [] this->n_i_arrow_j_arrow_j[i];
        delete [] this->n_bracket_i_paren_jj[i];
        delete [] this->n_paren_i_paren_jj[i];
        delete [] this->n_i_arrow_paren_jj[i];
    }
    delete [] this->n_i_j;
    delete [] this->n_i_arrow_j;  
    delete [] this->n_paren_i_paren_j_minus_one;
    delete [] this->n_bracket_i_paren_j_minus_one;
    delete [] this->n_i_arrow_minus_one_arrow_j;
    delete [] this->n_i_arrow_j_arrow_minus_one;
    delete [] this->n_i_arrow_paren_j_minus_one;
    delete [] this->n_paren_i_minus_one_arrow_j;
    delete [] this->n_paren_ii_arrow_j;
    delete [] this->n_i_arrow_j_arrow_j;
    delete [] this->n_bracket_i_paren_jj;
    delete [] this->n_paren_i_paren_jj;
    delete [] this->n_i_arrow_paren_jj;
}

CountingArray::CountingArray(){
    this->n_i = this->n_paren_ii = this->n_i_arrow_circ = this->n_paren_i_circ = this->n_i_arrow_minus_one = this->n_bracket_minus_one_paren_ii = 
    this->n_paren_minus_one_paren_ii = this->n_bracket_minus_one_paren_i_circ = this->n_bracket_zero_paren_i_circ = 
    this->n_paren_zero_paren_i_circ = this->n_bracket_circ_paren_ii = this->n_paren_circ_paren_ii = this->n_paren_i_minus_one = 
    this->n_bracket_circ_paren_i_minus_one = this->n_paren_circ_paren_i_minus_one = 
    this->n_minus_one_arrow_i = this->n_circ_arrow_i = this->n_bracket_i_paren_circ_minus_one = this->n_paren_i_paren_circ_minus_one =
    this->n_minus_one_arrow_paren_ii = this->n_i_arrow_paren_circ_square = this->n_i_arrow_paren_circ_circ = this->n_circ_arrow_paren_i_minus_one =
    this->n_circ_arrow_minus_one_arrow_i = this->n_paren_i_circ_arrow_zero = 
    this->n_paren_circ_circ_arrow_i = this->n_circ_arrow_i_arrow_minus_one = this->n_i_arrow_paren_circ_minus_one = this->n_circ_arrow_paren_ii = 
    this->n_i_arrow_minus_one_arrow_circ = this->n_paren_ii_arrow_circ = this->n_paren_ii_arrow_minus_one = this->n_minus_one_arrow_i_arrow_i = 
    this->n_i_arrow_circ_arrow_minus_one = this->n_i_arrow_i /*= this->n_zero_arrow_i*/ = this->n_minus_one_arrow_i_arrow_circ = 
    this->n_zero_arrow_i_arrow_circ = this->n_paren_circ_minus_one_arrow_i = this->n_paren_i_minus_one_arrow_circ = this->n_circ_arrow_i_arrow_i = 
    this->n_bracket_i_paren_circ_circ = this->n_paren_i_paren_circ_circ = this->n_i_arrow_circ_arrow_circ = this->n_paren_minus_one_paren_i_circ = NULL;

    this->n_i_j = this->n_i_arrow_j = this->n_paren_i_paren_j_minus_one = this->n_bracket_i_paren_j_minus_one = this->n_i_arrow_minus_one_arrow_j = 
    this->n_i_arrow_j_arrow_minus_one = this->n_i_arrow_paren_j_minus_one = this->n_paren_i_minus_one_arrow_j = this->n_paren_ii_arrow_j = 
    this->n_i_arrow_paren_jj = this->n_i_arrow_j_arrow_j = this->n_bracket_i_paren_jj = this->n_paren_i_paren_jj = NULL;
}


INTTYPE_REST CountingArray::get_n_ij(unsigned int i, unsigned int j){
    unsigned int i_star, j_star;
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
    if (i > j){
        i_star = i;
        j_star = j;
    } else {
        i_star = j;
        j_star = i;
    }

    return this->n_i_j[i_star][j_star];
}
INTTYPE_REST CountingArray::get_n_i_arrow_j(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_i_arrow_j[i][j];
}
        
bool CountingArray::set_n_ij(unsigned int i, unsigned int j, INTTYPE_REST v){
    /*if ( i >= this->degree || j >= this->degree || i == j){
        return false; // invalid case!
    }*/
    
    unsigned int i_star, j_star;
    if (i > j){
        i_star = i;
        j_star = j;
    } else {
        i_star = j;
        j_star = i;
    }

    this->n_i_j[i_star][j_star] = v;
    return true; 
}

bool CountingArray::set_n_i_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_i_arrow_j[i][j] = v;
    return true; 
}
bool CountingArray::set_n_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i[i] = v;
    return true;
}
// bool CountingArray::set_n_i_circ(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_i_circ[i] = v;
//     return true;
// }
bool CountingArray::set_n_paren_ii(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_ii[i] = v;
    return true;
}
bool CountingArray::set_n_i_arrow_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i[i];    
}

// INTTYPE_REST CountingArray::get_n_i_circ(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_i_circ[i];    
// }

INTTYPE_REST CountingArray::get_n_paren_ii(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_ii[i];    
}

INTTYPE_REST CountingArray::get_n_i_arrow_circ(unsigned int i){
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_circ[i];    
}

//added by shayesteh99

bool CountingArray::set_n_paren_i_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_i_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_i_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_i_circ[i];    
}

// bool CountingArray::set_n_paren_zero_i(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_paren_zero_i[i] = v;
//     return true;
// }

// INTTYPE_REST CountingArray::get_n_paren_zero_i(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_paren_zero_i[i];    
// }

bool CountingArray::set_n_paren_i_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_i_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_i_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_i_minus_one[i];    
}

bool CountingArray::set_n_i_arrow_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i_arrow_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_minus_one[i];    
}

bool CountingArray::set_n_minus_one_arrow_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_minus_one_arrow_i[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_minus_one_arrow_i(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_minus_one_arrow_i[i];    
}

// bool CountingArray::set_n_i_arrow_zero(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_i_arrow_zero[i] = v;
//     return true;
// }

// INTTYPE_REST CountingArray::get_n_i_arrow_zero(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_i_arrow_zero[i];    
// }

bool CountingArray::set_n_bracket_minus_one_paren_ii(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_bracket_minus_one_paren_ii[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_bracket_minus_one_paren_ii(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_bracket_minus_one_paren_ii[i];    
}

// bool CountingArray::set_n_bracket_zero_paren_ii(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_bracket_zero_paren_ii[i] = v;
//     return true;
// }

// INTTYPE_REST CountingArray::get_n_bracket_zero_paren_ii(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_bracket_zero_paren_ii[i];    
// }

bool CountingArray::set_n_bracket_circ_paren_ii(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_bracket_circ_paren_ii[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_bracket_circ_paren_ii(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_bracket_circ_paren_ii[i];    
}

bool CountingArray::set_n_paren_minus_one_paren_ii(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_minus_one_paren_ii[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_minus_one_paren_ii(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_minus_one_paren_ii[i];    
}

// bool CountingArray::set_n_paren_zero_paren_ii(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_paren_zero_paren_ii[i] = v;
//     return true;
// }

// INTTYPE_REST CountingArray::get_n_paren_zero_paren_ii(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_paren_zero_paren_ii[i];    
// }

bool CountingArray::set_n_paren_circ_paren_ii(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_circ_paren_ii[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_circ_paren_ii(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_circ_paren_ii[i];    
}

bool CountingArray::set_n_bracket_zero_paren_i_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_bracket_zero_paren_i_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_bracket_zero_paren_i_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_bracket_zero_paren_i_circ[i];    
}

bool CountingArray::set_n_paren_zero_paren_i_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_zero_paren_i_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_zero_paren_i_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_zero_paren_i_circ[i];    
}

bool CountingArray::set_n_bracket_circ_paren_i_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_bracket_circ_paren_i_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_bracket_circ_paren_i_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_bracket_circ_paren_i_minus_one[i];    
}

bool CountingArray::set_n_paren_circ_paren_i_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_circ_paren_i_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_circ_paren_i_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_circ_paren_i_minus_one[i];    
}

bool CountingArray::set_n_circ_arrow_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_circ_arrow_i[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_circ_arrow_i(unsigned int i){
    if ( i >= this->degree)
        return -1;
    return this->n_circ_arrow_i[i];    
}

bool CountingArray::set_n_bracket_i_paren_circ_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_bracket_i_paren_circ_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_bracket_i_paren_circ_minus_one(unsigned int i){
    if ( i >= this->degree)
        return -1;
    return this->n_bracket_i_paren_circ_minus_one[i];    
}

bool CountingArray::set_n_paren_i_paren_circ_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_i_paren_circ_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_i_paren_circ_minus_one(unsigned int i){
    if ( i >= this->degree)
        return -1;
    return this->n_paren_i_paren_circ_minus_one[i];    
}

bool CountingArray::set_n_minus_one_arrow_paren_ii(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_minus_one_arrow_paren_ii[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_minus_one_arrow_paren_ii(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_minus_one_arrow_paren_ii[i];    
}

bool CountingArray::set_n_i_arrow_paren_circ_square(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_paren_circ_square[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i_arrow_paren_circ_square(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_paren_circ_square[i];    
}

bool CountingArray::set_n_i_arrow_paren_circ_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_paren_circ_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i_arrow_paren_circ_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_paren_circ_circ[i];    
}

bool CountingArray::set_n_circ_arrow_paren_i_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_circ_arrow_paren_i_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_circ_arrow_paren_i_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_circ_arrow_paren_i_minus_one[i];    
}

bool CountingArray::set_n_circ_arrow_minus_one_arrow_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_circ_arrow_minus_one_arrow_i[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_circ_arrow_minus_one_arrow_i(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_circ_arrow_minus_one_arrow_i[i];    
}

bool CountingArray::set_n_paren_i_circ_arrow_zero(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_i_circ_arrow_zero[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_i_circ_arrow_zero(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_i_circ_arrow_zero[i];    
}

// bool CountingArray::set_n_paren_i_circ_arrow_minus_one(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_paren_i_circ_arrow_minus_one[i] = v;
//     return true;
// }

// INTTYPE_REST CountingArray::get_n_paren_i_circ_arrow_minus_one(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_paren_i_circ_arrow_minus_one[i];    
// }

bool CountingArray::set_n_circ_arrow_i_arrow_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_circ_arrow_i_arrow_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_circ_arrow_i_arrow_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_circ_arrow_i_arrow_minus_one[i];    
}

bool CountingArray::set_n_i_arrow_paren_circ_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_paren_circ_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i_arrow_paren_circ_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_paren_circ_minus_one[i];    
}

bool CountingArray::set_n_circ_arrow_paren_ii(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_circ_arrow_paren_ii[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_circ_arrow_paren_ii(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_circ_arrow_paren_ii[i];    
}

bool CountingArray::set_n_i_arrow_minus_one_arrow_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_minus_one_arrow_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i_arrow_minus_one_arrow_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_minus_one_arrow_circ[i];    
}

bool CountingArray::set_n_paren_ii_arrow_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_ii_arrow_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_ii_arrow_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_ii_arrow_circ[i];    
}

bool CountingArray::set_n_paren_ii_arrow_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_ii_arrow_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_ii_arrow_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_ii_arrow_minus_one[i];    
}

bool CountingArray::set_n_i_arrow_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_i[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i_arrow_i(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_i[i];    
}

// bool CountingArray::set_n_zero_arrow_i(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_zero_arrow_i[i] = v;
//     return true;
// }

// INTTYPE_REST CountingArray::get_n_zero_arrow_i(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_zero_arrow_i[i];    
// }

bool CountingArray::set_n_minus_one_arrow_i_arrow_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_minus_one_arrow_i_arrow_i[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_minus_one_arrow_i_arrow_i(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_minus_one_arrow_i_arrow_i[i];    
}

// bool CountingArray::set_n_zero_arrow_i_arrow_i(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_zero_arrow_i_arrow_i[i] = v;
//     return true;
// }

// INTTYPE_REST CountingArray::get_n_zero_arrow_i_arrow_i(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_zero_arrow_i_arrow_i[i];    
// }

bool CountingArray::set_n_circ_arrow_i_arrow_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_circ_arrow_i_arrow_i[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_circ_arrow_i_arrow_i(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_circ_arrow_i_arrow_i[i];    
}

bool CountingArray::set_n_i_arrow_circ_arrow_minus_one(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_circ_arrow_minus_one[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i_arrow_circ_arrow_minus_one(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_circ_arrow_minus_one[i];    
}

// bool CountingArray::set_n_paren_i_circ_arrow_i(unsigned int i, INTTYPE_REST v){
//     if (i >= this->degree)
//         return false;
//     this->n_paren_i_circ_arrow_i[i] = v;
//     return true;
// }

// INTTYPE_REST CountingArray::get_n_paren_i_circ_arrow_i(unsigned int i)
// {
//     if ( i >= this->degree)
//         return -1;
//     return this->n_paren_i_circ_arrow_i[i];    
// }

bool CountingArray::set_n_paren_circ_circ_arrow_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_circ_circ_arrow_i[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_circ_circ_arrow_i(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_circ_circ_arrow_i[i];    
}

bool CountingArray::set_n_minus_one_arrow_i_arrow_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_minus_one_arrow_i_arrow_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_minus_one_arrow_i_arrow_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_minus_one_arrow_i_arrow_circ[i];    
}

bool CountingArray::set_n_zero_arrow_i_arrow_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_zero_arrow_i_arrow_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_zero_arrow_i_arrow_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_zero_arrow_i_arrow_circ[i];    
}

bool CountingArray::set_n_paren_i_minus_one_arrow_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_i_minus_one_arrow_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_i_minus_one_arrow_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_i_minus_one_arrow_circ[i];    
}

bool CountingArray::set_n_paren_circ_minus_one_arrow_i(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_circ_minus_one_arrow_i[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_circ_minus_one_arrow_i(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_circ_minus_one_arrow_i[i];    
}

bool CountingArray::set_n_bracket_i_paren_circ_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_bracket_i_paren_circ_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_bracket_i_paren_circ_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_bracket_i_paren_circ_circ[i];    
}

bool CountingArray::set_n_paren_i_paren_circ_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_i_paren_circ_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_i_paren_circ_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_i_paren_circ_circ[i];    
}

bool CountingArray::set_n_i_arrow_circ_arrow_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_i_arrow_circ_arrow_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_i_arrow_circ_arrow_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_i_arrow_circ_arrow_circ[i];    
}


INTTYPE_REST CountingArray::get_n_paren_i_paren_j_minus_one(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_paren_i_paren_j_minus_one[i][j];
}

bool CountingArray::set_n_paren_i_paren_j_minus_one(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_paren_i_paren_j_minus_one[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_bracket_i_paren_j_minus_one(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_bracket_i_paren_j_minus_one[i][j];
}

bool CountingArray::set_n_bracket_i_paren_j_minus_one(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_bracket_i_paren_j_minus_one[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_i_arrow_minus_one_arrow_j(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_i_arrow_minus_one_arrow_j[i][j];
}

bool CountingArray::set_n_i_arrow_minus_one_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_i_arrow_minus_one_arrow_j[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_i_arrow_j_arrow_minus_one(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_i_arrow_j_arrow_minus_one[i][j];
}

bool CountingArray::set_n_i_arrow_j_arrow_minus_one(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_i_arrow_j_arrow_minus_one[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_i_arrow_paren_j_minus_one(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_i_arrow_paren_j_minus_one[i][j];
}

bool CountingArray::set_n_i_arrow_paren_j_minus_one(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_i_arrow_paren_j_minus_one[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_paren_i_minus_one_arrow_j(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_paren_i_minus_one_arrow_j[i][j];
}

bool CountingArray::set_n_paren_i_minus_one_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_paren_i_minus_one_arrow_j[i][j] = v;
    return true; 
}

bool CountingArray::set_n_bracket_minus_one_paren_i_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_bracket_minus_one_paren_i_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_bracket_minus_one_paren_i_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_bracket_minus_one_paren_i_circ[i];    
}

bool CountingArray::set_n_paren_minus_one_paren_i_circ(unsigned int i, INTTYPE_REST v){
    if (i >= this->degree)
        return false;
    this->n_paren_minus_one_paren_i_circ[i] = v;
    return true;
}

INTTYPE_REST CountingArray::get_n_paren_minus_one_paren_i_circ(unsigned int i)
{
    if ( i >= this->degree)
        return -1;
    return this->n_paren_minus_one_paren_i_circ[i];    
}

INTTYPE_REST CountingArray::get_n_paren_ii_arrow_j(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_paren_ii_arrow_j[i][j];
}

bool CountingArray::set_n_paren_ii_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_paren_ii_arrow_j[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_i_arrow_j_arrow_j(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_i_arrow_j_arrow_j[i][j];
}

bool CountingArray::set_n_i_arrow_j_arrow_j(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_i_arrow_j_arrow_j[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_i_arrow_paren_jj(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_i_arrow_paren_jj[i][j];
}

bool CountingArray::set_n_i_arrow_paren_jj(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_i_arrow_paren_jj[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_bracket_i_paren_jj(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_bracket_i_paren_jj[i][j];
}

bool CountingArray::set_n_bracket_i_paren_jj(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_bracket_i_paren_jj[i][j] = v;
    return true; 
}

INTTYPE_REST CountingArray::get_n_paren_i_paren_jj(unsigned int i, unsigned int j){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return -1; // invalid case!
    }
*/    
    return this->n_paren_i_paren_jj[i][j];
}

bool CountingArray::set_n_paren_i_paren_jj(unsigned int i, unsigned int j, INTTYPE_REST v){
/*
    if ( i >= this->degree || j >= this->degree || i == j){
        std::cout << "INVALID CASE!" << std::endl;
        std::cout << "i = " << i << " j = " << j << std::endl;
        return false; // invalid case!
    }
*/    
    this->n_paren_i_paren_jj[i][j] = v;
    return true; 
}

