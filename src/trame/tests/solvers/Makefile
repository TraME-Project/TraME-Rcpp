
# core compiling options
CC  = gcc-mp-7
CXX = g++-mp-7
FC  = gfortran-mp-7

CXX_STD = -std=c++11
OPT_FLAGS = -O3 -Wall -fopenmp -DTRAME_OMP

ARMA_INCLUDE_PATH = /opt/local/include

# install location
INSTALL_PATH=/Users/keithohara/Desktop/SCM/GitHub/TraME

# source directories
SDIR = ./..
TRAME_DIR = $(SDIR)
TRAME_HEADER_DIR = /Users/keithohara/Desktop/SCM/GitHub/TraME/include
TRAME_TEST_DIR = .

# general flags
CXXFLAGS = $(CXX_STD) -Wall $(OPT_FLAGS) -I$(ARMA_INCLUDE_PATH) -I$(TRAME_HEADER_DIR)
LIBS= -framework Accelerate -L/Users/keithohara/Desktop/SCM/GitHub/TraME -ltrame

# TraME Test Files
SOURCES_TRAME_SLVRS= $(TRAME_TEST_DIR)/arc_newton.cpp $(TRAME_TEST_DIR)/cupids_lp.cpp $(TRAME_TEST_DIR)/darum.cpp $(TRAME_TEST_DIR)/eap_nash.cpp $(TRAME_TEST_DIR)/ipfp.cpp $(TRAME_TEST_DIR)/jacobi.cpp $(TRAME_TEST_DIR)/max_welfare.cpp $(TRAME_TEST_DIR)/nodal_newton.cpp $(TRAME_TEST_DIR)/oap_lp.cpp
OBJECTS_TRAME_SLVRS= $(SOURCES_TRAME_SLVRS:.cpp=.test)

all: $(OBJECTS_TRAME_SLVRS)

# core TraME files
$(TRAME_TEST_DIR)/%.test: $(TRAME_TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

# cleanup and install
.PHONY: clean
clean:
	@rm -rf *.so ./*.gcov ./*.gcno ./*.gcda ./*.dSYM ./*.test
