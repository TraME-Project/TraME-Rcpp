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
 * logit class module
 *
 * Keith O'Hara
 * 09/06/2016
 */

 #include "ancillary/ancillary.hpp"
 #include "arums/arums.hpp"
 
 #include "R_arums.hpp"

RCPP_EXPOSED_CLASS(empirical_R)
RCPP_EXPOSED_CLASS(logit_R)

RCPP_MODULE(logit_module)
{
    using namespace Rcpp;

    // function overloading requires some trickery
    void (trame::arums::logit::*build_1)(trame::uint_t, trame::uint_t) = &trame::arums::logit::build ;
    void (trame::arums::logit::*build_2)(trame::uint_t, trame::uint_t, double, bool) = &trame::arums::logit::build ;

    SEXP (logit_R::*G_1)(const arma::vec&) = &logit_R::G_R ;
    SEXP (logit_R::*G_2)(const arma::vec&, const arma::mat&) = &logit_R::G_R ;

    SEXP (logit_R::*Gstar_1)(const arma::vec&) = &logit_R::Gstar_R ;
    SEXP (logit_R::*Gstar_2)(const arma::vec&, const arma::mat&) = &logit_R::Gstar_R ;

    // now we can declare the class
    class_<trame::arums::logit>( "logit_cpp" )
        .default_constructor()

        // basic objects
        .field( "nbX", &trame::arums::logit::nbX )
        .field( "nbY", &trame::arums::logit::nbY )

        .field( "dim_params", &trame::arums::logit::dim_params )
        .field( "sigma", &trame::arums::logit::sigma )
        .field( "outside_option", &trame::arums::logit::outside_option )

        .field( "U", &trame::arums::logit::U )
        .field( "mu", &trame::arums::logit::mu )

        .field( "U_sol", &trame::arums::logit::U_sol )
        .field( "mu_sol", &trame::arums::logit::mu_sol )

        // read only objects
        //.field_readonly( "", &trame::logit:: )

        // member functions
        .method( "build", build_1 )
        .method( "build", build_2 )
    ;

    class_<logit_R>( "logit" )
        .derives<trame::arums::logit>( "logit_cpp" )
        .default_constructor()

        .method( "G", G_1 )
        .method( "G", G_2 )
        .method( "Gstar", Gstar_1 )
        .method( "Gstar", Gstar_2 )
        .method( "Gbar", &logit_R::Gbar_R )
        .method( "simul", &logit_R::simul_R )
    ;
}

// wrapper functions to catch errors and handle memory pointers
SEXP logit_R::G_R(const arma::vec& n)
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

SEXP logit_R::G_R(const arma::vec& n, const arma::mat& U_inp)
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

SEXP logit_R::Gstar_R(const arma::vec& n)
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

SEXP logit_R::Gstar_R(const arma::vec& n, const arma::mat& mu_inp)
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

SEXP logit_R::Gbar_R(const arma::mat& U_bar, const arma::mat& mu_bar, const arma::vec& n)
{
    try {
        arma::mat U_out, mu_out;
        double val_out = this->Gbar(U_bar, mu_bar, n, U_out, mu_out);

        return Rcpp::List::create(Rcpp::Named("val") = val_out, Rcpp::Named("U") = U_out, Rcpp::Named("mu") = mu_out);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

empirical_R logit_R::simul_R(trame::uint_t n_draws)
{
    trame::arums::empirical emp_obj;
    this->simul_int(emp_obj,&n_draws,nullptr);

    return static_cast<empirical_R&>(emp_obj);
}
