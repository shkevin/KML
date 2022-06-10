#The Directories, Source, Includes, Objects, Binary and Resources
BUILDDIR    := build
SRCEXT      := cpp
OBJEXT      := o

#Defauilt Make
all: directories compile-all test
	@echo '*******************Compiled*********************'

c:
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=ON \
		-DBUILD_PYTHON=OFF \
		-DBUILD_COVERAGE=ON \
		-DBUILD_DOCUMENTATION=OFF && \
	make

python:
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=OFF \
		-DBUILD_PYTHON=ON \
		-DBUILD_DOCUMENTATION=OFF && \
	make

# Compile C++/Cython/Documentation code.
compile-all:
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=ON \
		-DBUILD_PYTHON=ON \
		-DBUILD_COVERAGE=ON \
		-DBUILD_DOCUMENTATION=OFF && \
	make

# Call Unittests for C++/Python.
test:
	[ -d $(BUILDDIR) ] && cd $(BUILDDIR) && ctest -V && \
	cd tools/python/KML/tests/ && python -m pytest -n auto --cov=. --doctest-modules

# Make documention. This only works if BUILD_DOCUMENTATIONS is ON
docs:
	[ -d $(BUILDDIR)/docs ] && \
	cd $(BUILDDIR)/docs/latex && \
	make

# Remake entire project.
remake: clean all

# Create the Directories.
directories:
	[ -d $(BUILDDIR)  ] || mkdir -p $(BUILDDIR)

# Clean only Objects and tar file.
clean:
	@$(RM) -rf $(BUILDDIR)

# Full Clean of entire project. This project formats c++ as .cc
cleaner: clean
	@$(RM) -rf $(BUILDDIR) *.$(SRCEXT)

#Non-File Targets
.PHONY: all remake clean cleaner
