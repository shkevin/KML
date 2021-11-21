#ifndef CLUSTER_H
#define CLUSTER_H

#include <limits>
#include <math.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

namespace Clustering {

    // Pulled from http://reasonabledeviations.com/2019/10/02/k-means-in-cpp/

    class Point {
        /* double x[N]; */
        /* int cluster_id; */
        /* double min_dist; */

        /* // Default constructor */
        /* Point() :  , cluster_id(-1), min_dist(-1) {}; */

        /* // Point specific constructor */
        /* Point(double x, double y) : x(x), y(y), cluster_id(-1), min_dist(-1) {}; */

        /* // Euclidean Point-wise distance */
        /* double distance(Point p) { */
        /*     return pow(p.x - x, 2) + pow(p.y - y, 2); */
        /* } */
    };


    class Cluster {

        public:

            /* vector<Point> points;  // Points in cluster */
            /* int cluster_id; // Cluster id */
            /* int num_points; // Number data points in cluster */

            /* // Can only have a cluster with points */
            /* Cluster(vector<Point> points, int cluster_id); */
            /* Cluster(int cluster_id); */

            /* // Cluster Functions */
            /* Point center(Cluster c, string type); */
            /* Point centroid(Cluster c); */

    };
}

#endif // CLUSTER_H
