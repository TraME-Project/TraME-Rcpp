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
 * Constant Elasticity of Substitution (CES) Marriage Matching Functions (MMFs) class
 *
 * Keith O'Hara
 * 11/08/2016
 *
 * This version:
 * 05/13/2017
 */

#include "trameR.hpp"

RCPP_MODULE(mmfs_ces_module)
{
    using namespace Rcpp ;

    // function overloading requires some trickery
    void (mmfs_ces_R::*build_1)(arma::mat, arma::mat, arma::mat) = &mmfs_ces_R::build_R ;
    void (mmfs_ces_R::*build_2)(arma::mat, arma::mat, arma::mat, bool) = &mmfs_ces_R::build_R ;

    SEXP (mmfs_ces_R::*M_1)(arma::mat, arma::mat) = &mmfs_ces_R::M_R ;
    SEXP (mmfs_ces_R::*M_2)(arma::mat, arma::mat, Rcpp::IntegerVector, Rcpp::IntegerVector) = &mmfs_ces_R::M_R ;

    // now we can declare the class
    class_<trame::mmfs::ces>( "mmfs_ces" )
        .default_constructor()

        // basic objects
        .field( "need_norm", &trame::mmfs::ces::need_norm )

        .field( "nbX", &trame::mmfs::ces::nbX )
        .field( "nbY", &trame::mmfs::ces::nbY )
        .field( "dim_params", &trame::mmfs::ces::dim_params )

        .field( "alpha", &trame::mmfs::ces::alpha )
        .field( "gamma", &trame::mmfs::ces::gamma )
        .field( "tau", &trame::mmfs::ces::tau )

        // read only objects
        //.field_readonly( "", &trame::mmfs::ces:: )

        // member functions
    ;

    class_<mmfs_ces_R>( "mmfs_ces_R" )
        .derives<trame::mmfs::ces>( "mmfs_ces" )
        .default_constructor()

        .method( "build", build_1 )
        .method( "build", build_2 )

        .method( "trans", &mmfs_ces_R::trans_R )

        .method( "M", M_1 )
        .method( "M", M_2 )
    ;
}

// wrapper functions to catch errors and handle memory pointers
void mmfs_ces_R::build_R(arma::mat alpha_inp, arma::mat gamma_inp, arma::mat tau_inp)
{
    try {
        this->build(alpha_inp,gamma_inp,tau_inp,false);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
	}
}

void mmfs_ces_R::build_R(arma::mat alpha_inp, arma::mat gamma_inp, arma::mat tau_inp, bool need_norm_inp)
{
    try {
        this->build(alpha_inp,gamma_inp,tau_inp,need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
	}
}

void mmfs_ces_R::trans_R()
{
    try {
        this->trans();
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
	}
}

SEXP mmfs_ces_R::M_R(arma::mat a_xs, arma::mat b_ys)
{
    try {
        arma::mat mu_out = this->M(a_xs,b_ys);
        //
        return Rcpp::wrap(mu_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
	}
    return R_NilValue;
}

SEXP mmfs_ces_R::M_R(arma::mat a_xs, arma::mat b_ys, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind)
{
    try {
        int x_ind_size = x_ind.size();
        int y_ind_size = y_ind.size();

        arma::mat mu_out;
        //
        // default case to mirror NULL
        if (x_ind_size == 0 && y_ind_size == 0) {
            mu_out = this->M(a_xs,b_ys);
        }
        //
        // correct for zero indexing (R indexing - 1)
        arma::uvec x_ind_uvec, y_ind_uvec;

        if (x_ind_size != 0) {
            x_ind_uvec = Rcpp::as<arma::uvec>(x_ind) - 1;
        }
        if (y_ind_size != 0) {
            y_ind_uvec = Rcpp::as<arma::uvec>(y_ind) - 1;
        }
        //
        if (x_ind_size != 0 && y_ind_size == 0) {
            mu_out = this->M(a_xs,b_ys,&x_ind_uvec,NULL);
        } else if (x_ind_size == 0 && y_ind_size != 0) {
            mu_out = this->M(a_xs,b_ys,NULL,&y_ind_uvec);
        } else {
            mu_out = this->M(a_xs,b_ys,&x_ind_uvec,&y_ind_uvec);
        }
        //
        return Rcpp::wrap(mu_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
	}
    return R_NilValue;
}