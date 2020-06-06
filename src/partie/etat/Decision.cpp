#include "partie/etat/Decision.hpp"
#include <exception>
#include <iostream>
#include <sstream>
#include "partie/Partie.hpp"
#include "partie/etat/PersoActif.hpp"

using namespace obj;
using namespace partie;
using namespace per;
using namespace std;

namespace partie::etat
{
    Decision::Decision(size_t indice) : m_equipe(indice) {}

    void Decision::operation(Partie&, const hex::Coordonnees&)
    {
        throw logic_error("Decision::operation : Operation non supportee.");
    }

    void Decision::operation(Partie&, size_t) { throw logic_error("Decision::operation : Operation non supportee."); }

    void Decision::operation(Partie& partie)
    {
        // Execute la stratégie de l'équipe active.
        Equipe& equipe = partie.getEquipe(m_equipe);
        equipe.jouer(partie);
    }

    string Decision::enTexte() const
    {
        stringstream ss;
        ss << "<Etat Decision>" << endl;
        ss << "equipe : " << m_equipe << endl;
        return ss.str();
    }

    APersonnage_S Decision::getPersoSelect()
    {
        throw logic_error("Decision::getPersoSelect : Aucun personnage selectionne.");
    }

    APersonnage_SC Decision::getPersoSelect() const
    {
        throw logic_error("Decision::getPersoSelect : Aucun personnage selectionne.");
    }

    IObjet_S Decision::getObjetSelect()
    {
        throw logic_error("Decision::getObjetSelect : Aucun objet selectionne.");
    }

    IObjet_SC Decision::getObjetSelect() const
    {
        throw logic_error("Decision::getObjetSelect : Aucun objet selectionne.");
    }

} // namespace partie::etat
