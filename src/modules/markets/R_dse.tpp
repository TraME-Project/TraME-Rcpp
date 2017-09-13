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
 * 11/10/2016
 *
 * This version:
 * 09/13/2017
 */

// these functions take SEXP input arguements instead of exposed class templates ('Ta') because
// Rcpp modules cannot distinguish between methods with the same number of arguments but with different types

template<typename Ta>
void dse_empirical_etu_R::build_ETU_R_int(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp)
{
    try {
        Ta* arums_obj_1 = Rcpp::as<Ta*>(arums_G_inp);
        Ta* arums_obj_2 = Rcpp::as<Ta*>(arums_H_inp);

        trame::arums::empirical empirical_1 = arums_obj_1->simul();
        trame::arums::empirical empirical_2 = arums_obj_2->simul();

        this->build(n_inp,m_inp,alpha_inp,gamma_inp,tau_inp,empirical_1,empirical_2,need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

template<typename Ta>
void dse_empirical_ltu_R::build_LTU_R_int(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& lambda_inp, const arma::mat& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp)
{
    try {
        Ta* arums_obj_1 = Rcpp::as<Ta*>(arums_G_inp);
        Ta* arums_obj_2 = Rcpp::as<Ta*>(arums_H_inp);

        trame::arums::empirical empirical_1 = arums_obj_1->simul();
        trame::arums::empirical empirical_2 = arums_obj_2->simul();

        this->build(n_inp,m_inp,lambda_inp,phi_inp,empirical_1,empirical_2,need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

template<typename Ta>
void dse_empirical_ntu_R::build_NTU_R_int(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp)
{
    try {
        Ta* arums_obj_1 = Rcpp::as<Ta*>(arums_G_inp);
        Ta* arums_obj_2 = Rcpp::as<Ta*>(arums_H_inp);

        trame::arums::empirical empirical_1 = arums_obj_1->simul();
        trame::arums::empirical empirical_2 = arums_obj_2->simul();

        this->build(n_inp,m_inp,alpha_inp,gamma_inp,empirical_1,empirical_2,need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

template<typename Ta>
void dse_empirical_tu_R::build_TU_R_int(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp)
{
    try {
        Ta* arums_obj_1 = Rcpp::as<Ta*>(arums_G_inp);
        Ta* arums_obj_2 = Rcpp::as<Ta*>(arums_H_inp);

        trame::arums::empirical empirical_1 = arums_obj_1->simul();
        trame::arums::empirical empirical_2 = arums_obj_2->simul();

        this->build(n_inp,m_inp,phi_inp,empirical_1,empirical_2,need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}
