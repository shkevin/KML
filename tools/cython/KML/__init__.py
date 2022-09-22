"""

KML is a Python module integrating streaming algorithms in the tightly-knit
world of scientific Python packages.

It aims to provide simple and efficient solutions to learning and describing
data streams where data can not fit in memory like in batch settings. These
tools should be accessable to everyone and reusable in various contexts.

See `URL` for complete documentation.
TODO: Add in URL once documentation is publically hosted.
"""
try:
    from ._version import version as __version__
    from ._version import version_tuple
except ImportError:
    __version__ = "unknown version"
    version_tuple = (0, 0, 0, "unknown version", "unknown")

__all__ = ["data_structures", "metrics", "statistics"]
