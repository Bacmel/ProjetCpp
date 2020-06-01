#include "partie/etat/FinPartie.hpp"
#include <iostream>
#include "donjon/IDonjon.hpp"
#include "donjon/cases/ICase.hpp"
#include "err/InfoErreur.hpp"
#include "hex/Coordonnees.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/Selection.hpp"

using namespace partie;
using namespace per;
using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace obj;
using namespace std;

namespace partie::etat
{
    FinPartie::FinPartie(size_t indice) : m_indiceGagnant(indice) {}

    void FinPartie::operation(Partie& partie, const Coordonnees&) { operation(partie); }

    void FinPartie::operation(Partie& partie, size_t) { operation(partie); }

    void FinPartie::operation(Partie& partie) { return; }

    void FinPartie::afficher() const { cout << " Etat Fin de Tour : " << m_indiceGagnant << endl; }

    APersonnage_SC FinPartie::getPersoSelect() const
    {
        throw invalid_argument("FinPartie::getPersoSelect() : Aucun personnage selectionne.");
    }

    IObjet_SC FinPartie::getObjetSelect() const
    {
        throw invalid_argument("FinPartie::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
