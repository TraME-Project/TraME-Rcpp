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
 * Generalized logit transform
 *
 * Keith O'Hara
 * 11/28/2014
 */

#include "trame.hpp"

arma::vec
trame::logit_trans(const arma::vec& pars, const arma::vec& lower_bounds, const arma::vec& upper_bounds)
{
	//
	arma::vec pars_trans = arma::log((pars - lower_bounds)/(upper_bounds - pars));
	//
	if (pars_trans.has_inf()) {
		arma::uvec inf_ind = arma::find_nonfinite(pars_trans);
		int n_inf = inf_ind.n_elem;
		double small_num = 1E-08;
		
		for (int i=0; i < n_inf; i++) {
			int inf_ind_i = inf_ind(i);
			if (pars_trans(inf_ind_i) < 0) {
				pars_trans(inf_ind_i) = std::log((pars(inf_ind_i) + small_num - lower_bounds(inf_ind_i))/(upper_bounds(inf_ind_i) - pars(inf_ind_i) - small_num));
			} else {
				pars_trans(inf_ind_i) = std::log((pars(inf_ind_i) - small_num - lower_bounds(inf_ind_i))/(upper_bounds(inf_ind_i) - pars(inf_ind_i) + small_num));
			}
		} 
	}
	//
	return pars_trans;
}

// logit_trans with [0,1] support
arma::vec trame::logit_trans(const arma::vec& pars)
{
	//
	arma::vec pars_trans = arma::log(pars/(1 - pars));
	//
	return pars_trans;
}

double trame::logit_trans(const double& pars, const double& lower_bounds, const double& upper_bounds)
{
	//
	double pars_trans = std::log((pars - lower_bounds)/(upper_bounds - pars));
	//
	return pars_trans;
}

/*
 * inverse transform
 */

arma::vec trame::logit_inv_trans(const arma::vec& pars_trans, const arma::vec& lower_bounds, const arma::vec& upper_bounds)
{
	//
	arma::vec pars = (lower_bounds + upper_bounds % arma::exp(pars_trans)) / (1 + arma::exp(pars_trans));
	//
	return pars;
}

// logit_inv_trans with [0,1] support
arma::vec trame::logit_inv_trans(const arma::vec& pars_trans)
{
	//
	arma::vec pars = arma::exp(pars_trans) / (1 + arma::exp(pars_trans));
	//
	return pars;
}

double trame::logit_inv_trans(const double& pars_trans, const double& lower_bounds, const double& upper_bounds)
{
	//
	double pars = (lower_bounds + upper_bounds * std::exp(pars_trans)) / (1 + std::exp(pars_trans));
	//
	return pars;
}
