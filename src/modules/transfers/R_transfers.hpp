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
 * Derived classes to provide wrappers to the TraME library
 */

class transfers_etu_R : public trame::transfers::etu
{
    public:
        void build_R(const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp);
        void build_R(const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, bool need_norm_inp);

        void trans_R();

        SEXP Psi_R(const arma::mat& U, const arma::mat& V);
        SEXP Psi_R(const arma::mat& U, const arma::mat& V, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP du_Psi_R(const arma::mat& U, const arma::mat& V);
        SEXP du_Psi_R(const arma::mat& U, const arma::mat& V, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP Ucal_R(const arma::mat& vs);
        SEXP Ucal_R(const arma::mat& vs, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP Vcal_R(const arma::mat& us);
        SEXP Vcal_R(const arma::mat& us, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);
};

class transfers_ltu_R : public trame::transfers::ltu
{
    public:
        void build_R(const arma::mat& lambda_inp, const arma::mat& phi_inp);
        void build_R(const arma::mat& lambda_inp, const arma::mat& phi_inp, bool need_norm_inp);

        void trans_R();

        SEXP Psi_R(const arma::mat& U, const arma::mat& V);
        SEXP Psi_R(const arma::mat& U, const arma::mat& V, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP du_Psi_R(const arma::mat& U, const arma::mat& V);
        SEXP du_Psi_R(const arma::mat& U, const arma::mat& V, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP Ucal_R(const arma::mat& vs);
        SEXP Ucal_R(const arma::mat& vs, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP Vcal_R(const arma::mat& us);
        SEXP Vcal_R(const arma::mat& us, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);
};

class transfers_ntu_R : public trame::transfers::ntu
{
    public:
        void build_R(const arma::mat& alpha_inp, const arma::mat& gamma_inp);
        void build_R(const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);

        void trans_R();

        SEXP Psi_R(const arma::mat& U, const arma::mat& V);
        SEXP Psi_R(const arma::mat& U, const arma::mat& V, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP du_Psi_R(const arma::mat& U, const arma::mat& V);
        SEXP du_Psi_R(const arma::mat& U, const arma::mat& V, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP Ucal_R(const arma::mat& vs);
        SEXP Ucal_R(const arma::mat& vs, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP Vcal_R(const arma::mat& us);
        SEXP Vcal_R(const arma::mat& us, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);
};

class transfers_tu_R : public trame::transfers::tu
{
    public:
        void build_R(const arma::mat& phi_inp);
        void build_R(const arma::mat& phi_inp, bool need_norm_inp);

        void trans_R();

        SEXP Psi_R(const arma::mat& U, const arma::mat& V);
        SEXP Psi_R(const arma::mat& U, const arma::mat& V, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP du_Psi_R(const arma::mat& U, const arma::mat& V);
        SEXP du_Psi_R(const arma::mat& U, const arma::mat& V, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP Ucal_R(const arma::mat& vs);
        SEXP Ucal_R(const arma::mat& vs, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);

        SEXP Vcal_R(const arma::mat& us);
        SEXP Vcal_R(const arma::mat& us, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind);
};
