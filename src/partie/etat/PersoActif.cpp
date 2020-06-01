#include "partie/etat/PersoActif.hpp"
#include <exception>
#include <iostream>
#include "donjon/IDonjon.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/FinTour.hpp"
#include "partie/etat/Initial.hpp"

using namespace partie;
using namespace per;
using namespace obj;
using namespace donjon;
using namespace std;

namespace partie::etat
{
    PersoActif::PersoActif(size_t indice, APersonnage_S PersoActif) : m_indiceEquipe(indice), m_personnage(PersoActif)
    {
    }

    void PersoActif::operation(Partie& partie, const hex::Coordonnees& coordonnees)
    {
        /* Annulation second clic. */
        if (m_personnage->getPosition() == coordonnees)
        {
            partie.setEtat(IEtat_S(new Initial(m_indiceEquipe)));
            return;
        }

        IDonjon_S donjon = partie.getDonjon();
        try
        {
            APersonnage_S personnage = donjon->trouver(coordonnees);
            /* Selection autre personnage de l'equipe. */
            if (m_indiceEquipe == partie.indiceEquipe(personnage))
            {
                m_personnage = personnage;
                return;
            }
        }
        catch (const runtime_error&)
        {
            try
            {
                /* Deplacement Marche. */
                donjon->deplace(*m_personnage, Deplacement::Marcher, coordonnees);
                partie.setEtat(IEtat_S(new FinTour(m_indiceEquipe)));
                partie.demande(coordonnees);
                return;
            }
            catch (...)
            {
                /* Annulation clic random. */
                partie.setEtat(IEtat_S(new Initial(m_indiceEquipe)));
                return;
            }
        }
    }

    void PersoActif::operation(Partie& partie, size_t objet) { return; }

    void PersoActif::afficher() const
    {
        cout << " Etat Personnage Actif : " << m_indiceEquipe << endl << "id : " << m_personnage->getId() << endl;
    }

    IObjet_SC PersoActif::getObjetSelect() const
    {
        throw invalid_argument("Initial::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
