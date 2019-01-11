# Project version
NAME		= jpp
VERSION = 0.0.1

# Paths
PREFIX    = /usr/local
MANPREFIX = $(PREFIX)/share/man

# Compilers
#CXX = clang++
#CC  = clang

# Includes/Libs
CXXINCS = -Iinclude
CCINCS  = -Iinclude
LIBS    = -lm

# Flags
COMMON_FLAGS = -DVERSION=\"$(VERSION)\"\
							 -Wall -Wextra -Werror\
							 -O3 -march=native

ADD_CXXFLAGS  = $(COMMON_FLAGS) -std=c++17
ADD_CCFLAGS   = $(COMMON_FLAGS) -std=c11
ADD_LD_FLAGS  = -fPIC

CXXFLAGS = $(CXXINCS) $(ADD_CXXFLAGS)
CCFLAGS  = $(CCINCS) $(ADD_CCFLAGS)
LD_FLAGS = $(LIBS) $(ADD_LD_FLAGS)
