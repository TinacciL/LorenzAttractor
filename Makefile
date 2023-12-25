# Makefile

# Compiler
FC = gcc

# Compilation flags
OFLAGS = -o

# Source files
SOURCES = lorenz_attractor.c

# Object files
OBJECTS = lorenz_attractor.o

# Executable
EXECUTABLE = lorenz_attractor.o

# Target to run the executable
run: $(EXECUTABLE)
	$(FC) $(SOURCES) $(OFLAGS) $(EXECUTABLE)
	./$(EXECUTABLE)

# Target to clean up generated files
clean:
	rm -f $(OBJECTS)
