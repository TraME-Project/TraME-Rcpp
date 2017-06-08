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
 * Non-Transferable Utility (NTU) transfers class
 *
 * Keith O'Hara
 * 08/15/2016
 *
 * This version:
 * 06/03/2017
 */

#include "trame.hpp"

void 
trame::transfers::ntu::build(const arma::mat& alpha_inp, const arma::mat& gamma_inp, bool need_norm_inp)
{
    need_norm = need_norm_inp;

    nbX = alpha_inp.n_rows;
    nbY = alpha_inp.n_cols;
    nbParams = 2*nbX*nbY;

    alpha = alpha_inp;
    gamma = gamma_inp;

    aux_alpha_exp = arma::exp(alpha_inp);
    aux_gamma_exp = arma::exp(gamma_inp);
}

void 
trame::transfers::ntu::trans()
{
    int nbX_temp = nbX;

    nbX = nbY;
    nbY = nbX_temp;
    //
    arma::mat alpha_temp = alpha;
    arma::mat aux_alpha_exp_temp = aux_alpha_exp;

    alpha = gamma.t();
    gamma = alpha_temp.t();

    aux_alpha_exp = aux_gamma_exp.t();
    aux_gamma_exp = aux_alpha_exp_temp.t();
    //
}

void
trame::transfers::ntu::gen_mmf(mmfs::min& mmf_obj)
const
{
    mmf_obj.build(alpha,gamma,need_norm);
}

trame::mmfs::min
trame::transfers::ntu::gen_mmf()
const
{
    mmfs::min mmf_obj;
    this->gen_mmf(mmf_obj);
    //
    return mmf_obj;
}

//
// DSE-related functions

arma::mat 
trame::transfers::ntu::Psi(const arma::mat& U, const arma::mat& V)
const
{
    return this->Psi(U,V,NULL,NULL);
}

// Implicit Parameterization
arma::mat 
trame::transfers::ntu::Psi(const arma::mat& U, const arma::mat& V, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = elem_max(U - alpha(x_ind,y_ind), V - gamma(x_ind,y_ind));
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::Psi(const double& U, const arma::mat& V, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = elem_max(U - alpha(x_ind,y_ind), V - gamma(x_ind,y_ind));
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::Psi(const arma::mat& U, const double& V, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = elem_max(U - alpha(x_ind,y_ind), V - gamma(x_ind,y_ind));
    //
    return ret;
}

double 
trame::transfers::ntu::Psi(const double& U, const double& V, int x_ind, int y_ind)
const
{
    double ret = std::max(U - alpha(x_ind,y_ind), V - gamma(x_ind,y_ind));
    //
    return ret;
}

// Derivative of Psi wrt u
arma::mat 
trame::transfers::ntu::du_Psi(const arma::mat& U, const arma::mat& V)
const
{
    return this->du_Psi(U,V,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::du_Psi(const arma::mat& U, const arma::mat& V, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = arma::zeros(x_ind.n_elem,y_ind.n_elem);
    ret.elem( arma::find(U - alpha(x_ind,y_ind) >= V - gamma(x_ind,y_ind)) ).ones();
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::du_Psi(const double& U, const arma::mat& V, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = arma::zeros(x_ind.n_elem,y_ind.n_elem);
    ret.elem( arma::find(U - alpha(x_ind,y_ind) >= V - gamma(x_ind,y_ind)) ).ones();
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::du_Psi(const arma::mat& U, const double& V, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = arma::zeros(x_ind.n_elem,y_ind.n_elem);
    ret.elem( arma::find(U - alpha(x_ind,y_ind) >= V - gamma(x_ind,y_ind)) ).ones();
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::dparams_Psi(const arma::mat& U, const arma::mat& V, const arma::mat& dparams)
const
{
    return this->dparams_Psi(U,V,&dparams);
}

arma::mat 
trame::transfers::ntu::dparams_Psi(const arma::mat& U, const arma::mat& V, const arma::mat* dparams)
const
{
    arma::mat ret(nbX,nbY);
    //
    arma::vec du_psi = arma::vectorise(du_Psi(U,V,NULL,NULL));

    if (!dparams) {
        ret = - arma::join_rows(arma::diagmat(du_psi),arma::diagmat(1 - du_psi));
    } else {
        arma::mat dparams_1 = dparams->rows(0,nbX*nbY-1);
        arma::mat dparams_2 = dparams->rows(nbX*nbY,2*nbX*nbY-1);

        ret = - arma::vectorise(du_psi % dparams_1 + (1 - du_psi) % dparams_2);
    }
    //
    return ret;
}

// Explicit Parameterization
arma::mat 
trame::transfers::ntu::Ucal(const arma::mat& vs)
const
{
    return this->Ucal(vs,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::Ucal(const arma::mat& vs, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = arma::zeros(x_ind.n_elem,y_ind.n_elem); // shouldn't be zero, should return an error
    //
    printf("no Ucal defined for NTU case\n");
    //
    return ret;
}

double 
trame::transfers::ntu::Ucal(const double& vs, int xs, int ys)
const
{
    double ret = 0; // shouldn't be zero, should return an error
    //
    printf("no Ucal defined for NTU case\n");
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::Vcal(const arma::mat& us)
const
{
    return this->Vcal(us,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::Vcal(const arma::mat& us, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret(x_ind.n_elem,y_ind.n_elem); // shouldn't be zero, should return an error
    //
    printf("no Vcal defined for NTU case\n");
    //
    return ret;
}

double 
trame::transfers::ntu::Vcal(const double& us, int xs, int ys)
const
{
    double ret = 0; // shouldn't be zero, should return an error
    //
    printf("no Vcal defined for NTU case\n");
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::UW(const arma::mat& Ws)
const
{
    return this->UW(Ws,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::UW(const arma::mat& Ws, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = - Psi(0.0,-Ws,&x_ind,&y_ind);
    //
    return ret;
}

double 
trame::transfers::ntu::UW(const double& Ws, int x_ind, int y_ind)
const
{
    double ret = - Psi((double) 0.0,-Ws,x_ind,y_ind);
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::VW(const arma::mat& Ws)
const
{
    return this->VW(Ws,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::VW(const arma::mat& Ws, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = - Psi(Ws,0.0,&x_ind,&y_ind);
    //
    return ret;
}

double 
trame::transfers::ntu::VW(const double& Ws, int x_ind, int y_ind)
const
{
    double ret = - Psi(Ws,(double) 0.0,x_ind,y_ind);
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::dw_UW(const arma::mat& Ws)
const
{
    return this->dw_UW(Ws,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::dw_UW(const arma::mat& Ws, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = 1.0 - du_Psi(0.0,-Ws,&x_ind,&y_ind);
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::dw_VW(const arma::mat& Ws)
const
{
    return this->dw_VW(Ws,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::dw_VW(const arma::mat& Ws, const arma::uvec* xs, const arma::uvec* ys)
const
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = - du_Psi(Ws,0.0,&x_ind,&y_ind);
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::WU(const arma::mat& Us)
{
    return this->WU(Us,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::WU(const arma::mat& Us, const arma::uvec* xs, const arma::uvec* ys)
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = Us - alpha(x_ind,y_ind);
    //
    return ret;
}

arma::mat 
trame::transfers::ntu::WV(const arma::mat& Vs)
{
    return this->WV(Vs,NULL,NULL);
}

arma::mat 
trame::transfers::ntu::WV(const arma::mat& Vs, const arma::uvec* xs, const arma::uvec* ys)
{
    arma::uvec x_ind = (xs) ? *xs : uvec_linspace(0, nbX-1);
    arma::uvec y_ind = (ys) ? *ys : uvec_linspace(0, nbY-1);
    //
    arma::mat ret = gamma(x_ind,y_ind) - Vs;
    //
    return ret;
}
