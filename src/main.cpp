#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "donjon/cases/Sol.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"
#include "hex/ICarte.hpp"
#include "hex/Masque.hpp"
#include "vue/cases/CaseDessinateur.hpp"

using namespace donjon::cases;
using namespace vue::cases;
using namespace std;
using namespace hex;
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Circuit Fight!");
    window.setFramerateLimit(30);

    ICarte_S<ICase_S> carte(new CarteHexagone<ICase_S>(5));
    function<ICase_S()> fournisseurSol = []() { return make_shared<Sol>(); };
    carte->remplir(fournisseurSol);
    Coordonnees positionTrou = Coordonnees().translate(Direction::Nord);
    (*carte)(positionTrou) = ICase_S(new Trou());
    (*carte)(Coordonnees(-1, -1)) = ICase_S(new Trou());
    CaseDessinateur cd(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            // on attrape les évènements de redimensionnement
            if (event.type == sf::Event::Resized)
            {
                // on met à jour la vue, avec la nouvelle taille de la fenêtre
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                View vue = sf::View(visibleArea);
                vue.zoom(2);
                window.setView(vue);
            }
        }
        window.clear(sf::Color::Black);
        auto itr = carte->iterateur();
        while (itr->aSuite())
        {
            Coordonnees pos = itr->suite();
            ICase_S iCase = (*carte)(pos);
            cd.dessine(pos, *iCase);
        }
        window.display();
    }
    return 0;
}
