#distutils: language = c++

cdef extern from "WindowedFAME.cc":
    pass

cdef extern from "StreamingMAD.cc":
    pass

cdef extern from "StreamingMAD.h" namespace "KML::Metrics":
    cdef cppclass StreamingMAD:
        StreamingMAD() except +
        void update(double) except +
        double evaluate() except +
