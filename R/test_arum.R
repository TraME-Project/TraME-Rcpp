################################################################################
##
##   Copyright (C) 2015 - 2016 Alfred Galichon
##
##   This file is part of the R package TraME.
##
##   The R package TraME is free software: you can redistribute it and/or modify
##   it under the terms of the GNU General Public License as published by
##   the Free Software Foundation, either version 2 of the License, or
##   (at your option) any later version.
##
##   The R package TraME is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public License
##   along with TraME. If not, see <http://www.gnu.org/licenses/>.
##
################################################################################

test_Logit <- function(nbDraws=1E4, seed=777, outsideOption=TRUE)
{
    set.seed(seed)
    ptm = proc.time()
    #
    message('*===================   Start of testLogit   ===================*\n')
    #

    logit_obj <- new(logit)

    U = matrix(c(1.6, 3.2, 1.1, 2.9, 1.0, 3.1),nrow=2,byrow=TRUE)
    mu = matrix(c(1, 3, 1, 2, 1, 3), nrow=2, byrow=TRUE)

    nbX = dim(U)[1]
    nbY = dim(U)[2]
    n = c(apply(mu,1,sum))

    logit_obj$build(nbX,nbY,1.0,TRUE)
    logit_obj$U = U

    sim_obj = logit_obj$simul(nbDraws)

    resG = logit_obj$G(n,U)
    resGSim = sim_obj$G(n,U)
    
    resGstar = logit_obj$Gstar(n,resG$mu)
    resGstarSim = sim_obj$Gstar(n,resGSim$mu)

    #
    message("(i) U and \\nabla G*(\\nabla G(U)) in (ii) cf and (iii) simulated logit:")
    print(c(U))
    print(c(resGstar$U))
    print(c(resGstarSim$U))
    
    message("\nG(U) in (i) cf and (ii) simulated logit:")
    print(resG$val)
    print(resGSim$val)
    
    message("\nG*(mu) in (i) cf and (ii) simulated logit:")
    print(resGstar$val)
    print(resGstarSim$val)
    #
    if(outsideOption){
        mubar = matrix(2,2,3)

        resGbar = logit_obj$Gbar(U,mubar,n)
        resGbarSim = sim_obj$Gbar(U,mubar,n)
        
        message("\nGbar(mu) in (i) cf and (ii) simulated logit:")
        print(resGbar$val)
        print(resGbarSim$val)
    }
    #
    time = proc.time() - ptm
    message(paste0('\nEnd of testLogit. Time elapsed = ', time["elapsed"], 's.\n'))
    #
    ret <- c(resGstar$U,resGstarSim$U,resG$val,resGSim$val,resGstar$val,resGstarSim$val,resGbar$val,resGbarSim$val)
    return(ret)
}

test_Probit <- function(nbDraws=1E4, seed=777, outsideOption=TRUE)
{
    set.seed(seed)
    ptm = proc.time()
    #
    message('*===================   Start of testProbit   ===================*\n')
    #
    
    probit_obj <- new(probit)

    U = matrix(c(1.6, 3.2, 1.1, 2.9, 1.0, 3.1),nrow=2,byrow=TRUE)
    mu = matrix(c(1, 3, 1, 2, 1, 3), nrow=2, byrow=TRUE)

    nbX = dim(U)[1]
    nbY = dim(U)[2]
    n = c(apply(mu,1,sum))

    rho = 0.5

    probit_obj$build(nbX,nbY,rho,TRUE)
    probit_obj$unifCorrelCovMatrices()

    sim_obj = probit_obj$simul(nbDraws)

    resGSim = sim_obj$G(n,U)

    resGstarSim = sim_obj$Gstar(n,resGSim$mu)

    mubar = matrix(2,2,3)

    resGbarSim = sim_obj$Gbar(U,mubar,n)
    #
    message("(i) U and \\nabla G*(\\nabla G(U)) in simulated probit:")
    print(c(U))
    print(c(resGstarSim$U))
    #
    time = proc.time() - ptm
    message(paste0('\nEnd of testProbit. Time elapsed = ', time["elapsed"], 's.\n')) 
    #
    ret <- c(resGstarSim$U)
    return(ret)
}

test_RUSC <- function(nbDraws=1E4,seed=777)
{
    set.seed(seed)
    ptm = proc.time()
    #
    message('*===================   Start of test_RUSC   ===================*\n')
    #
    
    rusc_obj <- new(rusc)

    U = matrix(c(1.6, 3.2, 1.1, 2.9, 1.0, 3.1),nrow=2,byrow=TRUE)
    mu = matrix(c(1, 3, 1, 2, 1, 3), nrow=2, byrow=TRUE)

    nbX = dim(U)[1]
    nbY = dim(U)[2]
    n = c(apply(mu,1,sum)) + 1

    zeta = matrix(1,nbX,1) %*% matrix(c(0.1, 0.2, 0.3, 0),1,nbY+1)

    rusc_obj$build(zeta,TRUE)
    rusc_obj$U = U

    sim_obj = rusc_obj$simul(nbDraws)

    resG = rusc_obj$G(n,U)
    resGSim = sim_obj$G(n,U)

    resGstar = rusc_obj$Gstar(n,resG$mu)
    resGstarSim = sim_obj$Gstar(n,resGSim$mu)

    mubar = matrix(2,2,3)

    resGbar = rusc_obj$Gbar(U,mubar,n)
    resGbarSim = sim_obj$Gbar(U,mubar,n)

    #
    # print

    message("G(U) in (i) cf and (ii) simulated RUSC:")
    print(c(resG$val))
    print(c(resGSim$val))
    
    message("\n\\nabla G(U) in (i) cf and (ii) simulated RUSC:")
    print(c(resG$mu))
    print(c(resGSim$mu))  
    
    #

    message("\n(i) U and \\nabla G*(\\nabla G(U)) in (ii) cf and (iii) simulated RUSC:")
    message("(Note: in RUSC, (ii) should be approx equal to (iii) but not to (i).)")
    print(c(U))
    print(c(resGstar$U))
    print(c(resGstarSim$U))
    
    resGstar2 = rusc_obj$Gstar(n,mu)
    resGstarSim2 = sim_obj$Gstar(n,mu)
    
    message("\n\\nabla G*(mu) in (i) closed form and (ii) simulated RUSC:")
    print(c(resGstar2$U))
    print(c(resGstarSim2$U))

    message("\nG*(mu) in (i) closed form and (ii) simulated RUSC:")
    print(c(resGstar2$val))
    print(c(resGstarSim2$val))
    
    #

    resG2 = rusc_obj$G(n,resGstar$U)
    resGSim2 = sim_obj$G(n,resGstarSim$U)

    message("\n\\nabla G \\nabla G*(mu) in (i) closed form and (ii) simulated RUSC:")
    print(c(resG2$mu))
    print(c(resGSim2$mu))

    #

    message("\nGbar(U,mubar) in (i) cf and (ii) simulated RUSC:")
    print(resGbar$val)
    print(resGbarSim$val)

    message("\n\\nabla Gbar(U,mubar) in (i) cf and (ii) simulated RUSC:")
    print(c(resGbar$mu))
    print(c(resGbarSim$mu))

    
    #
    time = proc.time()-ptm
    message(paste0('\nEnd of test_RUSC. Time elapsed = ', time["elapsed"], 's.\n')) 
    #
    ret <- c(resG$val,resGSim$val,resG$mu,resGSim$mu,resGstar$U,resGstarSim$U,resG2$U,resGSim2$U,resG2$val,resGSim2$val,resGstar2$mu,resGstarSim2$mu,resGbar$val,resGbarSim$val,resGbar$mu,resGbarSim$mu)
    return(ret)
}

test_RSC <- function(nbDraws=1E4,seed=777)
{
    set.seed(seed)
    ptm = proc.time()
    #
    message('*===================   Start of test_RSC   ===================*\n')
    #
    
    rsc_obj <- new(rsc)

    U = matrix(c(1.6, 3.2, 1.1, 2.9, 1.0, 3.1),nrow=2,byrow=TRUE)
    mu = matrix(c(1, 3, 1, 2, 1, 3), nrow=2, byrow=TRUE)

    nbX = dim(U)[1]
    nbY = dim(U)[2]
    n = c(apply(mu,1,sum)) + 1

    zeta = matrix(1,nbX,1) %*% matrix(c(0.1, 0.2, 0.3, 0),1,nbY+1)

    rsc_obj$build_beta(zeta,2,2)
    rsc_obj$U = U

    sim_obj = rsc_obj$simul(nbDraws)

    resG = rsc_obj$G(n,U)
    resGSim = sim_obj$G(n,U)

    resGstar = rsc_obj$Gstar(n,resG$mu)
    resGstarSim = sim_obj$Gstar(n,resGSim$mu)

    mubar = matrix(2,2,3)

    resGbar = rsc_obj$Gbar(U,mubar,n)
    resGbarSim = sim_obj$Gbar(U,mubar,n)

    #
    # print

    message("G(U) in (i) cf and (ii) simulated RSC:")
    print(c(resG$val))
    print(c(resGSim$val))
    
    message("\n\\nabla G(U) in (i) cf and (ii) simulated RSC:")
    print(c(resG$mu))
    print(c(resGSim$mu))  
    
    #

    message("\n(i) U and \\nabla G*(\\nabla G(U)) in (ii) cf and (iii) simulated RSC:")
    message("(Note: in RSC, (ii) should be approx equal to (iii) but not to (i).)")
    print(c(U))
    print(c(resGstar$U))
    print(c(resGstarSim$U))
    
    resGstar2 = rsc_obj$Gstar(n,mu)
    resGstarSim2 = sim_obj$Gstar(n,mu)
    
    message("\n\\nabla G*(mu) in (i) closed form and (ii) simulated RSC:")
    print(c(resGstar2$U))
    print(c(resGstarSim2$U))

    message("\nG*(mu) in (i) closed form and (ii) simulated RSC:")
    print(c(resGstar2$val))
    print(c(resGstarSim2$val))
    
    #

    resG2 = rsc_obj$G(n,resGstar$U)
    resGSim2 = sim_obj$G(n,resGstarSim$U)

    message("\n\\nabla G \\nabla G*(mu) in (i) closed form and (ii) simulated RSC:")
    print(c(resG2$mu))
    print(c(resGSim2$mu))

    #

    message("\nGbar(U,mubar) in (i) cf and (ii) simulated RSC:")
    print(resGbar$val)
    print(resGbarSim$val)

    message("\n\\nabla Gbar(U,mubar) in (i) cf and (ii) simulated RSC:")
    print(c(resGbar$mu))
    print(c(resGbarSim$mu))

    #

    # hess = rsc_obj$D2Gstar(mu,n)
    # thef = function(themu) (Gstar(RSCs,themu,n)$val)
    # hessNum = hessian(thef,mu)
    # message("\nD^2G^* (i) in cf and (ii) using numerical hessian:")
    # print(hess)
    # print(round(hessNum,6))
    #
    time = proc.time()-ptm
    message(paste0('\nEnd of test_RSC. Time elapsed = ', time["elapsed"], 's.\n')) 
    #
    ret <- c(resG$val,resGSim$val,resG$mu,resGSim$mu,resGstar$U,resGstarSim$U,resG2$U,resGSim2$U,resG2$val,resGSim2$val,resGstar2$mu,resGstarSim2$mu,resGbar$val,resGbarSim$val,resGbar$mu,resGbarSim$mu)
    return(ret)
}

tests_arum <- function(notifications=TRUE,nbDraws=1e4)
{
    ptm = proc.time()
    #
    res_logit  <- round(test_Logit(nbDraws=nbDraws),5)
    res_probit <- round(test_Probit(nbDraws=nbDraws),5)
    res_RUSC   <- round(test_RUSC(nbDraws=nbDraws),5)
    res_RSC    <- round(test_RSC(nbDraws=nbDraws),5)
    
    res_all <- c(res_logit,res_probit,res_RUSC,res_RSC)
    # MD5 checksum
    res_logit_md5  <- digest(res_logit,algo="md5")
    res_probit_md5 <- digest(res_probit,algo="md5")
    res_RUSC_md5   <- digest(res_RUSC,algo="md5")
    res_RSC_md5    <- digest(res_RSC,algo="md5")
    
    res_all_md5 <- digest(res_all,algo="md5")
    #
    time = proc.time() - ptm
    #
    if(notifications){
        message(paste0('All tests of arums completed. Overall time elapsed = ', time["elapsed"], 's.'))
    }
    #
    ret <- list(res_all_md5=res_all_md5,res_logit_md5=res_logit_md5,res_probit_md5=res_probit_md5,
                res_RUSC_md5=res_RUSC_md5,res_RSC_md5=res_RSC_md5)
    #
    return(ret)
}
