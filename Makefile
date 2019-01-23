.POSIX:

include config.mk

# Sources
CXXSRC = $(shell find src -name "*.cpp")
CCSRC  = $(shell find src -name "*.c")

# Objects
CXXOBJ = $(CXXSRC:.cpp=.o)
CCOBJ  = $(CCSRC:.c=.o)
OBJ    = $(CXXOBJ) $(CCOBJ)

# Dependency files
DEPS   = $(OBJ:.o=.d)

all: $(NAME) #tests

# Compilation
.cpp.o:
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@
.c.o:
	$(CC) $(CCFLAGS) -MMD -c $< -o $@

# Linking
$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LD_FLAGS)

# Dependencies
-include $(DEPS)

tests:
	$(MAKE) -C tests run

clean:
	rm -f $(NAME) $(OBJ) $(DEPS)
	$(MAKE) -C tests clean

.PHONY: all clean tests
