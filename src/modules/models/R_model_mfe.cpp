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
 * model<mfe<.>> class module
 *
 * Keith O'Hara
 * 10/23/2016
 *
 * This version:
 * 09/13/2017
 */

#include "trameR.hpp"

RCPP_EXPOSED_CLASS(mmfs_cd_R)
RCPP_EXPOSED_CLASS(mmfs_ces_R)
RCPP_EXPOSED_CLASS(mmfs_geo_R)
RCPP_EXPOSED_CLASS(mmfs_min_R)

RCPP_EXPOSED_CLASS(mfe_cd_R)
RCPP_EXPOSED_CLASS(mfe_ces_R)
RCPP_EXPOSED_CLASS(mfe_geo_R)
RCPP_EXPOSED_CLASS(mfe_min_R)

RCPP_EXPOSED_CLASS(model_mfe_geo_R)

RCPP_MODULE(model_mfe_module)
{
    using namespace Rcpp ;

    //
    // function overloading requires some trickery

    // geo
    void (model_mfe_geo_R::*build_geo_1)(const arma::mat& X_inp, const arma::mat& Y_inp) = &model_mfe_geo_R::build_geo_R ;
    void (model_mfe_geo_R::*build_geo_2)(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_mfe_geo_R::build_geo_R ;
    void (model_mfe_geo_R::*build_geo_3)(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp, double sigma_inp) = &model_mfe_geo_R::build_geo_R ;

    SEXP (model_mfe_geo_R::*mme_regul_geo_1)(const arma::mat& mu_hat, double lambda) = &model_mfe_geo_R::mme_regul_geo_R ;
    SEXP (model_mfe_geo_R::*mme_woregul_geo_1)(const arma::mat& mu_hat) = &model_mfe_geo_R::mme_woregul_geo_R ;

    // now we can declare the class
    class_<trame::model_base>( "model_base" )
        .default_constructor()

        // basic objects
        .field( "need_norm", &trame::model<trame::mfe<trame::mmfs::geo>>::need_norm )

        .field( "nbX", &trame::model<trame::mfe<trame::mmfs::geo>>::nbX )
        .field( "nbY", &trame::model<trame::mfe<trame::mmfs::geo>>::nbY )

        .field( "dX", &trame::model<trame::mfe<trame::mmfs::geo>>::dX )
        .field( "dY", &trame::model<trame::mfe<trame::mmfs::geo>>::dY )
        .field( "dim_theta", &trame::model<trame::mfe<trame::mmfs::geo>>::dim_theta )

        .field( "n", &trame::model<trame::mfe<trame::mmfs::geo>>::n )
        .field( "m", &trame::model<trame::mfe<trame::mmfs::geo>>::m )
    ;

    class_<trame::model<trame::mfe<trame::mmfs::geo>>>( "model_mfe_geo_cpp" )
        .derives<trame::model_base>( "model_base" )
        .default_constructor()
    ;

    class_<model_mfe_geo_R>( "model_mfe_geo" )
        // .derives<trame::dse_base>( "dse_base" )
        .derives<trame::model<trame::mfe<trame::mmfs::geo>>>( "model_mfe_geo_cpp" )
        .default_constructor()

        .method( "build", build_geo_1 )
        .method( "build", build_geo_2 )
        .method( "build", build_geo_3 )

        .method( "get_market", &model_mfe_geo_R::get_market )
        .method( "set_market", &model_mfe_geo_R::set_market )

        .method( "mme", mme_regul_geo_1 )
        .method( "mme", mme_woregul_geo_1 )
    ;

}

//
// wrapper functions to catch errors and handle memory pointers

// geo

void model_mfe_geo_R::build_geo_R(const arma::mat& X_inp, const arma::mat& Y_inp)
{
    try {
        this->build(X_inp,Y_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void model_mfe_geo_R::build_geo_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(X_inp,Y_inp,n_inp,m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void model_mfe_geo_R::build_geo_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp, double sigma_inp)
{
    try {
        this->build(X_inp,Y_inp,n_inp,m_inp,sigma_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

SEXP model_mfe_geo_R::mme_regul_geo_R(const arma::mat& mu_hat, double lambda)
{
    try {
        double val_out;
        arma::mat theta_hat;

        bool success = this->mme_regul(mu_hat,theta_hat,lambda,val_out);

        return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("value") = val_out, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP model_mfe_geo_R::mme_woregul_geo_R(const arma::mat& mu_hat)
{
    try {
        double val_out;
        arma::mat theta_hat;

        bool success = this->mme_woregul(mu_hat,theta_hat,val_out);

        return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("value") = val_out, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

mfe_geo_R model_mfe_geo_R::get_market()
{
    mfe_geo_R market_obj_out = static_cast<mfe_geo_R&>(market_obj);

    return market_obj_out;
}

void model_mfe_geo_R::set_market(mfe_geo_R market_obj_inp)
{
    try {
        market_obj = static_cast< trame::mfe<trame::mmfs::geo>& >(market_obj_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}
