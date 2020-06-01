#include "partie/etat/FinTour.hpp"
#include <iostream>
#include "donjon/cases/ICase.hpp"
#include "hex/Coordonnees.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/Initial.hpp"

using namespace partie;
using namespace per;
using namespace donjon::cases;
using namespace hex;
using namespace obj;
using namespace std;

namespace partie::etat
{
    FinTour::FinTour(size_t indice) : m_indiceEquipe(indice) {}

    void FinTour::operation(Partie& partie, const Coordonnees& coordonnees) { operation(partie); }

    void FinTour::operation(Partie& partie, IObjet_S objet) { operation(partie); }

    void FinTour::operation(Partie& partie)
    {
        ICarte_SC<ICase_S> carte = partie.getDonjon()->getCarte();
        /*Mise à jour objet. */
        auto itro = carte->iterateur();
        while (itro->aSuite())
        {
            Coordonnees c = itro->suite();
            (*carte)(c)->actualiser();
        }
        /*Mise à jour membre de l'equipe. */
        set<size_t> equipe = partie.getEquipes().at(m_indiceEquipe);
        for (auto id : equipe)
        {
            partie.getDonjon()->getPersonnageParId(id)->actualiser();
        }
        size_t nbEquipe = partie.getEquipes().size();
        partie.setEtat(IEtat_S(new Initial((m_indiceEquipe+1)%nbEquipe)));
        return;
    }

    void FinTour::afficher() const { cout << " Etat Fin de Tour : " << m_indiceEquipe << endl; }

} // namespace partie::etat