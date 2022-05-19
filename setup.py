#!/usr/bin/env python
import os
from glob import glob
from os import scandir
from os.path import sep

from setuptools import Extension, find_packages, setup
from setuptools.command.build_ext import build_ext as _build_ext

# check if cython is installed
try:
    from Cython.Build import cythonize
except ImportError:
    print("Cython could not be found!")
    use_cython = False
else:
    use_cython = True


def get_version():
    """Load the version from version.py, without importing it.
    This function assumes that the last line in the file contains a variable defining the
    version string with single quotes.
    """
    try:
        with open(f"{CYTHON_DIR}/version.py", "r") as f:
            return f.read().split("=")[-1].replace('"', "").strip()
    except IOError:
        return "0.0.1"


def get_readme():
    """Load README.md for display on PyPI."""
    with open("README.md") as f:
        return f.read()


# Avoid a gcc warning below: -Wstrict-prototypes
class my_build_ext(_build_ext):
    def build_extensions(self):
        if "-Wstrict-prototypes" in self.compiler.compiler_so:
            self.compiler.compiler_so.remove("-Wstrict-prototypes")
        super().build_extensions()


# Get Cython sources with their C++ files.
CYTHON_DIR = "tools/cython/KML"
PYTHON_DIR = "tools/python/KML"
SRC_DIR = "tools/cpp/KML/src"
CPPFLAGS = ["-O3", "-std=c++11"]
pyx_sources = glob(f"{CYTHON_DIR}/**/*.pyx", recursive=True)
include_dirs = [f.path for f in scandir(SRC_DIR) if f.is_dir()]

# Build the Cython extensions.
ext_modules = []
to_strip = "tools/cython/"
for pyx in pyx_sources:
    name = pyx.replace(to_strip, "").split(".")[0].replace(sep, ".")
    ext_modules.append(
        Extension(
            name=name,
            sources=[pyx],
            library_dirs=include_dirs,
            include_dirs=include_dirs,
            language="c++",
            extra_compile_args=CPPFLAGS,
        )
    )

setup(
    name="PyKML",
    version=get_version(),
    description="Streaming Machine Learning in C++/Cython.",
    long_description=get_readme(),
    long_description_content_type="text/markdown",
    author="Kevin Cox",
    author_email="shkevin@yahoo.com",
    url="",
    cmdclass={"build_ext": my_build_ext},
    # packages=find_packages(),
    # package_data={"": [f"{PYTHON_DIR}/tests"]},
    ext_modules=cythonize(ext_modules, compiler_directives={"language_level": "3"}),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: MacOS",
        "Operating System :: Unix",
    ],
    python_requires=">=3.6",
    setup_requires=["cython>=0.24.1"],
    install_requires=["cython>=0.24.1"],
)
