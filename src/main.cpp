#include <SFML/Graphics.hpp>
#include <iostream>
#include "hex/ICarte.hpp"
#include "hex/CarteHexagone.hpp"

using namespace std;

int main()
{
    // sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    // window.setFramerateLimit(30);

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) window.close();
    //     }

    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }

    hex::ICarte<bool> *carte = new hex::CarteHexagone<bool>(3);
    hex::Coordonnees c(0, 0);
    (*carte)(c) = true;
    std::cout << c << " = " << (*carte)(c) << std::endl;
    c = hex::Coordonnees(-3, 0);
    (*carte)(c) = true;
    try
    {
        c.translate(hex::Direction::SUD);
        cout << c << endl;
        (*carte)(c);
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }
    delete carte;
    return 0;
}
