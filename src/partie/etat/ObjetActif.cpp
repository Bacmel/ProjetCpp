#include "partie/etat/ObjetActif.hpp"
#include <iostream>
#include <stdexcept>
#include "partie/Partie.hpp"
#include "partie/etat/FinTour.hpp"
#include "partie/etat/PersoActif.hpp"

using namespace donjon;
using namespace hex;
using namespace obj;
using namespace std;

namespace partie::etat
{
    ObjetActif::ObjetActif(size_t equipe, per::APersonnage_S personnage, obj::IObjet_S objet) :
        m_equipe(equipe),
        m_personnage(personnage),
        m_objet(objet)
    {
    }

    ObjetActif::~ObjetActif() {}

    void ObjetActif::afficher() const
    {
        std::cout << "ObjetActif{"
                  << "m_equipe : " << m_equipe << ", m_personnage : " << m_personnage << ", m_objet : " << m_objet
                  << "}\n";
    }

    void ObjetActif::operation(Partie& partie, const hex::Coordonnees& coordonnees)
    {
        IDonjon_S donjon = partie.getDonjon();
        Coordonnees origine = m_personnage->getPosition();

        try
        {
            m_objet->utiliser(*donjon, origine, coordonnees);
            // Passe en fin de tour et actualise la MAE.
            partie.setEtat(std::make_shared<FinTour>(m_equipe));
            partie.demande();
        }
        catch (...)
        {
            // Ne rien faire.
        }
    }

    void ObjetActif::operation(Partie& partie, size_t indiceObjet)
    {
        if (indiceObjet < m_personnage->tailleSac())
        {
            IObjet_S objet = m_personnage->getObjet(indiceObjet);
            if (objet == m_objet)
            {
                // On a resélectionné l'objet. On va le dessélectionner.
                partie.setEtat(std::make_shared<PersoActif>(m_equipe, m_personnage));
            }
            else
            {
                // On a changé d'objet sélectionné.
                m_objet = objet;
            }
        }
        else
        {
            throw std::logic_error("ObjetActif::operation : L'indice est hors du sac.");
        }
    }

    void ObjetActif::operation(Partie&) { throw logic_error("ObjetActif::operation() : operation non supporte"); }

} // namespace partie::etat
