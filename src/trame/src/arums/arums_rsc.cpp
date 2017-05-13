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
 * Random Scalar Coefficient (RSC) additive random utility model (ARUM) class
 *
 * Keith O'Hara
 * 08/08/2016
 * 
 * This version:
 * 02/21/2017
 */

#include "trame.hpp"

trame::arums::rsc::rsc(int nbX_inp, int nbY_inp)
{
    this->build(nbX_inp, nbY_inp);
}

trame::arums::rsc::rsc(arma::mat zeta_inp, bool outsideOption_inp)
{
    this->build(zeta_inp, outsideOption_inp);
}

trame::arums::rsc::rsc(arma::mat zeta_inp, double alpha, double beta)
{
    this->build_beta(zeta_inp, alpha, beta);
}

void 
trame::arums::rsc::build(int nbX_inp, int nbY_inp)
{
    nbX = nbX_inp;
    nbY = nbY_inp;
}

void 
trame::arums::rsc::build(arma::mat zeta_inp, bool outsideOption_inp)
{
    if (!outsideOption_inp) {
        return;
    }
    //
    outsideOption = true;
    nbX = zeta_inp.n_rows;
    nbY = zeta_inp.n_cols - 1;
    nbParams = zeta_inp.n_elem;

    zeta = zeta_inp;
    aux_ord = arma::zeros(nbX,nbY+1);
    //
    arma::mat D =  arma::eye(nbY+1,nbY+1) - arma::join_cols(arma::zeros(1,nbY+1), arma::join_rows(arma::eye(nbY,nbY),arma::zeros(nbY,1)));
    arma::mat D_inv = arma::inv(D);

    arma::mat neg_ones(nbY,1);
    neg_ones.fill(-1);
    arma::mat N_temp = arma::join_rows(arma::eye(nbY,nbY),neg_ones);
    //
    arma::uvec ordx_temp;
    arma::mat Psigmax(nbY+1,nbY+1);

    aux_Influence_lhs.zeros(nbY,nbY+1,nbX);
    aux_Influence_rhs.zeros(nbY+1,nbY+1,nbX);
    aux_Psigma.zeros(nbY+1,nbY+1,nbX);
    aux_DinvPsigma.zeros(nbY+1,nbY+1,nbX);
    //
    for (int i=0; i < nbX; i++) {
        ordx_temp = arma::sort_index(zeta_inp.row(i));
        aux_ord.row(i) = arma::conv_to< arma::rowvec >::from(ordx_temp);

        Psigmax.zeros();
        for (int j=0; j < nbY+1; j++) {
            Psigmax(j,ordx_temp(j)) = 1;
        }

        aux_Influence_lhs.slice(i) = N_temp * (Psigmax.t() * D_inv);
        aux_Influence_rhs.slice(i) = D * Psigmax;

        aux_Psigma.slice(i) = arma::eye(nbY+1,nbY+1) * Psigmax;
        aux_DinvPsigma.slice(i) = D_inv * Psigmax;
    }
}

// epsilon is a beta(alpha,beta) distribution
void 
trame::arums::rsc::build_beta(arma::mat zeta_inp, double alpha, double beta)
{
    dist_pars = new double[2];
    dist_pars[0] = alpha;
    dist_pars[1] = beta;

    aux_cdf_eps   = pbeta;
    aux_quant_eps = qbeta;
    aux_pdf_eps   = dbeta;
    aux_pot_eps   = iqbeta;

    aux_cdf_eps_vec   = pbeta;
    aux_quant_eps_vec = qbeta;
    aux_pdf_eps_vec   = dbeta;
    aux_pot_eps_vec   = iqbeta;
    //
    build(zeta_inp,true);
}

double 
trame::arums::rsc::G(const arma::vec& n)
{   
    double val = this->G(n,U,mu_sol);
    //
    return val;
}

double 
trame::arums::rsc::G(const arma::vec& n, const arma::mat& U_inp, arma::mat& mu_out)
{
    double val=0.0, val_x;

    mu_out.set_size(nbX,nbY);
    //
    arma::mat mu_x_temp;

    for (int i=0; i<nbX; i++) {
        val_x = Gx(U_inp.row(i).t(), mu_x_temp, i);
        //
        val += n(i)*val_x;
        mu_out.row(i) = arma::trans(n(i)*mu_x_temp);
    }
    //
    return val;
}

double 
trame::arums::rsc::Gx(const arma::mat& U_x_inp, arma::mat& mu_x_out, int x)
{
    int nbAlt = nbY + 1;
    int j,y,z;

    double val_x=0, E_eps_temp=0, E_eps_temp_next=0, cumul_temp=0;
    double run_max=0, run_min=0, run_temp=0;
    double mu_x_tilde_y, e_y;

    arma::vec mu_x_tilde = arma::zeros(nbAlt,1);
    arma::vec U_x_tilde = arma::join_cols(arma::vectorise(U_x_inp),arma::zeros(1,1)); // Keith: RSC only works with outsideOption = true?
    //
    for (int i=0; i < nbAlt; i++) {
        y = aux_ord(x,i);
        run_max = quantile(0);
        //
        j = 0;

        while (j < i) {
            z = aux_ord(x,j);

            if (zeta(x,z) != zeta(x,y)) {
                run_temp = (U_x_tilde(y) - U_x_tilde(z)) / (zeta(x,z) - zeta(x,y));
                run_max = std::max(run_max,run_temp);
            } else {
                run_max = INFINITY;
            }

            j++;
        }
        //
        run_min = quantile(1);
        //
        j = nbAlt-1;

        while (j > i) {
            z = aux_ord(x,j);
            
            if (zeta(x,z) != zeta(x,y)) {
                run_temp = (U_x_tilde(y) - U_x_tilde(z)) / (zeta(x,z) - zeta(x,y));
                run_min = std::min(run_min,run_temp);
            }

            j--;
        }
        //
        if (run_min > run_max) {
            mu_x_tilde_y = std::max(cdf(run_min) - cdf(run_max),0.0);
        } else {
            mu_x_tilde_y = 0;
        }

        mu_x_tilde(y) = mu_x_tilde_y;
        //
        if (mu_x_tilde_y > 0) {
            cumul_temp += mu_x_tilde_y;
            e_y = quantile(cumul_temp);

            E_eps_temp_next = e_y * cumul_temp - pot(cumul_temp);

            val_x += mu_x_tilde_y*U_x_tilde(y) + zeta(x,y)*(E_eps_temp_next - E_eps_temp);
            //
            E_eps_temp = E_eps_temp_next;
        }
    }
    //
    mu_x_out = mu_x_tilde.rows(0,nbAlt-2);
    //
    return val_x;
}

double 
trame::arums::rsc::Gstar(const arma::vec& n)
{
    return this->Gstar(n,mu_sol,U_sol);
}

double 
trame::arums::rsc::Gstar(const arma::vec& n, const arma::mat& mu_inp, arma::mat& U_out)
{
    double val=0.0, val_x_temp;

    U_out.set_size(nbX,nbY);
    //
    arma::vec U_x_temp;

    for (int i=0; i<nbX; i++) {
        val_x_temp = Gstarx((mu_inp.row(i).t())/n(i),U_x_temp,i);
        //
        val += n(i)*val_x_temp;
        U_out.row(i) = arma::trans(U_x_temp);
    }
    //
    return val;
}

double 
trame::arums::rsc::Gstarx(const arma::mat& mu_x_inp, arma::mat &U_x_out, int x)
{
    double val_x = 0;

    arma::vec ts_temp(mu_x_inp.n_elem+1);
    ts_temp.rows(0,mu_x_inp.n_elem-1) = mu_x_inp;
    ts_temp(mu_x_inp.n_elem) = 1 - arma::accu(mu_x_inp);

    arma::vec ts_full = aux_DinvPsigma.slice(x) * ts_temp;
    arma::vec ts = ts_full.rows(0,nbY-1);
    //
    arma::vec pots_inp = arma::join_cols(arma::zeros(1,1),ts_full);
    arma::vec pots = pot(pots_inp);

    arma::vec diff_pots = pots.rows(1,nbY+1) - pots.rows(0,nbY);
    //
    val_x = - arma::accu( (aux_Psigma.slice(x)*zeta.row(x).t()) % diff_pots );

    arma::mat e_mat = arma::diagmat( arma::join_cols(arma::zeros(1,1),quantile(ts)) );
    U_x_out = - aux_Influence_lhs.slice(x) * e_mat * aux_Influence_rhs.slice(x) * zeta.row(x).t();
    //
    return val_x;
}

double 
trame::arums::rsc::Gstarx(arma::vec& U_x, const arma::vec& mu_x_inp, const arma::mat& zeta,
                          const arma::mat& aux_DinvPsigma, const arma::mat& aux_Psigma,
                          const arma::mat& aux_Influence_lhs, const arma::mat& aux_Influence_rhs,
                          arma::vec (*pot_eps_vec)(arma::vec pot_inp, double* dist_pars),
                          arma::vec (*quantile_eps_vec)(arma::vec quant_inp, double* dist_pars),
                          double* dist_pars, int nbY, int x)
{
    arma::vec ts_temp(mu_x_inp.n_elem+1);
    ts_temp.rows(0,mu_x_inp.n_elem-1) = mu_x_inp;
    ts_temp(mu_x_inp.n_elem) = 1-arma::accu(mu_x_inp);

    arma::vec ts_full = aux_DinvPsigma * ts_temp;
    arma::vec ts = ts_full.rows(0,nbY-1);
    //
    arma::vec pots_inp = arma::join_cols(arma::zeros(1,1),ts_full);
    arma::vec pots = (*pot_eps_vec)(pots_inp, dist_pars);

    arma::vec diff_pots = pots.rows(1,nbY+1) - pots.rows(0,nbY);
    //
    double val_x = - arma::accu( aux_Psigma*zeta.row(x).t() % diff_pots );

    arma::mat e_mat = arma::diagmat( arma::join_cols(arma::zeros(1,1),(*quantile_eps_vec)(ts,dist_pars)) );
    U_x = - aux_Influence_lhs * e_mat * aux_Influence_rhs * zeta.row(x).t();
    //
    return val_x;
}

double 
trame::arums::rsc::Gbar(const arma::mat& Ubar, const arma::mat& mubar, const arma::vec& n, arma::mat& U_out, arma::mat& mu_out)
{
    double val = 0.0, val_temp;

    U_out.set_size(nbX,nbY);
    mu_out.set_size(nbX,nbY);
    //
    arma::mat U_x_temp, mu_x_temp;

    for (int i=0; i<nbX; i++) {
        val_temp = Gbarx(Ubar.row(i).t(),(mubar.row(i).t())/n(i),U_x_temp,mu_x_temp,i);

        val += n(i)*val_temp;
        U_out.row(i) = arma::trans(U_x_temp);
        mu_out.row(i) = arma::trans(n(i)*mu_x_temp);
    }
    //
    return val;
}

double 
trame::arums::rsc::Gbarx(const arma::vec& Ubar_x, const arma::vec& mubar_x, arma::mat& U_x_out, arma::mat& mu_x_out, int x)
{
    if (!outsideOption) {
        printf("Gbarx not implemented yet when outsideOption==false");
        return 0.0;
    }
    //
    arma::vec lb = arma::zeros(nbY,1);
    arma::vec ub = mubar_x;

    arma::vec sol_vec = mubar_x/2.0;
    double obj_val = 0, ret = 0;
    //
    // opt data
    trame_rsc_gbar_opt_data opt_data;

    opt_data.x = x;
    opt_data.nbY = nbY;
    opt_data.Ubar_x = Ubar_x;
    opt_data.zeta = zeta;

    opt_data.aux_DinvPsigma = aux_DinvPsigma.slice(x);
    opt_data.aux_Psigma = aux_Psigma.slice(x);
    opt_data.aux_Influence_lhs = aux_Influence_lhs.slice(x);
    opt_data.aux_Influence_rhs = aux_Influence_rhs.slice(x);

    opt_data.pot_eps_vec = aux_pot_eps_vec;
    opt_data.quantile_eps_vec = aux_quant_eps_vec;

    opt_data.dist_pars = dist_pars;
    //
    bool success = generic_constr_optim(sol_vec,lb,ub,Gbar_opt_objfn,&opt_data,Gbar_opt_constr,&opt_data,&obj_val);
    //
    if (success) {
        mu_x_out = sol_vec;

        arma::vec U_x_temp;
        Gstarx(sol_vec,U_x_temp,x);
        U_x_out = U_x_temp;

        ret = -obj_val;
    }
    return ret;
}

arma::mat 
trame::arums::rsc::D2Gstar(const arma::vec& n, bool x_first)
{
    arma::mat ret;
    this->D2Gstar(ret,n,mu,x_first);
    //
    return ret;
}

void 
trame::arums::rsc::D2Gstar(arma::mat& ret, const arma::vec& n, bool x_first)
{
    this->D2Gstar(ret,n,mu,x_first);
}

arma::mat 
trame::arums::rsc::D2Gstar(const arma::vec& n, const arma::mat& mu_inp, bool x_first)
{
    arma::mat ret;
    this->D2Gstar(ret,n,mu_inp,x_first);
    //
    return ret;
}

void 
trame::arums::rsc::D2Gstar(arma::mat& hess, const arma::vec& n, const arma::mat& mu_inp, bool x_first)
{
    hess.zeros(nbX*nbY,nbX*nbY);

    arma::vec mu_x0 = n - arma::sum(mu_inp,1);

    arma::umat mat_inds(nbY,nbX); // indices to place the results (complicated)
    for (int i=0; i < nbX; i++) {
        for (int j=0; j < nbY; j++) {
            if (x_first) {
                mat_inds(j,i) = i + j*nbX;
            } else {
                mat_inds(j,i) = i*nbY + j;
            }
        }
    }
    //
    arma::mat C, d_mu_e_temp, d_mu_e;
    arma::vec ts_temp(nbY+1), ts_full, erestr_temp, erestr, erestr_pdf;

    for (int i=0; i < nbX; i++) {
        C = - arma::trans( arma::repmat(aux_Influence_rhs.slice(i) * zeta.row(i).t(),1,nbY) % aux_Influence_lhs.slice(i).t() );

        ts_temp.rows(0,nbY-1) = mu_inp.row(i).t();
        ts_temp(nbY) = mu_x0(i);

        ts_full = aux_DinvPsigma.slice(i) * ts_temp / n(i);
        //
        erestr_temp = quantile(ts_full);
        erestr = erestr_temp.rows(0,nbY-1);
        erestr_pdf = pdf(erestr);
        //
        d_mu_e_temp = arma::join_cols(arma::zeros(1,nbY),arma::diagmat(1 / erestr_pdf)) * aux_DinvPsigma.slice(i).rows(0,nbY-1);
        d_mu_e = d_mu_e_temp.cols(0,nbY-1) - arma::repmat(d_mu_e_temp.col(nbY),1,nbY);
        //
        hess(mat_inds.col(i),mat_inds.col(i)) = C * d_mu_e / n(i);
    }
}

arma::mat 
trame::arums::rsc::dparams_NablaGstar(const arma::vec& n, arma::mat* dparams_inp, bool x_first)
{
    arma::mat ret;
    this->dparams_NablaGstar(ret,n,mu_sol,dparams_inp,x_first);
    //
    return ret;
}

void 
trame::arums::rsc::dparams_NablaGstar(arma::mat &ret, const arma::vec& n, arma::mat* dparams_inp, bool x_first)
{
    this->dparams_NablaGstar(ret,n,mu_sol,dparams_inp,x_first);
}

arma::mat 
trame::arums::rsc::dparams_NablaGstar(const arma::vec& n, const arma::mat& mu_inp, arma::mat* dparams_inp, bool x_first)
{
    arma::mat ret;
    this->dparams_NablaGstar(ret,n,mu_inp,dparams_inp,x_first);
    //
    return ret;
}

void 
trame::arums::rsc::dparams_NablaGstar(arma::mat& ret, const arma::vec& n, const arma::mat& mu_inp, arma::mat* dparams, bool x_first)
{
    arma::mat dparams_mat = (dparams) ? *dparams : arma::eye(nbParams,nbParams);

    int nbDirs = std::floor(dparams_mat.n_elem / (nbX*nbX*(nbY+1)));

    ret.set_size(nbX*nbY,nbX*nbDirs);
    ret.zeros();
    //
    // indices to place the results (complicated)
    arma::umat mat_inds_1(nbDirs,nbX);
    arma::umat mat_inds_2(nbDirs,nbX);
    arma::umat mat_inds_3(nbDirs,nbX);

    for (int i=0; i<nbX; i++) {
        for (int j=0; j<nbDirs; j++) {
            if (x_first) {
                mat_inds_1(j,i) = i + j*nbX;
                mat_inds_2(j,i) = i + j*nbX;
                mat_inds_3(j,i) = i + j*nbX;
            } else {
                mat_inds_1(j,i) = i + j*nbX;
                mat_inds_2(j,i) = i + j*nbX;
                mat_inds_3(j,i) = i*nbY + j;
            }
        }
    }

    if (nbDirs > nbY) {
        mat_inds_3.shed_row(nbDirs-1);
    }
    //
    arma::mat e_mat;
    arma::vec ts_temp(nbY+1), ts_full, ts;

    for (int i=0; i<nbX; i++) {
        ts_temp.rows(0,nbY-1) = mu_inp.row(i).t();
        ts_temp(nbY) = n(i) - arma::accu(mu_inp.row(i));

        arma::vec ts_full = aux_DinvPsigma.slice(i) * ts_temp / n(i);
        arma::vec ts = ts_full.rows(0,nbY-1);

        e_mat = arma::diagmat( arma::join_cols(arma::zeros(1,1),quantile(ts)) );

        ret(mat_inds_3.col(i),mat_inds_1.col(i)) = - aux_Influence_lhs.slice(i) * e_mat * aux_Influence_rhs.slice(i) * dparams_mat(mat_inds_2.col(i),mat_inds_2.col(i));
    }
}

trame::arums::empirical 
trame::arums::rsc::simul()
{
    empirical emp_obj;
    this->simul(emp_obj,NULL,NULL);
    //
    return emp_obj;
}

trame::arums::empirical 
trame::arums::rsc::simul(int* nbDraws, int* seed)
{
    empirical emp_obj;
    this->simul(emp_obj,nbDraws,seed);
    //
    return emp_obj;
}

void 
trame::arums::rsc::simul(empirical& obj_out)
{
    this->simul(obj_out,NULL,NULL);
}

void 
trame::arums::rsc::simul(empirical& obj_out, int* nbDraws, int* seed_val)
{
    int n_draws = 0;
    if (nbDraws) {
        n_draws = *nbDraws;
    } else {
#ifdef TRAME_DEFAULT_SIM_DRAWS
        n_draws = TRAME_DEFAULT_SIM_DRAWS;
#else
        n_draws = 1000;
#endif
    }
    //
    if (seed_val) {
        arma::arma_rng::set_seed(*seed_val);
    }
    //
    arma::cube atoms(n_draws,nbY+1,nbX);

    for (int i=0; i<nbX; i++) {
        atoms.slice(i) = quantile(arma::randu(n_draws,1)) * zeta.row(i);
    }
    //
    obj_out.nbX = nbX;
    obj_out.nbY = nbY;
    obj_out.nbParams = atoms.n_elem;
    obj_out.atoms = atoms;
    obj_out.aux_nbDraws = n_draws;
    obj_out.xHomogenous = false;
    obj_out.outsideOption = outsideOption;

    if (outsideOption) {
        obj_out.nbOptions = nbY + 1;
    } else {
        obj_out.nbOptions = nbY;
    }
    //
    if (seed_val) {
        arma::arma_rng::set_seed_random(); // need to reset the seed
    }
}

/*
 * optimization-related functions
 */

double 
trame::arums::rsc::Gbar_opt_objfn(const arma::vec& vals_inp, arma::vec* grad, void* opt_data)
{
    trame_rsc_gbar_opt_data *d = reinterpret_cast<trame_rsc_gbar_opt_data*>(opt_data);
    //
    int x = d->x;
    int nbY = d->nbY;

    arma::mat Ubar_x = d->Ubar_x;
    arma::mat zeta = d->zeta;
    arma::mat aux_DinvPsigma = d->aux_DinvPsigma;
    arma::mat aux_Psigma = d->aux_Psigma;
    arma::mat aux_Influence_lhs = d->aux_Influence_lhs;
    arma::mat aux_Influence_rhs = d->aux_Influence_rhs;

    double* dist_pars = d->dist_pars;
    //
    arma::vec mu_x_inp = vals_inp, U_x_temp;

	double val_x = Gstarx(U_x_temp, mu_x_inp, zeta,
                          aux_DinvPsigma,aux_Psigma,
                          aux_Influence_lhs,aux_Influence_rhs,
                          d->pot_eps_vec,d->quantile_eps_vec,
                          dist_pars,nbY,x);

    double ret = val_x - arma::accu(mu_x_inp % Ubar_x);
    //
    if (grad) {
        *grad = U_x_temp - Ubar_x;
    }
    //
    return ret;
}

double 
trame::arums::rsc::Gbar_opt_constr(const arma::vec& vals_inp, arma::vec* grad, void* constr_data)
{
    //
    double ret = arma::accu(vals_inp) - 1;
    //
    if (grad) {
        trame_rsc_gbar_opt_data *d = reinterpret_cast<trame_rsc_gbar_opt_data*>(constr_data);
        int nbY = d->nbY;

        *grad = arma::ones(nbY,1);
    }
    //
    return ret;
}

/*
 * Distribution-related functions
 */

double 
trame::arums::rsc::cdf(double x)
{
    double res;

    res = (*aux_cdf_eps)(x, dist_pars);

    return res;
}

arma::vec 
trame::arums::rsc::cdf(arma::vec x)
{
    arma::vec res;

    res = (*aux_cdf_eps_vec)(x, dist_pars);

    return res;
}

double 
trame::arums::rsc::pdf(double x)
{
    double res;

    res = (*aux_pdf_eps)(x, dist_pars);

    return res;
}

arma::vec 
trame::arums::rsc::pdf(arma::vec x)
{
    arma::vec res;

    res = (*aux_pdf_eps_vec)(x, dist_pars);

    return res;
}

double 
trame::arums::rsc::quantile(double x)
{
    double res;

    res = (*aux_quant_eps)(x, dist_pars);

    return res;
}

arma::vec 
trame::arums::rsc::quantile(arma::vec x)
{
    arma::vec res;

    res = (*aux_quant_eps_vec)(x, dist_pars);

    return res;
}

double 
trame::arums::rsc::pot(double x)
{
    double res;

    res = (*aux_pot_eps)(x, dist_pars);

    return res;
}

arma::vec 
trame::arums::rsc::pot(arma::vec x)
{
    arma::vec res;

    res = (*aux_pot_eps_vec)(x, dist_pars);

    return res;
}

// old

/*
double trame::arums::rsc::Gbarx(const arma::vec& Ubar_x, const arma::vec& mubar_x, arma::mat& U_x_out, arma::mat& mu_x_out, int x)
{
    if (!outsideOption) {
        printf("Gbarx not implemented yet when outsideOption==false");
        return 0.0;
    }
    //
    arma::vec lb = arma::zeros(nbY,1);
    arma::vec ub = mubar_x;

    std::vector<double> sol_vec = arma::conv_to< std::vector<double> >::from(mubar_x/2.0);
    double obj_val = 0;
    double ret = 0;
    //
    // opt data
    trame_nlopt_opt_data opt_data;

    opt_data.rsc_gbar.x = x;
    opt_data.rsc_gbar.nbY = nbY;
    opt_data.rsc_gbar.Ubar_x = Ubar_x;
    opt_data.rsc_gbar.zeta = zeta;

    opt_data.rsc_gbar.aux_DinvPsigma = aux_DinvPsigma.slice(x);
    opt_data.rsc_gbar.aux_Psigma = aux_Psigma.slice(x);
    opt_data.rsc_gbar.aux_Influence_lhs = aux_Influence_lhs.slice(x);
    opt_data.rsc_gbar.aux_Influence_rhs = aux_Influence_rhs.slice(x);

    opt_data.rsc_gbar.pot_eps_vec = aux_pot_eps_vec;
    opt_data.rsc_gbar.quantile_eps_vec = aux_quant_eps_vec;

    opt_data.rsc_gbar.dist_pars = dist_pars;

    //
    // constr data
    trame_nlopt_constr_data constr_data;
    constr_data.rsc_gbar.nbY = nbY;
    //
    bool success = generic_nlopt(nbY,sol_vec,obj_val,lb.memptr(),ub.memptr(),trame::arums::rsc::Gbar_opt_objfn,trame::arums::rsc::Gbar_opt_constr,opt_data,constr_data);
    //
    arma::vec U_x_temp;
    arma::vec sol_temp = arma::conv_to<arma::vec>::from(sol_vec);

    if (success) {
        mu_x_out = sol_temp;
        Gstarx(sol_temp,U_x_temp,x);
        U_x_out = U_x_temp;
        ret = -obj_val;
    }
    return ret;
}*/

/*
double trame::arums::rsc::Gbar_opt_objfn(const std::vector<double> &x_inp, std::vector<double> &grad, void *opt_data)
{
    trame_nlopt_opt_data *d = reinterpret_cast<trame_nlopt_opt_data*>(opt_data);

    int x = d->rsc_gbar.x;
    arma::mat Ubar_x = d->rsc_gbar.Ubar_x;
    arma::mat zeta = d->rsc_gbar.zeta;
    arma::mat aux_DinvPsigma = d->rsc_gbar.aux_DinvPsigma;
    arma::mat aux_Psigma = d->rsc_gbar.aux_Psigma;
    arma::mat aux_Influence_lhs = d->rsc_gbar.aux_Influence_lhs;
    arma::mat aux_Influence_rhs = d->rsc_gbar.aux_Influence_rhs;

    double* dist_pars = d->rsc_gbar.dist_pars;

    int nbY = d->rsc_gbar.nbY;

    arma::vec U_x_temp;
    arma::vec mu_x_inp = arma::conv_to<arma::vec>::from(x_inp);

	double val_x = Gstarx(U_x_temp, mu_x_inp, zeta,
                          aux_DinvPsigma,aux_Psigma,
                          aux_Influence_lhs,aux_Influence_rhs,
                          d->rsc_gbar.pot_eps_vec,d->rsc_gbar.quantile_eps_vec,
                          dist_pars,nbY,x);

    double ret = val_x - arma::accu(mu_x_inp % Ubar_x);
    //
    if (!grad.empty()) {
        grad = arma::conv_to< std::vector<double> >::from(U_x_temp - Ubar_x);
    }
    //
    return ret;
}*/

/*
double trame::arums::rsc::Gbar_opt_constr(const std::vector<double> &x_inp, std::vector<double> &grad, void *constr_data)
{
    trame_nlopt_constr_data *d = reinterpret_cast<trame_nlopt_constr_data*>(constr_data);

    int nbY = d->rsc_gbar.nbY;

    arma::vec mu_x_inp = arma::conv_to<arma::vec>::from(x_inp);

    double ret = arma::accu(mu_x_inp) - 1;
    //
    if (!grad.empty()) {
        grad = arma::conv_to< std::vector<double> >::from(arma::ones<arma::vec>(nbY,1));
    }
    //
    return ret;
}*/
