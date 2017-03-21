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
 * Transferable Utility (TU) transfers class
 *
 * Keith O'Hara
 * 08/15/2016
 *
 * This version:
 * 03/13/2017
 */

// some functions are const restricted because of calls to const market pointers in equilibrium solvers

class tu
{
    public:
        // build objects
        bool need_norm;

        int transfers_type = 1;
        int nbX;
        int nbY;
        int nbParams;

        arma::mat phi;
        arma::mat aux_phi_exp; // exp(phi_inp/(2*sigma)), also labelled K_TU

        // member functions
        void build(const arma::mat& phi_TU, bool need_norm_TU);
        
        void trans();
        
        //
        // MFE-related functions
        arma::mat M(const arma::mat& a_xs, const arma::mat& b_ys) const;
        arma::mat M(const arma::mat& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat M(const double& a_xs, const arma::mat& b_ys, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat M(const arma::mat& a_xs, const double& b_ys, arma::uvec* xs, arma::uvec* ys) const;

        arma::mat Mx0(const arma::mat& a_x) const;
        arma::mat M0y(const arma::mat& b_y) const;

        //
        // DSE-related functions
        arma::mat Psi(const arma::mat& U, const arma::mat& V) const;
        arma::mat Psi(const arma::mat& U, const arma::mat& V, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat Psi(const double& U, const arma::mat& V, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat Psi(const arma::mat& U, const double& V, arma::uvec* xs, arma::uvec* ys) const;
        double Psi(const double& U, const double& V, int x_ind, int y_ind) const;

        arma::mat du_Psi(const arma::mat& U, const arma::mat& V) const;
        arma::mat du_Psi(const arma::mat& U, const arma::mat& V, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat du_Psi(const double& U, const arma::mat& V, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat du_Psi(const arma::mat& U, const double& V, arma::uvec* xs, arma::uvec* ys) const;

        arma::mat dtheta_Psi(const arma::mat& U, const arma::mat& V, const arma::mat& dtheta);
        arma::mat dtheta_Psi(const arma::mat& U, const arma::mat& V, const arma::mat* dtheta);

        arma::mat Ucal(const arma::mat& vs) const;
        arma::mat Ucal(const arma::mat& vs, arma::uvec* xs, arma::uvec* ys) const;
        double Ucal(const double& vs, int xs, int ys) const;
        arma::mat Vcal(const arma::mat& us) const;
        arma::mat Vcal(const arma::mat& us, arma::uvec* xs, arma::uvec* ys) const;
        double Vcal(const double& us, int xs, int ys) const;

        arma::mat UW(const arma::mat& Ws) const;
        arma::mat UW(const arma::mat& Ws, arma::uvec* xs, arma::uvec* ys) const;
        double UW(const double& Ws, int x_ind, int y_ind) const;
        arma::mat VW(const arma::mat& Ws) const;
        arma::mat VW(const arma::mat& Ws, arma::uvec* xs, arma::uvec* ys) const;
        double VW(const double& Ws, int x_ind, int y_ind) const;

        arma::mat dw_UW(const arma::mat& Ws) const;
        arma::mat dw_UW(const arma::mat& Ws, arma::uvec* xs, arma::uvec* ys) const;
        arma::mat dw_VW(const arma::mat& Ws) const;
        arma::mat dw_VW(const arma::mat& Ws, arma::uvec* xs, arma::uvec* ys) const;

        arma::mat WU(const arma::mat& Us);
        arma::mat WU(const arma::mat& Us, arma::uvec* xs, arma::uvec* ys);
        arma::mat WV(const arma::mat& Vs);
        arma::mat WV(const arma::mat& Vs, arma::uvec* xs, arma::uvec* ys);
};
