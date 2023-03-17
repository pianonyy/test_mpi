#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Point2D {
    double x;
    double y;
};

std::vector<Point2D> loadPointsFromCSV(const std::string& filePath) {
    std::vector<Point2D> points;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return points;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;

        Point2D point;
        std::getline(ss, token, ',');
        point.x = std::stod(token);

        std::getline(ss, token, ',');
        point.y = std::stod(token);

        points.push_back(point);
    }

    file.close();
    return points;
}

int main() {
    std::vector<Point2D> points = loadPointsFromCSV("points.csv");

    for (const auto& point : points) {
        std::cout << "x: " << point.x << ", y: " << point.y << std::endl;
    }

    return 0;
}
