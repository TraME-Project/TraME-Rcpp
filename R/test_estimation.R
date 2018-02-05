################################################################################
##
##   Copyright (C) 2015 - 2018 the TraME Team:
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

# test_loglikelihood <- function(seed=777, nbX=5, nbY=4, dX=3, dY=2)
# {  
#     set.seed(seed)
#     tm = proc.time()
#     #
#     message('*===================   Start of test_loglikelihood   ===================*\n')
#     #
    
#     n = rep(1,nbX)
#     m = rep(1,nbY)  
    
#     xs = matrix(runif(nbX*dX),nrow=nbX)
#     ys = matrix(runif(nbY*dY),nrow=nbY)
    
#     #

#     logitM = new(logit)
#     logitW = new(logit)

#     logitM$build(nbX,nbY)
#     logitW$build(nbY,nbX)

#     A <- matrix(1,nrow=dX,ncol=dY)
#     phi <- xs %*% A %*% t(ys) 
    
#     mktSim <- new(dse_empirical_tu)
#     mktSim$build(n,m,phi,logitM,logitW,FALSE)

#     #

#     res <- cupids_lp(mktSim)

#     mu_hat <- res$mu

#     mu_hat_x0 <- n - apply(mu_hat,1,sum)
#     mu_hat_0y <- m - apply(mu_hat,2,sum)

#     #

#     muhat = CupidsLP(mktSim, T, F)$mu
#     muhatx0  = n-apply(muhat,1,sum)
#     muhat0y  = m-apply(muhat,2,sum)
#     #
#     TUlogitmodel = buildModel_TU_logit(array(kronecker(ys,xs) , dim=c(nbX,nbY,dX*dY) ),n,m)
#     theta0=initparam(TUlogitmodel)$param
#     market = parametricMarket(TUlogitmodel,theta0)
#     dtheta = diag(TUlogitmodel$nbParams)
#     #dtheta = matrix(0.1,nrow=6,ncol=1)
#     #
#     tsf = proc.time()  
#     #mudmu = dtheta_mu_default(TUlogitmodel,market,theta0,dtheta)
#     mudmu = dtheta_mu_default(TUlogitmodel,market,theta0)
#     message(paste0('Time elapsed - general: ', round((proc.time()-tsf)["elapsed"],5), 's.')) 
#     #
#     tsf = proc.time()  
#     dmunum = dtheta_mu_numeric(TUlogitmodel,market,theta0,dtheta)
#     message(paste0('Time elapsed - numerical: ', round((proc.time()-tsf)["elapsed"],5), 's.')) 
#     #
#     tsf = proc.time()    
#     dmulogit=dtheta_mu_logit(TUlogitmodel,market,theta0,dtheta)
#     message(paste0('Time elapsed - logit: ', round((proc.time()-tsf)["elapsed"],5), 's.')) 
#     #
#     mu = mudmu$mu 
#     #
#     LL = sum(2* muhat * log(mudmu$mu)) + sum(muhatx0 * log(mudmu$mux0s)) + sum(muhat0y * log(mudmu$mu0ys)) 
#     gradLL = apply( c( t( t(2* muhat/matrix(mudmu$mu,nrow=nbX) - muhatx0 / mudmu$mux0s)  - muhat0y / mudmu$mu0ys ) )* mudmu$dmu   ,2,sum) 
#     gradLLlogit = apply( c( t( t(2* muhat/matrix(dmulogit$mu,nrow=nbX) - muhatx0 / dmulogit$mux0s)  - muhat0y / dmulogit$mu0ys ) )* dmulogit$dmu   ,2,sum) 
#     gradLLnum = apply( c( t( t(2* muhat/matrix(dmunum$mu,nrow=nbX) - muhatx0 / dmunum$mux0s)  - muhat0y / dmunum$mu0ys ) )* dmunum$dmu   ,2,sum)
#     #
#     print(gradLL)
#     print(gradLLlogit)
#     print(gradLLnum)
#     #
#     time = proc.time() - tm  
#     message(paste0('\nEnd of test_loglikelihood. Time elapsed = ', round(time["elapsed"],5), 's.\n'))
#     #
#     ret <- c(LL,gradLL,gradLLlogit,gradLLnum)
#     return(ret)
# }

test_mle <- function(seed=777, nbX=80, nbY=72, noiseScale=0.1, dX=3, dY=3)
{  
    set.seed(seed)
    tm = proc.time()
    #
    message('*===================   Start of test_mle   ===================*\n')
    #
    
    sigma = 1

    n = rep(1,nbX)
    m = rep(1,nbY)

    xs = matrix(runif(nbX*dX),nrow=nbX)
    ys = matrix(runif(nbY*dY),nrow=nbY)

    A = matrix(1,nrow=dX,ncol=dY)
    phi = xs %*% A %*% t(ys) 

    mfe_geo_obj <- new(mfe_geo)
    mfe_geo_obj$build(n,m,phi,sigma,FALSE)

    #

    noise = matrix(1 + noiseScale*rnorm(nbX*nbY),nrow=nbX)

    mu_hat = mfe_geo_obj$solve("ipfp")$mu * noise

    #

    model_obj = new(model_dse_logit_tu)
    model_obj$build(xs,ys,n,m)

    res = model_obj$mle(mu_hat)

    thetahat = res$theta_hat

    #
    message("Estimator:")
    print(thetahat)
    #
    time = proc.time() - tm
    message(paste0('\nEnd of test_mle. Time elapsed = ', round(time["elapsed"],5), 's.\n')) 
    #
    ret <- c(thetahat)
    return(ret)
}

test_mme <- function(seed=777, nbX=80, nbY=72, noiseScale=0.1, dX=3, dY=3)
{  
    set.seed(seed)
    tm = proc.time()
    #
    message('*===================   Start of test_mme   ===================*\n')
    #
    
    sigma = 1

    n = rep(1,nbX)
    m = rep(1,nbY)

    xs = matrix(runif(nbX*dX),nrow=nbX)
    ys = matrix(runif(nbY*dY),nrow=nbY)

    A = matrix(1,nrow=dX,ncol=dY)
    phi = xs %*% A %*% t(ys) 

    mfe_geo_obj <- new(mfe_geo)
    mfe_geo_obj$build(n,m,phi,sigma,FALSE)

    #

    noise = matrix(1 + noiseScale*rnorm(nbX*nbY),nrow=nbX)

    mu_hat = mfe_geo_obj$solve("ipfp")$mu * noise

    #

    model_obj = new(model_dse_logit_tu)
    model_obj$build(xs,ys,n,m)

    res = model_obj$mme(mu_hat)

    thetahat = res$theta_hat

    #
    message("Estimator:")
    print(thetahat)  
    #
    time = proc.time() - tm  
    message(paste0('\nEnd of test_mme. Time elapsed = ', round(time["elapsed"],5), 's.\n')) 
    #
    ret <- c(thetahat)
    return(ret)
}

###################################################################################
###################################################################################
###################################################################################
# mLogLikelihoodBenchmark = function(theta)
# {
#   theA = matrix(theta,dX,dY)
#   thephi = xs %*% theA %*% t(ys)
#   thephiBis = matrix(TUlogitmodel$kron %*% c(theta),nrow=TUlogitmodel$nbX)
#   themkt = build_market_TU_logit(n,m,thephi)
#   res = ipfp(themkt,notifications=F)
#   themu = res$mu
#   thegrad = matrix(0,dX,dY)
#   for (i in 1:dX)
#     for (j in 1:dY)
#     {thegrad[i,j]= sum( t( (themu - muhat) * xs[,i]) * ys[,j]) 
#     }
#   mux0s  = n-apply(themu,1,sum)
#   mu0ys  = m-apply(themu,2,sum) 
#   entrop = 2 * sum(themu *log(themu) ) + sum(mux0s *log(mux0s)  - n*log(n)) +  sum(mu0ys*log(mu0ys)- m*log(m))
#   theval = sum( (themu - muhat) *thephi  ) - entrop  
#   return(list(objective=theval,gradient=c(thegrad) ))
# }

tests_estimation = function(notifications=TRUE,nbDraws=1e3)
{
    ptm = proc.time()
    #
    # res_LL  <- round(test_loglikelihood(),5)
    res_mle <- round(test_mle(),5)
    res_mme <- round(test_mme(),5)
    
    # res_all <- c(res_LL,res_mle,res_mme)
    res_all <- c(res_mle,res_mme)
    # MD5 checksum
    # res_LL_md5 <- digest(res_LL,algo="md5")
    res_mle_md5 <- digest(res_mle,algo="md5")
    res_mme_md5 <- digest(res_mme,algo="md5")
    
    res_all_md5 <- digest(res_all,algo="md5")
    #
    time = proc.time() - ptm
    if(notifications){
        message(paste0('All tests of Estimation completed. Overall time elapsed = ', round(time["elapsed"],5), 's.'))
    }
    #
    # ret <- list(res_all_md5=res_all_md5,res_LL_md5=res_LL_md5,res_mle_md5=res_mle_md5,res_mme_md5=res_mme_md5)
    ret <- list(res_all_md5=res_all_md5,res_mle_md5=res_mle_md5,res_mme_md5=res_mme_md5)
    #
    return(ret)
}
