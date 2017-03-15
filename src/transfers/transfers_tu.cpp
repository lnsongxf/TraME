/*################################################################################
  ##
  ##   Copyright (C) 2015 - 2017 the TraME Team:
  ##      Alfred Galichon
  ##      Keith O'Hara
  ##      Simon Weber
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
 * TU transfers class
 *
 * Keith O'Hara
 * 08/15/2016
 *
 * This version:
 * 03/12/2017
 */

#include "trame.hpp"

void trame::tu::build(const arma::mat& phi_TU, bool need_norm_TU)
{
    need_norm = need_norm_TU;

    nbX = phi_TU.n_rows;
    nbY = phi_TU.n_cols;
    nbParams = nbX*nbY;

    phi = phi_TU;
    aux_phi_exp = arma::exp(phi_TU / 2.0);
}

void trame::tu::trans()
{
    int nbX_temp = nbX;

    nbX = nbY;
    nbY = nbX_temp;
    
    phi = phi.t();
    aux_phi_exp = aux_phi_exp.t();
}

//
// MFE-related functions

arma::mat trame::tu::M(const arma::mat& a_xs, const arma::mat& b_ys)
const
{
    arma::mat ret = this->M(a_xs,b_ys,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::M(const arma::mat& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat term_1 = aux_phi_exp(x_ind,y_ind);
    arma::mat term_2 = arma::sqrt(a_xs * b_ys.t());

    arma::mat ret = term_1 % term_2;
    //
    return ret;
}

arma::mat trame::tu::M(const double& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat term_1 = aux_phi_exp(x_ind,y_ind);
    arma::mat term_2 = arma::sqrt(a_xs * b_ys.t());

    arma::mat ret = term_1 % term_2;
    //
    return ret;
}

arma::mat trame::tu::M(const arma::mat& a_xs, const double& b_ys, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1); 
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat term_1 = aux_phi_exp(x_ind,y_ind);
    arma::mat term_2 = arma::sqrt(a_xs * b_ys);

    arma::mat ret = term_1 % term_2;
    //
    return ret;
}

arma::mat trame::tu::Mx0(const arma::mat& a_x)
const
{
    return a_x;
}

arma::mat trame::tu::M0y(const arma::mat& b_y)
const
{
    return b_y;
}

//
// DSE-related functions

arma::mat trame::tu::Psi(const arma::mat& U, const arma::mat& V)
const
{
    arma::mat ret = this->Psi(U,V,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::Psi(const arma::mat& U, const arma::mat& V, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = (U + V - phi(x_ind,y_ind)) / 2;
    //
    return ret;
}

arma::mat trame::tu::Psi(const double& U, const arma::mat& V, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = (U + V - phi(x_ind,y_ind)) / 2;
    //
    return ret;
}

arma::mat trame::tu::Psi(const arma::mat& U, const double& V, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = (U + V - phi(x_ind,y_ind)) / 2;
    //
    return ret;
}

double trame::tu::Psi(const double& U, const double& V, int x_ind, int y_ind)
const
{
    double ret = (U + V - phi(x_ind,y_ind)) / 2;
    //
    return ret;
}

arma::mat trame::tu::du_Psi(const arma::mat& U, const arma::mat& V)
const
{
    arma::mat ret = this->du_Psi(U,V,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::du_Psi(const arma::mat& U, const arma::mat& V, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret(x_ind.n_elem,y_ind.n_elem);
    ret.fill(0.5);
    //
    return ret;
}

arma::mat trame::tu::du_Psi(const double& U, const arma::mat& V, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret(x_ind.n_elem,y_ind.n_elem);
    ret.fill(0.5);
    //
    return ret;
}

arma::mat trame::tu::du_Psi(const arma::mat& U, const double& V, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret(x_ind.n_elem,y_ind.n_elem);
    ret.fill(0.5);
    //
    return ret;
}

arma::mat trame::tu::dtheta_Psi(const arma::mat& U, const arma::mat& V, const arma::mat& dtheta)
{
    arma::mat ret = this->dtheta_Psi(U,V,&dtheta);
    //
    return ret;
}

arma::mat trame::tu::dtheta_Psi(const arma::mat& U, const arma::mat& V, const arma::mat* dtheta)
{
    arma::mat ret(nbX,nbY);
    //
    if (!dtheta) {
        ret = - 0.5*arma::eye(nbX*nbY,nbX*nbY);
    } else {
        ret = - (*dtheta)/2;
    }
    //
    return ret;
}

arma::mat trame::tu::Ucal(const arma::mat& vs)
const
{
    arma::mat ret = this->Ucal(vs,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::Ucal(const arma::mat& vs, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = phi(x_ind,y_ind) - vs;
    //
    return ret;
}

double trame::tu::Ucal(const double& vs, int xs, int ys)
const
{
    double ret = phi(xs,ys) - vs;
    //
    return ret;
}

arma::mat trame::tu::Vcal(const arma::mat& us)
const
{
    arma::mat ret = this->Vcal(us,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::Vcal(const arma::mat& us, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = phi(x_ind,y_ind) - us;
    //
    return ret;
}

double trame::tu::Vcal(const double& us, int xs, int ys)
const
{
    double ret = phi(xs,ys) - us;
    //
    return ret;
}

arma::mat trame::tu::UW(const arma::mat& Ws)
const
{
    arma::mat ret = this->UW(Ws,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::UW(const arma::mat& Ws, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = - Psi(0.0,-Ws,&x_ind,&y_ind);
    //
    return ret;
}

double trame::tu::UW(const double& Ws, int x_ind, int y_ind)
const
{
    double ret = - Psi((double) 0.0,-Ws,x_ind,y_ind);
    //
    return ret;
}

arma::mat trame::tu::VW(const arma::mat& Ws)
const
{
    arma::mat ret = this->VW(Ws,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::VW(const arma::mat& Ws, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = - Psi(Ws,0.0,&x_ind,&y_ind);
    //
    return ret;
}

double trame::tu::VW(const double& Ws, int x_ind, int y_ind)
const
{
    double ret = - Psi(Ws,(double) 0.0,x_ind,y_ind);
    //
    return ret;
}

arma::mat trame::tu::dw_UW(const arma::mat& Ws)
const
{
    arma::mat ret = this->dw_UW(Ws,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::dw_UW(const arma::mat& Ws, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = 1.0 - du_Psi(0.0,-Ws,&x_ind,&y_ind);
    //
    return ret;
}

arma::mat trame::tu::dw_VW(const arma::mat& Ws)
const
{
    arma::mat ret = this->dw_VW(Ws,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::dw_VW(const arma::mat& Ws, arma::uvec* xs, arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = - du_Psi(Ws,0.0,&x_ind,&y_ind);
    //
    return ret;
}

arma::mat trame::tu::WU(const arma::mat& Us)
{
    arma::mat ret = this->WU(Us,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::WU(const arma::mat& Us, arma::uvec* xs, arma::uvec* ys)
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = 2*Us - phi(x_ind,y_ind);
    //
    return ret;
}

arma::mat trame::tu::WV(const arma::mat& Vs)
{
    arma::mat ret = this->WV(Vs,NULL,NULL);
    //
    return ret;
}

arma::mat trame::tu::WV(const arma::mat& Vs, arma::uvec* xs, arma::uvec* ys)
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = phi(x_ind,y_ind) - 2*Vs;
    //
    return ret;
}
