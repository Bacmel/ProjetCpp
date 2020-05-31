#include "partie/etat/FinTour.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/Initial.hpp"
#include "donjon/cases/ICase.hpp"
#include "hex/Coordonnees.hpp"

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
        auto itre = partie.getEquipes().at(m_indiceEquipe).begin();
        for(itre; itre != partie.getEquipes().at(m_indiceEquipe).end(); itre++)
        {
            partie.getDonjon()->getPersonnageParId(*itre)->actualiser();
        }
        partie.setEtat(IEtat_S(new Initial(m_indiceEquipe)));
    }
} // namespace partie::etat