#include "partie/etat/FinPartie.hpp"
#include <exception>
#include <iostream>
#include <sstream>
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
    FinPartie::FinPartie(size_t indice) : m_equipe(indice) {}

    void FinPartie::operation(Partie&, const Coordonnees&)
    {
        throw logic_error("FinPartie::operation : operation non supporte");
    }

    void FinPartie::operation(Partie&, size_t) { throw logic_error("FinPartie::operation : operation non supporte"); }

    void FinPartie::operation(Partie&) {}

    string FinPartie::enTexte() const
    {
        stringstream ss;
        ss << "<Etat FinPartie>" << endl;
        ss << "equipe : " << m_equipe << endl;
        return ss.str();
    }

    APersonnage_S FinPartie::getPersoSelect()
    {
        throw logic_error("FinPartie::getPersoSelect : Aucun personnage selectionne.");
    }

    APersonnage_SC FinPartie::getPersoSelect() const
    {
        throw logic_error("FinPartie::getPersoSelect : Aucun personnage selectionne.");
    }

    IObjet_S FinPartie::getObjetSelect()
    {
        throw logic_error("FinPartie::getObjetSelect : Aucun objet selectionne.");
    }

    IObjet_SC FinPartie::getObjetSelect() const
    {
        throw logic_error("FinPartie::getObjetSelect : Aucun objet selectionne.");
    }

} // namespace partie::etat
