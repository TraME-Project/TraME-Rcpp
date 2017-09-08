# TraME

**Tra***nsportation **M***ethods for **E***conometrics

### Overview

TraME (Transportation Methods for Econometrics) is an R package for for 
solving problems of equilibrium computation and estimation in consumer 
demand and matching frameworks via the Mass Transportation Approach.

### Status [![Build Status](https://travis-ci.org/TraME-Project/TraME.svg?branch=master)](https://travis-ci.org/TraME-Project/TraME) [![Build status](https://ci.appveyor.com/api/projects/status/github/TraME-Project/TraME-Rcpp?branch=master)](https://ci.appveyor.com/project/kthohr/trame-rcpp/branch/master)

The package is under active development and should be considered as
`alpha stage' software.

### Installation and Testing

The quickest way to install TraME is via the devtools package.
```
install.packages("devtools")
library(devtools)
install_github("TraME-Project/TraME-R")
```
The TraME test routines are invoked as follows:
```
library(TraME)
tests_TraME()
```

Note that TraME requires compilation, and so an appropriate development environment is necessary to install the package.
* For Windows users, get [Rtools](https://cran.r-project.org/bin/windows/Rtools/).
* For Mac users, get Xcode and install gfortran 4.8.2, the latter of which can be [obtained using](http://www.thecoatlessprofessor.com/programming/rcpp-rcpparmadillo-and-os-x-mavericks-lgfortran-and-lquadmath-error/)
```
curl -O http://r.research.att.com/libs/gfortran-4.8.2-darwin13.tar.bz2
sudo tar fvxz gfortran-4.8.2-darwin13.tar.bz2 -C /
```

### Authors

Alfred Galichon and the TraME team.

### License

GPL (>= 2) 
