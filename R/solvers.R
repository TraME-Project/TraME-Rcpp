################################################################################
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
################################################################################

arc_newton <- function(market_inp)
{
    #
    solver_out <- .Call("arc_newton_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

cupids_lp <- function(market_inp)
{
    #
    solver_out <- .Call("cupids_lp_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

darum <- function(market_inp)
{
    #
    solver_out <- .Call("darum_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

eap_nash <- function(market_inp)
{
    #
    solver_out <- .Call("eap_nash_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

jacobi <- function(market_inp)
{
    #
    solver_out <- .Call("jacobi_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

max_welfare <- function(market_inp)
{
    #
    solver_out <- .Call("max_welfare_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

oap_lp <- function(market_inp)
{
    #
    solver_out <- .Call("oap_lp_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

ipfp <- function(market_inp)
{
    #
    solver_out <- .Call("ipfp_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

nodal_newton <- function(market_inp)
{
    #
    solver_out <- .Call("nodal_newton_R", market_inp, PACKAGE = "TraME.Rcpp")
    #
    return(solver_out)
}

