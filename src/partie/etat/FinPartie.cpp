#include "partie/etat/FinPartie.hpp"
#include <exception>
#include <iostream>
#include "donjon/IDonjon.hpp"
#include "donjon/cases/ACase.hpp"
#include "err/InfoErreur.hpp"
#include "hex/Coordonnees.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/SelectionAuto.hpp"

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

    void FinPartie::operation(Partie&, const Coordonnees&)
    {
        throw logic_error("FinPartie::operation : operation non supporte");
    }

    void FinPartie::operation(Partie&, size_t) { throw logic_error("FinPartie::operation : operation non supporte"); }

    void FinPartie::operation(Partie&) {}

    void FinPartie::afficher() const { cout << " Etat Fin de Partie : " << m_indiceGagnant << endl; }

    APersonnage_SC FinPartie::getPersoSelect() const
    {
        throw logic_error("FinPartie::getPersoSelect : Aucun personnage selectionne.");
    }

    IObjet_SC FinPartie::getObjetSelect() const
    {
        throw logic_error("FinPartie::getObjetSelect : Aucun objet selectionne.");
    }

} // namespace partie::etat
