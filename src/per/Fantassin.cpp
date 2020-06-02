#include "per/Fantassin.hpp"
#include "err/DeplacementErreur.hpp"
#include "hex/Coordonnees.hpp"
#include "per/IPersonnageVisiteur.hpp"

namespace per
{
    Fantassin::Fantassin() : APersonnage(1, hex::Coordonnees()) {}

    void Fantassin::deplacer(Deplacement deplacement, hex::Coordonnees cible)
    {
        switch (deplacement)
        {
        case Deplacement::Forcer:
            m_position = cible;
            break;
        case Deplacement::Marcher:
            if (m_position.distance(cible) != 1)
            { throw err::DeplacementErreur("Fantassin::deplacer : Hors de porter de marche"); }
            else
            {
                m_position = cible;
                notifier(*this);
            }
            break;
        default:
            throw err::DeplacementErreur("Fantassin::deplacer : Deplacement non precise");
        }
    }

    void Fantassin::accepter(IPersonnageVisiteur& visiteur) const { visiteur.visiter(*this); }

    void Fantassin::actualiser() {}

} // namespace per