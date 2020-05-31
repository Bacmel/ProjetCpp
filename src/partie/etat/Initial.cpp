#include "partie/etat/Initial.hpp"
#include "partie/Partie.hpp"
#include "partie/etat/PersoActif.hpp"
#include <exception>


using namespace partie;
using namespace per;
using namespace std;

namespace partie::etat
{
    Initial::Initial(size_t indice) { m_indiceEquipe = indice; }

    void Initial::operation(Partie& partie, hex::Coordonnees coordonnees)
    {
        try
        {
            APersonnage_S personnage = partie.getDonjon()->trouver(coordonnees);
            if(m_indiceEquipe == partie.indiceEquipe(personnage))
            {
                partie.setEtat(IEtat_S(new PersoActif(m_indiceEquipe, personnage)));
            }
        }
        catch (runtime_error e)
        {
        }
    }

    void Initial::operation(Partie& partie, obj::IObjet_S objet) { return; }

} // namespace partie::etat