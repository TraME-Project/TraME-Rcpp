/*################################################################################
  ##
  ##   Copyright (C) 2016-2017 Keith O'Hara
  ##
  ##   This file is part of the OptimLib C++ library.
  ##
  ##   OptimLib is free software: you can redistribute it and/or modify
  ##   it under the terms of the GNU General Public License as published by
  ##   the Free Software Foundation, either version 2 of the License, or
  ##   (at your option) any later version.
  ##
  ##   OptimLib is distributed in the hope that it will be useful,
  ##   but WITHOUT ANY WARRANTY; without even the implied warranty of
  ##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  ##   GNU General Public License for more details.
  ##
  ################################################################################*/

/*
 * Conjugate Gradient (CG) method for non-linear optimization
 *
 * Keith O'Hara
 * 12/23/2016
 *
 * This version:
 * 07/19/2017
 */

#include "optim.hpp"

bool
optim::cg_int(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad_out, void* opt_data)> opt_objfn, void* opt_data, double* value_out, opt_settings* settings_inp)
{
    // notation: 'p' stands for '+1'.
    //
    bool success = false;
    
    const int n_vals = init_out_vals.n_elem;

    //
    // CG settings

    opt_settings settings;

    if (settings_inp) {
        settings = *settings_inp;
    }
    
    const int conv_failure_switch = settings.conv_failure_switch;
    const int iter_max = settings.iter_max;
    const double err_tol = settings.err_tol;

    const int cg_method = settings.cg_method; // update method
    const double cg_restart_threshold = settings.cg_restart_threshold;

    const double wolfe_cons_1 = 1E-03; // line search tuning parameters
    const double wolfe_cons_2 = 0.10;

    //
    // initialization

    arma::vec x = init_out_vals;
    
    double t_init = 1;

    arma::vec grad(n_vals); // gradient
    opt_objfn(x,&grad,opt_data);

    double err = arma::accu(arma::abs(grad));
    if (err <= err_tol) {
        return true;
    }
    //
    arma::vec d = - grad, d_p;
    arma::vec x_p = x, grad_p = grad;

    double t = line_search_mt(t_init, x_p, grad_p, d, &wolfe_cons_1, &wolfe_cons_2, opt_objfn, opt_data);

    err = arma::accu(arma::abs(grad_p)); // check updated values
    if (err <= err_tol) {
        init_out_vals = x_p;
        return true;
    }

    //
    // begin loop

    int iter = 0;

    while (err > err_tol && iter < iter_max) {
        iter++;
        //
        double beta = cg_update(grad,grad_p,d,iter,cg_method,cg_restart_threshold);
        d_p = - grad_p + beta*d;
        //
        t_init = t * (arma::dot(grad,d) / arma::dot(grad_p,d_p));

        grad = grad_p;

        t = line_search_mt(t_init, x_p, grad_p, d, &wolfe_cons_1, &wolfe_cons_2, opt_objfn, opt_data);
        //
        err = arma::accu(arma::abs(grad_p));
        // err = std::max( arma::norm(grad_p, 2), arma::norm(x_p - x, 2) );

        d = d_p;
        x = x_p;
    }
    //
    error_reporting(init_out_vals,x_p,opt_objfn,opt_data,success,value_out,err,err_tol,iter,iter_max,conv_failure_switch);
    //
    return success;
}

bool
optim::cg(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad_out, void* opt_data)> opt_objfn, void* opt_data)
{
    return cg_int(init_out_vals,opt_objfn,opt_data,nullptr,nullptr);
}

bool
optim::cg(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad_out, void* opt_data)> opt_objfn, void* opt_data, opt_settings& settings)
{
    return cg_int(init_out_vals,opt_objfn,opt_data,nullptr,&settings);
}

bool
optim::cg(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad_out, void* opt_data)> opt_objfn, void* opt_data, double& value_out)
{
    return cg_int(init_out_vals,opt_objfn,opt_data,&value_out,nullptr);
}

bool
optim::cg(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad_out, void* opt_data)> opt_objfn, void* opt_data, double& value_out, opt_settings& settings)
{
    return cg_int(init_out_vals,opt_objfn,opt_data,&value_out,&settings);
}

//
// update formula

double optim::cg_update(const arma::vec& grad, const arma::vec& grad_p, const arma::vec& direc, const int iter, const int cg_method, const double cg_restart_threshold)
{
    // threshold test
    double ratio_value = std::abs( arma::dot(grad_p,grad) ) / arma::dot(grad_p,grad_p);

    if ( ratio_value > cg_restart_threshold ) {
        return 0.0;
    } else {
        double beta = 1.0;

        if (cg_method==1) { // Fletcher-Reeves (FR)
            beta = arma::dot(grad_p,grad_p) / arma::dot(grad,grad);
        } else if (cg_method==2) { // Polak-Ribiere (PR) + 
            beta = arma::dot(grad_p,grad_p - grad) / arma::dot(grad,grad);

            // beta = std::max(beta,0.0); 
        } else if (cg_method==3) { // FR-PR hybrid, see eq. 5.48 in Nocedal and Wright
            if (iter > 1) {
                const double beta_FR = arma::dot(grad_p,grad_p) / arma::dot(grad,grad);
                const double beta_PR = arma::dot(grad_p,grad_p - grad) / arma::dot(grad,grad);
                
                if (beta_PR < - beta_FR) {
                    beta = -beta_FR;
                } else if (std::abs(beta_PR) <= beta_FR) {
                    beta = beta_PR;
                } else { // beta_PR > beta_FR
                    beta = beta_FR;
                }
            } else { // default to PR+
                beta = arma::dot(grad_p,grad_p - grad) / arma::dot(grad,grad);

                // beta = std::max(beta,0.0);
            }
        } else if (cg_method==4) { // Hestenes-Stiefel
            beta = arma::dot(grad_p,grad_p - grad) / arma::dot(grad_p - grad,direc);
        } else if (cg_method==5) { // Dai-Yuan
            beta = arma::dot(grad_p,grad_p) / arma::dot(grad_p - grad,direc);
        } else if (cg_method==6) { // Hager-Zhang
            arma::vec y = grad_p - grad;

            arma::vec term_1 = y - 2*direc*(arma::dot(y,y) / arma::dot(y,direc));
            arma::vec term_2 = grad_p / arma::dot(y,direc);

            beta = arma::dot(term_1,term_2);
        }
        //
        beta = std::max(beta,0.0); 

        return beta;
    }
}
