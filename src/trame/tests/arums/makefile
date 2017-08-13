
# core compiling options
CC  = gcc-mp-7
CXX = g++-mp-7
FC  = gfortran-mp-7

CXX_STD = -std=c++11
OPT_FLAGS = -O3 -Wall

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
SOURCES_TRAME_ARUMS= $(TRAME_TEST_DIR)/logit.cpp $(TRAME_TEST_DIR)/none.cpp $(TRAME_TEST_DIR)/probit.cpp $(TRAME_TEST_DIR)/rsc.cpp $(TRAME_TEST_DIR)/rusc.cpp
OBJECTS_TRAME_ARUMS= $(SOURCES_TRAME_ARUMS:.cpp=.test)

all: $(OBJECTS_TRAME_ARUMS)

# core TraME files
$(TRAME_TEST_DIR)/%.test: $(TRAME_TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

# cleanup and install
.PHONY: clean
clean:
	@rm -rf *.so ./*.gcov ./*.gcno ./*.gcda ./*.dSYM ./*.test
