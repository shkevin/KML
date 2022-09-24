"""KML Summary Statistics Module.

The Streaming Summary Statistics module attempts to define summary
statistics on data streams.
"""

from .StreamingIQR import PyStreamingIQR
from .StreamingMean import PyStreamingMean
from .StreamingP2Quantile import PyStreamingP2Quantile
from .StreamingVariance import PyStreamingVariance
from .WindowedFAME import PyWindowedFAME
from .WindowedP2Quantile import PyWindowedP2Quantile
