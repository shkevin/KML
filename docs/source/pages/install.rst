.. image:: ../_static/r_KMLSimple.png
   :width: 100px
   :align: right
   :target: https://github.com/shkevin/KML

.. _install:

============
Installation
============

Python
^^^^^^^^^^^^

Using a Package Manager
-----------------------------

A package manager (conda, apt, yum, MacPorts, etc) should generally be your
first stop for installing KML - it will make it easy to install KML and
its dependencies, keep them up-to-date, and uninstall them cleanly.

If you're new to Python or unsure where to start, we strongly recommend taking
a look at :ref:`Anaconda <anaconda-installation>`, which the KML developers
use during their day-to-day work.

.. toctree::
  :maxdepth: 2

  anaconda-installation.rst

Using Pip
---------

If your package manager doesn't support KML, or doesn't have the latest
version, your next option should be Python setup tools like `pip`.  You can
always install the latest stable version of KML and its required
dependencies using::

    $ pip install KML

... following that, you'll be able to use all of KML's features.

From Source
-----------

Finally, if you want to work with the latest, bleeding-edge KML goodness,
you can install it using the source code::

    $ git clone https://github.com/shkevin/KML
    $ cd KML
    $ pip isntall -e .

The setup script installs KML's required dependencies and copies KML into
your Python site-packages directory, ready to go.
