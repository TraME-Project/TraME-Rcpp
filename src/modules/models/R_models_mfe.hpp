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
 * Derived market classes to provide wrappers to the TraME library
 *
 * Keith O'Hara
 * 10/20/2016
 *
 * This version:
 * 09/13/2017
 */

//
// MFE-geo

class model_mfe_geo_R : public trame::model< trame::mfe<trame::mmfs::geo> >
{
    public:
        void build_geo_R(const arma::mat& X_inp, const arma::mat& Y_inp);
        void build_geo_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp);
        void build_geo_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp, double sigma_inp);

        SEXP mme_regul_geo_R(const arma::mat& mu_hat, double lambda);
        SEXP mme_woregul_geo_R(const arma::mat& mu_hat);

        mfe_geo_R get_market();
        void set_market(mfe_geo_R market_obj_inp);
};
