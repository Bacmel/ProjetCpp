#include <SFML/Graphics.hpp>
#include <iostream>
#include "hex/CarteHexagone.hpp"
#include "hex/ICarte.hpp"
#include "hex/Masque.hpp"

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
    shared_ptr<hex::ICarte<bool>> carte(new hex::CarteHexagone<bool>(3));
    hex::Coordonnees c(0, 0);
    (*carte)(c) = true;
    std::cout << c << " = " << (*carte)(c) << std::endl;
    c = hex::Coordonnees(-3, 0);
    (*carte)(c) = true;
    try
    {
        c = c.translate(hex::Direction::SudEst);
        cout << c << endl;
        (*carte)(c);
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    hex::IIterator_S<hex::Coordonnees> itr = carte->iterateur();
    cout << "Iteration sur les Coordonnees" << endl;
    size_t compte = 0;
    while (itr->aSuite())
    {
        compte++;
        hex::Coordonnees cItr = itr->suite();
        cout << "Point " << compte << " : " << cItr;
        cout << " Contient : " << (*carte)(cItr);
        cout << endl;
    }
    cout << "Il y a " << compte << " cases." << endl;

    hex::ICarte_S<bool> masque(new hex::CarteHexagone<bool>(1));
    masque->remplir(true);
    carte->remplir(*masque, hex::Coordonnees(1, 2));

    itr = carte->iterateur();
    cout << "Iteration sur les Coordonnees" << endl;
    compte = 0;
    while (itr->aSuite())
    {
        compte++;
        hex::Coordonnees cItr = itr->suite();
        cout << "Point " << compte << " : " << cItr;
        cout << " Contient : " << (*carte)(cItr);
        cout << endl;
    }
    cout << "Il y a " << compte << " cases." << endl;

    hex::Masque m1(1);
    m1.remplir(true);

    hex::Masque m2(1);
    m2.remplir(false);
    hex::Coordonnees c2(1, 0);
    m2(c2) = true;

    cout << "ET" << endl;
    hex::Masque et(m1 && m2);
    auto itrEt = et.iterateur();
    while (itrEt->aSuite())
    {
        hex::Coordonnees coord = itrEt->suite();
        cout << coord << '\t' << m1(coord) << " && " << m2(coord) << " = " << et(coord) << endl;
    }

    return 0;
}
