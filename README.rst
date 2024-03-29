.. Adapted from https://github.com/othneildrew/Best-README-Template/blob/master/README.md

|Logo|

.. class:: center

.. inclusion-marker-do-not-remove

.. Shields

|Docs| |CI| |Coverage| |Issues| |MIT License| |LinkedIn|

Table of Contents
=================

#. `About The Project <#about-the-project>`__

   -  `Built With <#built-with>`__

#. `Getting Started <#getting-started>`__

   -  `Requirements <#requirements>`__
   -  `Building <#building>`__
   -  `Installation <#installation>`__
   -  `Usage <#usage>`__

#. `Roadmap <#roadmap>`__
#. `Contributing <#contributing>`__
#. `License <#license>`__
#. `Contact <#contact>`__
#. `Acknowledgments <#acknowledgments>`__

About The Project
=================

The KML tool was developed for streaming machine/online learning (ML), and is
implemented in C++11 and Python. The core framework was developed in C++
in order to achieve high performance, while Python is exposed through
Cython compilation. Python was used in order to be easily adopted by
other researchers, data scientists, or machine learning engineers.

Built With
----------

KML was developed with these libraries and frameworks.

============== ======================
|C++|          |Python|
============== ======================
|Eigen3|       |Cython|
============== ======================

Getting Started
===============

Follow the guidelines for building and installing KML.

Requirements
------------

Software used in building KML are listed below.

============== ====================== ==================================
Software       Version                Description
============== ====================== ==================================
Cmake          3.14+                  Cmake for building project
C++11 compiler e.g., gnu c++, clang++ KML uses C++11 for developed tools
Eigen          ~3.4                   Eigen C++ matrix library
Cython         0.29.24+               Cython version required to compile
Python3        3.7-3.11.0             Python version supported
Doxygen        1.8.17+ (optional)     For building C++ documentation
gcovr          4.2+ (optional)        For creating C++ coverage
cppcheck       1.90+ (optional)       For creating static code analysis
============== ====================== ==================================

Building
--------

Common make commands are located in the Makefile.

Building KML can be accomplished by using cmake. See below for cmake
options.

==================== ======= ==================================
Option               Default Description
==================== ======= ==================================
CMAKE_BUILD_TYPE     Debug   Which build type to use
BUILD_PYTHON         OFF     Compile Cython modules into Python
BUILD_COVERAGE       OFF     Create C++ code coverage report
BUILD_DOCUMENTATION  OFF     Build C++ documentation repot
BUILD_TESTING        OFF     Build and run C++ unit tests
BUILD_STATIC_ANLYSIS OFF     Build Static Code Analysis
==================== ======= ==================================

Example common build usage:

.. code:: bash

   cmake \
       .. \
       -DCMAKE_BUILD_TYPE=Debug \
       -DBUILD_TESTING=ON \
       -DBUILD_PYTHON=ON \
       -DBUILD_COVERAGE=OFF \
       -DBUILD_DOCUMENTATION=OFF \
       -DBUILD_STATIC_ANALYSIS=OFF

   make -j

Building Python Docker
======================

Building the Python Docker container can be done with any of the one methods listed below.

Method 1: Using the Makefile command.
.. code:: bash

    make docker

Method 2: Using Docker build directly.
.. code:: bash

    docker build -t kml:latest .

Method 3: Using docker-compose.
.. code:: bash

    docker-compose up

Installation
============

For installing the KML Python package:

Be sure to build the C++/Python with the example build above. After
building, the Python package will be located in the build/tools/packages
directory. There will be a source distribution and a wheel distrubtion.

For installing the source distribution (tar.gz):

.. code:: bash

   pip install KML-<MAJOR>.<MINOR>.<PATCH>.tar.gz

Where MAJOR, MINOR, and PATCH are from the current KML version.

For installing the wheel distribution (whl):

.. code:: bash

   pip install KML-<MAJOR>.<MINOR>.<PATCH>-cp<PYVERSION>-cp<PYVERSION>m-<DIST>.whl

Where MAJOR, MINOR, and PATCH are from the current KML version. And
where PYVERSION is the Python version used to build the wheel, and DIST
is the OS distribution used during build (e.g., linux).

Usage
=====

Common Python usage examples can be found in the "View Examples" link on
GitHub. See the documentation for a more detailed usage for C++.

Roadmap
=======

-  [X] Basic summary statistics
-  [X] Windowed data structures
-  [ ] Neural Network Framework

   -  [ ] Streaming Autoencoder

See the `open issues <https://github.com/shkevin/KML/issues>`__ for a
full list of proposed features (and known issues).

Project leaders
===============

Maintainers:

-  `shkevin <https://github.com/shkevin>`__

Operations:

-  `shkevin <https://github.com/shkevin>`__

.. .. raw:: html

..    <p align="right">(<a href="#readme-top">back to top</a>)</p>

Contributing
============

If you have a suggestion that would make this better, please fork the
repo and create a pull request.

1. Fork the Project
2. Create your Feature Branch (``git checkout -b feature/NewFeature``)
3. Commit your Changes (``git commit -m 'Adding some new feature'``)
4. Push to the Branch (``git push origin feature/NewFeature``)
5. Open a Pull Request

License
=======

Distributed under the MIT License. See ``LICENSE.rst`` for more
information.

Contact
=======

Kevin Cox - shk3vin7@gmail.com

Project Link: https://github.com/shkevin/KML

Acknowledgments
===============

.. Languages/Frameworks
.. |CI| image:: https://github.com/shkevin/KML/actions/workflows/build.yml/badge.svg
   :target: https://github.com/shkevin/KML/actions/workflows/build.yml
.. |Issues| image:: https://img.shields.io/github/issues/shkevin/KML
   :target: https://github.com/shkevin/KML/issues
.. |MIT License| image:: https://img.shields.io/github/license/shkevin/KML
   :target: https://github.com/shkevin/KML/blob/master/LICENSE.txt
.. |LinkedIn| image:: https://img.shields.io/badge/-LinkedIn-black.svg?color=Blue&style=social&logo=linkedin&colorB=555
   :target: https://www.linkedin.com/in/kevin-cox-640334195/
.. |C++| image:: https://img.shields.io/badge/-C++11-00599C?logo=cplusplus&logoColor=white&style=flat&labelColor=black
   :target: https://isocpp.org/wiki/faq/cpp11
.. |Eigen3| image:: https://img.shields.io/badge/-Eigen3-00599C?logo=cplusplus&logoColor=white&style=flat&labelColor=black&color=9cf
   :target: https://eigen.tuxfamily.org/index.php?title=Main_Page
.. |Python| image:: https://img.shields.io/badge/-Python3-3776AB?logo=python&logoColor=white&style=flat&labelColor=black&color=yellowgreen
   :target: https://www.python.org/
.. |Cython| image:: https://img.shields.io/badge/-Cython-3776AB?logo=python&logoColor=white&style=flat&labelColor=black&color=yellow
   :target: https://cython.org/

.. |Docs| image:: https://img.shields.io/badge/docs-latest-brightgreen
   :target: https://shkevin.github.io/KML/
.. |Coverage| image:: https://codecov.io/github/shkevin/KML/branch/main/graph/badge.svg?token=QSS0KO8RR9
   :target: https://codecov.io/github/shkevin/KML
.. |Logo| image:: docs/images/HQ%2001-03-resized.png
   :width: 800px
   :height: 400px
   :target: https://github.com/shkevin/KML
