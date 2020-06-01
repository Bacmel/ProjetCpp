#include "partie/etat/FinTour.hpp"
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
    FinTour::FinTour(size_t indice) : m_indiceEquipe(indice) {}

    void FinTour::operation(Partie& partie, const Coordonnees&) { operation(partie); }

    void FinTour::operation(Partie& partie, size_t) { operation(partie); }

    void FinTour::operation(Partie& partie) { return; }

    void FinTour::afficher() const { cout << " Etat Fin de Partie : " << m_indiceEquipe << endl; }

    APersonnage_SC FinTour::getPersoSelect() const
    {
        throw invalid_argument("FinTour::getPersoSelect() : Aucun personnage selectionne.");
    }

    IObjet_SC FinTour::getObjetSelect() const
    {
        throw invalid_argument("FinTour::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
