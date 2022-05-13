#The Directories, Source, Includes, Objects, Binary and Resources
BUILDDIR    := build
SRCEXT      := cpp
OBJEXT      := o

#Defauilt Make
all: directories compile test
	@echo '*******************Compiled*********************'

# Compile C++/Cython code
compile:
	cd $(BUILDDIR) && \
	cmake \
	    .. \
	    -DCMAKE_BUILD_TYPE=Debug \
	    -DBUILD_TESTING=ON \
		-DBUILD_PYTHON=ON && \
	make

# Call Unittests for C++
test:
	cd $(BUILDDIR) && ctest -V

#Remake
remake: clean all

#Make the Directories
directories:
	[ -d $(BUILDDIR)  ] || mkdir -p $(BUILDDIR)

#Clean only Objects and tar file.
clean:
	@$(RM) -rf $(BUILDDIR)

#Full Clean, Objects,Binaries, and tar file.
cleaner: clean
	@$(RM) -rf $(BUILDDIR) *.cpp

#Non-File Targets
.PHONY: all remake clean cleaner
