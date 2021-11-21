#ifndef CLUSTERING_KMEANS_H
#define CLUSTERING_KMEANS_H

#include <vector>

using std::vector;

namespace Unsupervised {

    namespace Clustering {

        class Kmeans {

        private:
            int k;  // Number of clusters
            int max_iter;  // Maximum iterations used
            float tol;  // Convergence tolerance
            vector<int> cluster_ids;

        public:
            // Kmeans constructor
            Kmeans(int k, int max_iter, float tol);

            // Kmeans destructor
            ~Kmeans();

            // Functions
            void fit(vector<vector<int>> X);
            vector<int> predict(vector<vector<int>> X);
        };
    }
}

#endif //CLUSTERING_KMEANS_H
