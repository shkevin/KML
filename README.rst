.. raw:: html

   <!--Adapted from https://github.com/othneildrew/Best-README-Template/blob/master/README.md-->

.. raw:: html

   <!-- PROJECT SHIELDS -->

|CI| |Issues| |MIT License| |LinkedIn|

.. raw:: html

   <!-- [![Contributors][contributors-shield]][contributors-url] -->

.. raw:: html

   <!-- [![Forks][forks-shield]][forks-url] -->

.. raw:: html

   <!-- [![Stargazers][stars-shield]][stars-url] -->

.. raw:: html

   <!-- PROJECT LOGO -->

.. container::

   .. raw:: html

      <h3 align="center">

   KML

   .. raw:: html

      </h3>

   .. raw:: html

      <p align="center">

   Streaming machine learning framework. Explore the docs » View
   Examples · Report Bug · Request Feature

   .. raw:: html

      </p>

.. raw:: html

   <!-- TABLE OF CONTENTS -->

.. raw:: html

   <details open>

Table of Contents

.. raw:: html

   <ol>

.. raw:: html

   <li>

About The Project

.. raw:: html

   <ul>

.. raw:: html

   <li>

Built With

.. raw:: html

   </li>

.. raw:: html

   </ul>

.. raw:: html

   </li>

.. raw:: html

   <li>

Getting Started

.. raw:: html

   <ul>

.. raw:: html

   <li>

Requirements

.. raw:: html

   </li>

.. raw:: html

   <li>

Building

.. raw:: html

   </li>

.. raw:: html

   <li>

Installation

.. raw:: html

   </li>

.. raw:: html

   <li>

Usage

.. raw:: html

   </li>

.. raw:: html

   </ul>

.. raw:: html

   </li>

.. raw:: html

   <li>

Roadmap

.. raw:: html

   </li>

.. raw:: html

   <li>

Contributing

.. raw:: html

   </li>

.. raw:: html

   <li>

License

.. raw:: html

   </li>

.. raw:: html

   <li>

Contact

.. raw:: html

   </li>

.. raw:: html

   <li>

Acknowledgments

.. raw:: html

   </li>

.. raw:: html

   </ol>

.. raw:: html

   </details>

.. raw:: html

   <!-- ABOUT THE PROJECT -->

About The Project
-----------------

The KML tool was developed for streaming machine learning (ML), and is
implemented in C++11 and Python. The core framework was developed in C++
in order to achieve high performance, while Python is exposed through
Cython compilation. Python was used in order to be easily adopted by
other researchers, data scientists, or machine learning engineers.

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

Built With
~~~~~~~~~~

KML was developed with these libraries and frameworks.

-  |C++|

   -  |Eigen3|

-  |Python|

   -  |Cython|

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- GETTING STARTED -->

Getting Started
---------------

Follow the guidelines for building and installing KML.

Requirements
~~~~~~~~~~~~

Software used in building KML are listed below.

============== ====================== ==================================
Software       Version                Description
============== ====================== ==================================
Cmake          3.14+                  Cmake for building project
C++11 compiler e.g., gnu c++, clang++ KML uses C++11 for developed tools
Cython         0.29.24+               Cython version required to compile
Python3        3.7-3.11.0             Python version supported
Doxygen        1.8.17+ (optional)     For building C++ documentation
gcovr          4.2+ (optional)        For creating C++ coverage
============== ====================== ==================================

Building
~~~~~~~~

Common make commands are located in the Makefile.

Building KML can be accomplished by using cmake. See below for cmake
options.

=================== ======= ==================================
Option              Default Description
=================== ======= ==================================
CMAKE_BUILD_TYPE    Debug   Which build type to use
BUILD_PYTHON        OFF     Compile Cython modules into Python
BUILD_COVERAGE      OFF     Create C++ code coverage report
BUILD_DOCUMENTATION OFF     Build C++ documentation repot
BUILD_TESTING       OFF     Build and run C++ unit tests
=================== ======= ==================================

Example common build usage:

.. code:: bash

   cmake \
       .. \
       -DCMAKE_BUILD_TYPE=Debug \
       -DBUILD_TESTING=ON \
       -DBUILD_PYTHON=ON \
       -DBUILD_COVERAGE=OFF \
       -DBUILD_DOCUMENTATION=OFF

   make -j

Installation
~~~~~~~~~~~~

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

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- USAGE EXAMPLES -->

Usage
~~~~~

Common Python usage examples can be found in the “View Examples” link
above. See the documentation for a more detailed usage for C++.

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- ROADMAP -->

Roadmap
-------

-  [X] Basic summary statistics
-  [X] Windowed data structures
-  [ ] Neural Network Framework

   -  [ ] Streaming Autoencoder

See the `open issues <https://github.com/shkevin/KML/issues>`__ for a
full list of proposed features (and known issues).

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- CONTRIBUTING -->

Project leaders
---------------

Maintainers:

-  `shkevin <https://github.com/shkevin>`__

Operations:

-  `shkevin <https://github.com/shkevin>`__

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- CONTRIBUTING -->

Contributing
------------

If you have a suggestion that would make this better, please fork the
repo and create a pull request.

1. Fork the Project
2. Create your Feature Branch (``git checkout -b feature/NewFeature``)
3. Commit your Changes (``git commit -m 'Adding some new feature'``)
4. Push to the Branch (``git push origin feature/NewFeature``)
5. Open a Pull Request

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- LICENSE -->

License
-------

Distributed under the MIT License. See ``LICENSE.txt`` for more
information.

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- CONTACT -->

Contact
-------

Kevin Cox - shk3vin7@gmail.com

Project Link: https://github.com/shkevin/KML

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- ACKNOWLEDGMENTS -->

Acknowledgments
---------------

.. raw:: html

   <p align="right">

(back to top)

.. raw:: html

   </p>

.. raw:: html

   <!-- MARKDOWN LINKS & IMAGES -->

.. raw:: html

   <!-- Languages/Frameworks -->

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
