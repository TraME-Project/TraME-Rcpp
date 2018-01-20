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
// MFE

#ifndef _R_mfe_HPP
#define _R_mfe_HPP

class mfe_cd_R : public trame::mfe<trame::mmfs::cd>
{
    public:
        void build_R(const arma::vec& n_inp, const arma::vec& m_inp);
        void build_R(double sigma_inp, bool need_norm_inp);
        void build_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& lambda_inp, const arma::mat& phi_inp, double sigma_inp, bool need_norm_inp);

        mmfs_cd_R get_mmfs();
        void set_mmfs(mmfs_cd_R mmfs_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
        SEXP solve_R(Rcpp::CharacterVector solver_inp, double tol_inp, int max_iter_inp);
};

class mfe_ces_R : public trame::mfe<trame::mmfs::ces>
{
    public:
        void build_R(const arma::vec& n_inp, const arma::vec& m_inp);
        void build_R(double sigma_inp, bool need_norm_inp);
        void build_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, double sigma_inp, bool need_norm_inp);

        mmfs_ces_R get_mmfs();
        void set_mmfs(mmfs_ces_R mmfs_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
        SEXP solve_R(Rcpp::CharacterVector solver_inp, double tol_inp, int max_iter_inp);
};

class mfe_geo_R : public trame::mfe<trame::mmfs::geo>
{
    public:
        void build_R(const arma::vec& n_inp, const arma::vec& m_inp);
        void build_R(double sigma_inp, bool need_norm_inp);
        void build_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, double sigma_inp, bool need_norm_inp);

        mmfs_geo_R get_mmfs();
        void set_mmfs(mmfs_geo_R mmfs_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
        SEXP solve_R(Rcpp::CharacterVector solver_inp, double tol_inp, int max_iter_inp);
};

class mfe_min_R : public trame::mfe<trame::mmfs::min>
{
    public:
        void build_R(const arma::vec& n_inp, const arma::vec& m_inp);
        void build_R(double sigma_inp, bool need_norm_inp);
        void build_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, double sigma_inp, bool need_norm_inp);

        mmfs_min_R get_mmfs();
        void set_mmfs(mmfs_min_R mmfs_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
        SEXP solve_R(Rcpp::CharacterVector solver_inp, double tol_inp, int max_iter_inp);
};

#endif
