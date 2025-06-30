# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#

from recommonmark.parser import CommonMarkParser
from sphinx.builders.html import StandaloneHTMLBuilder
import subprocess, os, sys
import textwrap

# Check if we're running on Read the Docs' servers
read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

# -- Project information -----------------------------------------------------

project = 'arduino-xensiv-3d-magnetic-sensor-tlx493d'
copyright = '2022 Infineon Technologies AG'
author = 'Infineon Technologies AG'

# The full version, including alpha/beta/rc tags
release = '1.1.0'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx_rtd_theme',
    'sphinx.ext.autodoc',
    'sphinxemoji.sphinxemoji',
    'sphinx_tabs.tabs',
    'sphinx.ext.intersphinx',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',
    'sphinx_sitemap',
    'sphinx.ext.graphviz',
    'sphinx.ext.inheritance_diagram',
    'breathe',
    'exhale'
]

autosectionlabel_prefix_document = True

source_suffix = [
    '.rst',
]

suppress_warnings = ['autosectionlabel.*', 'epub.duplicated_toc_entry']

# Setup the exhale extension
exhale_args = {
    # These arguments are required
    "containmentFolder":     "./exhale-auto-docs",
    "rootFileName":          "api_list.rst",
    "rootFileTitle":         "API List",
    "doxygenStripFromPath":  "..",
    # Suggested optional arguments
    "createTreeView":        True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin":    textwrap.dedent('''
        INPUT            = ../src 
        GENERATE_LATEX   = NO
        GENERATE_HTML    = NO
        GENERATE_XML     = YES
        RECURSIVE        = YES
        VERBATIM_HEADERS = YES                                
    '''),

    # Configure what not to show in the API index page
    "unabridgedOrphanKinds": {"function", "define", "dir","file", "variable", "namespace"},
    "fullToctreeMaxDepth" : 4
}

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'build', 'Thumbs.db', '.DS_Store']

highlight_language = 'c++'

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_rtd_theme"

html_logo = 'img/ifx_logo_white_green_s.png'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_templates']

# -- Breathe configuration -------------------------------------------------

breathe_projects = {
	"arduino-xensiv-3d-magnetic-sensor-tlx493d": "build/xml/"
}
breathe_default_project = "arduino-xensiv-3d-magnetic-sensor-tlx493d"
breathe_default_members = ('members', 'undoc-members')