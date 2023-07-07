/*
  Author: Lunnos
  Github: github.com/LunnosMp4
  File: Main.cpp
*/

#include "Population.hpp"

std::vector<Color> readImage(const std::string& path, int *width, int *height) {
    std::vector<Color> pixels;
    sf::Image image;
    image.loadFromFile(path);
    *width = image.getSize().x;
    *height = image.getSize().y;
    for (int x = 0; x < *width; x++) {
        for (int y = 0; y < *height; y++) {
            pixels.push_back(Color(image.getPixel(x, y)));
        }
    }
    return pixels;
}

sf::Image vectorToImage(const std::vector<Color>& colorVector, int width, int height) {
    sf::Image image;
    image.create(height, width); // swap height and width
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const Color& color = colorVector[y * width + x];
            image.setPixel(y, x, color.toSfColor()); // swap x and y
        }
    }
    return image;
}

void updateWindow(sf::RenderWindow& window, std::vector<Color> colorVector, int width, int height) {
    sf::Image image = vectorToImage(colorVector, width, height);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
    }

    window.clear();
    window.draw(sprite);
    window.display();
}

int main(int ac, char** av) {
    int width, height;
    float mutationRate = 0.01;
    int populationSize = 50;
    int generations = 100000;
    std::string path = "resources/creeper.jpg";

    if (ac == 5) {
        generations = std::stoi(av[1]);
        populationSize = std::stoi(av[2]);
        mutationRate = std::stof(av[3]);
        path = av[4];
    } else if (ac != 1) {
        std::cerr << "Usage: ./ImageGeneration [generations] [populationSize] [mutationRate] [path]" << std::endl;
        std::cerr << "Example: ./ImageGeneration 500 50 0.01 resources/creeper.jpg" << std::endl;
        std::cerr << "No arguments will use default values list above" << std::endl;
        return 84;
    }

    std::vector<Color> target = readImage(path, &width, &height);

    std::shared_ptr<Population> population = std::make_shared<Population>(populationSize);
    sf::RenderWindow window(sf::VideoMode(width, height), "TSP");

    while (window.isOpen()) {
        if (population->run(generations, mutationRate, width, height, target, window))
            break;    
    }
}