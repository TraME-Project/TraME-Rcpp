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
 * Cobb-Douglas (CD) Marriage Matching Functions (MMFs) class
 *
 * Keith O'Hara
 * 11/08/2016
 *
 * This version:
 * 09/13/2017
 */

 #include "ancillary/ancillary.hpp"
 #include "mmfs/mmfs.hpp"

 #include "R_mmfs.hpp"

RCPP_MODULE(mmfs_cd_module)
{
    using namespace Rcpp ;

    // function overloading requires some trickery
    void (mmfs_cd_R::*build_1)(const arma::mat&, const arma::mat&) = &mmfs_cd_R::build_R ;
    void (mmfs_cd_R::*build_2)(const arma::mat&, const arma::mat&, bool) = &mmfs_cd_R::build_R ;

    SEXP (mmfs_cd_R::*M_1)(const arma::mat&, const arma::mat&) = &mmfs_cd_R::M_R ;
    SEXP (mmfs_cd_R::*M_2)(const arma::mat&, const arma::mat&, Rcpp::IntegerVector, Rcpp::IntegerVector) = &mmfs_cd_R::M_R ;

    // now we can declare the class
    class_<trame::mmfs::cd>( "mmfs_cd_cpp" )
        .default_constructor()

        // basic objects
        .field( "need_norm", &trame::mmfs::cd::need_norm )

        .field( "nbX", &trame::mmfs::cd::nbX )
        .field( "nbY", &trame::mmfs::cd::nbY )
        .field( "dim_params", &trame::mmfs::cd::dim_params )

        .field( "lambda", &trame::mmfs::cd::lambda )
        .field( "phi", &trame::mmfs::cd::phi )

        // read only objects
        //.field_readonly( "", &trame::mmfs::cd:: )

        // member functions
    ;

    class_<mmfs_cd_R>( "mmfs_cd" )
        .derives<trame::mmfs::cd>( "mmfs_cd_cpp" )
        .default_constructor()

        .method( "build", build_1 )
        .method( "build", build_2 )

        .method( "trans", &mmfs_cd_R::trans_R )

        .method( "M", M_1 )
        .method( "M", M_2 )
    ;
}

// wrapper functions to catch errors and handle memory pointers
void mmfs_cd_R::build_R(const arma::mat& lambda_inp, const arma::mat& phi_inp)
{
    try {
        this->build(lambda_inp,phi_inp,false);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mmfs_cd_R::build_R(const arma::mat& lambda_inp, const arma::mat& phi_inp, bool need_norm_inp)
{
    try {
        this->build(lambda_inp,phi_inp,need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mmfs_cd_R::trans_R()
{
    try {
        this->trans();
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

SEXP mmfs_cd_R::M_R(const arma::mat& a_xs, const arma::mat& b_ys)
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

SEXP mmfs_cd_R::M_R(const arma::mat& a_xs, const arma::mat& b_ys, Rcpp::IntegerVector x_ind, Rcpp::IntegerVector y_ind)
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
            mu_out = this->M(a_xs,b_ys,&x_ind_uvec,nullptr);
        } else if (x_ind_size == 0 && y_ind_size != 0) {
            mu_out = this->M(a_xs,b_ys,nullptr,&y_ind_uvec);
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
