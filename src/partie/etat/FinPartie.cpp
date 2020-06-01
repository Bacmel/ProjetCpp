#include "partie/etat/FinPartie.hpp"
#include <iostream>
#include "donjon/cases/ICase.hpp"
#include "hex/Coordonnees.hpp"
#include "partie/Partie.hpp"
#include "donjon/IDonjon.hpp"
#include "partie/etat/Selection.hpp"
#include "err/InfoErreur.hpp"

using namespace partie;
using namespace per;
using namespace donjon;
using namespace donjon::cases;
using namespace hex;
using namespace obj;
using namespace std;

namespace partie::etat
{
    FinPartie::FinPartie(size_t indice) : m_indiceGagnant(indice) {}

    void FinPartie::operation(Partie& partie, const Coordonnees&) { operation(partie); }

    void FinPartie::operation(Partie& partie, size_t) { operation(partie); }

    void FinPartie::operation(Partie& partie)
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
        set<size_t> equipe = partie.getEquipes().at(m_indiceGagnant);
        for (auto id : equipe)
        {
            APersonnage_S p = donjon->getPersonnageParId(id);
            donjon->degat(p->getZoneEffet());
            p->actualiser();
        }
        donjon->actualiser();
        try
        {
            size_t i = partie.indiceGagnant();
            partie.setEtat(IEtat_S(new FinPartie(i)));
            partie.demande(Coordonnees());
            return;
        }
        catch(const err::InfoErreur&)
        {
            size_t nbEquipe = partie.getEquipes().size();
            partie.setEtat(IEtat_S(new Selection((m_indiceGagnant + 1) % nbEquipe)));
            partie.demande(Coordonnees());
            return;
        }
    }

    void FinPartie::afficher() const { cout << " Etat Fin de Tour : " << m_indiceGagnant << endl; }

    APersonnage_SC FinPartie::getPersoSelect() const
    {
        throw invalid_argument("FinPartie::getPersoSelect() : Aucun personnage selectionne.");
    }

    IObjet_SC FinPartie::getObjetSelect() const
    {
        throw invalid_argument("FinPartie::getObjetSelect() : Aucun objet selectionne.");
    }

} // namespace partie::etat
