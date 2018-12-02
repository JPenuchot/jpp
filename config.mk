# Project version

VERSION = 0.0.1

# Paths

PREFIX    = /usr/local
MANPREFIX = $(PREFIX)/share/man

# Includes/Libs

CPP_INCS = -Iinclude
#C_INCS = -Iinclude
LIBS = -lm

# Compilers

CPP          = clang++
CC           = clang

# Flags

COMMON_FLAGS = -DVERSION=\"$(VERSION)\" \
							-Wall -Wextra -Werror \
							-O3 -march=native

CPP_FLAGS    = -std=c++17 $(COMMON_FLAGS)
C_FLAGS      = -std=c11 $(COMMON_FLAGS)
LD_FLAGS     = -fPIC

JP_CPP_FLAGS = $(CPP_INCS) $(CPP_FLAGS)
JP_C_FLAGS   = $(C_INCS) $(C_FLAGS)
JP_LD_FLAGS  = $(LIBS) $(LD_FLAGS)
