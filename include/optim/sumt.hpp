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
 * Sequential unconstrained minimization technique (SUMT)
 *
 * Keith O'Hara
 * 01/15/2016
 *
 * This version:
 * 01/17/2017
 */

#ifndef _sumt_HPP
#define _sumt_HPP

struct sumt_struct {
    double c_pen;
};

bool sumt(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad, void* opt_data)> opt_objfn, void* opt_data,
          std::function<double (const arma::vec& vals_inp, arma::vec* grad, void* constr_data)> constr_fn, void* constr_data,
          double* value_out);

bool sumt(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad, void* opt_data)> opt_objfn, void* opt_data,
          std::function<double (const arma::vec& vals_inp, arma::vec* grad, void* constr_data)> constr_fn, void* constr_data);

#endif
