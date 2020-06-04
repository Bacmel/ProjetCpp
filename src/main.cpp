#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "controlleur/PartieCont.hpp"
#include "donjon/cases/Sol.hpp"
#include "err/SansObjetErreur.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"
#include "hex/ICarte.hpp"
#include "hex/Masque.hpp"
#include "partie/Equipe.hpp"
#include "partie/Partie.hpp"
#include "partie/strat/JoueurHumain.hpp"
#include "per/Heros.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "vue/CaseDessinable.hpp"
#include "vue/Fenetre.hpp"
#include "vue/PartieDessinable.hpp"
#include "vue/PersonnageDessinable.hpp"

using namespace donjon::cases;
using namespace vue;
using namespace std;
using namespace hex;
using namespace sf;
using namespace obj;
using namespace partie;
using namespace partie::strat;
using namespace per;
using namespace controlleur;

int main()
{
    VideoMode vm = sf::VideoMode(500, 500);
    Fenetre fen(vm, "Circuit Fight!");
    sf::RenderWindow& window = fen.getRenderWindow();
    window.setFramerateLimit(60);

    IStrategie_S strat1 = make_shared<JoueurHumain>();
    Partie partie(strat1);

    IObjet_S gravityGun(new GravityGun());
    partie.genererObjet(gravityGun);
    IObjet_S taser(new Taser());
    partie.genererObjet(taser);
    // Crée l'équipe 1
    APersonnage_S heros = make_shared<Heros>(3);
    partie.genererPersonnage(heros, 0);
    APersonnage_S fantassin = make_shared<Fantassin>();
    partie.genererPersonnage(fantassin, 0);
    // Crée l'équipe 2
    IStrategie_S strat2 = make_shared<JoueurHumain>();
    size_t eqp2 = partie.genererEquipe(strat1);
    APersonnage_S herosAdverse = make_shared<Heros>(3);
    partie.genererPersonnage(herosAdverse, eqp2);

    PartieDessinable pd(25, partie);

    auto carte = partie.getDonjon()->getCarte();

    fen.setDessinateur([&](RenderWindow& rw) { rw.draw(pd); });

    PartieCont control(pd, partie);
    fen.attacher(Event::EventType::MouseButtonPressed, &control);
    partie.demande();
    fen.actualiser();
    return 0;
}
