#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;
#define MAX 10
#define PRINT 0

struct Point {
    double x, y;
    int cluster;
};

// Function to generate a random double between two values
double randomDouble(double minVal, double maxVal) {
    return minVal + static_cast<double>(rand()) / RAND_MAX * (maxVal - minVal);
}

vector<Point> initializeRandomPoints(int n, double minX, double maxX, double minY, double maxY) {
    vector<Point> points(n);

    srand(time(0));
    for (int i = 0; i < n; i++) {
        double x = randomDouble(minX, maxX);
        double y = randomDouble(minY, maxY);
        points[i] = { x, y };
    }

    return points;
}

double distance(Point a, Point b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

void kMeans(vector<Point>& points, int k) {
    // Initialize centroids
    vector<Point> centroids(k);
    for (int i = 0; i < k; i++) {
        centroids[i] = points[i];
        centroids[i].cluster = i;
    }

    bool converged = false;
    while (!converged) {
        converged = true;
        // Assign points to nearest centroid
        // #pragma omp parallel num_threads(MAX)
        for (int i = 0; i < points.size(); i++) {
            double min_dist = distance(points[i], centroids[0]);
            int min_index = 0;
            // #pragma omp parallel for
            for (int j = 1; j < k; j++) {
                double dist = distance(points[i], centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_index = j;
                }
            }
            if (points[i].cluster != min_index) {
                points[i].cluster = min_index;
                converged = false;
            }
        }
        // Recalculate centroids
        for (int i = 0; i < k; i++) {
            double sum_x = 0, sum_y = 0;
            int count = 0;
            for (int j = 0; j < points.size(); j++) {
                if (points[j].cluster == i) {
                    sum_x += points[j].x;
                    sum_y += points[j].y;
                    count++;
                }
            }
            if (count > 0) {
                double new_x = sum_x / count;
                double new_y = sum_y / count;
                if (new_x != centroids[i].x || new_y != centroids[i].y) {
                    centroids[i].x = new_x;
                    centroids[i].y = new_y;
                    converged = false;
                }
            }
        }
    }
}

int main() {
    /* Two variants for initialization specify points manually, randomly creation */

    // Randomly creation
    vector<Point> points_rand = initializeRandomPoints(100000, 0.0, 1.0, 0.0, 1.0);
    
    if (PRINT) {
        // Print the coordinates of each point
        for (int i = 0; i < points_rand.size(); i++) {
            cout << "(" << points_rand[i].x << ", " << points_rand[i].y << ")" << endl;
        }
    }


    // Specify points manually
    vector<Point> points = { {1, 1}, {1.5, 2}, {3, 4}, {5, 7}, {3.5, 5}, {4.5, 5}, {3.5, 4.5}, {113.5, 114.5} };

    int k = 10;
    
    auto start = high_resolution_clock::now();
    // Run k-means clustering algorithm in sequantional mode
    kMeans(points_rand, k);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    
    if (PRINT) {
        // Print results
        for (int i = 0; i < points_rand.size(); i++) {
            cout << "Point (" << points_rand[i].x << ", " << points_rand[i].y << ") belongs to cluster " << points_rand[i].cluster << endl;
        }
    }

    // Print the duration in milliseconds
    cout << "Duration: " << duration << " microseconds" << endl;
    return 0;
}