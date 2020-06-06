#include "partie/etat/SelectionMan.hpp"
#include <exception>
#include <iostream>
#include <sstream>
#include "partie/Partie.hpp"
#include "partie/etat/PersoActif.hpp"

using namespace partie;
using namespace per;
using namespace obj;
using namespace std;

namespace partie::etat
{
    SelectionMan::SelectionMan(size_t indice) { m_equipe = indice; }

    void SelectionMan::operation(Partie& partie, const hex::Coordonnees& coordonnees)
    {
        try
        {
            APersonnage_S personnage = partie.getDonjon()->trouver(coordonnees);
            if (m_equipe == partie.indiceEquipe(personnage))
            {
                // Si le personnage fait partie de l'équipe, on le rend actif.
                partie.setEtat(IEtat_S(new PersoActif(m_equipe, personnage)));
                return;
            }
        }
        catch (const runtime_error&)
        {
            // Le personnage ne fait pas partie du jeu.
        }
    }

    void SelectionMan::operation(Partie&, size_t)
    {
        throw logic_error("SelectionMan::operation : Operation non supportee.");
    }

    void SelectionMan::operation(Partie&) { throw logic_error("SelectionMan::operation : Operation non supportee."); }

    string SelectionMan::enTexte() const
    {
        stringstream ss;
        ss << "<Etat SelectionMan>" << endl;
        ss << "equipe : " << m_equipe << endl;
        return ss.str();
    }

    APersonnage_S SelectionMan::getPersoSelect()
    {
        throw logic_error("SelectionMan::getPersoSelect() : Aucun personnage selectionne.");
    }

    APersonnage_SC SelectionMan::getPersoSelect() const
    {
        throw logic_error("SelectionMan::getPersoSelect() : Aucun personnage selectionne.");
    }

    IObjet_S SelectionMan::getObjetSelect()
    {
        throw logic_error("SelectionMan::getObjetSelect() : Aucun objet selectionne.");
    }

    IObjet_SC SelectionMan::getObjetSelect() const
    {
        throw logic_error("SelectionMan::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
