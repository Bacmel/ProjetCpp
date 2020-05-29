#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "donjon/cases/Sol.hpp"
#include "err/SansObjetErreur.hpp"
#include "hex/CarteHexagone.hpp"
#include "hex/Coordonnees.hpp"
#include "hex/ICarte.hpp"
#include "hex/Masque.hpp"
#include "vue/Fenetre.hpp"
#include "vue/ObjetDessinateur.hpp"
#include "vue/cases/CaseDessinateur.hpp"
#include "per/Heros.hpp"
#include "vue/PersonnageDessinateur.hpp"

using namespace donjon::cases;
using namespace vue::cases;
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
    (*carte)(Coordonnees())->deposer(gravityGun);

    APersonnage_S heros = make_shared<Heros>(3);
    heros->deplacer(Deplacement::Marcher, Coordonnees().translate(Direction::NordEst));
    heros->subitAttaque(1);

    CaseDessinateur cd(window);
    ObjetDessinateur od(window);
    PersonnageDessinateur pd(window);

    fen.setDessinateur([&](RenderWindow& rw) {
        auto itr = carte->iterateur();
        while (itr->aSuite())
        {
            Coordonnees pos = itr->suite();
            ICase_S iCase = (*carte)(pos);
            cd.dessine(pos, *iCase);
            try
            {
                const IObjet& iObjet = iCase->getObjet();
                od.dessiner(pos, iObjet);
            }
            catch (const err::SansObjetErreur& ex)
            {
            }
            pd.dessiner(*heros);
        }
    });

    fen.actualiser();
    return 0;
}
