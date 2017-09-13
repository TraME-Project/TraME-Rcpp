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
 * 09/13/2017
 */

//
// DSE-logit

class model_dse_logit_etu_R : public trame::model< trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::etu> >
{
    public:
        void build_ETU_R(const arma::cube& phi_xyk_inp);
        void build_ETU_R(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp);
        void build_ETU_R(const arma::mat& X_inp, const arma::mat& Y_inp);
        void build_ETU_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp);

        SEXP mle_ETU_R(const arma::mat& mu_hat);
        SEXP mme_ETU_R(const arma::mat& mu_hat);

        dse_logit_etu_R get_market();
        void set_market(dse_logit_etu_R market_obj_inp);
};

// class model_dse_logit_ltu_R : public trame::model< trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ltu> >
// {
//     public:
//         void build_LTU_R(const arma::cube& phi_xyk_inp);
//         void build_LTU_R(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp);
//         void build_LTU_R(const arma::mat& X_inp, const arma::mat& Y_inp);
//         void build_LTU_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp);

//         SEXP mle_LTU_R(const arma::mat& mu_hat);
//         SEXP mme_LTU_R(const arma::mat& mu_hat);

//         dse_logit_ltu_R get_market();
//         void set_market(dse_logit_ltu_R market_obj_inp);
// };

// class model_dse_logit_ntu_R : public trame::model< trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::ntu> >
// {
//     public:
//         void build_NTU_R(const arma::cube& phi_xyk_inp);
//         void build_NTU_R(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp);
//         void build_NTU_R(const arma::mat& X_inp, const arma::mat& Y_inp);
//         void build_NTU_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp);

//         SEXP mle_NTU_R(const arma::mat& mu_hat);
//         SEXP mme_NTU_R(const arma::mat& mu_hat);

//         dse_logit_ntu_R get_market();
//         void set_market(dse_logit_ntu_R market_obj_inp);
// };

class model_dse_logit_tu_R : public trame::model< trame::dse<trame::arums::logit,trame::arums::logit,trame::transfers::tu> >
{
    public:
        void build_TU_R(const arma::cube& phi_xyk_inp);
        void build_TU_R(const arma::cube& phi_xyk_inp, const arma::vec& n_inp, const arma::vec& m_inp);
        void build_TU_R(const arma::mat& X_inp, const arma::mat& Y_inp);
        void build_TU_R(const arma::mat& X_inp, const arma::mat& Y_inp, const arma::vec& n_inp, const arma::vec& m_inp);

        SEXP mle_TU_R(const arma::mat& mu_hat);
        SEXP mme_TU_R(const arma::mat& mu_hat);

        dse_logit_tu_R get_market();
        void set_market(dse_logit_tu_R market_obj_inp);
};
