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
 * general model class
 *
 * Keith O'Hara
 * 11/19/2016
 *
 * This version:
 * 05/27/2017
 */

class model_base
{
    public:
        // build objects
        bool need_norm;

        int nbX;
        int nbY;

        int dX;
        int dY;
        int dim_theta;

        arma::vec n;
        arma::vec m;
};

template<class Tm>
class model : public model_base
{
    Tm market_obj;
};

template<typename Tg, typename Th, typename Tt>
class model<dse<Tg,Th,Tt>> : public model_base
{
    public:
        // build objects
        arma::mat model_data;
        // arma::cube phi_xyk;

        dse<Tg,Th,Tt> market_obj;
        // member functions
        void build(const arma::cube& phi_xyk_inp);
        void build(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp);
        void build(const arma::mat& X_inp, const arma::mat& Y_inp);
        void build(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp);

        // void build_market_TU(const arma::mat& theta);
        // template<typename Ta, typename Tb> void build_market_TU(const arma::mat& theta, const Ta& arums_G_inp, const Tb& arums_H_inp);
        // template<typename Ta, typename Tb> void build_market_TU(const arma::mat& theta, const Ta& arums_G_inp, const Tb& arums_H_inp, int nbDraws, int seed);

        void model_to_market(const arma::mat& theta);

        void dtheta(const arma::mat* delta_theta_inp, arma::mat& dtheta_Psi_out);
        void dtheta(const arma::mat* delta_theta_inp, arma::mat& dtheta_Psi_out, arma::mat* dtheta_G_out, arma::mat* dtheta_H_out);

        void dtheta_mu(const arma::mat& theta, const arma::mat* dtheta, arma::mat& mu_out, arma::vec& mu_x0_out, arma::vec& mu_0y_out, arma::mat& dmu);

        bool mme(const arma::mat& mu_hat, arma::mat& theta_hat);
        bool mme(const arma::mat& mu_hat, arma::mat& theta_hat, double* val_out, arma::mat* mu_out, arma::mat* U_out, arma::mat* V_out);

        bool mle(const arma::mat& mu_hat, arma::mat& theta_hat, const arma::mat* theta_0_inp);

        // solve wrappers
        bool solve(arma::mat& mu_sol);
        bool solve(arma::mat& mu_sol, const char* solver);
        bool solve(arma::mat& mu_sol, arma::mat& U, arma::mat& V, const char* solver);

    private:
        // internal build functions
        void build_int(const arma::cube& phi_xyk_inp, const arma::vec* n_inp, const arma::vec* m_inp);
        void build_int(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec* n_inp, const arma::vec* m_inp);

        // arma::mat Phi_xy();
        arma::mat Phi_xy_theta(const arma::mat& theta);
        void initial_theta(arma::mat& params);

        // optimization-related objects
        bool model_mle_optim(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad, void* opt_data)> opt_objfn, void* opt_data, double* value_out, double* err_tol_inp, int* max_iter_inp);
        static double log_likelihood(const arma::vec& vals_inp, arma::vec* grad, void* opt_data);

        bool model_mme_optim(arma::vec& init_out_vals, std::function<double (const arma::vec& vals_inp, arma::vec* grad, void* opt_data)> opt_objfn, void* opt_data, double* value_out, double* err_tol_inp, int* max_iter_inp);
        static double model_mme_opt_objfn(const arma::vec& vals_inp, arma::vec* grad, void* opt_data);
};

#include "model_int.tpp"
#include "model_dse.tpp"
