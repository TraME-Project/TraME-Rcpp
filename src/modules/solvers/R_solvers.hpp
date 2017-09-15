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

#ifndef _R_solvers_HPP
#define _R_solvers_HPP

#include "trameR.hpp"

// DSE
RcppExport SEXP arc_newton_R(SEXP market_inp);
RcppExport SEXP cupids_lp_R(SEXP market_inp);
RcppExport SEXP darum_R(SEXP market_inp);
RcppExport SEXP eap_nash_R(SEXP market_inp);
RcppExport SEXP jacobi_R(SEXP market_inp);
RcppExport SEXP max_welfare_R(SEXP market_inp);
RcppExport SEXP oap_lp_R(SEXP market_inp);

// MFE
RcppExport SEXP ipfp_R(SEXP market_inp);
RcppExport SEXP nodal_newton_R(SEXP market_inp);

#endif