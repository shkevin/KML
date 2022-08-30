#!/usr/bin/env python
import multiprocessing
from distutils.command.build import build as _build
from glob import glob
from os import walk
from os.path import sep
from pathlib import Path, PurePath
from sys import argv
from typing import List

from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext as _build_ext

# Get Cython sources with their C++ files.
PARENT_DIR = Path(__file__).resolve().parent
CYTHON_DIR = Path(PARENT_DIR, "tools/cython")
SRC_DIR = Path(PARENT_DIR, "tools/cpp/KML/src")
HEADERS_DIR = Path(PARENT_DIR, "tools/cpp/KML/include")
CPPFLAGS = ["-O3", "-std=c++11"]
pyx_location = str(PurePath("/KML/**/*.pyx"))
pyx_sources = glob(f"{CYTHON_DIR}{pyx_location}", recursive=True)
include_dirs = [x[0] for x in walk(HEADERS_DIR)]
src_dirs = [x[0] for x in walk(SRC_DIR)]
include_all = include_dirs + src_dirs


def get_buildlib():
    """Attempt to parse build lib from user input.

    Try to get the build directory from the cmake arguments. If the
    build_lib not specified, default to ./build.

    Returns:
        Path: Path to build directory.
    """
    build_lib = "./build"
    for i, a in enumerate(argv):
        # Handle python setup.py call
        if a == "build_ext":
            for build_arg in argv[i:]:
                if build_arg.startswith("--build-lib"):
                    build_lib = build_arg.split("=")[-1]
                    break
        # Handle pip wheel call
        elif a.startswith("-w"):
            build_lib = argv[i + 1]
            break

    build_lib = PurePath(PARENT_DIR, build_lib)
    return build_lib


class my_build_ext(_build_ext):
    # Avoid a gcc warning below: -Wstrict-prototypes
    def build_extensions(self):
        if "-Wstrict-prototypes" in self.compiler.compiler_so:
            self.compiler.compiler_so.remove("-Wstrict-prototypes")
        super().build_extensions()


class my_build(_build):
    def finalize_options(self):
        super().finalize_options()
        # __builtins__.__NUMPY_SETUP__ = False
        # import numpy

        # for extension in self.distribution.ext_modules:
        #     extension.include_dirs.append(numpy.get_include())
        from Cython.Build import cythonize

        self.distribution.ext_modules = cythonize(
            self.distribution.ext_modules,
            # Don't build in source tree (this leaves behind .c files)
            build_dir=get_buildlib(),
            # Don't generate an .html output file. This will contain source.
            annotate=False,
            # Parallelize our build
            nthreads=multiprocessing.cpu_count() * 2,
            # Tell Cython we're using Python 3
            language_level=3,
            # (Optional) Always rebuild, even if files untouched
            force=False,
        )


def get_extensions() -> List[Extension]:
    """Get Cython extensions from project.

    Build the Cython extensions with the cpp headers and sources.

    Returns:
        List[Extension]: List of Cython Extensions.
    """
    ext_modules = []
    to_strip = str(CYTHON_DIR) + sep
    pyx_to_strip = str(PARENT_DIR) + sep
    for pyx in pyx_sources:
        name = pyx.replace(to_strip, "").split(".")[0].replace(sep, ".")
        pyx = pyx.replace(pyx_to_strip, "")
        ext_modules.append(
            Extension(
                name=name,
                sources=[pyx],
                include_dirs=include_all,  # Path to .h files
                language="c++",
                extra_compile_args=CPPFLAGS,
            )
        )
    return ext_modules


setup(
    cmdclass={"build_ext": my_build_ext, "build": my_build},
    ext_modules=get_extensions(),
)
