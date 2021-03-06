/*################################################################################
  ##
  ##   Copyright (C) 2015 - 2017 the TraME Team:
  ##      Alfred Galichon
  ##      Keith O'Hara
  ##
  ##   This file is part of TraME.
  ##
  ##   TraME is free software: you can redistribute it and/or modify
  ##   it under the terms of the GNU General Public License as published by
  ##   the Free Software Foundation, either version 2 of the License, or
  ##   (at your option) any later version.
  ##
  ##   TraME is distributed in the hope that it will be useful,
  ##   but WITHOUT ANY WARRANTY; without even the implied warranty of
  ##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  ##   GNU General Public License for more details.
  ##
  ##   You should have received a copy of the GNU General Public License
  ##   along with TraME. If not, see <http://www.gnu.org/licenses/>.
  ##
  ################################################################################*/

/*
 * Leontief Marriage Matching Functions (MMFs) class
 * Corresponds to NTU transfers class
 *
 * Keith O'Hara
 * 08/15/2016
 *
 * This version:
 * 03/27/2017
 */

#include "trame.hpp"

void 
trame::mmfs::min::build(const arma::mat& alpha_NTU, const arma::mat& gamma_NTU, bool need_norm_NTU)
{
    need_norm = need_norm_NTU;

    nbX = alpha_NTU.n_rows;
    nbY = alpha_NTU.n_cols;
    nbParams = 2*nbX*nbY;

    alpha = alpha_NTU;
    gamma = gamma_NTU;

    aux_alpha_exp = arma::exp(alpha_NTU);
    aux_gamma_exp = arma::exp(gamma_NTU);
}

void 
trame::mmfs::min::trans()
{
    int nbX_temp = nbX;

    nbX = nbY;
    nbY = nbX_temp;
    //
    arma::mat alpha_temp = alpha;
    arma::mat aux_alpha_exp_temp = aux_alpha_exp;

    alpha = gamma.t();
    gamma = alpha_temp.t();

    aux_alpha_exp = aux_gamma_exp.t();
    aux_gamma_exp = aux_alpha_exp_temp.t();
    //
}

//
// MFE-related functions

arma::mat 
trame::mmfs::min::M(const arma::mat& a_xs, const arma::mat& b_ys)
const
{
    arma::mat ret = this->M(a_xs,b_ys,NULL,NULL);
    //
    return ret;
}

arma::mat 
trame::mmfs::min::M(const arma::mat& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat term_1 = elem_prod(a_xs, aux_alpha_exp(x_ind,y_ind));
    arma::mat term_2 = arma::trans( elem_prod(b_ys, arma::trans(aux_alpha_exp(x_ind,y_ind))) );

    arma::mat ret = arma::min(term_1, term_2);
    //
    return ret;
}

arma::mat 
trame::mmfs::min::M(const double& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, (int) nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, (int) nbY-1);
    //
    arma::mat term_1 = a_xs * aux_alpha_exp(x_ind,y_ind);
    arma::mat term_2 = arma::trans( elem_prod(b_ys, arma::trans(aux_alpha_exp(x_ind,y_ind))) );

    arma::mat ret = arma::min(term_1, term_2);
    //
    return ret;
}

arma::mat 
trame::mmfs::min::M(const arma::mat& a_xs, const double& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, (int) nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, (int) nbY-1);
    //
    arma::mat term_1 = elem_prod(a_xs, aux_alpha_exp(x_ind,y_ind));
    arma::mat term_2 = b_ys * aux_alpha_exp(x_ind,y_ind);

    arma::mat ret = arma::min(term_1, term_2);
    //
    return ret;
}

arma::mat 
trame::mmfs::min::Mx0(const arma::mat& a_x)
const
{
    return a_x;
}

arma::mat 
trame::mmfs::min::M0y(const arma::mat& b_y)
const
{
    return b_y;
}
