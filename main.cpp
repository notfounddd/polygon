#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Helper function to determine whether a point is inside a concave polygon
bool isPointInside(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygon) {
    int n = polygon.size();
    if (n < 3) {
        return false;
    }

    int insideCount = 0;
    for (int i = 0; i < n; ++i) {
        const sf::Vector2f& p1 = polygon[i];
        const sf::Vector2f& p2 = polygon[(i + 1) % n];

        // Check if point is to the left of edge
        if (((p2.y <= point.y) && (point.y < p1.y)) ||
            ((p1.y <= point.y) && (point.y < p2.y))) {
            float intersection = (point.y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
            if (intersection < point.x) {
                insideCount++;
            }
        }
    }

    // If count is odd, point is inside the polygon
    return insideCount % 2 == 1;
}

// Function to enter parameters for polygon

void EnterParameters(){
    int AmountPeakInPolygon;
    std::vector<sf::Vector2f> vector;
    std::cin >> AmountPeakInPolygon;
    for (int i = 0; i < AmountPeakInPolygon; i++){
        int CoordX;int CoordY;
        std::cout << "Enter X and Y coordinates" << std::endl;
        std::cin >> CoordX >> CoordY;
        vector.push_back(sf::Vector2f (CoordX,CoordY));
    }
    for (int i = 0; i < vector.size(); i++){
        std::cout << "peak number : " << i+1 << " with coordinates : " << vector[i].x << " , " << vector[i].y << std::endl;
    }
}

int main() {
    EnterParameters();

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Concave Polygon Test");

    // Concave polygon15) Вершины многоугольника: (-1, -1), (-1, 4), (4, 4), (4, -1), (1, 1)
    //Точка: (2, -2)
    std::vector<sf::Vector2f> polygon = {
            sf::Vector2f(-50, -50),
            sf::Vector2f(-50, 90),
            sf::Vector2f(190, 190),
            sf::Vector2f(40, -50),
            sf::Vector2f(50, 50)
    };

    sf::View view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(800, 800));
    window.setView(view);

    // Test points
    std::vector<sf::Vector2f> points = {
            sf::Vector2f(200, 200), // Inside
            sf::Vector2f(150, 150), // Outside
            sf::Vector2f(300, 250) // On edge
    };

    std::string input;

    while (window.isOpen()) {


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        window.clear();

        // Draw polygon
        for (size_t i = 0; i < polygon.size(); ++i) {
            size_t nextIndex = (i + 1) % polygon.size();
            sf::Vertex line[] = {
                    sf::Vertex(polygon[i]),
                    sf::Vertex(polygon[nextIndex])
            };
            window.draw(line, 2, sf::LinesStrip);
        }

        // Draw test points
        for (const auto& point : points) {
            sf::CircleShape circle(5);
            circle.setPosition(point - sf::Vector2f(5, 5));
            circle.setFillColor(isPointInside(point, polygon) ? sf::Color::Green : sf::Color::Red);
            window.draw(circle);
        }

        //window.draw(playerText);
        //std::cin >> input;
        window.display();
    }
    return 0;
}