# Example makefile for a basic program
# Note that 
CC = g++
SRCDIR = ./src
BUILDDIR = ./build
TESTFILES = $(wildcard $(SRCDIR)/*.cpp)
TEST_EXE = $(BUILDDIR)/test

test: $(TESTFILES)
	$(CC) -o $(TEST_EXE) $(TESTFILES)

# Note that core files are the result of program fails...
# Therefore we remove them
# Note that the "-" in front of rm means that if this command fails
# Then it does not matter, continue with the build.
clean:
	-rm -f $(BUILDDIR)/*.o $(BUILDDIR)/core $(TEST_EXE)

rebuild: clean test

# Special macros:
# $@ -- This is the name of the target. Useful for making generic actions for many 
# 		different targets
# $? -- Stores the list of dependencies more recent than the target