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

// some functions are const restricted because of calls to const market pointers in equilibrium solvers

class min
{
    public:
        // build objects
        bool need_norm;
        
        int transfers_type = 1;
        int nbX;
        int nbY;
        int nbParams;

        arma::mat alpha;
        arma::mat gamma;

        arma::mat aux_alpha_exp; // exp(alpha_NTU / sigma), also labelled A_NTU
        arma::mat aux_gamma_exp; // exp(gamma_NTU / sigma), also labelled B_NTU

        // member functions
        void build(const arma::mat& alpha_NTU, const arma::mat& gamma_NTU, bool need_norm_NTU);
        
        void trans();
        
        //
        arma::mat M(const arma::mat& a_xs, const arma::mat& b_ys) const;
        arma::mat M(const arma::mat& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat M(const double& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat M(const arma::mat& a_xs, const double& b_ys, arma::uvec* xs, arma::uvec* ys) const;

        arma::mat Mx0(const arma::mat& a_x) const;
        arma::mat M0y(const arma::mat& b_y) const;
};
