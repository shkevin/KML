# -*- coding: utf-8 -*-
# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

import os
import subprocess
import sys

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.

PARENT_DIR = os.path.abspath(".")
PROJECT_DIR = os.path.abspath("..")
sys.path.insert(0, os.path.abspath("../tools/cython"))

# Doxygen
subprocess.call("doxygen Doxyfile.in", shell=True)

# -- Project information -----------------------------------------------------

project = "KML"
copyright = "2022, Kevin Cox"
author = "Kevin Cox"


# -- General configuration ---------------------------------------------------

# Tell Sphinx to use both the `breathe` and `exhale` extensions
extensions = [
    "sphinx.ext.autodoc",
    "sphinx.ext.intersphinx",
    "sphinx.ext.autosectionlabel",
    "sphinx.ext.todo",
    "sphinx.ext.coverage",
    "sphinx.ext.mathjax",
    "sphinx.ext.ifconfig",
    "sphinx.ext.viewcode",
    "sphinx_sitemap",
    "sphinx.ext.inheritance_diagram",
    "breathe",
    "exhale",
    "sphinx.ext.napoleon",
]

# Setup the `breathe` extension
breathe_projects = {"KML": "_doxygen/xml"}
breathe_default_project = "KML"

# Setup the `exhale` extension
from textwrap import dedent

exhale_args = {
    ############################################################################
    # These arguments are required.                                            #
    ############################################################################
    "containmentFolder": "./api",
    "rootFileName": "library_root.rst",
    "rootFileTitle": "C++ API",
    "doxygenStripFromPath": f"{PROJECT_DIR}/tools/cpp/",
    ############################################################################
    # Suggested optional arguments.                                            #
    ############################################################################
    "createTreeView": True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin": dedent(
        """
        INPUT       = ../tools/cpp/KML/include
        # For this code-base, the following helps Doxygen get past a macro
        # that it has trouble with.  It is only meaningful for this code,
        # not for yours.
        PREDEFINED += NAMESPACE_BEGIN(arbitrary)="namespace arbitrary {"
        PREDEFINED += NAMESPACE_END(arbitrary)="}"
    """
    ),
    ############################################################################
    # HTML Theme specific configurations.                                      #
    ############################################################################
    # Fix broken Sphinx RTD Theme 'Edit on GitHub' links
    # Search for 'Edit on GitHub' on the FAQ:
    #     http://exhale.readthedocs.io/en/latest/faq.html
    "pageLevelConfigMeta": ":github_url: https://github.com/shkevin/KML",
    ############################################################################
    # Main library page layout example configuration.                          #
    ############################################################################
    "afterTitleDescription": dedent(
        """
        Welcome to the developer reference to Exhale Companion.  The code being
        documented here is largely meaningless and was only created to test
        various corner cases e.g. nested namespaces and the like.

        .. note::

            The text you are currently reading was fed to ``exhale_args`` using
            the :py:data:`~exhale.configs.afterTitleDescription` key.  Full
            reStructuredText syntax can be used.

        .. tip::

           Sphinx / Exhale support unicode!  You're ``conf.py`` already has
           it's encoding declared as ``# -*- coding: utf-8 -*-`` **by
           default**.  If you want to pass Unicode strings into Exhale, simply
           prefix them with a ``u`` e.g. ``u"👽😱💥"`` (of course you would
           actually do this because you are writing with åçćëñtß or
           non-English 寫作 😉).
    """
    ),
    "afterHierarchyDescription": dedent(
        """
        Below the hierarchies comes the full API listing.

        1. The text you are currently reading is provided by
           :py:data:`~exhale.configs.afterHierarchyDescription`.
        2. The Title of the next section *just below this* normally defaults to
           ``Full API``, but the title was changed by providing an argument to
           :py:data:`~exhale.configs.fullApiSubSectionTitle`.
        3. You can control the number of bullet points for each linked item on
           the remainder of the page using
           :py:data:`~exhale.configs.fullToctreeMaxDepth`.
    """
    ),
    "fullApiSubSectionTitle": "Custom Full API SubSection Title",
    "afterBodySummary": dedent(
        """
        You read all the way to the bottom?!  This text is specified by giving
        an argument to :py:data:`~exhale.configs.afterBodySummary`.  As the docs
        state, this summary gets put in after a **lot** of information.  It's
        available for you to use if you want it, but from a design perspective
        it's rather unlikely any of your users will even see this text.
    """
    ),
    ############################################################################
    # Individual page layout example configuration.                            #
    ############################################################################
    # Example of adding contents directives on custom kinds with custom title
    "contentsTitle": "Page Contents",
    "kindsWithContentsDirectives": ["class", "file", "namespace", "struct"],
    # This is a testing site which is why I'm adding this
    "includeTemplateParamOrderList": True,
    ############################################################################
    # useful to see ;)
    "verboseBuild": True,
}

# Tell sphinx what the primary language being documented is.
primary_domain = "cpp"

# Tell sphinx what the pygments highlight language should be.
highlight_language = "cpp"

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_rtd_theme"
html_theme_options = {
    "canonical_url": "",
    "analytics_id": "",  #  Provided by Google in your dashboard
    "display_version": True,
    "prev_next_buttons_location": "bottom",
    "style_external_links": False,
    "logo_only": True,
    # Toc options
    "collapse_navigation": True,
    "sticky_navigation": True,
    "navigation_depth": 4,
    "includehidden": True,
    "titles_only": False,
}
html_logo = "images/HQ 01-03-resized.png"
github_url = "https://github.com/shkevin/KML"
# html_baseurl = ''

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]

# -- Breathe configuration -------------------------------------------------

# breathe_projects = {"KML": "_build/xml/"}
# breathe_default_project = "KML"
# breathe_default_members = ("members", "undoc-members")
