# -*- coding: utf-8 -*-
# Configuration file for the Sphinx documentation builder.

# -- Path setup --------------------------------------------------------------
import os
import subprocess
import sys

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
PROJECT_DIR = os.path.abspath("../..")
sys.path.insert(0, os.path.abspath(f"{PROJECT_DIR}/tools/cython/KML/"))

# Doxygen
# subprocess.call("doxygen ../Doxyfile.in", shell=True)

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
    "sphinx.ext.napoleon",
    "sphinx.ext.autosummary",
    "breathe",
    "exhale",
]

# Setup the `exhale` extension
from textwrap import dedent

exhale_args = {
    ############################################################################
    # These arguments are required.                                            #
    ############################################################################
    "containmentFolder": "_build/api",
    "rootFileName": "library_root.rst",
    "rootFileTitle": "C++ API",
    "doxygenStripFromPath": f"{PROJECT_DIR}/tools/cpp/KML",
    ############################################################################
    # Suggested optional arguments.                                            #
    ############################################################################
    "createTreeView": False,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin": dedent(
        """
        INPUT       = ../../tools/cpp/KML/include
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
        Welcome to the developer reference to the KLM library. This documentation
        is specific only to the C++ library portion.
    """
    ),
    "afterHierarchyDescription": dedent(
        """
    """
    ),
    "fullApiSubSectionTitle": "Full API",
    "afterBodySummary": dedent(
        """
    """
    ),
    ############################################################################
    # Individual page layout example configuration.                            #
    ############################################################################
    # Example of adding contents directives on custom kinds with custom title
    "contentsTitle": "Page Contents",
    "kindsWithContentsDirectives": ["class", "file", "namespace", "struct"],
    "includeTemplateParamOrderList": False,
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
html_logo = "../images/HQ 01-03-resized.png"
github_url = "https://github.com/shkevin/KML"

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = []

source_suffix = [".rst", ".md"]
source_parsers = {
    ".md": "recommonmark.parser.CommonMarkParser",
}

# Plugin settings
# Napoleon settings
napoleon_google_docstring = True
napoleon_numpy_docstring = True
napoleon_include_init_with_doc = False
napoleon_include_private_with_doc = False
napoleon_include_special_with_doc = True
napoleon_use_admonition_for_examples = False
napoleon_use_admonition_for_notes = False
napoleon_use_admonition_for_references = False
napoleon_use_ivar = False
napoleon_use_param = True
napoleon_use_rtype = True

# -- Breathe configuration -------------------------------------------------
breathe_default_project = "KML"
breathe_projects = {"KML": "_build/_doxygen/xml"}
breathe_default_members = ("members", "undoc-members")
