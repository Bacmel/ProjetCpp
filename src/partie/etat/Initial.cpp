#include "partie/etat/Initial.hpp"
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
    Initial::Initial(size_t indice) { m_indiceEquipe = indice; }

    void Initial::operation(Partie& partie, const hex::Coordonnees& coordonnees)
    {
        try
        {
            APersonnage_S personnage = partie.getDonjon()->trouver(coordonnees);
            if (m_indiceEquipe == partie.indiceEquipe(personnage))
            {
                partie.setEtat(IEtat_S(new PersoActif(m_indiceEquipe, personnage)));
                return;
            }
        }
        catch (const runtime_error&)
        {
        }
    }

    void Initial::operation(Partie&, size_t) { throw std::logic_error("Initial::operation : Opération invalide."); }

    void Initial::operation(Partie&) { throw std::logic_error("Initial::operation : Opération invalide."); }

    void Initial::afficher() const { cout << " Etat initial : " << m_indiceEquipe << endl; }

    APersonnage_SC Initial::getPersoSelect() const
    {
        throw invalid_argument("Initial::getPersoSelect() : Aucun personnage selectionne.");
    }

    IObjet_SC Initial::getObjetSelect() const
    {
        throw invalid_argument("Initial::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
