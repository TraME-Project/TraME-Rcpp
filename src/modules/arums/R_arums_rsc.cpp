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
 * RSC class module
 *
 * Keith O'Hara
 * 08/08/2016
 */

#include "trameR.hpp"

RCPP_EXPOSED_CLASS(empirical_R)
RCPP_EXPOSED_CLASS(rsc_R)

RCPP_MODULE(rsc_module)
{
    using namespace Rcpp ;

    // function overloading requires some trickery
    void (trame::arums::rsc::*build_1)(int, int) = &trame::arums::rsc::build ;

    SEXP (rsc_R::*G_1)(arma::vec) = &rsc_R::G_R ;
    SEXP (rsc_R::*G_2)(arma::vec, arma::mat) = &rsc_R::G_R ;

    SEXP (rsc_R::*Gstar_1)(arma::vec) = &rsc_R::Gstar_R ;
    SEXP (rsc_R::*Gstar_2)(arma::vec, arma::mat) = &rsc_R::Gstar_R ;
  
    // now we can declare the class
    class_<trame::arums::rsc>( "rsc" )
        .default_constructor()

        // basic objects
        .field( "nbX", &trame::arums::rsc::nbX )
        .field( "nbY", &trame::arums::rsc::nbY )

        .field( "dim_params", &trame::arums::rsc::dim_params )
        .field( "outside_option", &trame::arums::rsc::outside_option )

        .field( "zeta", &trame::arums::rsc::zeta )

        .field( "U", &trame::arums::rsc::U )
        .field( "mu", &trame::arums::rsc::mu )

        .field( "U_sol", &trame::arums::rsc::U_sol )
        .field( "mu_sol", &trame::arums::rsc::mu_sol )

        // read only objects
        .field_readonly( "aux_ord", &trame::arums::rsc::aux_ord )

        .field_readonly( "aux_Influence_lhs", &trame::arums::rsc::aux_Influence_lhs )
        .field_readonly( "aux_Influence_rhs", &trame::arums::rsc::aux_Influence_rhs )

        .field_readonly( "aux_DinvPsigma", &trame::arums::rsc::aux_DinvPsigma )
        .field_readonly( "aux_Psigma", &trame::arums::rsc::aux_Psigma )

        // member functions
        .method( "build", build_1 )
        .method( "build_beta", &trame::arums::rsc::build_beta )
    ;

    class_<rsc_R>( "rsc_R" )
        .derives<trame::arums::rsc>( "rsc" )
        .default_constructor()

        .method( "G", G_1 )
        .method( "G", G_2 )
        .method( "Gx", &rsc_R::Gx_R )
        .method( "Gstar", Gstar_1 )
        .method( "Gstar", Gstar_2 )
        .method( "Gstarx", &rsc_R::Gstarx_R )
        .method( "Gbar", &rsc_R::Gbar_R )
        .method( "simul", &rsc_R::simul_R )
    ;
}

// wrapper functions to catch errors and handle memory pointers
SEXP rsc_R::G_R(arma::vec n)
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

SEXP rsc_R::G_R(arma::vec n, arma::mat U_inp)
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

SEXP rsc_R::Gx_R(arma::mat U_x_inp, int x)
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

SEXP rsc_R::Gstar_R(arma::vec n)
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

SEXP rsc_R::Gstar_R(arma::vec n, arma::mat mu_inp)
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

SEXP rsc_R::Gstarx_R(arma::mat mu_x_inp, int x)
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

SEXP rsc_R::Gbar_R(arma::mat U_bar, arma::mat mu_bar, arma::vec n)
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

empirical_R rsc_R::simul_R(int nb_draws, int seed_val)
{
    trame::arums::empirical emp_obj = this->simul(nb_draws,seed_val);

    empirical_R emp_R_obj = static_cast<empirical_R&>(emp_obj);

    return emp_R_obj;
}
