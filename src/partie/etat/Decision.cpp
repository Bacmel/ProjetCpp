#include "partie/etat/Decision.hpp"
#include <exception>
#include <iostream>
#include "partie/Partie.hpp"
#include "partie/etat/PersoActif.hpp"

using namespace partie;
using namespace per;
using namespace obj;
using namespace std;

namespace partie::etat
{
    Decision::Decision(size_t indice, Equipe& equipe)
    {
        m_indiceEquipe = indice;
        m_equipe = &equipe;
    }

    void Decision::operation(Partie&, const hex::Coordonnees&)
    {
        throw std::logic_error("Decision::operation : Opération invalide.");
    }

    void Decision::operation(Partie&, size_t) { throw std::logic_error("Decision::operation : Opération invalide."); }

    void Decision::operation(Partie& partie) {m_equipe->jouer(partie);}
    
    void Decision::afficher() const
    {
        cout << " Etat initial : " << m_indiceEquipe << endl;
    }

    APersonnage_SC Decision::getPersoSelect() const
    {
        throw invalid_argument("Decision::getPersoSelect() : Aucun personnage selectionne.");
    }

    IObjet_SC Decision::getObjetSelect() const
    {
        throw invalid_argument("Decision::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
