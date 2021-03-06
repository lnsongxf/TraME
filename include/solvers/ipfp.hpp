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
 * Iterated Proportional Fitting Procedure (IPFP) for MFE-type markets
 *
 * Keith O'Hara
 * 08/16/2016
 *
 * This version:
 * 02/15/2017
 */

#ifndef _trame_ipfp_HPP
#define _trame_ipfp_HPP

// internal function
template<typename Tt>
bool ipfp_int(const mfe<Tt>& market, arma::mat* mu_out, arma::vec* mu_x0_out, arma::vec* mu_0y_out, arma::mat* U_out, arma::mat* V_out, arma::vec* u_out, arma::vec* v_out, const double* tol_inp, const int* max_iter_inp, const arma::vec* by_start);

// wrappers
template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, const double& tol_inp);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, const int& max_iter_inp);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, const arma::vec& by_start);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, const double& tol_inp, const int& max_iter_inp);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, const double& tol_inp, const arma::vec& by_start);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, const int& max_iter_inp, const arma::vec& by_start);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, const double& tol_inp, const int& max_iter_inp, const arma::vec& by_start);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, arma::mat& U_out, arma::mat& V_out);

template<typename Tt>
bool ipfp(const mfe<Tt>& market, arma::mat& mu_out, arma::vec& mu_x0_out, arma::vec& mu_0y_out, arma::mat& U_out, arma::mat& V_out, arma::vec& u_out, arma::vec& v_out, double* tol_inp, int* max_iter_inp, arma::vec* by_start);

#include "ipfp.tpp"

#endif
