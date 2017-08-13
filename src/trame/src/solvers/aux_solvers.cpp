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
 * auxiliary functions for equilibrium solvers
 *
 * Keith O'Hara
 * 08/23/2016
 *
 * This version:
 * 07/26/2016
 */

#include "trame.hpp"

/*
 * build disaggregate epsilon function; used in cupids_lp
 * takes U_xy and arums as input; returns U_iy as output.
 */

int 
trame::build_disaggregate_epsilon(arma::vec n, const trame::arums::empirical& arums_emp_inp, arma::mat& epsilon_iy, arma::mat& epsilon0_i, arma::mat& I_ix)
{
    const int nbX = arums_emp_inp.nbX;
    const int nbY = arums_emp_inp.nbY;

    const int nb_draws = arums_emp_inp.aux_nb_draws;
    const int nbI = nbX * nb_draws;

    arma::vec I_01(nbX);
    arma::mat epsilon;
    arma::mat epsilons = arma::zeros(nbI,nbY+1);
    I_ix.zeros(nbI,nbX);
    //
    for (int x=0; x < nbX; x++) {
        if (arums_emp_inp.x_homogeneous) {
            epsilon = arums_emp_inp.atoms.slice(0);
        } else {
            epsilon = arums_emp_inp.atoms.slice(x);
        }
        //
        epsilons.rows(x*nb_draws,(x+1)*nb_draws-1) = epsilon;
        //
        I_01.zeros();
        I_01(x) = 1;
        
        I_ix.rows(x*nb_draws,(x+1)*nb_draws-1) = arma::repmat(I_01.t(),nb_draws,1);
    }
    //
    epsilon_iy = epsilons.cols(0,nbY-1);
    epsilon0_i = epsilons.col(nbY);
    //
    return nb_draws;
}
