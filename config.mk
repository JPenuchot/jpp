# Project version
NAME		= jpp
VERSION = 0.0.1

# Paths
PREFIX    = /usr/local
MANPREFIX = $(PREFIX)/share/man

# Compilers
CPP = clang++
CC  = clang

# Includes/Libs
CPP_INCS = -Iinclude
C_INCS   = -Iinclude
LIBS     = -lm

# Flags
COMMON_FLAGS = -DVERSION=\"$(VERSION)\"\
							 -Wall -Wextra -Werror\
							 -O3 -march=native

ADD_CPP_FLAGS  = $(COMMON_FLAGS) -std=c++17
ADD_C_FLAGS    = $(COMMON_FLAGS) -std=c11
ADD_LD_FLAGS   = -fPIC

CPP_FLAGS = $(CPP_INCS) $(ADD_CPP_FLAGS)
C_FLAGS   = $(C_INCS) $(ADD_C_FLAGS)
LD_FLAGS  = $(LIBS) $(ADD_LD_FLAGS)
