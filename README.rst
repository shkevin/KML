.. Adapted from https://github.com/othneildrew/Best-README-Template/blob/master/README.md

.. raw:: html

   <a name="readme-top"></a>

.. PROJECT LOGO
.. role:: raw-html-m2r(raw)
   :format: html

:raw-html-m2r:`<br />`

.. raw:: html

   <div align="center">
     <a href="https://github.com/shkevin/KML">
       <!-- <img src="docs/images/PNG 01-00.png" alt="Logo" width="250" height="250"> -->
       <!-- <img src="docs/images/3D Mockup 01-00.jpg" alt="Logo" height="400"> -->
       <img src="docs/images/HQ 01-03-resized.png" alt="Logo" width="800" height="400">
     </a>

     <h3 align="center">KML</h3>

     <p align="center">
       Streaming machine learning framework.
       <br />
       <a href="https://github.com/shkevin/KML"><strong>Explore the docs »</strong></a>
       <br />
       <br />
       <a href="https://github.com/shkevin/KML/tools/python/notebooks">View Examples</a>
       ·
       <a href="https://github.com/shkevin/KML/issues">Report Bug</a>
       ·
       <a href="https://github.com/shkevin/KML/issues">Request Feature</a>
     </p>
   </div>

.. inclusion-marker-do-not-remove

.. Shields

|CI| |Issues| |MIT License| |LinkedIn|

.. Table of Contents
.. raw:: html

   <details open>
     <summary>Table of Contents</summary>
     <ol>
       <li>
         <a href="#about-the-project">About The Project</a>
         <ul>
           <li><a href="#built-with">Built With</a></li>
         </ul>
       </li>
       <li>
         <a href="#getting-started">Getting Started</a>
         <ul>
           <li><a href="#requirements">Requirements</a></li>
           <li><a href="#building">Building</a></li>
           <li><a href="#installation">Installation</a></li>
           <li><a href="#usage">Usage</a></li>
         </ul>
       </li>
       <li><a href="#roadmap">Roadmap</a></li>
       <li><a href="#contributing">Contributing</a></li>
       <li><a href="#license">License</a></li>
       <li><a href="#contact">Contact</a></li>
       <li><a href="#acknowledgments">Acknowledgments</a></li>
     </ol>
   </details>

About The Project
-----------------

The KML tool was developed for streaming machine/online learning (ML), and is
implemented in C++11 and Python. The core framework was developed in C++
in order to achieve high performance, while Python is exposed through
Cython compilation. Python was used in order to be easily adopted by
other researchers, data scientists, or machine learning engineers.

.. raw:: html

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

Built With
~~~~~~~~~~

KML was developed with these libraries and frameworks.

-  |C++|

   -  |Eigen3|

-  |Python|

   -  |Cython|

.. raw:: html

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

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

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

Usage
~~~~~

Common Python usage examples can be found in the “View Examples” link
above. See the documentation for a more detailed usage for C++.

.. raw:: html

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

Roadmap
-------

-  [X] Basic summary statistics
-  [X] Windowed data structures
-  [ ] Neural Network Framework

   -  [ ] Streaming Autoencoder

See the `open issues <https://github.com/shkevin/KML/issues>`__ for a
full list of proposed features (and known issues).

.. raw:: html

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

Project leaders
---------------

Maintainers:

-  `shkevin <https://github.com/shkevin>`__

Operations:

-  `shkevin <https://github.com/shkevin>`__

.. raw:: html

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

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

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

License
-------

Distributed under the MIT License. See ``LICENSE.rst`` for more
information.

.. raw:: html

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

Contact
-------

Kevin Cox - shk3vin7@gmail.com

Project Link: https://github.com/shkevin/KML

.. raw:: html

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

Acknowledgments
---------------

.. raw:: html

   <p align="right">(<a href="#readme-top">back to top</a>)</p>

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
