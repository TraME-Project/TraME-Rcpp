/*################################################################################
  ##
  ##   Copyright (C) 2015 - 2018 the TraME Team:
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
 * mfe<mmf> class module
 *
 * Keith O'Hara
 * 10/20/2016
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

RCPP_MODULE(mfe_mmf_module)
{
    using namespace Rcpp ;

    //
    // function overloading requires some trickery

    // CD
    void (mfe_cd_R::*build_cd_1)(const arma::vec&, const arma::vec&) = &mfe_cd_R::build_R ;
    void (mfe_cd_R::*build_cd_2)(double, bool) = &mfe_cd_R::build_R ;
    void (mfe_cd_R::*build_cd_3)(const arma::vec&, const arma::vec&, const arma::mat&, const arma::mat&, double, bool) = &mfe_cd_R::build_R ;

    // SEXP (mfe_cd_R::*solve_cd_1)() = &mfe_cd_R::solve_R ;
    SEXP (mfe_cd_R::*solve_cd_2)(Rcpp::CharacterVector) = &mfe_cd_R::solve_R ;
    SEXP (mfe_cd_R::*solve_cd_3)(Rcpp::CharacterVector, double tol_inp, int max_iter) = &mfe_cd_R::solve_R ;

    // CES
    void (mfe_ces_R::*build_ces_1)(const arma::vec&, const arma::vec&) = &mfe_ces_R::build_R ;
    void (mfe_ces_R::*build_ces_2)(double, bool) = &mfe_ces_R::build_R ;
    void (mfe_ces_R::*build_ces_3)(const arma::vec&, const arma::vec&, const arma::mat&, const arma::mat&, const arma::mat&, double, bool) = &mfe_ces_R::build_R ;

    // SEXP (mfe_ces_R::*solve_ces_1)() = &mfe_ces_R::solve_R ;
    SEXP (mfe_ces_R::*solve_ces_2)(Rcpp::CharacterVector) = &mfe_ces_R::solve_R ;
    SEXP (mfe_ces_R::*solve_ces_3)(Rcpp::CharacterVector, double tol_inp, int max_iter) = &mfe_ces_R::solve_R ;

    // Geo
    void (mfe_geo_R::*build_geo_1)(const arma::vec&, const arma::vec&) = &mfe_geo_R::build_R ;
    void (mfe_geo_R::*build_geo_2)(double, bool) = &mfe_geo_R::build_R ;
    void (mfe_geo_R::*build_geo_3)(const arma::vec&, const arma::vec&, const arma::mat&, double, bool) = &mfe_geo_R::build_R ;

    // SEXP (mfe_geo_R::*solve_geo_1)() = &mfe_geo_R::solve_R ;
    SEXP (mfe_geo_R::*solve_geo_2)(Rcpp::CharacterVector) = &mfe_geo_R::solve_R ;
    SEXP (mfe_geo_R::*solve_geo_3)(Rcpp::CharacterVector, double tol_inp, int max_iter) = &mfe_geo_R::solve_R ;

    // Min
    void (mfe_min_R::*build_min_1)(const arma::vec&, const arma::vec&) = &mfe_min_R::build_R ;
    void (mfe_min_R::*build_min_2)(double, bool) = &mfe_min_R::build_R ;
    void (mfe_min_R::*build_min_3)(const arma::vec&, const arma::vec&, const arma::mat&, const arma::mat&, double, bool) = &mfe_min_R::build_R ;

    // SEXP (mfe_min_R::*solve_min_1)() = &mfe_min_R::solve_R ;
    SEXP (mfe_min_R::*solve_min_2)(Rcpp::CharacterVector) = &mfe_min_R::solve_R ;
    SEXP (mfe_min_R::*solve_min_3)(Rcpp::CharacterVector, double tol_inp, int max_iter) = &mfe_min_R::solve_R ;
  
    //
    // now we can declare the class

    // CD
    class_<trame::mfe<trame::mmfs::cd>>( "mfe_cd_cpp" )
        .default_constructor()

        // basic objects
        .field( "need_norm", &trame::mfe<trame::mmfs::cd>::need_norm )
        .field( "outside_option", &trame::mfe<trame::mmfs::cd>::outside_option )

        .field( "nbX", &trame::mfe<trame::mmfs::cd>::nbX )
        .field( "nbY", &trame::mfe<trame::mmfs::cd>::nbY )
    ;

    class_<mfe_cd_R>( "mfe_cd" )
        .derives<trame::mfe<trame::mmfs::cd>>( "mfe_cd_cpp" )
        .default_constructor()

        .method( "build", build_cd_1 )
        .method( "build", build_cd_2 )
        .method( "build", build_cd_3 )

        .method( "get_mmfs", &mfe_cd_R::get_mmfs )
        .method( "set_mmfs", &mfe_cd_R::set_mmfs )

        // .method( "solve", solve_cd_1 )
        .method( "solve", solve_cd_2 )
        .method( "solve", solve_cd_3 )
    ;

    // CES
    class_<trame::mfe<trame::mmfs::ces>>( "mfe_ces_cpp" )
        .default_constructor()

        // basic objects
        .field( "need_norm", &trame::mfe<trame::mmfs::ces>::need_norm )
        .field( "outside_option", &trame::mfe<trame::mmfs::ces>::outside_option )

        .field( "nbX", &trame::mfe<trame::mmfs::ces>::nbX )
        .field( "nbY", &trame::mfe<trame::mmfs::ces>::nbY )
    ;

    class_<mfe_ces_R>( "mfe_ces" )
        .derives<trame::mfe<trame::mmfs::ces>>( "mfe_ces_cpp" )
        .default_constructor()

        .method( "build", build_ces_1 )
        .method( "build", build_ces_2 )
        .method( "build", build_ces_3 )

        .method( "get_mmfs", &mfe_ces_R::get_mmfs )
        .method( "set_mmfs", &mfe_ces_R::set_mmfs )

        // .method( "solve", solve_ces_1 )
        .method( "solve", solve_ces_2 )
        .method( "solve", solve_ces_3 )
    ;

    // Geo
    class_<trame::mfe<trame::mmfs::geo>>( "mfe_geo_cpp" )
        .default_constructor()

        // basic objects
        .field( "need_norm", &trame::mfe<trame::mmfs::geo>::need_norm )
        .field( "outside_option", &trame::mfe<trame::mmfs::geo>::outside_option )

        .field( "nbX", &trame::mfe<trame::mmfs::geo>::nbX )
        .field( "nbY", &trame::mfe<trame::mmfs::geo>::nbY )
    ;

    class_<mfe_geo_R>( "mfe_geo" )
        .derives<trame::mfe<trame::mmfs::geo>>( "mfe_geo_cpp" )
        .default_constructor()

        .method( "build", build_geo_1 )
        .method( "build", build_geo_2 )
        .method( "build", build_geo_3 )

        .method( "get_mmfs", &mfe_geo_R::get_mmfs )
        .method( "set_mmfs", &mfe_geo_R::set_mmfs )

        // .method( "solve", solve_geo_1 )
        .method( "solve", solve_geo_2 )
        .method( "solve", solve_geo_3 )
    ;

    // Min
    class_<trame::mfe<trame::mmfs::min>>( "mfe_min_cpp" )
        .default_constructor()

        // basic objects
        .field( "need_norm", &trame::mfe<trame::mmfs::min>::need_norm )
        .field( "outside_option", &trame::mfe<trame::mmfs::min>::outside_option )

        .field( "nbX", &trame::mfe<trame::mmfs::min>::nbX )
        .field( "nbY", &trame::mfe<trame::mmfs::min>::nbY )
    ;

    class_<mfe_min_R>( "mfe_min" )
        .derives<trame::mfe<trame::mmfs::min>>( "mfe_min_cpp" )
        .default_constructor()

        .method( "build", build_min_1 )
        .method( "build", build_min_2 )
        .method( "build", build_min_3 )

        .method( "get_mmfs", &mfe_min_R::get_mmfs )
        .method( "set_mmfs", &mfe_min_R::set_mmfs )

        // .method( "solve", solve_min_1 )
        .method( "solve", solve_min_2 )
        .method( "solve", solve_min_3 )
    ;
}

// wrapper functions to catch errors and handle memory pointers

//
// CD

void mfe_cd_R::build_R(const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(n_inp, m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mfe_cd_R::build_R(double sigma_inp, bool need_norm_inp)
{
    try {
        this->build(sigma_inp, need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mfe_cd_R::build_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& lambda_inp, const arma::mat& phi_inp, double sigma_inp, bool need_norm_inp)
{
    try {
        this->build(sigma_inp,need_norm_inp);
        this->build(n_inp, m_inp, lambda_inp, phi_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

mmfs_cd_R mfe_cd_R::get_mmfs()
{
    mmfs_cd_R mmfs_obj_out = static_cast<mmfs_cd_R&>(mmfs_obj);

    return mmfs_obj_out;
}

void mfe_cd_R::set_mmfs(mmfs_cd_R mmfs_inp)
{
    try {
        mmfs_obj = static_cast<trame::mmfs::cd&>(mmfs_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

SEXP mfe_cd_R::solve_R(Rcpp::CharacterVector solver_inp)
{
    try {
        arma::mat mu_sol;
        bool success = this->solve(mu_sol, solver_inp[0]);
        //
        return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP mfe_cd_R::solve_R(Rcpp::CharacterVector solver_inp, double tol_inp, int max_iter_inp)
{
    try {
        arma::mat mu_sol;
        bool success = ipfp(*this, mu_sol, tol_inp, max_iter_inp);
        //
        return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

// SEXP mfe_cd_R::solve_R()
// {
//     try {
//         std::cout << "basic solver called" << std::endl;
//         arma::mat mu_sol;
//         bool success = this->solve(mu_sol);
//         //
//         return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
//     return R_NilValue;
// }

//
// CES

void mfe_ces_R::build_R(const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(n_inp, m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mfe_ces_R::build_R(double sigma_inp, bool need_norm_inp)
{
    try {
        this->build(sigma_inp, need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mfe_ces_R::build_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, double sigma_inp, bool need_norm_inp)
{
    try {
        this->build(sigma_inp, need_norm_inp);
        this->build(n_inp, m_inp, alpha_inp, gamma_inp, tau_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

mmfs_ces_R mfe_ces_R::get_mmfs()
{
    mmfs_ces_R mmfs_obj_out = static_cast<mmfs_ces_R&>(mmfs_obj);

    return mmfs_obj_out;
}

void mfe_ces_R::set_mmfs(mmfs_ces_R mmfs_inp)
{
    try {
        mmfs_obj = static_cast<trame::mmfs::ces&>(mmfs_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

// SEXP mfe_ces_R::solve_R()
// {
//     try {
//         arma::mat mu_sol;
//         bool success = this->solve(mu_sol);
//         //
//         return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
//     return R_NilValue;
// }

SEXP mfe_ces_R::solve_R(Rcpp::CharacterVector solver_inp)
{
    try {
        arma::mat mu_sol;
        bool success = this->solve(mu_sol, solver_inp[0]);
        //
        return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP mfe_ces_R::solve_R(Rcpp::CharacterVector solver_inp, double tol_inp, int max_iter_inp)
{
    try {
        arma::mat mu_sol;
        bool success = ipfp(*this, mu_sol, tol_inp, max_iter_inp);
        //
        return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

//
// Geo

void mfe_geo_R::build_R(const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(n_inp, m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mfe_geo_R::build_R(double sigma_inp, bool need_norm_inp)
{
    try {
        this->build(sigma_inp, need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mfe_geo_R::build_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, double sigma_inp, bool need_norm_inp)
{
    try {
        this->build(sigma_inp, need_norm_inp);
        this->build(n_inp, m_inp, phi_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

mmfs_geo_R mfe_geo_R::get_mmfs()
{
    mmfs_geo_R mmfs_obj_out = static_cast<mmfs_geo_R&>(mmfs_obj);

    return mmfs_obj_out;
}

void mfe_geo_R::set_mmfs(mmfs_geo_R mmfs_inp)
{
    try {
        mmfs_obj = static_cast<trame::mmfs::geo&>(mmfs_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

// SEXP mfe_geo_R::solve_R()
// {
//     try {
//         arma::mat mu_sol;
//         bool success = this->solve(mu_sol);
//         //
//         return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
//     return R_NilValue;
// }

SEXP mfe_geo_R::solve_R(Rcpp::CharacterVector solver_inp)
{
    try {
        arma::mat mu_sol;
        bool success = this->solve(mu_sol, solver_inp[0]);
        //
        return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP mfe_geo_R::solve_R(Rcpp::CharacterVector solver_inp, double tol_inp, int max_iter_inp)
{
    try {
        arma::mat mu_sol;
        bool success = ipfp(*this, mu_sol, tol_inp, max_iter_inp);
        //
        return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

//
// Min

void mfe_min_R::build_R(const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(n_inp, m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mfe_min_R::build_R(double sigma_inp, bool need_norm_inp)
{
    try {
        this->build(sigma_inp, need_norm_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void mfe_min_R::build_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, double sigma_inp, bool need_norm_inp)
{
    try {
        this->build(sigma_inp, need_norm_inp);
        this->build(n_inp, m_inp, alpha_inp, gamma_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

mmfs_min_R mfe_min_R::get_mmfs()
{
    mmfs_min_R mmfs_obj_out = static_cast<mmfs_min_R&>(mmfs_obj);

    return mmfs_obj_out;
}

void mfe_min_R::set_mmfs(mmfs_min_R mmfs_inp)
{
    try {
        mmfs_obj = static_cast<trame::mmfs::min&>(mmfs_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

// SEXP mfe_min_R::solve_R()
// {
//     try {
//         arma::mat mu_sol;
//         bool success = this->solve(mu_sol);
//         //
//         return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
//     return R_NilValue;
// }

SEXP mfe_min_R::solve_R(Rcpp::CharacterVector solver_inp)
{
    try {
        arma::mat mu_sol;
        bool success = this->solve(mu_sol, solver_inp[0]);
        //
        return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP mfe_min_R::solve_R(Rcpp::CharacterVector solver_inp, double tol_inp, int max_iter_inp)
{
    try {
        arma::mat mu_sol;
        bool success = ipfp(*this, mu_sol, tol_inp, max_iter_inp);
        //
        return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}
