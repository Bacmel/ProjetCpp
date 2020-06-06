#include "partie/etat/PersoActif.hpp"
#include <exception>
#include <iostream>
#include <sstream>
#include "donjon/IDonjon.hpp"
#include "err/DeplacementErreur.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/FinTour.hpp"
#include "partie/etat/ObjetActif.hpp"
#include "partie/etat/SelectionMan.hpp"

using namespace err;
using namespace partie;
using namespace per;
using namespace obj;
using namespace donjon;
using namespace std;

namespace partie::etat
{
    PersoActif::PersoActif(size_t indice, APersonnage_S PersoActif) : m_equipe(indice), m_personnage(PersoActif) {}

    void PersoActif::operation(Partie& partie, const hex::Coordonnees& coordonnees)
    {
        // Annulation second clic.
        if (m_personnage->getPosition() == coordonnees)
        {
            partie.setEtat(IEtat_S(new SelectionMan(m_equipe)));
            return;
        }

        // Selectionne un autre personnage de l'equipe.
        IDonjon_S donjon = partie.getDonjon();
        try
        {
            APersonnage_S personnage = donjon->trouver(coordonnees);
            if (m_equipe == partie.indiceEquipe(personnage))
            {
                m_personnage = personnage;
                return;
            }
        }
        catch (const runtime_error&)
        {
            // On a pas de personnage sur la case cliquée.
            try
            {
                // Deplacement Marche et fin du tour
                donjon->deplacer(*m_personnage, Deplacement::Marcher, coordonnees);
                partie.setEtat(IEtat_S(new FinTour(m_equipe)));
                partie.demander();
                return;
            }
            catch (const invalid_argument&)
            {
            }
            catch (const DeplacementErreur&)
            {
            }
        }
    }

    void PersoActif::operation(Partie& partie, size_t indiceObjet)
    {
        // Si le personnage possêde un objet à l'indice, on le sélectionne.
        if (indiceObjet < m_personnage->tailleSac())
        {
            IObjet_S objet = m_personnage->getObjet(indiceObjet);
            partie.setEtat(IEtat_S(new ObjetActif(m_equipe, m_personnage, objet)));
        }
    }

    void PersoActif::operation(Partie&) { throw logic_error("PersoActif::operation() : operation non supporte"); }

    string PersoActif::enTexte() const
    {
        stringstream ss;
        ss << "<Etat PersoActif>" << endl;
        ss << "equipe : " << m_equipe << endl;
        return ss.str();
    }

    IObjet_S PersoActif::getObjetSelect()
    {
        throw logic_error("SelectionMan::getObjetSelect() : Aucun objet selectionne.");
    }

    IObjet_SC PersoActif::getObjetSelect() const
    {
        throw logic_error("SelectionMan::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
