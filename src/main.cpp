#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "donjon/cases/Sol.hpp"
#include "err/SansObjetErreur.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"
#include "hex/ICarte.hpp"
#include "hex/Masque.hpp"
#include "per/Heros.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "vue/CaseDessinable.hpp"
#include "vue/Fenetre.hpp"
#include "vue/PersonnageDessinateur.hpp"

using namespace donjon::cases;
using namespace vue;
using namespace std;
using namespace hex;
using namespace sf;
using namespace obj;
using namespace per;

int main()
{
    VideoMode vm = sf::VideoMode(500, 500);
    Fenetre fen(vm, "Circuit Fight!");
    sf::RenderWindow& window = fen.getRenderWindow();
    window.setFramerateLimit(60);

    ICarte_S<ICase_S> carte(new CarteHexagone<ICase_S>(5));
    function<ICase_S()> fournisseurSol = []() { return make_shared<Sol>(); };
    carte->remplir(fournisseurSol);
    Coordonnees positionTrou = Coordonnees().translate(Direction::Nord);
    (*carte)(positionTrou) = ICase_S(new Trou());
    (*carte)(Coordonnees(-1, -1)) = ICase_S(new Trou());

    IObjet_S gravityGun(new GravityGun());
    (*carte)(Coordonnees().translate(Direction::NordOuest))->deposer(gravityGun);

    APersonnage_S heros = make_shared<Heros>(3);
    heros->deplacer(Deplacement::Marcher, Coordonnees().translate(Direction::NordEst));
    heros->subitAttaque(1);

    PersonnageDessinateur pd(window);
    pd.setRayon(25);

    CaseDessinable cdbl(25);
    utils::HexPixelConvertisseur hpc;

    fen.setDessinateur([&](RenderWindow& rw) {
        auto itr = carte->iterateur();
        while (itr->aSuite())
        {
            Coordonnees pos = itr->suite();
            ICase_S iCase = (*carte)(pos);
            cdbl.setCase(*iCase);
            auto pixel = hpc(cdbl.getCote(), pos);
            auto dim = rw.getSize();
            cdbl.setPosition(pixel.x + dim.x / 2., pixel.y + dim.y / 2.);
            rw.draw(cdbl);
            pd.dessine(heros->getPosition(), *heros);
        }
    });

    fen.actualiser();
    return 0;
}
