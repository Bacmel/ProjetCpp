#include "partie/etat/FinTour.hpp"
#include <iostream>
#include "donjon/IDonjon.hpp"
#include "donjon/cases/ICase.hpp"
#include "err/InfoErreur.hpp"
#include "hex/Coordonnees.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/FinPartie.hpp"
#include "partie/etat/Selection.hpp"

using namespace partie;
using namespace per;
using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace obj;
using namespace std;

namespace partie::etat
{
    FinTour::FinTour(size_t indice) : m_indiceEquipe(indice) {}

    void FinTour::operation(Partie&, const Coordonnees&) { throw logic_error("FinTour::operation() : operation non supporte"); }

    void FinTour::operation(Partie&, size_t) { throw logic_error("FinTour::operation() : operation non supporte"); }

    void FinTour::operation(Partie& partie)
    {
        IDonjon_S donjon = partie.getDonjon();
        ICarte_SC<ICase_S> carte = partie.getDonjon()->getCarte();
        /*Mise à jour objet. */
        auto itro = carte->iterateur();
        while (itro->aSuite())
        {
            Coordonnees c = itro->suite();
            (*carte)(c)->actualiser();
        }
        /*Mise à jour membre de l'equipe. */
        set<size_t>& equipe = partie.getEquipes().at(m_indiceEquipe);
        for (auto id : equipe)
        {
            try
            {
                APersonnage_S p = donjon->getPersonnageParId(id);
                donjon->degat(p->getZoneEffet());
                p->actualiser();
            }
            catch(const runtime_error&)
            {
                equipe.erase(id);
            }
        }
        donjon->actualiser();
        try
        {
            size_t i = partie.indiceGagnant();
            partie.setEtat(IEtat_S(new FinPartie(i)));
            partie.demande();
            return;
        }
        catch (const err::InfoErreur&)
        {
            size_t nbEquipe = partie.getEquipes().size();
            partie.setEtat(IEtat_S(new Selection((m_indiceEquipe + 1) % nbEquipe)));
            partie.demande();
            return;
        }
    }

    void FinTour::afficher() const { cout << " Etat Fin de Tour : " << m_indiceEquipe << endl; }

    APersonnage_SC FinTour::getPersoSelect() const
    {
        throw invalid_argument("FinTour::getPersoSelect() : Aucun personnage selectionne.");
    }

    IObjet_SC FinTour::getObjetSelect() const
    {
        throw invalid_argument("FinTour::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
