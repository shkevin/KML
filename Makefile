# The Directories, Source, Includes, Objects, Binary and Resources
BUILDDIR    := build
SRCEXT      := cpp
OBJEXT      := o

# Global Settings
DOCKER_IMAGE=kml
GIT_COMMIT_ID=$$(git log --format="%H" -n 1 | head -c 7)
DOCKER_TAG=latest

# Default Make
all: directories compile-all test coverage
	@echo '*******************Compiled*********************'

# Build docker image
build: clean
	docker build -t ${DOCKER_IMAGE}:${DOCKER_TAG} .

# Compile C++ code
c: directories
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=ON \
		-DBUILD_PYTHON=OFF \
		-DBUILD_COVERAGE=ON \
		-DBUILD_DOCUMENTATION=OFF && \
	make

# Compile Cython/Python code
python: directories
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=OFF \
		-DBUILD_PYTHON=ON \
		-DBUILD_DOCUMENTATION=OFF && \
	make

# Compile C++/Cython/Documentation code.
compile-all: directories
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=ON \
		-DBUILD_PYTHON=ON \
		-DBUILD_COVERAGE=ON \
		-DBUILD_DOCUMENTATION=OFF && \
	make

# Mount repo to Docker image
develop:
	docker run --rm -i \
		--name kml \
		-v "$$PWD":/kml \
		-t ${DOCKER_IMAGE}:${DOCKER_TAG} \
		/bin/bash

# Call Unittests for C++/Python.
test:
	[ -d $(BUILDDIR) ] && cd $(BUILDDIR) && ctest -V && \
	cd tools/python/KML/tests/ && python -m pytest --cov=. --doctest-modules

# Call Unittests for C++/Python for built wheel.
test_wheel:
	[ -d $(BUILDDIR) ] && cd $(BUILDDIR)/tools/packages && \
	pip3 install KML*.whl --force-reinstall && \
	python3 -m pytest ../python/KML/tests/ && \
	pip uninstall KML

# Test Docker image
docker_test: build
	docker run \
		-t ${DOCKER_IMAGE}:${DOCKER_TAG} \
		make test \
		make test_wheel

# Create the C++ Coverage.
coverage:
	[ -d $(BUILDDIR) ] && cd $(BUILDDIR) make coverage

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

# Clean build folder.
clean:
	@$(RM) -rf $(BUILDDIR)

# Full Clean of entire project. This project formats c++ as .cc
cleaner: clean
	@$(RM) -rf $(BUILDDIR) *.$(SRCEXT)

# Non-File Targets
.PHONY: all remake clean cleaner
