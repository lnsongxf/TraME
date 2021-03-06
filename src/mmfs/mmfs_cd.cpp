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
 * Cobb-Douglas (CD) Marriage Matching Functions (MMFs) class
 * Corresponds to LTU transfers class
 *
 * Keith O'Hara
 * 08/15/2016
 *
 * This version:
 * 03/27/2017
 */

#include "trame.hpp"

void 
trame::mmfs::cd::build(const arma::mat& lambda_inp, const arma::mat& phi_inp, bool need_norm_inp)
{
    need_norm = need_norm_inp;

    nbX = lambda_inp.n_rows;
    nbY = lambda_inp.n_cols;
    nbParams = 2*nbX*nbY;

    lambda = lambda_inp;
    phi = phi_inp;

    aux_zeta = 1 - lambda_inp;
    aux_phi_exp = arma::exp(phi_inp);
}

void 
trame::mmfs::cd::trans()
{
    int nbX_temp = nbX;

    nbX = nbY;
    nbY = nbX_temp;
    //
    arma::mat lambda_temp;

    lambda = aux_zeta.t();
    aux_zeta = lambda_temp.t();

    phi = phi.t();
    aux_phi_exp = aux_phi_exp.t();
    //
}

//
// MFE-related functions

// matching function

arma::mat 
trame::mmfs::cd::M(const arma::mat& a_xs, const arma::mat& b_ys)
const
{
    arma::mat ret = this->M(a_xs,b_ys,NULL,NULL);
    //
    return ret;
}

arma::mat 
trame::mmfs::cd::M(const arma::mat& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat term_1 = arma::exp(elem_prod(lambda(x_ind,y_ind), arma::log(a_xs)));
    arma::mat term_2 = arma::trans(arma::exp( elem_prod(arma::trans(aux_zeta(x_ind,y_ind)), arma::log(b_ys)) ));
    arma::mat term_3 = aux_phi_exp(x_ind,y_ind);

    arma::mat ret = term_1 % term_2 % term_3;
    //
    return ret;
}

arma::mat 
trame::mmfs::cd::M(const double& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, (int) nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, (int) nbY-1);
    //
    arma::mat term_1 = arma::exp(lambda(x_ind,y_ind) * std::log(a_xs));
    arma::mat term_2 = arma::trans(arma::exp( elem_prod(arma::trans(aux_zeta(x_ind,y_ind)), arma::log(b_ys)) ));
    arma::mat term_3 = aux_phi_exp(x_ind,y_ind);

    arma::mat ret = term_1 % term_2 % term_3;
    //
    return ret;
}

arma::mat 
trame::mmfs::cd::M(const arma::mat& a_xs, const double& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, (int) nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, (int) nbY-1);
    //
    arma::mat term_1 = arma::exp(elem_prod(lambda(x_ind,y_ind), arma::log(a_xs)));
    arma::mat term_2 = arma::exp(aux_zeta(x_ind,y_ind) * std::log(b_ys));
    arma::mat term_3 = aux_phi_exp(x_ind,y_ind);
        
    arma::mat ret = term_1 % term_2 % term_3;
    //
    return ret;
}

//

arma::mat 
trame::mmfs::cd::dmu_x0(const arma::mat& a_xs, const arma::mat& b_ys)
const
{
    arma::mat term_1 = elem_prod( lambda, arma::exp(elem_prod(lambda - 1.0, arma::log(a_xs))) );
    arma::mat term_2 = arma::trans(arma::exp( elem_prod(arma::trans(aux_zeta), arma::log(b_ys)) ));
    arma::mat term_3 = aux_phi_exp;

    arma::mat ret = term_1 % term_2 % term_3;
    //
    return ret;
}

arma::mat 
trame::mmfs::cd::dmu_0y(const arma::mat& a_xs, const arma::mat& b_ys)
const
{
    arma::mat term_1 = arma::exp(elem_prod(lambda, arma::log(a_xs)));
    arma::mat term_2 = elem_prod(aux_zeta, arma::trans(arma::exp( elem_prod(arma::trans(aux_zeta) - 1.0, arma::log(b_ys)))) );
    arma::mat term_3 = aux_phi_exp;

    arma::mat ret = term_1 % term_2 % term_3;
    //
    return ret;
}

arma::mat 
trame::mmfs::cd::dparams_M(const arma::mat& a_xs, const arma::mat& b_ys)
const
{
    return this->dparams_M(a_xs,b_ys,NULL);
}

arma::mat 
trame::mmfs::cd::dparams_M(const arma::mat& a_xs, const arma::mat& b_ys, const arma::mat* delta_params_M)
const
{
    arma::mat term_1 = arma::exp(elem_prod(lambda, arma::log(a_xs)));
    arma::mat term_2 = arma::trans(arma::exp( elem_prod(arma::trans(aux_zeta), arma::log(b_ys)) ));
    arma::mat term_3 = aux_phi_exp;

    arma::mat log_ratio = arma::log(a_xs * arma::trans(1.0 / b_ys));

    arma::mat der_1 = log_ratio % term_1 % term_2 % term_3;
    arma::mat der_2 = term_1 % term_2;

    arma::mat ret;

    if (delta_params_M) {
        arma::mat delta_params_1 = arma::reshape((*delta_params_M).rows(0,nbX*nbY-1),nbX,nbY);
        arma::mat delta_params_2 = arma::reshape((*delta_params_M).rows(nbX*nbY,2*nbX*nbY-1),nbX,nbY);

        ret = arma::vectorise(delta_params_1 % der_1 + delta_params_2 % der_2);
    } else {
        ret = arma::join_rows( arma::diagmat(arma::vectorise(der_1)), arma::diagmat(arma::vectorise(der_2)) );
    }
    //
    return ret;
}

arma::mat 
trame::mmfs::cd::Mx0(const arma::mat& a_x)
const
{
    return a_x;
}

arma::mat 
trame::mmfs::cd::M0y(const arma::mat& b_y)
const
{
    return b_y;
}
