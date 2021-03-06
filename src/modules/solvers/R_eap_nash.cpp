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
 * EAP Nash solver
 *
 * Keith O'Hara
 * 09/15/2017
 */

#include "R_solvers.hpp"

RCPP_EXPOSED_CLASS(dse_empirical_etu_R)
RCPP_EXPOSED_CLASS(dse_empirical_ltu_R)
RCPP_EXPOSED_CLASS(dse_empirical_ntu_R)
RCPP_EXPOSED_CLASS(dse_empirical_tu_R)

RCPP_EXPOSED_CLASS(dse_logit_etu_R)
RCPP_EXPOSED_CLASS(dse_logit_ltu_R)
RCPP_EXPOSED_CLASS(dse_logit_ntu_R)
RCPP_EXPOSED_CLASS(dse_logit_tu_R)

RCPP_EXPOSED_CLASS(dse_none_etu_R)
RCPP_EXPOSED_CLASS(dse_none_ltu_R)
RCPP_EXPOSED_CLASS(dse_none_ntu_R)
RCPP_EXPOSED_CLASS(dse_none_tu_R)

RCPP_EXPOSED_CLASS(dse_rsc_etu_R)
RCPP_EXPOSED_CLASS(dse_rsc_ltu_R)
RCPP_EXPOSED_CLASS(dse_rsc_ntu_R)
RCPP_EXPOSED_CLASS(dse_rsc_tu_R)

RCPP_EXPOSED_CLASS(dse_rusc_etu_R)
RCPP_EXPOSED_CLASS(dse_rusc_ltu_R)
RCPP_EXPOSED_CLASS(dse_rusc_ntu_R)
RCPP_EXPOSED_CLASS(dse_rusc_tu_R)

SEXP eap_nash_R(SEXP market_inp, SEXP x_first_inp)
{
    try {
        bool x_first = Rcpp::as<bool>(x_first_inp);
        bool success = false;
        arma::mat mu_out, u_out, v_out;
        arma::vec mu_x0_out, mu_0y_out;

        double err_tol = 1E-08;
        trame::uint_t max_iter = 5000U;

        if (Rf_inherits(market_inp, "Rcpp_dse_empirical_etu")) {
            dse_empirical_etu_R* market_obj = Rcpp::as<dse_empirical_etu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_empirical_ltu")) {
            dse_empirical_ltu_R* market_obj = Rcpp::as<dse_empirical_ltu_R*>(market_inp);
            
            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_empirical_ntu")) {
            dse_empirical_ntu_R* market_obj = Rcpp::as<dse_empirical_ntu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_empirical_tu")) {
            dse_empirical_tu_R* market_obj = Rcpp::as<dse_empirical_tu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        //
        else if (Rf_inherits(market_inp, "Rcpp_dse_logit_etu")) {
            dse_logit_etu_R* market_obj = Rcpp::as<dse_logit_etu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_logit_ltu")) {
            dse_logit_ltu_R* market_obj = Rcpp::as<dse_logit_ltu_R*>(market_inp);
            
            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_logit_ntu")) {
            dse_logit_ntu_R* market_obj = Rcpp::as<dse_logit_ntu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_logit_tu")) {
            dse_logit_tu_R* market_obj = Rcpp::as<dse_logit_tu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        //
        else if (Rf_inherits(market_inp, "Rcpp_dse_none_etu")) {
            dse_none_etu_R* market_obj = Rcpp::as<dse_none_etu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_none_ltu")) {
            dse_none_ltu_R* market_obj = Rcpp::as<dse_none_ltu_R*>(market_inp);
            
            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_none_ntu")) {
            dse_none_ntu_R* market_obj = Rcpp::as<dse_none_ntu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_none_tu")) {
            dse_none_tu_R* market_obj = Rcpp::as<dse_none_tu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        //
        else if (Rf_inherits(market_inp, "Rcpp_dse_rsc_etu")) {
            dse_rsc_etu_R* market_obj = Rcpp::as<dse_rsc_etu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_rsc_ltu")) {
            dse_rsc_ltu_R* market_obj = Rcpp::as<dse_rsc_ltu_R*>(market_inp);
            
            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_rsc_ntu")) {
            dse_rsc_ntu_R* market_obj = Rcpp::as<dse_rsc_ntu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_rsc_tu")) {
            dse_rsc_tu_R* market_obj = Rcpp::as<dse_rsc_tu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        //
        else if (Rf_inherits(market_inp, "Rcpp_dse_rusc_etu")) {
            dse_rusc_etu_R* market_obj = Rcpp::as<dse_rusc_etu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_rusc_ltu")) {
            dse_rusc_ltu_R* market_obj = Rcpp::as<dse_rusc_ltu_R*>(market_inp);
            
            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_rusc_ntu")) {
            dse_rusc_ntu_R* market_obj = Rcpp::as<dse_rusc_ntu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        else if (Rf_inherits(market_inp, "Rcpp_dse_rusc_tu")) {
            dse_rusc_tu_R* market_obj = Rcpp::as<dse_rusc_tu_R*>(market_inp);

            success = trame::eap_nash_int(*market_obj,&mu_out,&mu_x0_out,&mu_0y_out,&u_out,&v_out,x_first,err_tol,max_iter);
        }
        //
        else {
            ::Rf_error( "trame: unrecognized market type" );
            return R_NilValue;
        }

        return Rcpp::List::create(Rcpp::Named("mu") = mu_out, Rcpp::Named("mu_x0") = mu_x0_out, Rcpp::Named("mu_0y") = mu_0y_out, Rcpp::Named("u") = u_out, Rcpp::Named("v") = v_out, Rcpp::Named("success") = success);
    } catch( std::exception &ex ) {
        forward_exception_to_r( ex );
    } catch(...) {
        ::Rf_error( "trame: C++ exception (unknown reason)" );
    }
    return R_NilValue;
}
