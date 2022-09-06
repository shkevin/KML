============
Installation
============

Users
-----

To use KML install it with pip::

    pip install KML

Developers
----------

If you are a developer that also wants to work on KML, install it from git::

    git clone git://github.com/shkevin/KML.git
    cd KML
    mkvirtualenv kml

    python install -e .

.. note::

    To run the KML tests with coverage, you must build the KML package. Refer to KML/Makefile
	for examples.

Supported platforms
-------------------

KML supports the following versions of Python:

* Python 3.7 - 3.11.0

It is tested primarily on Linux, but due to its minimal dependencies it should work perfectly on both Mac and Windows.

.. note::

    KML also works with `iPython <http://ipython.org/>`_ or `Jupyter <https://jupyter.org/>`_.
