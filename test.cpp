#include <iostream>
#include <fstream>
#include <vector>

struct Point2D {
    double x;
    double y;
};

std::vector<Point2D> loadPointsFromFile(const std::string& filePath) {
    std::vector<Point2D> points;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return points;
    }

    double x, y;
    while (file >> x >> y) {
        Point2D point { x, y };
        points.push_back(point);
    }

    file.close();
    return points;
}

int main() {
    std::vector<Point2D> points = loadPointsFromFile("points.csv");

    for (const auto& point : points) {
        std::cout << "x: " << point.x << ", y: " << point.y << std::endl;
    }

    return 0;
}
