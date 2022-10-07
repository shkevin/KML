# -*- coding: utf-8 -*-
# Configuration file for the Sphinx documentation builder.
import os
import sys
from textwrap import dedent

from sphinx_gallery.sorting import FileNameSortKey

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
PROJECT_DIR = os.path.abspath("../../")
sys.path.insert(0, os.path.abspath(PROJECT_DIR))
sys.path.insert(0, os.path.abspath("../../tools/cpp"))
sys.path.insert(0, os.path.abspath("_ext"))

# -- Project information -----------------------------------------------------
from kml import __version__

project = "KML"
copyright = "2022, Kevin Cox"
author = "Kevin Cox"
master_doc = "index"
nitpicky = False

release = __version__
version = release

# Doxygen - Use this only if not using exhale.
# subprocess.call("doxygen ../Doxyfile.in", shell=True)

# -- General configuration ---------------------------------------------------

# Tell Sphinx to use both the `breathe` and `exhale` extensions
extensions = [
    "sphinx.ext.autodoc",
    "sphinx.ext.intersphinx",
    "sphinx.ext.todo",
    "sphinx.ext.coverage",
    "sphinx.ext.mathjax",
    "sphinx.ext.ifconfig",
    "sphinx.ext.viewcode",
    "sphinx.ext.inheritance_diagram",
    "sphinx.ext.napoleon",
    "sphinx.ext.autosummary",
    "sphinx.ext.autodoc.typehints",
    "sphinx_sitemap",
    "sphinx_rtd_theme",
    "breathe",
    "exhale",
    "nbsphinx",
    "IPython.sphinxext.ipython_console_highlighting",
    "sphinx_gallery.load_style",
    "sphinx_copybutton",
]

exclude_patterns = ["**/.ipynb_checkpoints"]

# Setup the `exhale` extension
exhale_args = {
    ############################################################################
    # These arguments are required.                                            #
    ############################################################################
    "containmentFolder": "_build/cpp_api",
    "rootFileName": "library_root.rst",
    "rootFileTitle": "C++ API",
    "doxygenStripFromPath": f"{PROJECT_DIR}/tools/cpp/",
    ############################################################################
    # Suggested optional arguments.                                            #
    ############################################################################
    "createTreeView": True,
    "includeTemplateParamOrderList": True,
    # "exhaleUseDoxyfile": True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin": dedent(
        """
     INPUT       = ../../tools/cpp/KML/
     FILE_PATTERNS          = *.h *.tcc *.cc
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
     Welcome to the developer reference to the KML library. This documentation
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
    "kindsWithContentsDirectives": ["dir", "class", "file", "namespace", "struct"],
    #############################################################################
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
html_theme = "sphinx_rtd_theme"
html_theme_options = {
    "canonical_url": "",
    "display_version": True,
    "prev_next_buttons_location": "bottom",
    "style_external_links": False,
    "logo_only": False,
    # Toc options
    "collapse_navigation": False,
    "sticky_navigation": True,
    "navigation_depth": 2,
    "includehidden": False,
    "titles_only": False,
    # Set the color and the accent color
    "style_nav_header_background": "#8d37d7",
}
html_short_title = "KML"
html_logo = "../images/HQ 01-03-resized.png"
github_url = "https://github.com/shkevin/KML"
html_sidebars = {"**": ["logo-text.html", "globaltoc.html", "searchbox.html"]}

html_context = {
    # "display_github": True,  # Add 'Edit on Github' link instead of 'View page source'
    # "last_updated": True,
    "commit": False
}

pygments_style = "sphinx"

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]
templates_path = ["_templates"]
html_css_files = ["custom.css"]

source_suffix = [".rst", ".md", ".ipynb"]


def warn_undocumented_members(app, what, name, obj, options, lines):
    if what not in [] and len(lines) == 0:
        print("WARNING: %s is undocumented: %s" % (what, name))
        lines.append(".. Warning:: %s '%s' undocumented" % (what, name))


def setup(app):
    app.connect("autodoc-process-docstring", warn_undocumented_members)


# -- Options for LaTeX output ---------------------------------------------

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',
    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',
    # Additional stuff for the LaTeX preamble.
    #
    # 'preamble': '',
    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
    (
        master_doc,
        "KML.tex",
        "KML Python/C++ Project Documentation",
        "Kevin Cox",
        "manual",
    )
]

# -- Options for manual page output ---------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    (
        master_doc,
        "python_cpp_example",
        "Python/C++ Project Example Documentation",
        [author],
        1,
    )
]

# -- Plugin Settings ---------------------------------------------------------
# Todo Extension
# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = True

# Intersphinx
intersphinx_mapping = {
    "python": ("https://docs.python.org/3", None),
    "sphinx": ("https://www.sphinx-doc.org/en/master/", None),
    "ipython": ("https://ipython.readthedocs.io/en/latest/", None),
    "pytest": ("https://docs.pytest.org/en/latest/", None),
    "jupyter-notebook": ("https://jupyter-notebook.readthedocs.io/en/stable/", None),
    "jupyterhub": ("https://jupyterhub.readthedocs.io/en/stable/", None),
    "nbconvert": ("https://nbconvert.readthedocs.io/en/latest/", None),
    "jupyter-contrib-nbextensions": (
        "https://jupyter-contrib-nbextensions.readthedocs.io/en/latest/",
        None,
    ),
    "sphinx": ("https://www.sphinx-doc.org/en/master/", None),
    "nbsphinx": ("https://nbsphinx.readthedocs.io/en/0.4.2/", None),
    "pandas": ("https://pandas.pydata.org/pandas-docs/stable/", None),
    "python-basics": ("https://python-basics-tutorial.readthedocs.io/en/latest/", None),
}

# Napolean
napoleon_google_docstring = True
napoleon_numpy_docstring = False
napoleon_include_init_with_doc = True
napoleon_include_private_with_doc = False
napoleon_include_special_with_doc = True
napoleon_use_admonition_for_examples = False
napoleon_use_admonition_for_notes = False
napoleon_use_admonition_for_references = False
napoleon_use_ivar = False
napoleon_use_param = True
napoleon_use_rtype = True
napoleon_type_aliases = False
napoleon_attr_annotations = True

# Autodoc
autoclass_content = "both"
autodoc_default_flags = ["members", "inherited-members", "show-inheritance"]
autodoc_default_options = {
    "members": True,
    "inherited-members": True,
    "show-inheritance": True,
    "undoc-member": True,
    "member-order": "bysource",
}
autodoc_typehints = "signature"
autosummary_generate = True
set_type_checking_flag = False

# Sphinx Gallery
sphinx_gallery_conf = {
    "doc_module": "kml",
    "show_memory": False,
    "examples_dirs": [f"notebooks/"],
    "gallery_dirs": ["auto_examples"],
    "within_subsection_order": FileNameSortKey,
    "matplotlib_animations": True,
    "binder": {},
    "inspect_global_variables": False,
    "remove_config_comments": True,
    "plot_gallery": True,
    "download_all_examples": False,
    # avoid generating too many cross links
    "inspect_global_variables": False,
    "remove_config_comments": True,
    "plot_gallery": "True",
}

# Nbsphinx
nbsphinx_allow_errors = True

# Copybutton
# Setup the copybutton extension
copybutton_prompt_text = r">>> |\.\.\. |\$ |In \[\d*\]: | {2,5}\.\.\.: | {5,8}: "
copybutton_prompt_is_regexp = True

# -- Breathe configuration -------------------------------------------------
breathe_default_project = "kml"
breathe_projects = {"kml": "_build/doxygen/xml"}
breathe_default_members = tuple(autodoc_default_flags)
breathe_domain_by_extension = {"hpp": "cpp"}
