.POSIX:

include config.mk

# Sources
CPP_SRC = $(shell find src -name *.cpp)
C_SRC   = $(shell find src -name *.c)

# Objects
CPP_OBJ = $(CPP_SRC:.cpp=.o)
C_OBJ   = $(C_SRC:.c=.o)
OBJ     = $(CPP_OBJ) $(C_OBJ)

# Dependency files
DEPS    = $(OBJ:.o=.d)

all: $(NAME)

# Compilation
.cpp.o:
	$(CPP) $(CPP_FLAGS) -MMD -c $< -o $@
.c.o:
	$(CC) $(C_FLAGS) -MMD -c $< -o $@

# Linking
$(NAME): $(OBJ)
	$(CPP) -o $@ $(OBJ) $(LD_FLAGS)

# Dependencies
-include $(DEPS)

clean:
	rm -f $(NAME) $(OBJ) $(DEPS)

.PHONY: all clean
