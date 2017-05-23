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
 * Derived market classes to provide wrappers to the TraME library
 *
 * Keith O'Hara
 * 10/20/2016
 *
 * This version:
 * 11/13/2016
 */

class mfe_cd_R : public trame::mfe<trame::mmfs::cd>
{
    public:
        void build_R(arma::vec n_inp, arma::vec m_inp);
        void build_R(double sigma_inp, bool need_norm_inp);
        void build_R(arma::vec n_inp, arma::vec m_inp, double sigma_inp, bool need_norm_inp);
        void build_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp);

        mmfs_cd_R get_mmfs();
        void set_mmfs(mmfs_cd_R mmfs_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
};

class mfe_ces_R : public trame::mfe<trame::mmfs::ces>
{
    public:
        void build_R(arma::vec n_inp, arma::vec m_inp);
        void build_R(double sigma_inp, bool need_norm_inp);
        void build_R(arma::vec n_inp, arma::vec m_inp, double sigma_inp, bool need_norm_inp);
        void build_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, arma::mat tau_inp);

        mmfs_ces_R get_mmfs();
        void set_mmfs(mmfs_ces_R mmfs_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
};

class mfe_geo_R : public trame::mfe<trame::mmfs::geo>
{
    public:
        void build_R(arma::vec n_inp, arma::vec m_inp);
        void build_R(double sigma_inp, bool need_norm_inp);
        void build_R(arma::vec n_inp, arma::vec m_inp, double sigma_inp, bool need_norm_inp);
        void build_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp);

        mmfs_geo_R get_mmfs();
        void set_mmfs(mmfs_geo_R mmfs_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
};

class mfe_min_R : public trame::mfe<trame::mmfs::min>
{
    public:
        void build_R(arma::vec n_inp, arma::vec m_inp);
        void build_R(double sigma_inp, bool need_norm_inp);
        void build_R(arma::vec n_inp, arma::vec m_inp, double sigma_inp, bool need_norm_inp);
        void build_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp);

        mmfs_min_R get_mmfs();
        void set_mmfs(mmfs_min_R mmfs_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
};

/*
class dse_empirical_R : public trame::dse<trame::empirical>
{
    public:
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_LTU_R_int(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& lambda_inp, const arma::mat& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, bool need_norm_inp);
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_NTU_R_int(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_TU_R_int(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        
        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
        bool solve_R_int(arma::mat& mu_sol, const char* solver);

        empirical_R get_arums_G();
        void set_arums_G(empirical_R arums_G_inp);
        empirical_R get_arums_H();
        void set_arums_H(empirical_R arums_H_inp);
        void set_arums(empirical_R arums_G_inp, empirical_R arums_H_inp);

        transfers_R get_transfers_R();
        void set_transfers_R(transfers_R trans_obj_inp);
};

class dse_logit_R : public trame::dse<trame::logit>
{
    public:
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, logit_R arums_G_inp, logit_R arums_H_inp, bool need_norm_inp);
        
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, bool need_norm_inp);
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, logit_R arums_G_inp, logit_R arums_H_inp, bool need_norm_inp);
        
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, logit_R arums_G_inp, logit_R arums_H_inp, bool need_norm_inp);
        
        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        logit_R get_arums_G();
        void set_arums_G(logit_R arums_G_inp);
        logit_R get_arums_H();
        void set_arums_H(logit_R arums_H_inp);
        void set_arums(logit_R arums_G_inp, logit_R arums_H_inp);

        transfers_R get_transfers_R();
        void set_transfers_R(transfers_R trans_obj_inp);
};

class dse_none_R : public trame::dse<trame::none>
{
    public:
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, none_R arums_G_inp, none_R arums_H_inp, bool need_norm_inp);
        
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, bool need_norm_inp);
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, none_R arums_G_inp, none_R arums_H_inp, bool need_norm_inp);
        
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, none_R arums_G_inp, none_R arums_H_inp, bool need_norm_inp);
        
        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        none_R get_arums_G();
        void set_arums_G(none_R arums_G_inp);
        none_R get_arums_H();
        void set_arums_H(none_R arums_H_inp);
        void set_arums(none_R arums_G_inp, none_R arums_H_inp);

        transfers_R get_transfers_R();
        void set_transfers_R(transfers_R trans_obj_inp);
};

class dse_rsc_R : public trame::dse<trame::rsc>
{
    public:
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, rsc_R arums_G_inp, rsc_R arums_H_inp, bool need_norm_inp);
        
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, bool need_norm_inp);
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, rsc_R arums_G_inp, rsc_R arums_H_inp, bool need_norm_inp);
        
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, rsc_R arums_G_inp, rsc_R arums_H_inp, bool need_norm_inp);
        
        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rsc_R get_arums_G();
        void set_arums_G(rsc_R arums_G_inp);
        rsc_R get_arums_H();
        void set_arums_H(rsc_R arums_H_inp);
        void set_arums(rsc_R arums_G_inp, rsc_R arums_H_inp);

        transfers_R get_transfers_R();
        void set_transfers_R(transfers_R trans_obj_inp);
};

class dse_rusc_R : public trame::dse<trame::rusc>
{
    public:
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_LTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat lambda_inp, arma::mat phi_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp);
        
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, bool need_norm_inp);
        void build_NTU_R(arma::vec n_inp, arma::vec m_inp, arma::mat alpha_inp, arma::mat gamma_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp);
        
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, bool need_norm_inp);
        void build_TU_R(arma::vec n_inp, arma::vec m_inp, arma::mat phi_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp);
        
        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rusc_R get_arums_G();
        void set_arums_G(rusc_R arums_G_inp);
        rusc_R get_arums_H();
        void set_arums_H(rusc_R arums_H_inp);
        void set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp);

        transfers_R get_transfers_R();
        void set_transfers_R(transfers_R trans_obj_inp);
};

#include "trame_R_markets.tpp"
*/