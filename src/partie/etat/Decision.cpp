#include "partie/etat/Decision.hpp"
#include <exception>
#include <iostream>
#include "partie/Partie.hpp"
#include "partie/etat/PersoActif.hpp"

using namespace obj;
using namespace partie;
using namespace per;
using namespace std;

namespace partie::etat
{
    Decision::Decision(size_t indice) : m_indiceEquipe(indice) {}

    void Decision::operation(Partie&, const hex::Coordonnees&)
    {
        throw logic_error("Decision::operation : Operation non supportee.");
    }

    void Decision::operation(Partie&, size_t) { throw logic_error("Decision::operation : Operation non supportee."); }

    void Decision::operation(Partie& partie)
    {
        // Execute la stratégie de l'équipe active.
        Equipe& equipe = partie.getEquipe(m_indiceEquipe);
        equipe.jouer(partie);
    }

    void Decision::afficher() const { cout << " Decision : " << m_indiceEquipe << endl; }

    APersonnage_SC Decision::getPersoSelect() const
    {
        throw logic_error("Decision::getPersoSelect : Aucun personnage selectionne.");
    }

    IObjet_SC Decision::getObjetSelect() const
    {
        throw logic_error("Decision::getObjetSelect : Aucun objet selectionne.");
    }

} // namespace partie::etat
