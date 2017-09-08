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
 * dse<rusc,rusc,.> class module
 *
 * Keith O'Hara
 * 10/23/2016
 *
 * This version:
 * 08/13/2017
 */

 #include "trameR.hpp"
 
 RCPP_EXPOSED_CLASS(rusc_R)
 RCPP_EXPOSED_CLASS(transfers_etu_R)
 RCPP_EXPOSED_CLASS(transfers_ltu_R)
 RCPP_EXPOSED_CLASS(transfers_ntu_R)
 RCPP_EXPOSED_CLASS(transfers_tu_R)
 RCPP_EXPOSED_CLASS(dse_rusc_etu_R)
 RCPP_EXPOSED_CLASS(dse_rusc_ltu_R)
 RCPP_EXPOSED_CLASS(dse_rusc_ntu_R)
 RCPP_EXPOSED_CLASS(dse_rusc_tu_R)
 
 RCPP_MODULE(dse_rusc_module)
 {
     using namespace Rcpp ;
 
     //
     // function overloading requires some trickery
 
     // ETU
     void (dse_rusc_etu_R::*build_ETU_1)(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, arma::mat tau_inp, bool need_norm_inp) = &dse_rusc_etu_R::build_ETU_R ;
     void (dse_rusc_etu_R::*build_ETU_2)(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, arma::mat tau_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp) = &dse_rusc_etu_R::build_ETU_R ;
     SEXP (dse_rusc_etu_R::*solve_ETU_2)(Rcpp::CharacterVector solver_inp) = &dse_rusc_etu_R::solve_R ;
 
     // LTU
     void (dse_rusc_ltu_R::*build_LTU_1)(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, bool need_norm_inp) = &dse_rusc_ltu_R::build_LTU_R ;
     void (dse_rusc_ltu_R::*build_LTU_2)(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp) = &dse_rusc_ltu_R::build_LTU_R ;
     SEXP (dse_rusc_ltu_R::*solve_LTU_2)(Rcpp::CharacterVector solver_inp) = &dse_rusc_ltu_R::solve_R ;
     
     // NTU
     void (dse_rusc_ntu_R::*build_NTU_1)(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, bool need_norm_inp) = &dse_rusc_ntu_R::build_NTU_R ;
     void (dse_rusc_ntu_R::*build_NTU_2)(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp) = &dse_rusc_ntu_R::build_NTU_R ;
     SEXP (dse_rusc_ntu_R::*solve_NTU_2)(Rcpp::CharacterVector solver_inp) = &dse_rusc_ntu_R::solve_R ;
 
     // TU
     void (dse_rusc_tu_R::*build_TU_1)(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, bool need_norm_inp) = &dse_rusc_tu_R::build_TU_R ;
     void (dse_rusc_tu_R::*build_TU_2)(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp) = &dse_rusc_tu_R::build_TU_R ;
     SEXP (dse_rusc_tu_R::*solve_TU_2)(Rcpp::CharacterVector solver_inp) = &dse_rusc_tu_R::solve_R ;
 
     // now we can declare the class
     class_<trame::dse_base>( "dse_base" )
         .default_constructor()
 
         // basic objects
         .field( "ETU", &trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>::ETU )
         .field( "LTU", &trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>::LTU )
         .field( "NTU", &trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>::NTU )
         .field( "TU", &trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>::TU )
 
         .field( "need_norm", &trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>::need_norm )
         .field( "outside_option", &trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>::outside_option )
 
         .field( "nbX", &trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>::nbX )
         .field( "nbY", &trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>::nbY )
     ;
 
     class_<trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>>( "dse_rusc_etu_cpp" )
         .derives<trame::dse_base>( "dse_base" )
         .default_constructor()
     ;
 
     class_<dse_rusc_etu_R>( "dse_rusc_etu" )
         // .derives<trame::dse_base>( "dse_base" )
         .derives<trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>>( "dse_rusc_etu_cpp" )
         .default_constructor()
 
         .method( "build", build_ETU_1 )
         .method( "build", build_ETU_2 )
 
         // .method( "solve", solve_R_1 )
         .method( "solve", solve_ETU_2 )
 
         .method( "get_arums_G", &dse_rusc_etu_R::get_arums_G )
         .method( "set_arums_G", &dse_rusc_etu_R::set_arums_G )
         .method( "get_arums_H", &dse_rusc_etu_R::get_arums_H )
         .method( "set_arums_H", &dse_rusc_etu_R::set_arums_H )
         .method( "set_arums", &dse_rusc_etu_R::set_arums )
 
         .method( "get_transfers", &dse_rusc_etu_R::get_transfers_R )
         .method( "set_transfers", &dse_rusc_etu_R::set_transfers_R )
     ;
 
     class_<trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::ltu>>( "dse_rusc_ltu_cpp" )
         .derives<trame::dse_base>( "dse_base" )
         .default_constructor()
     ;
 
     class_<dse_rusc_ltu_R>( "dse_rusc_ltu" )
         // .derives<trame::dse_base>( "dse_base" )
         .derives<trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::ltu>>( "dse_rusc_ltu_cpp" )
         .default_constructor()
 
         .method( "build", build_LTU_1 )
         .method( "build", build_LTU_2 )
 
         // .method( "solve", solve_R_1 )
         .method( "solve", solve_LTU_2 )
 
         .method( "get_arums_G", &dse_rusc_ltu_R::get_arums_G )
         .method( "set_arums_G", &dse_rusc_ltu_R::set_arums_G )
         .method( "get_arums_H", &dse_rusc_ltu_R::get_arums_H )
         .method( "set_arums_H", &dse_rusc_ltu_R::set_arums_H )
         .method( "set_arums", &dse_rusc_ltu_R::set_arums )
 
         .method( "get_transfers", &dse_rusc_ltu_R::get_transfers_R )
         .method( "set_transfers", &dse_rusc_ltu_R::set_transfers_R )
     ;
 
     class_<trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::ntu>>( "dse_rusc_ntu_cpp" )
         .derives<trame::dse_base>( "dse_base" )
         .default_constructor()
     ;
 
     class_<dse_rusc_ntu_R>( "dse_rusc_ntu" )
         // .derives<trame::dse_base>( "dse_base" )
         .derives<trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::ntu>>( "dse_rusc_ntu_cpp" )
         .default_constructor()
 
         .method( "build", build_NTU_1 )
         .method( "build", build_NTU_2 )
 
         // .method( "solve", solve_R_1 )
         .method( "solve", solve_NTU_2 )
 
         .method( "get_arums_G", &dse_rusc_ntu_R::get_arums_G )
         .method( "set_arums_G", &dse_rusc_ntu_R::set_arums_G )
         .method( "get_arums_H", &dse_rusc_ntu_R::get_arums_H )
         .method( "set_arums_H", &dse_rusc_ntu_R::set_arums_H )
         .method( "set_arums", &dse_rusc_ntu_R::set_arums )
 
         .method( "get_transfers", &dse_rusc_ntu_R::get_transfers_R )
         .method( "set_transfers", &dse_rusc_ntu_R::set_transfers_R )
     ;
 
     class_<trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::tu>>( "dse_rusc_tu_cpp" )
         .derives<trame::dse_base>( "dse_base" )
         .default_constructor()
     ;
 
     class_<dse_rusc_tu_R>( "dse_rusc_tu" )
         // .derives<trame::dse_base>( "dse_base" )
         .derives<trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::tu>>( "dse_rusc_tu_cpp" )
         .default_constructor()
 
         .method( "build", build_TU_1 )
         .method( "build", build_TU_2 )
 
         // .method( "solve", solve_R_1 )
         .method( "solve", solve_TU_2 )
 
         .method( "get_arums_G", &dse_rusc_tu_R::get_arums_G )
         .method( "set_arums_G", &dse_rusc_tu_R::set_arums_G )
         .method( "get_arums_H", &dse_rusc_tu_R::get_arums_H )
         .method( "set_arums_H", &dse_rusc_tu_R::set_arums_H )
         .method( "set_arums", &dse_rusc_tu_R::set_arums )
 
         .method( "get_transfers", &dse_rusc_tu_R::get_transfers_R )
         .method( "set_transfers", &dse_rusc_tu_R::set_transfers_R )
     ;
 }
 
 // wrapper functions to catch errors and handle memory pointers
 void dse_rusc_etu_R::build_ETU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, arma::mat tau_inp, bool need_norm_inp)
 {
     try {
         int nbX = n_inp.n_elem;
         int nbY = m_inp.n_elem;
 
         trame::arums::rusc rusc_1(nbX,nbY), rusc_2(nbY,nbX);
         this->build(n_inp,m_inp,alpha_inp,gamma_inp,tau_inp,rusc_1,rusc_2,need_norm_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 void dse_rusc_etu_R::build_ETU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, arma::mat tau_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp)
 {
     try {
         trame::arums::rusc rusc_1 = static_cast<trame::arums::rusc&>(arums_G_inp);
         trame::arums::rusc rusc_2 = static_cast<trame::arums::rusc&>(arums_H_inp);
 
         this->build(n_inp,m_inp,alpha_inp,gamma_inp,tau_inp,rusc_1,rusc_2,need_norm_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 // SEXP dse_rusc_R::solve_R()
 // {
 //     try {
 //         arma::mat mu_sol;
 //         bool success = this->solve(mu_sol, (char*) "jacobi");
 //         //
 //         return Rcpp::List::create(Rcpp::Named("mu") = mu_sol, Rcpp::Named("success") = success);
 //     } catch( std::exception &ex ) {
 //         forward_exception_to_r( ex );
 //     } catch(...) {
 //         ::Rf_error( "trame: C++ exception (unknown reason)" );
 //     }
 //     return R_NilValue;
 // }
 
 SEXP dse_rusc_etu_R::solve_R(Rcpp::CharacterVector solver_inp)
 {
     try {
         arma::mat mu_sol;
         // char* solver = solver_inp[0];
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
 
 rusc_R dse_rusc_etu_R::get_arums_G()
 {
     rusc_R arums_obj_out = static_cast<rusc_R&>(arums_G);
 
     return arums_obj_out;
 }
 
 void dse_rusc_etu_R::set_arums_G(rusc_R arums_G_inp)
 {
     try {
         arums_G = static_cast<trame::arums::rusc&>(arums_G_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 rusc_R dse_rusc_etu_R::get_arums_H()
 {
     rusc_R arums_obj_out = static_cast<rusc_R&>(arums_H);
 
     return arums_obj_out;
 }
 
 void dse_rusc_etu_R::set_arums_H(rusc_R arums_H_inp)
 {
     try {
         arums_H = static_cast<trame::arums::rusc&>(arums_H_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 void dse_rusc_etu_R::set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp)
 {
     try {
         arums_G = static_cast<trame::arums::rusc&>(arums_G_inp);
         arums_H = static_cast<trame::arums::rusc&>(arums_H_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 transfers_etu_R dse_rusc_etu_R::get_transfers_R()
 {
     transfers_etu_R trans_obj_out = static_cast<transfers_etu_R&>(trans_obj);
 
     return trans_obj_out;
 }
 
 void dse_rusc_etu_R::set_transfers_R(transfers_etu_R trans_obj_inp)
 {
     try {
         trans_obj = static_cast<trame::transfers::etu&>(trans_obj_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 //
 // LTU
 
 void dse_rusc_ltu_R::build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, bool need_norm_inp)
 {
     try {
         int nbX = n_inp.n_elem;
         int nbY = m_inp.n_elem;
 
         trame::arums::rusc rusc_1(nbX,nbY), rusc_2(nbY,nbX);
         this->build(n_inp,m_inp,lambda_inp,phi_inp,rusc_1,rusc_2,need_norm_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 void dse_rusc_ltu_R::build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp)
 {
     try {
         trame::arums::rusc rusc_1 = static_cast<trame::arums::rusc&>(arums_G_inp);
         trame::arums::rusc rusc_2 = static_cast<trame::arums::rusc&>(arums_H_inp);
 
         this->build(n_inp,m_inp,lambda_inp,phi_inp,rusc_1,rusc_2,need_norm_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 SEXP dse_rusc_ltu_R::solve_R(Rcpp::CharacterVector solver_inp)
 {
     try {
         arma::mat mu_sol;
         // char* solver = solver_inp[0];
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
 
 rusc_R dse_rusc_ltu_R::get_arums_G()
 {
     rusc_R arums_obj_out = static_cast<rusc_R&>(arums_G);
 
     return arums_obj_out;
 }
 
 void dse_rusc_ltu_R::set_arums_G(rusc_R arums_G_inp)
 {
     try {
         arums_G = static_cast<trame::arums::rusc&>(arums_G_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 rusc_R dse_rusc_ltu_R::get_arums_H()
 {
     rusc_R arums_obj_out = static_cast<rusc_R&>(arums_H);
 
     return arums_obj_out;
 }
 
 void dse_rusc_ltu_R::set_arums_H(rusc_R arums_H_inp)
 {
     try {
         arums_H = static_cast<trame::arums::rusc&>(arums_H_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 void dse_rusc_ltu_R::set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp)
 {
     try {
         arums_G = static_cast<trame::arums::rusc&>(arums_G_inp);
         arums_H = static_cast<trame::arums::rusc&>(arums_H_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 transfers_ltu_R dse_rusc_ltu_R::get_transfers_R()
 {
     transfers_ltu_R trans_obj_out = static_cast<transfers_ltu_R&>(trans_obj);
 
     return trans_obj_out;
 }
 
 void dse_rusc_ltu_R::set_transfers_R(transfers_ltu_R trans_obj_inp)
 {
     try {
         trans_obj = static_cast<trame::transfers::ltu&>(trans_obj_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 //
 // NTU
 
 void dse_rusc_ntu_R::build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, bool need_norm_inp)
 {
     try {
         int nbX = n_inp.n_elem;
         int nbY = m_inp.n_elem;
 
         trame::arums::rusc rusc_1(nbX,nbY), rusc_2(nbY,nbX);
         this->build(n_inp,m_inp,alpha_inp,gamma_inp,rusc_1,rusc_2,need_norm_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 void dse_rusc_ntu_R::build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp)
 {
     try {
         trame::arums::rusc rusc_1 = static_cast<trame::arums::rusc&>(arums_G_inp);
         trame::arums::rusc rusc_2 = static_cast<trame::arums::rusc&>(arums_H_inp);
 
         this->build(n_inp,m_inp,alpha_inp,gamma_inp,rusc_1,rusc_2,need_norm_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 SEXP dse_rusc_ntu_R::solve_R(Rcpp::CharacterVector solver_inp)
 {
     try {
         arma::mat mu_sol;
         // char* solver = solver_inp[0];
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
 
 rusc_R dse_rusc_ntu_R::get_arums_G()
 {
     rusc_R arums_obj_out = static_cast<rusc_R&>(arums_G);
 
     return arums_obj_out;
 }
 
 void dse_rusc_ntu_R::set_arums_G(rusc_R arums_G_inp)
 {
     try {
         arums_G = static_cast<trame::arums::rusc&>(arums_G_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 rusc_R dse_rusc_ntu_R::get_arums_H()
 {
     rusc_R arums_obj_out = static_cast<rusc_R&>(arums_H);
 
     return arums_obj_out;
 }
 
 void dse_rusc_ntu_R::set_arums_H(rusc_R arums_H_inp)
 {
     try {
         arums_H = static_cast<trame::arums::rusc&>(arums_H_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 void dse_rusc_ntu_R::set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp)
 {
     try {
         arums_G = static_cast<trame::arums::rusc&>(arums_G_inp);
         arums_H = static_cast<trame::arums::rusc&>(arums_H_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 transfers_ntu_R dse_rusc_ntu_R::get_transfers_R()
 {
     transfers_ntu_R trans_obj_out = static_cast<transfers_ntu_R&>(trans_obj);
 
     return trans_obj_out;
 }
 
 void dse_rusc_ntu_R::set_transfers_R(transfers_ntu_R trans_obj_inp)
 {
     try {
         trans_obj = static_cast<trame::transfers::ntu&>(trans_obj_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 //
 // TU
 
 void dse_rusc_tu_R::build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, bool need_norm_inp)
 {
     try {
         int nbX = n_inp.n_elem;
         int nbY = m_inp.n_elem;
 
         trame::arums::rusc rusc_1(nbX,nbY), rusc_2(nbY,nbX);
         this->build(n_inp,m_inp,phi_inp,rusc_1,rusc_2,need_norm_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 void dse_rusc_tu_R::build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp)
 {
     try {
         trame::arums::rusc rusc_1 = static_cast<trame::arums::rusc&>(arums_G_inp);
         trame::arums::rusc rusc_2 = static_cast<trame::arums::rusc&>(arums_H_inp);
 
         this->build(n_inp,m_inp,phi_inp,rusc_1,rusc_2,need_norm_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 SEXP dse_rusc_tu_R::solve_R(Rcpp::CharacterVector solver_inp)
 {
     try {
         arma::mat mu_sol;
         // char* solver = solver_inp[0];
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
 
 rusc_R dse_rusc_tu_R::get_arums_G()
 {
     rusc_R arums_obj_out = static_cast<rusc_R&>(arums_G);
 
     return arums_obj_out;
 }
 
 void dse_rusc_tu_R::set_arums_G(rusc_R arums_G_inp)
 {
     try {
         arums_G = static_cast<trame::arums::rusc&>(arums_G_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 rusc_R dse_rusc_tu_R::get_arums_H()
 {
     rusc_R arums_obj_out = static_cast<rusc_R&>(arums_H);
 
     return arums_obj_out;
 }
 
 void dse_rusc_tu_R::set_arums_H(rusc_R arums_H_inp)
 {
     try {
         arums_H = static_cast<trame::arums::rusc&>(arums_H_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 void dse_rusc_tu_R::set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp)
 {
     try {
         arums_G = static_cast<trame::arums::rusc&>(arums_G_inp);
         arums_H = static_cast<trame::arums::rusc&>(arums_H_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 
 transfers_tu_R dse_rusc_tu_R::get_transfers_R()
 {
     transfers_tu_R trans_obj_out = static_cast<transfers_tu_R&>(trans_obj);
 
     return trans_obj_out;
 }
 
 void dse_rusc_tu_R::set_transfers_R(transfers_tu_R trans_obj_inp)
 {
     try {
         trans_obj = static_cast<trame::transfers::tu&>(trans_obj_inp);
     } catch( std::exception &ex ) {
         forward_exception_to_r( ex );
     } catch(...) {
         ::Rf_error( "trame: C++ exception (unknown reason)" );
     }
 }
 