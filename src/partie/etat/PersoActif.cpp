#include "partie/etat/PersoActif.hpp"
#include <exception>
#include "donjon/IDonjon.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/FinTour.hpp"

using namespace partie;
using namespace per;
using namespace donjon;
using namespace std;

namespace partie::etat
{
    PersoActif::PersoActif(size_t indice, APersonnage_S PersoActif) : m_indiceEquipe(indice), m_personnage(PersoActif)
    {
    }

    void PersoActif::operation(Partie& partie, const hex::Coordonnees& coordonnees)
    {
        IDonjon_S donjon = partie.getDonjon();
        try
        {
            APersonnage_S personnage = donjon->trouver(coordonnees);
            /* Autre personnage de l'equipe. */
            if (personnage != m_personnage && m_indiceEquipe == partie.indiceEquipe(personnage))
            { partie.setEtat(IEtat_S(new PersoActif(m_indiceEquipe, personnage))); }
        }
        catch (const runtime_error&)
        {
            try
            {
                donjon->deplace(*m_personnage, Deplacement::Marcher, coordonnees);
                partie.setEtat(IEtat_S(new FinTour(m_indiceEquipe)));
            }
            catch (const runtime_error&)
            {
            }
        }
    }

    void PersoActif::operation(Partie& partie, obj::IObjet_S objet) { return; }

} // namespace partie::etat