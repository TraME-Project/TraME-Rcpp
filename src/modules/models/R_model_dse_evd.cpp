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
 * model<dse<logit,logit,.>> class module
 *
 * Keith O'Hara
 * 10/23/2016
 *
 * This version:
 * 09/13/2017
 */

#include "trameR.hpp"

RCPP_EXPOSED_CLASS(logit_R)

RCPP_EXPOSED_CLASS(transfers_etu_R)
RCPP_EXPOSED_CLASS(transfers_ltu_R)
RCPP_EXPOSED_CLASS(transfers_ntu_R)
RCPP_EXPOSED_CLASS(transfers_tu_R)

RCPP_EXPOSED_CLASS(dse_logit_etu_R)
RCPP_EXPOSED_CLASS(dse_logit_ltu_R)
RCPP_EXPOSED_CLASS(dse_logit_ntu_R)
RCPP_EXPOSED_CLASS(dse_logit_tu_R)

RCPP_EXPOSED_CLASS(model_dse_logit_etu_R)
// RCPP_EXPOSED_CLASS(model_dse_logit_ltu_R)
// RCPP_EXPOSED_CLASS(model_dse_logit_ntu_R)
RCPP_EXPOSED_CLASS(model_dse_logit_tu_R)

RCPP_MODULE(model_dse_logit_module)
{
    using namespace Rcpp ;

    //
    // function overloading requires some trickery

    // ETU
    void (model_dse_logit_etu_R::*build_ETU_1)(const arma::cube& phi_xyk_inp) = &model_dse_logit_etu_R::build_ETU_R ;
    void (model_dse_logit_etu_R::*build_ETU_2)(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_dse_logit_etu_R::build_ETU_R ;
    void (model_dse_logit_etu_R::*build_ETU_3)(const arma::mat& X_inp, const arma::mat& Y_inp) = &model_dse_logit_etu_R::build_ETU_R ;
    void (model_dse_logit_etu_R::*build_ETU_4)(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_dse_logit_etu_R::build_ETU_R ;

    SEXP (model_dse_logit_etu_R::*mle_ETU_1)(const arma::mat& mu_hat) = &model_dse_logit_etu_R::mle_ETU_R ;
    SEXP (model_dse_logit_etu_R::*mme_ETU_1)(const arma::mat& mu_hat) = &model_dse_logit_etu_R::mme_ETU_R ;

    // LTU
    // void (model_dse_logit_ltu_R::*build_LTU_1)(const arma::cube& phi_xyk_inp) = &model_dse_logit_ltu_R::build_LTU_R ;
    // void (model_dse_logit_ltu_R::*build_LTU_2)(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_dse_logit_ltu_R::build_LTU_R ;
    // void (model_dse_logit_ltu_R::*build_LTU_3)(const arma::mat& X_inp, const arma::mat& Y_inp) = &model_dse_logit_ltu_R::build_LTU_R ;
    // void (model_dse_logit_ltu_R::*build_LTU_4)(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_dse_logit_ltu_R::build_LTU_R ;

    // SEXP (model_dse_logit_ltu_R::*mle_LTU_1)(const arma::mat& mu_hat) = &model_dse_logit_ltu_R::mle_LTU_R ;
    // SEXP (model_dse_logit_ltu_R::*mme_LTU_1)(const arma::mat& mu_hat) = &model_dse_logit_ltu_R::mme_LTU_R ;
    
    // // NTU
    // void (model_dse_logit_ntu_R::*build_NTU_1)(const arma::cube& phi_xyk_inp) = &model_dse_logit_ntu_R::build_NTU_R ;
    // void (model_dse_logit_ntu_R::*build_NTU_2)(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_dse_logit_ntu_R::build_NTU_R ;
    // void (model_dse_logit_ntu_R::*build_NTU_3)(const arma::mat& X_inp, const arma::mat& Y_inp) = &model_dse_logit_ntu_R::build_NTU_R ;
    // void (model_dse_logit_ntu_R::*build_NTU_4)(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_dse_logit_ntu_R::build_NTU_R ;

    // SEXP (model_dse_logit_ntu_R::*mle_NTU_1)(const arma::mat& mu_hat) = &model_dse_logit_ntu_R::mle_NTU_R ;
    // SEXP (model_dse_logit_ntu_R::*mme_NTU_1)(const arma::mat& mu_hat) = &model_dse_logit_ntu_R::mme_NTU_R ;

    // TU
    void (model_dse_logit_tu_R::*build_TU_1)(const arma::cube& phi_xyk_inp) = &model_dse_logit_tu_R::build_TU_R ;
    void (model_dse_logit_tu_R::*build_TU_2)(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_dse_logit_tu_R::build_TU_R ;
    void (model_dse_logit_tu_R::*build_TU_3)(const arma::mat& X_inp, const arma::mat& Y_inp) = &model_dse_logit_tu_R::build_TU_R ;
    void (model_dse_logit_tu_R::*build_TU_4)(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp) = &model_dse_logit_tu_R::build_TU_R ;

    SEXP (model_dse_logit_tu_R::*mle_TU_1)(const arma::mat& mu_hat) = &model_dse_logit_tu_R::mle_TU_R ;
    SEXP (model_dse_logit_tu_R::*mme_TU_1)(const arma::mat& mu_hat) = &model_dse_logit_tu_R::mme_TU_R ;

    // now we can declare the class
    class_<trame::model_base>( "model_base" )
        .default_constructor()

        // basic objects
        .field( "need_norm", &trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>::need_norm )

        .field( "nbX", &trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>::nbX )
        .field( "nbY", &trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>::nbY )

        .field( "dX", &trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>::dX )
        .field( "dY", &trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>::dY )
        .field( "dim_theta", &trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>::dim_theta )

        .field( "n", &trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>::n )
        .field( "m", &trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>::m )
    ;

    class_<trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>>( "model_dse_logit_etu_cpp" )
        .derives<trame::model_base>( "model_base" )
        .default_constructor()
    ;

    class_<model_dse_logit_etu_R>( "model_dse_logit_etu" )
        // .derives<trame::dse_base>( "dse_base" )
        .derives<trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>>>( "model_dse_logit_etu_cpp" )
        .default_constructor()

        .method( "build", build_ETU_1 )
        .method( "build", build_ETU_2 )
        .method( "build", build_ETU_3 )
        .method( "build", build_ETU_4 )

        .method( "get_market", &model_dse_logit_etu_R::get_market )
        .method( "set_market", &model_dse_logit_etu_R::set_market )

        .method( "mle", mle_ETU_1 )
        .method( "mme", mme_ETU_1 )
    ;

    // class_<trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ltu>>>( "model_dse_logit_ltu" )
    //     .derives<trame::model_base>( "model_base" )
    //     .default_constructor()
    // ;

    // class_<model_dse_logit_ltu_R>( "model_dse_logit_ltu_R" )
    //     // .derives<trame::dse_base>( "dse_base" )
    //     .derives<trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ltu>>>( "model_dse_logit_ltu" )
    //     .default_constructor()

    //     .method( "build", build_LTU_1 )
    //     .method( "build", build_LTU_2 )
    //     .method( "build", build_LTU_3 )
    //     .method( "build", build_LTU_4 )

    //     .method( "get_market", &model_dse_logit_ltu_R::get_market )
    //     .method( "set_market", &model_dse_logit_ltu_R::set_market )

    //     .method( "mle", mle_LTU_1 )
    //     .method( "mme", mme_LTU_1 )
    // ;

    // class_<trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ntu>>>( "model_dse_logit_ntu" )
    //     .derives<trame::model_base>( "model_base" )
    //     .default_constructor()
    // ;

    // class_<model_dse_logit_ntu_R>( "model_dse_logit_ntu_R" )
    //     // .derives<trame::dse_base>( "dse_base" )
    //     .derives<trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ntu>>>( "model_dse_logit_ntu" )
    //     .default_constructor()

    //     .method( "build", build_NTU_1 )
    //     .method( "build", build_NTU_2 )
    //     .method( "build", build_NTU_3 )
    //     .method( "build", build_NTU_4 )

    //     .method( "get_market", &model_dse_logit_ntu_R::get_market )
    //     .method( "set_market", &model_dse_logit_ntu_R::set_market )

    //     .method( "mle", mle_NTU_1 )
    //     .method( "mme", mme_NTU_1 )
    // ;

    class_<trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::tu>>>( "model_dse_logit_tu_cpp" )
        .derives<trame::model_base>( "model_base" )
        .default_constructor()
    ;

    class_<model_dse_logit_tu_R>( "model_dse_logit_tu" )
        // .derives<trame::dse_base>( "dse_base" )
        .derives<trame::model<trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::tu>>>( "model_dse_logit_tu_cpp" )
        .default_constructor()

        .method( "build", build_TU_1 )
        .method( "build", build_TU_2 )
        .method( "build", build_TU_3 )
        .method( "build", build_TU_4 )

        .method( "get_market", &model_dse_logit_tu_R::get_market )
        .method( "set_market", &model_dse_logit_tu_R::set_market )

        .method( "mle", mle_TU_1 )
        .method( "mme", mme_TU_1 )
    ;

}

//
// wrapper functions to catch errors and handle memory pointers

// ETU

void model_dse_logit_etu_R::build_ETU_R(const arma::cube& phi_xyk_inp)
{
    try {
        this->build(phi_xyk_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void model_dse_logit_etu_R::build_ETU_R(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(phi_xyk_inp,n_inp,m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void model_dse_logit_etu_R::build_ETU_R(const arma::mat& X_inp, const arma::mat& Y_inp)
{
    try {
        this->build(X_inp,Y_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void model_dse_logit_etu_R::build_ETU_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(X_inp,Y_inp,n_inp,m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

SEXP model_dse_logit_etu_R::mle_ETU_R(const arma::mat& mu_hat)
{
    try {
        arma::mat theta_hat;

        bool success = this->mle(mu_hat,theta_hat,nullptr);

        return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP model_dse_logit_etu_R::mme_ETU_R(const arma::mat& mu_hat)
{
    try {
        arma::mat theta_hat;

        bool success = this->mme(mu_hat,theta_hat,nullptr);

        return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

dse_logit_etu_R model_dse_logit_etu_R::get_market()
{
    dse_logit_etu_R market_obj_out = static_cast<dse_logit_etu_R&>(market_obj);

    return market_obj_out;
}

void model_dse_logit_etu_R::set_market(dse_logit_etu_R market_obj_inp)
{
    try {
        market_obj = static_cast< trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>& >(market_obj_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

// LTU

// void model_dse_logit_ltu_R::build_LTU_R(const arma::cube& phi_xyk_inp)
// {
//     try {
//         this->build(phi_xyk_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// void model_dse_logit_ltu_R::build_LTU_R(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp)
// {
//     try {
//         this->build(phi_xyk_inp,n_inp,m_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// void model_dse_logit_ltu_R::build_LTU_R(const arma::mat& X_inp, const arma::mat& Y_inp)
// {
//     try {
//         this->build(X_inp,Y_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// void model_dse_logit_ltu_R::build_LTU_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp)
// {
//     try {
//         this->build(X_inp,Y_inp,n_inp,m_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// SEXP model_dse_logit_ltu_R::mle_LTU_R(const arma::mat& mu_hat)
// {
//     try {
//         arma::mat theta_hat;

//         bool success = this->mle(mu_hat,theta_hat,nullptr);

//         return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("success") = success);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
//     return R_NilValue;
// }

// SEXP model_dse_logit_ltu_R::mme_LTU_R(const arma::mat& mu_hat)
// {
//     try {
//         arma::mat theta_hat;

//         bool success = this->mme(mu_hat,theta_hat,nullptr);

//         return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("success") = success);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
//     return R_NilValue;
// }

// dse_logit_ltu_R model_dse_logit_ltu_R::get_market()
// {
//     dse_logit_ltu_R market_obj_out = static_cast<dse_logit_ltu_R&>(market_obj);

//     return market_obj_out;
// }

// void model_dse_logit_ltu_R::set_market(dse_logit_ltu_R market_obj_inp)
// {
//     try {
//         market_obj = static_cast< trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ltu>& >(market_obj_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// // NTU

// void model_dse_logit_ntu_R::build_NTU_R(const arma::cube& phi_xyk_inp)
// {
//     try {
//         this->build(phi_xyk_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// void model_dse_logit_ntu_R::build_NTU_R(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp)
// {
//     try {
//         this->build(phi_xyk_inp,n_inp,m_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// void model_dse_logit_ntu_R::build_NTU_R(const arma::mat& X_inp, const arma::mat& Y_inp)
// {
//     try {
//         this->build(X_inp,Y_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// void model_dse_logit_ntu_R::build_NTU_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp)
// {
//     try {
//         this->build(X_inp,Y_inp,n_inp,m_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }

// SEXP model_dse_logit_ntu_R::mle_NTU_R(const arma::mat& mu_hat)
// {
//     try {
//         arma::mat theta_hat;

//         bool success = this->mle(mu_hat,theta_hat,nullptr);

//         return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("success") = success);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
//     return R_NilValue;
// }

// SEXP model_dse_logit_ntu_R::mme_NTU_R(const arma::mat& mu_hat)
// {
//     try {
//         arma::mat theta_hat;

//         bool success = this->mme(mu_hat,theta_hat,nullptr);

//         return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("success") = success);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
//     return R_NilValue;
// }

// dse_logit_ntu_R model_dse_logit_ntu_R::get_market()
// {
//     dse_logit_ntu_R market_obj_out = static_cast<dse_logit_ntu_R&>(market_obj);

//     return market_obj_out;
// }

// void model_dse_logit_ntu_R::set_market(dse_logit_ntu_R market_obj_inp)
// {
//     try {
//         market_obj = static_cast< trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ntu>& >(market_obj_inp);
//     } catch( std::exception &ex ) {
//         forward_exception_to_r( ex );
//     } catch(...) {
//         ::Rf_error( "trame: C++ exception (unknown reason)" );
//     }
// }


// TU

void model_dse_logit_tu_R::build_TU_R(const arma::cube& phi_xyk_inp)
{
    try {
        this->build(phi_xyk_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void model_dse_logit_tu_R::build_TU_R(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(phi_xyk_inp,n_inp,m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void model_dse_logit_tu_R::build_TU_R(const arma::mat& X_inp, const arma::mat& Y_inp)
{
    try {
        this->build(X_inp,Y_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

void model_dse_logit_tu_R::build_TU_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp)
{
    try {
        this->build(X_inp,Y_inp,n_inp,m_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}

SEXP model_dse_logit_tu_R::mle_TU_R(const arma::mat& mu_hat)
{
    try {
        arma::mat theta_hat;

        bool success = this->mle(mu_hat,theta_hat,nullptr);

        return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

SEXP model_dse_logit_tu_R::mme_TU_R(const arma::mat& mu_hat)
{
    try {
        arma::mat theta_hat;

        bool success = this->mme(mu_hat,theta_hat,nullptr);

        return Rcpp::List::create(Rcpp::Named("theta_hat") = theta_hat, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}

dse_logit_tu_R model_dse_logit_tu_R::get_market()
{
    dse_logit_tu_R market_obj_out = static_cast<dse_logit_tu_R&>(market_obj);

    return market_obj_out;
}

void model_dse_logit_tu_R::set_market(dse_logit_tu_R market_obj_inp)
{
    try {
        market_obj = static_cast< trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::tu>& >(market_obj_inp);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
}
