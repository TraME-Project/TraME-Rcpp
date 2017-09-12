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
 * 08/13/2017
 */

//
// DSE-empirical

/*
class dse_empirical_R : public trame::dse<trame::empirical>
{
    public:
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& lambda_inp, const arma::mat& phi_inp, bool need_norm_inp);
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& lambda_inp, const arma::mat& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_LTU_R_int(const const arma::vec&& n_inp, const const arma::vec&& m_inp, const const arma::mat&& lambda_inp, const const arma::mat&& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_NTU_R_int(const const arma::vec&& n_inp, const const arma::vec&& m_inp, const const arma::mat&& alpha_inp, const const arma::mat&& gamma_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, bool need_norm_inp);
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_TU_R_int(const const arma::vec&& n_inp, const const arma::vec&& m_inp, const const arma::mat&& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        
        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);
        bool solve_R_int(const arma::mat&& mu_sol, const char* solver);

        empirical_R get_arums_G();
        void set_arums_G(empirical_R arums_G_inp);
        empirical_R get_arums_H();
        void set_arums_H(empirical_R arums_H_inp);
        void set_arums(empirical_R arums_G_inp, empirical_R arums_H_inp);

        transfers_R get_transfers_R();
        void set_transfers_R(transfers_R trans_obj_inp);
};
*/

class dse_empirical_etu_R : public trame::dse<trame::arums::empirical,trame::arums::empirical,trame::transfers::etu>
{
    public:
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, bool need_norm_inp);
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_ETU_R_int(const const arma::vec&& n_inp, const const arma::vec&& m_inp, const const arma::mat&& alpha_inp, const const arma::mat&& gamma_inp, const const arma::mat&& tau_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);

        transfers_etu_R get_transfers_R();
        void set_transfers_R(transfers_etu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        empirical_R get_arums_G();
        void set_arums_G(empirical_R arums_G_inp);
        empirical_R get_arums_H();
        void set_arums_H(empirical_R arums_H_inp);
        void set_arums(empirical_R arums_G_inp, empirical_R arums_H_inp);
};

class dse_empirical_ltu_R : public trame::dse<trame::arums::empirical,trame::arums::empirical,trame::transfers::ltu>
{
    public:
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_LTU_R_int(const const arma::vec&& n_inp, const const arma::vec&& m_inp, const const arma::mat&& lambda_inp, const const arma::mat&& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);

        transfers_ltu_R get_transfers_R();
        void set_transfers_R(transfers_ltu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        empirical_R get_arums_G();
        void set_arums_G(empirical_R arums_G_inp);
        empirical_R get_arums_H();
        void set_arums_H(empirical_R arums_H_inp);
        void set_arums(empirical_R arums_G_inp, empirical_R arums_H_inp);
};

class dse_empirical_ntu_R : public trame::dse<trame::arums::empirical,trame::arums::empirical,trame::transfers::ntu>
{
    public:
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_NTU_R_int(const const arma::vec&& n_inp, const const arma::vec&& m_inp, const const arma::mat&& alpha_inp, const const arma::mat&& gamma_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);

        transfers_ntu_R get_transfers_R();
        void set_transfers_R(transfers_ntu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        empirical_R get_arums_G();
        void set_arums_G(empirical_R arums_G_inp);
        empirical_R get_arums_H();
        void set_arums_H(empirical_R arums_H_inp);
        void set_arums(empirical_R arums_G_inp, empirical_R arums_H_inp);
};

class dse_empirical_tu_R : public trame::dse<trame::arums::empirical,trame::arums::empirical,trame::transfers::tu>
{
    public:
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, bool need_norm_inp);
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);
        template<typename Ta> void build_TU_R_int(const const arma::vec&& n_inp, const const arma::vec&& m_inp, const const arma::mat&& phi_inp, SEXP arums_G_inp, SEXP arums_H_inp, bool need_norm_inp);

        transfers_tu_R get_transfers_R();
        void set_transfers_R(transfers_tu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        empirical_R get_arums_G();
        void set_arums_G(empirical_R arums_G_inp);
        empirical_R get_arums_H();
        void set_arums_H(empirical_R arums_H_inp);
        void set_arums(empirical_R arums_G_inp, empirical_R arums_H_inp);
};

#include "R_dse.tpp"

//
// DSE-logit

class dse_logit_etu_R : public trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu>
{
    public:
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, bool need_norm_inp);
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, logit_R arums_G_inp, logit_R arums_H_inp, bool need_norm_inp);

        transfers_etu_R get_transfers_R();
        void set_transfers_R(transfers_etu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        logit_R get_arums_G();
        void set_arums_G(logit_R arums_G_inp);
        logit_R get_arums_H();
        void set_arums_H(logit_R arums_H_inp);
        void set_arums(logit_R arums_G_inp, logit_R arums_H_inp);
};

class dse_logit_ltu_R : public trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ltu>
{
    public:
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, logit_R arums_G_inp, logit_R arums_H_inp, bool need_norm_inp);

        transfers_ltu_R get_transfers_R();
        void set_transfers_R(transfers_ltu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        logit_R get_arums_G();
        void set_arums_G(logit_R arums_G_inp);
        logit_R get_arums_H();
        void set_arums_H(logit_R arums_H_inp);
        void set_arums(logit_R arums_G_inp, logit_R arums_H_inp);
};

class dse_logit_ntu_R : public trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ntu>
{
    public:
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, logit_R arums_G_inp, logit_R arums_H_inp, bool need_norm_inp);

        transfers_ntu_R get_transfers_R();
        void set_transfers_R(transfers_ntu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        logit_R get_arums_G();
        void set_arums_G(logit_R arums_G_inp);
        logit_R get_arums_H();
        void set_arums_H(logit_R arums_H_inp);
        void set_arums(logit_R arums_G_inp, logit_R arums_H_inp);
};

class dse_logit_tu_R : public trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::tu>
{
    public:
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, bool need_norm_inp);
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, logit_R arums_G_inp, logit_R arums_H_inp, bool need_norm_inp);

        transfers_tu_R get_transfers_R();
        void set_transfers_R(transfers_tu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        logit_R get_arums_G();
        void set_arums_G(logit_R arums_G_inp);
        logit_R get_arums_H();
        void set_arums_H(logit_R arums_H_inp);
        void set_arums(logit_R arums_G_inp, logit_R arums_H_inp);
};

//
// DSE-none

class dse_none_etu_R : public trame::dse<trame::arums::none,trame::arums::none,trame::transfers::etu>
{
    public:
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, bool need_norm_inp);
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, none_R arums_G_inp, none_R arums_H_inp, bool need_norm_inp);

        transfers_etu_R get_transfers_R();
        void set_transfers_R(transfers_etu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        none_R get_arums_G();
        void set_arums_G(none_R arums_G_inp);
        none_R get_arums_H();
        void set_arums_H(none_R arums_H_inp);
        void set_arums(none_R arums_G_inp, none_R arums_H_inp);
};

class dse_none_ltu_R : public trame::dse<trame::arums::none,trame::arums::none,trame::transfers::ltu>
{
    public:
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, none_R arums_G_inp, none_R arums_H_inp, bool need_norm_inp);

        transfers_ltu_R get_transfers_R();
        void set_transfers_R(transfers_ltu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        none_R get_arums_G();
        void set_arums_G(none_R arums_G_inp);
        none_R get_arums_H();
        void set_arums_H(none_R arums_H_inp);
        void set_arums(none_R arums_G_inp, none_R arums_H_inp);
};

class dse_none_ntu_R : public trame::dse<trame::arums::none,trame::arums::none,trame::transfers::ntu>
{
    public:
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, none_R arums_G_inp, none_R arums_H_inp, bool need_norm_inp);

        transfers_ntu_R get_transfers_R();
        void set_transfers_R(transfers_ntu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        none_R get_arums_G();
        void set_arums_G(none_R arums_G_inp);
        none_R get_arums_H();
        void set_arums_H(none_R arums_H_inp);
        void set_arums(none_R arums_G_inp, none_R arums_H_inp);
};

class dse_none_tu_R : public trame::dse<trame::arums::none,trame::arums::none,trame::transfers::tu>
{
    public:
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, bool need_norm_inp);
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, none_R arums_G_inp, none_R arums_H_inp, bool need_norm_inp);

        transfers_tu_R get_transfers_R();
        void set_transfers_R(transfers_tu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        none_R get_arums_G();
        void set_arums_G(none_R arums_G_inp);
        none_R get_arums_H();
        void set_arums_H(none_R arums_H_inp);
        void set_arums(none_R arums_G_inp, none_R arums_H_inp);
};

//
// DSE-rsc

class dse_rsc_etu_R : public trame::dse<trame::arums::rsc,trame::arums::rsc,trame::transfers::etu>
{
    public:
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, bool need_norm_inp);
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, rsc_R arums_G_inp, rsc_R arums_H_inp, bool need_norm_inp);

        transfers_etu_R get_transfers_R();
        void set_transfers_R(transfers_etu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rsc_R get_arums_G();
        void set_arums_G(rsc_R arums_G_inp);
        rsc_R get_arums_H();
        void set_arums_H(rsc_R arums_H_inp);
        void set_arums(rsc_R arums_G_inp, rsc_R arums_H_inp);
};

class dse_rsc_ltu_R : public trame::dse<trame::arums::rsc,trame::arums::rsc,trame::transfers::ltu>
{
    public:
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, rsc_R arums_G_inp, rsc_R arums_H_inp, bool need_norm_inp);

        transfers_ltu_R get_transfers_R();
        void set_transfers_R(transfers_ltu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rsc_R get_arums_G();
        void set_arums_G(rsc_R arums_G_inp);
        rsc_R get_arums_H();
        void set_arums_H(rsc_R arums_H_inp);
        void set_arums(rsc_R arums_G_inp, rsc_R arums_H_inp);
};

class dse_rsc_ntu_R : public trame::dse<trame::arums::rsc,trame::arums::rsc,trame::transfers::ntu>
{
    public:
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, rsc_R arums_G_inp, rsc_R arums_H_inp, bool need_norm_inp);

        transfers_ntu_R get_transfers_R();
        void set_transfers_R(transfers_ntu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rsc_R get_arums_G();
        void set_arums_G(rsc_R arums_G_inp);
        rsc_R get_arums_H();
        void set_arums_H(rsc_R arums_H_inp);
        void set_arums(rsc_R arums_G_inp, rsc_R arums_H_inp);
};

class dse_rsc_tu_R : public trame::dse<trame::arums::rsc,trame::arums::rsc,trame::transfers::tu>
{
    public:
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, bool need_norm_inp);
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, rsc_R arums_G_inp, rsc_R arums_H_inp, bool need_norm_inp);

        transfers_tu_R get_transfers_R();
        void set_transfers_R(transfers_tu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rsc_R get_arums_G();
        void set_arums_G(rsc_R arums_G_inp);
        rsc_R get_arums_H();
        void set_arums_H(rsc_R arums_H_inp);
        void set_arums(rsc_R arums_G_inp, rsc_R arums_H_inp);
};

//
// DSE-rusc

class dse_rusc_etu_R : public trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::etu>
{
    public:
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, bool need_norm_inp);
        void build_ETU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, const arma::mat& tau_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp);

        transfers_etu_R get_transfers_R();
        void set_transfers_R(transfers_etu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rusc_R get_arums_G();
        void set_arums_G(rusc_R arums_G_inp);
        rusc_R get_arums_H();
        void set_arums_H(rusc_R arums_H_inp);
        void set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp);
};

class dse_rusc_ltu_R : public trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::ltu>
{
    public:
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_LTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp);

        transfers_ltu_R get_transfers_R();
        void set_transfers_R(transfers_ltu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rusc_R get_arums_G();
        void set_arums_G(rusc_R arums_G_inp);
        rusc_R get_arums_H();
        void set_arums_H(rusc_R arums_H_inp);
        void set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp);
};

class dse_rusc_ntu_R : public trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::ntu>
{
    public:
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp);
        void build_NTU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& alpha_inp, const arma::mat& gamma_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp);

        transfers_ntu_R get_transfers_R();
        void set_transfers_R(transfers_ntu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rusc_R get_arums_G();
        void set_arums_G(rusc_R arums_G_inp);
        rusc_R get_arums_H();
        void set_arums_H(rusc_R arums_H_inp);
        void set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp);
};

class dse_rusc_tu_R : public trame::dse<trame::arums::rusc,trame::arums::rusc,trame::transfers::tu>
{
    public:
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, bool need_norm_inp);
        void build_TU_R(const arma::vec& n_inp, const arma::vec& m_inp, const arma::mat& phi_inp, rusc_R arums_G_inp, rusc_R arums_H_inp, bool need_norm_inp);

        transfers_tu_R get_transfers_R();
        void set_transfers_R(transfers_tu_R trans_obj_inp);

        SEXP solve_R();
        SEXP solve_R(Rcpp::CharacterVector solver_inp);

        rusc_R get_arums_G();
        void set_arums_G(rusc_R arums_G_inp);
        rusc_R get_arums_H();
        void set_arums_H(rusc_R arums_H_inp);
        void set_arums(rusc_R arums_G_inp, rusc_R arums_H_inp);
};
