
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
LIBS= -L/Users/keithohara/Desktop/SCM/GitHub/TraME -ltrame -framework Accelerate

# TraME Test Files
SOURCES_TRAME_ANC= $(TRAME_TEST_DIR)/inv_pwa.cpp
OBJECTS_TRAME_ANC= $(SOURCES_TRAME_ANC:.cpp=.test)

all: $(OBJECTS_TRAME_ANC)

# core TraME files
$(TRAME_TEST_DIR)/%.test: $(TRAME_TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

# cleanup and install
.PHONY: clean
clean:
	@rm -rf *.so ./*.gcov ./*.gcno ./*.gcda ./*.dSYM ./*.test
