#include "partie/etat/FinTour.hpp"
#include <iostream>
#include <sstream>
#include "donjon/IDonjon.hpp"
#include "donjon/cases/ACase.hpp"
#include "err/InfoErreur.hpp"
#include "hex/Coordonnees.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/FinPartie.hpp"
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
    FinTour::FinTour(size_t indice) : m_equipe(indice) {}

    void FinTour::operation(Partie&, const Coordonnees&)
    {
        throw logic_error("FinTour::operation : operation non supporte");
    }

    void FinTour::operation(Partie&, size_t) { throw logic_error("FinTour::operation : operation non supporte"); }

    void FinTour::operation(Partie& partie)
    {
        IDonjon_S donjon = partie.getDonjon();
        ICarte_S<ACase_S> carte = partie.getDonjon()->getCarte();
        /*Mise à jour objet. */
        auto itro = carte->iterateur();
        while (itro->aSuite())
        {
            Coordonnees c = itro->suite();
            (*carte)(c)->actualiser();
        }
        /* Mise à jour membre de l'equipe. */
        vector<Equipe>& equipes = partie.getEquipes();
        Equipe& equipe = equipes.at(m_equipe);
        for (size_t indice = 0; indice < equipe.compterMembres(); indice++)
        {
            try
            {
                APersonnage_S p = equipe.getMembre(indice);
                donjon->degat(p->getZoneEffet());
                p->actualiser();
            }
            catch (const out_of_range&)
            {
            }
        }
        equipe.retirerMorts();
        donjon->actualiser();
        // On regarde si on a un gagnant.
        try
        {
            size_t i = partie.indiceGagnant();
            partie.setEtat(IEtat_S(new FinPartie(i)));
            partie.demander();
            return;
        }
        catch (const err::InfoErreur&)
        {
            // On en a pas, la partie continue.
            size_t nbEquipe = partie.getEquipes().size();
            partie.setEtat(IEtat_S(new SelectionAuto((m_equipe + 1) % nbEquipe)));
            partie.demander();
            return;
        }
    }

    string FinTour::enTexte() const
    {
        stringstream ss;
        ss << "<Etat FinTour>" << endl;
        ss << "equipe : " << m_equipe << endl;
        return ss.str();
    }

    APersonnage_S FinTour::getPersoSelect()
    {
        throw logic_error("FinTour::getPersoSelect : Aucun personnage selectionne.");
    }

    APersonnage_SC FinTour::getPersoSelect() const
    {
        throw logic_error("FinTour::getPersoSelect : Aucun personnage selectionne.");
    }

    IObjet_S FinTour::getObjetSelect()
    {
        throw logic_error("FinTour::getObjetSelect : Aucun objet selectionne.");
    }

    IObjet_SC FinTour::getObjetSelect() const
    {
        throw logic_error("FinTour::getObjetSelect : Aucun objet selectionne.");
    }

} // namespace partie::etat
