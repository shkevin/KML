#!/usr/bin/env python
import multiprocessing
import os
from ast import literal_eval
from distutils.command.build import build as _build
from os import walk
from pathlib import Path, PurePath
from sys import argv
from typing import List

from setuptools import Extension, find_packages, setup
from setuptools.command.build_ext import build_ext as _build_ext

# Get Cython sources with their C++ files.
PARENT_DIR = Path(os.path.abspath(__file__)).parent
CYTHON_DIR = Path(PARENT_DIR, "tools/cython/kml")
SRC_DIR = Path(PARENT_DIR, "tools/cpp/KML/src")
HEADERS_DIR = Path(PARENT_DIR, "tools/cpp/KML/include")
CPPFLAGS = ["-Wall", "-O3", "-std=c++11"]
pyx_sources = CYTHON_DIR.rglob("**/*.py")
include_dirs = [x[0] for x in walk(HEADERS_DIR)]
src_dirs = [x[0] for x in walk(SRC_DIR)]
include_all = include_dirs + src_dirs

try:
    from Cython.Build import cythonize

    USE_CYTHON = True
except ImportError:
    USE_CYTHON = False

# Multiprocessing changed start method for Mac in Python3.8. This is
# used to enforce that the spawn method is fork, and should work across
# all OS. Warnings may be observed due to this change.
if os.uname().sysname == "Darwin":
    from multiprocessing import set_start_method

    set_start_method("fork", force=True)


def get_readme() -> str:
    """Retrieve the readme as a string.

    Retrieve the current readme in the parent directory. This
    is returned as a string and used in the long description.

    Returns:
        str: String representation of readme.
    """
    with open(Path(PARENT_DIR, "README.rst"), "r", encoding="utf8") as f:
        return f.read()


def get_version() -> str:
    """Load the version from version.py

    Load the version from version.py without importing it.
    This function assumes that the last line in the file contains a
    variable defining the version string with single quotes.

    Returns:
        str: Version number
    """
    try:
        with open(Path(CYTHON_DIR, "_version.py"), "r") as f:
            version_tuple = f.read().splitlines()[-1]
            version = literal_eval(version_tuple.split("=")[-1].lstrip())[:3]
            version = ".".join(str(x) for x in version)
            return version
    except IOError:
        return ""


def get_buildlib() -> str:
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

    # build_lib = PurePath(build_lib)
    build_lib = os.path.relpath(build_lib)
    return build_lib


class my_build_ext(_build_ext):
    # Avoid a gcc warning below: -Wstrict-prototypes
    def build_extensions(self) -> None:
        """Build the Cython extensions.

        Build the cython extensions. This is currently used to remove
        the strict-prototypes flag that is irrelevant to C++.
        """
        if "-Wstrict-prototypes" in self.compiler.compiler_so:
            self.compiler.compiler_so.remove("-Wstrict-prototypes")
        super().build_extensions()


class my_build(_build):
    def finalize_options(self) -> None:
        """Finalize the build options for Cython.

        This is overriden from the origina Cython build in order
        to finalize custom build options for kml.
        """
        super().finalize_options()
        if USE_CYTHON:
            from Cython.Compiler import Options

            Options.fail_fast = True

            self.distribution.ext_modules = cythonize(
                self.distribution.ext_modules,
                # Don't build in source tree (this leaves behind .cpp files).
                build_dir=get_buildlib(),
                # Don't generate an .html output file. This will contain source.
                annotate=False,
                # Parallelize our build.
                nthreads=multiprocessing.cpu_count() * 2,
                # Tell Cython we're using Python 3.
                language_level=3,
                # (Optional) Always rebuild, even if files untouched.
                force=False,
                # (Optional) Specify compiler directives.
                compiler_directives={
                    "embedsignature": True,  # Will give types in docs.
                },
            )


def scandir(_dir, files: List[str] = None) -> List[str]:
    """Scan the Cython directory for pyx files.

    Scan the Cython directory in order to get a list of
    files to convert to extensions.

    Args:
        _dir: Directory to search.
        files: Cython files found.

    Returns:
        List[str]: Cython files found.
    """
    if files is None:
        files = []

    for file in os.listdir(_dir):
        path = os.path.join(_dir, file)
        if os.path.isfile(path) and path.endswith(".pyx"):
            path = path.replace(str(CYTHON_DIR.parent) + os.path.sep, "")
            files.append(path.replace(os.path.sep, ".")[:-4])
        elif os.path.isdir(path):
            scandir(path, files)
    return files


def get_extensions() -> List[Extension]:
    """Retrieve the Cython extensions.

    Retrieve the Cython extensions used for the kml project.

    Returns:
        List[Extension]: List of Cython extensions.
    """
    ext_names = scandir(CYTHON_DIR)
    ext_modules = []
    for name in ext_names:
        extPath = name.replace(".", os.path.sep) + ".pyx"
        extPath = PurePath("tools/cython", extPath)
        extension = Extension(
            name,
            [str(extPath)],
            include_dirs=["."] + include_all,
            extra_compile_args=CPPFLAGS,
            extra_link_args=["-g"],
        )
        ext_modules.append(extension)
    return ext_modules


setup(
    name="kml",
    url="https://github.com/shkevin/KML",
    author="Kevin Cox",
    author_email="shk3vin7@gmail.com",
    long_description=get_readme(),
    long_description_content_type="text/x-rst",
    version=get_version(),
    # use_scm_version=True,
    cmdclass={"build_ext": my_build_ext, "build": my_build},
    packages=find_packages("tools/cython"),
    package_dir={"": "tools/cython"},
    ext_modules=get_extensions(),
    zip_safe=False,
    include_package_data=True,
)
