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
 * empirical class module
 *
 * Keith O'Hara
 * 09/06/2016
 */

// #include "trameR.hpp"

#include "ancillary/ancillary.hpp"
#include "arums/arums.hpp"

#include "R_arums.hpp"

RCPP_MODULE(empirical_module)
{
    using namespace Rcpp ;

    // function overloading requires some trickery
    SEXP (empirical_R::*build_1)(int, int) = &empirical_R::build_R ;

    SEXP (empirical_R::*G_1)(const arma::vec&) = &empirical_R::G_R ;
    SEXP (empirical_R::*G_2)(const arma::vec&, const arma::mat&) = &empirical_R::G_R ;

    SEXP (empirical_R::*Gstar_1)(const arma::vec&) = &empirical_R::Gstar_R ;
    SEXP (empirical_R::*Gstar_2)(const arma::vec&, const arma::mat&) = &empirical_R::Gstar_R ;
    
    // now we can declare the class
    class_<trame::arums::empirical>( "empirical_cpp" )
        .default_constructor()

        // basic objects
        .field( "nbX", &trame::arums::empirical::nbX )
        .field( "nbY", &trame::arums::empirical::nbY )

        .field( "dim_params", &trame::arums::empirical::dim_params )
        .field( "aux_n_draws", &trame::arums::empirical::aux_n_draws )
        .field( "nb_options", &trame::arums::empirical::nb_options )

        .field( "x_homogeneous", &trame::arums::empirical::x_homogeneous )
        .field( "outside_option", &trame::arums::empirical::outside_option )

        .field( "atoms", &trame::arums::empirical::atoms )

        .field( "U", &trame::arums::empirical::U )
        .field( "mu", &trame::arums::empirical::mu )

        .field( "U_sol", &trame::arums::empirical::U_sol )
        .field( "mu_sol", &trame::arums::empirical::mu_sol )

        // read only objects
        //.field_readonly( "k_Gstar", &empirical::k_Gstar )

        // member functions
    ;

    class_<empirical_R>( "empirical" )
        .derives<trame::arums::empirical>( "empirical_cpp" )
        .default_constructor()

        .method( "build", build_1 )

        .method( "G", G_1 )
        .method( "G", G_2 )
        .method( "Gx", &empirical_R::Gx_R )
        .method( "Gstar", Gstar_1 )
        .method( "Gstar", Gstar_2 )
        .method( "Gstarx", &empirical_R::Gstarx_R )
        .method( "Gbar", &empirical_R::Gbar_R )
    ;
}

// wrapper functions to catch errors and handle memory pointers

SEXP empirical_R::build_R(int nbX_inp, int nbY_inp)
{
    try {
        this->build(nbX_inp, nbY_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP empirical_R::G_R(const arma::vec& n)
{
    try {
        double val_out = this->G(n);
        //
        return Rcpp::List::create(Rcpp::Named("val") = val_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP empirical_R::G_R(const arma::vec& n, const arma::mat& U_inp)
{
    try {
        arma::mat mu_out;
        double val_out = this->G(n, U_inp, mu_out);
        //
        return Rcpp::List::create(Rcpp::Named("val") = val_out, Rcpp::Named("mu") = mu_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP empirical_R::Gx_R(const arma::mat& U_x_inp, int x)
{
    try {
        arma::mat mu_x_out;
        double val_x_out = this->Gx(U_x_inp, mu_x_out, x);
        //
        return Rcpp::List::create(Rcpp::Named("val_x") = val_x_out, Rcpp::Named("mu_x") = mu_x_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP empirical_R::Gstar_R(const arma::vec& n)
{   
    try {
        double val_out = this->Gstar(n);
        //
        return Rcpp::List::create(Rcpp::Named("val") = val_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP empirical_R::Gstar_R(const arma::vec& n, const arma::mat& mu_inp)
{   
    try {
        arma::mat U_out;
        double val_out = this->Gstar(n, mu_inp, U_out);
        //
        return Rcpp::List::create(Rcpp::Named("val") = val_out, Rcpp::Named("U") = U_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP empirical_R::Gstarx_R(const arma::mat& mu_x_inp, int x)
{   
    try {
        arma::mat U_x_out;
        double val_x_out = this->Gstarx(mu_x_inp, U_x_out, x);
        //
        return Rcpp::List::create(Rcpp::Named("val_x") = val_x_out, Rcpp::Named("U_x") = U_x_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP empirical_R::Gbar_R(const arma::mat& U_bar, const arma::mat& mu_bar, const arma::vec& n)
{
    try {
        arma::mat U_out, mu_out;
        double val_out = this->Gbar(U_bar, mu_bar, n, U_out, mu_out);
        //
        return Rcpp::List::create(Rcpp::Named("val") = val_out, Rcpp::Named("U") = U_out, Rcpp::Named("mu") = mu_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}
