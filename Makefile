.DEFAULT_GOAL := all

# The Directories, Source, Includes, Objects, Binary and Resources.
BUILDDIR    := build
SRCEXT      := cpp
OBJEXT      := o

# Global Settings.
DOCKER_IMAGE=kml
GIT_COMMIT_ID=$$(git log --format="%H" -n 1 | head -c 7)
DOCKER_TAG=latest
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
PPATH=$(PYTHONPATH)
TARGET_MAX_CHAR_NUM=20
undefine PYTHONPATH

# COLORS.
GREEN  := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
WHITE  := $(shell tput -Txterm setaf 7)
RESET  := $(shell tput -Txterm sgr0)

all: directories compile-all test test_wheel coverage
	@echo '*******************Compiled*********************'

## Build the docker image for KML.
build: clean
	docker build -t ${DOCKER_IMAGE}:${DOCKER_TAG} .

## Build and compile just the C++ code/Coverage/Testing.
c: directories
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=ON \
		-DBUILD_PYTHON=OFF \
		-DBUILD_COVERAGE=ON \
		-DBUILD_DOCUMENTATION=OFF && \
	make -j

## Compile just the Python/Cython code/documentation.
python: directories
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=OFF \
		-DBUILD_PYTHON=ON \
		-DBUILD_DOCUMENTATION=ON && \
	make -j

## Build and compile with every option on.
compile-all: directories
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=ON \
		-DBUILD_PYTHON=ON \
		-DBUILD_COVERAGE=ON \
		-DBUILD_DOCUMENTATION=ON \
		-DBUILD_STATIC_ANALYSIS=ON && \
	make -j

analyze: directories
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=OFF \
		-DBUILD_PYTHON=OFF \
		-DBUILD_COVERAGE=OFF \
		-DBUILD_DOCUMENTATION=OFF \
		-DBUILD_STATIC_ANALYSIS=ON && \
	make -j

## Mount the docker image and run.
develop:
	docker run --rm -i \
		--name kml \
		-v "$$PWD":/kml \
		-t ${DOCKER_IMAGE}:${DOCKER_TAG} \
		/bin/bash

## Call Unittests for C++/Python.
test:
	[ -d $(BUILDDIR) ] && cd $(BUILDDIR) && ctest -V

## Call Unittests for C++/Python for built wheel. Requires prior build.
test_wheel:
	[ -d $(BUILDDIR) ] && \
	cd $(BUILDDIR)/tools/packages && \
	python3 -m pip install KML*.whl --force-reinstall && \
	python3 -m pytest -p no:cacheprovider ../python/tests && \
	pip uninstall KML -y

## Call Unittests for C++/Python for sdist. Requires prior build.
test_source:
	[ -d $(BUILDDIR) ] && \
	cd $(BUILDDIR)/tools/packages && \
	pip3 install KML*.tar.gz --force-reinstall && \
	python3 -m pytest -p no:cacheprovider ../python/tests && \
	pip uninstall KML -y

## Test Docker image
docker_test: build
	docker run \
		-t ${DOCKER_IMAGE}:${DOCKER_TAG} \
		make test \
		make test_wheel

## Create the C++ Coverage.
coverage:
	[ -d $(BUILDDIR) ] && cd $(BUILDDIR) make coverage

## Remake entire project.
remake: clean all

## Create the build directories.
directories:
	[ -d $(BUILDDIR)  ] || mkdir -p $(BUILDDIR)

## Clean build folder.
clean:
	@$(RM) -rf $(BUILDDIR) ./tox

## Full Clean of entire project. This project formats c++ as .cc
cleaner: clean
	@$(RM) -rf $(BUILDDIR) *.$(SRCEXT) *__pycache__

# Pulled from: https://gist.github.com/prwhite/8168133
## Show help
help:
	@echo ''
	@echo 'Usage:'
	@echo '  ${YELLOW}make${RESET} ${GREEN}<target>${RESET}'
	@echo ''
	@echo 'Targets:'
	@awk '/^[a-zA-Z\-\0-9]+:/ { \
		helpMessage = match(lastLine, /^## (.*)/); \
		if (helpMessage) { \
			helpCommand = substr($$1, 0, index($$1, ":")-1); \
			helpMessage = substr(lastLine, RSTART + 3, RLENGTH); \
			printf "  ${YELLOW}%-$(TARGET_MAX_CHAR_NUM)s${RESET} ${GREEN}%s${RESET}\n", helpCommand, helpMessage; \
		} \
	} \
	{ lastLine = $$0 }' $(MAKEFILE_LIST)

# Non-File Targets
.PHONY: all remake clean cleaner help
