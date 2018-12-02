.POSIX:

include config.mk

CPP_SRC    = $(shell find src/ -name "*.cpp")
C_SRC      = $(shell find src/ -name "*.c")
CPP_OBJ    = $(CPP_SRC:.cpp=.o)
C_OBJ      = $(C_SRC:.c=.o)
OBJ        = $(CPP_OBJ) $(C_OBJ)
COMPILE_DB = $(OBJ:.o=.o.json)

all: options jpp

options:
	@echo
	@echo Build options:
	@echo
	@echo "CPP_FLAGS   = $(JP_CPP_FLAGS)"
	@echo "JP_LD_FLAGS = $(JP_LD_FLAGS)"
	@echo "CPP         = $(CPP)"
	@echo

.cpp.o:
	$(CPP) $(JP_CPP_FLAGS) -c $< -o $@ -MJ $@.json

.c.o:
	$(CC) $(JP_C_FLAGS) -c $< -o $@ -MJ $@.json

jpp: $(OBJ)
	$(CPP) -o $@ $(OBJ) $(JP_LD_FLAGS)
	cat $(COMPILE_DB) > compile_commands.json

clean:
	rm -f jpp compile_commands.json $(COMPILE_DB) $(OBJ)

.PHONY: all options clean
