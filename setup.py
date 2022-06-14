#!/usr/bin/env python
from glob import escape, glob
from os import scandir
from os.path import join, realpath, relpath, sep
from pathlib import Path, PurePath
from sys import argv

from setuptools import Extension, setup
from setuptools.command.build_ext import build_ext as _build_ext

# check if cython is installed.
try:
    from Cython.Build import cythonize
except ImportError:
    print("Cython could not be found!")
    use_cython = False
else:
    use_cython = True

# Get Cython sources with their C++ files.
PACKAGE_NAME = "KML"
PARENT_DIR = Path(__file__).resolve().parent
CYTHON_DIR = PurePath(PARENT_DIR, "tools/cython")
SRC_DIR = PurePath(PARENT_DIR, "tools/cpp/KML/src")
CPPFLAGS = ["-O3", "-std=c++11"]
REQUIREMENTS_DIR = "./tools/python/KML/requirements/"
pyx_location = str(PurePath("/KML/**/*.pyx"))
pyx_sources = glob(f"{CYTHON_DIR}{pyx_location}", recursive=True)
include_dirs = [f.path for f in scandir(SRC_DIR) if f.is_dir()]


def get_version():
    """Load the version from version.py, without importing it.
    This function assumes that the last line in the file contains a
    variable defining the version string with single quotes.
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


def get_reqs(fname="requirements.txt"):
    with open(PurePath(REQUIREMENTS_DIR, fname)) as fd:
        reqs = fd.read().splitlines()
        return list(filter(lambda x: not x.startswith("#"), reqs))


def get_buildlib():
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

    build_lib = PurePath(build_lib)
    return build_lib


# Avoid a gcc warning below: -Wstrict-prototypes
class my_build_ext(_build_ext):
    def build_extensions(self):
        if "-Wstrict-prototypes" in self.compiler.compiler_so:
            self.compiler.compiler_so.remove("-Wstrict-prototypes")
        super().build_extensions()


# Build the Cython extensions.
ext_modules = []
to_strip = str(CYTHON_DIR) + sep
pyx_to_strip = str(PARENT_DIR) + sep
for pyx in pyx_sources:
    name = pyx.replace(to_strip, "").split(".")[0].replace(sep, ".")
    pyx = pyx.replace(pyx_to_strip, "")
    print(pyx)
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
    name="KML",
    version=get_version(),
    description="Streaming Machine Learning in C++/Cython.",
    long_description=get_readme(),
    long_description_content_type="text/markdown",
    author="Kevin Cox",
    author_email="shkevin@yahoo.com",
    url="https://github.com/shkevin/KML",
    cmdclass={"build_ext": my_build_ext},
    ext_modules=cythonize(
        ext_modules,
        compiler_directives={"language_level": "3"},
        build_dir=relpath(get_buildlib()),
    ),
    classifiers=[
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: Implementation :: CPython",
        "Programming Language :: Python :: Implementation :: PyPy",
        "Operating System :: MacOS",
        "Operating System :: Unix",
    ],
    python_requires=">=3.6",
    setup_requires=["wheel", "cython>=0.24.1"],
    install_requires=get_reqs("requirements.txt"),
    extras_require={"test": get_reqs("test_requirements.txt")},
)
