#include "donjon/Donjon.hpp"
#include <algorithm>
#include "err/SansObjetErreur.hpp"
using namespace hex;
using namespace per;
using namespace obj;
using namespace donjon::cases;
using namespace std;
using namespace err;

namespace donjon
{
    Donjon::Donjon(const hex::ICarte_S<ICase_S>& carte) : m_personnages(), m_carte(carte) {}

    void Donjon::invoquer(per::APersonnage_S personnage, const hex::Coordonnees& position)
    {
        if (personnage == nullptr) { return; }
        // Vérifie que le personnage n'est pas déjà présent.
        auto itrFin = m_personnages.end();
        size_t idNouveau = personnage->getId();
        auto itr =
            find_if(m_personnages.begin(), itrFin, [&](const APersonnage_S& p) { return p->getId() == idNouveau; });
        if (itr != itrFin) { throw invalid_argument("Donjon::invoquer : Ce personnage est déjà présent."); }
        // Vérifie que le personnage peut se trouver sur la case.
        deplace(*personnage, Deplacement::Forcer, position);
        // Insert le personnage.
        m_personnages.push_back(personnage);
    }

    void Donjon::deplace(per::APersonnage& personnage, per::Deplacement type, const hex::Coordonnees& position)
    {
        // Vérifie qu'une case existe à ces coordonnées.
        ICase_S iCase(nullptr);
        try
        {
            iCase = (*m_carte)(position);
        }
        catch (const std::out_of_range& ex)
        {
            throw std::invalid_argument("Donjon::deplace : Coordonnées invalides (pas de case)");
        }
        // Vérifie que la case est praticable.
        if (iCase == nullptr) { throw std::invalid_argument("Donjon::deplace : Case nulle"); }
        if (!iCase->estPraticable()) { throw std::invalid_argument("Donjon::deplace : Case non praticable"); }
        // Vérifie qu'aucun joueur ne soit à ces coordonnées.
        if (estOccupee(position))
        { throw std::invalid_argument("Donjon::deplace : Coordonnées invalides (déjà occupées)"); }
        // Met à jour la position du joueur et notifie la case.
        personnage.deplacer(type, position);
        iCase->enEntree(personnage);
    }

    void Donjon::pousse(const std::map<hex::Coordonnees, hex::Direction>& aoe, size_t distance)
    {
        for (const pair<Coordonnees, Direction>& pair : aoe)
        {
            Coordonnees position = pair.first;
            Direction direction = pair.second;
            APersonnage_S personnage(nullptr);
            try
            {
                personnage = trouver(position);
            }
            catch (const runtime_error& exception)
            {
                // Pas de personnage sur cette case.
                continue;
            }
            pousse(personnage, direction, distance);
        }
    }

    void Donjon::degat(const std::map<hex::Coordonnees, size_t>& aoe)
    {
        for (const std::pair<Coordonnees, size_t>& pair : aoe)
        {
            Coordonnees position = pair.first;
            size_t dommages = pair.second;
            for (const APersonnage_S& personnage : m_personnages)
            {
                Coordonnees perPos = personnage->getPosition();
                if (position == perPos) { personnage->subitAttaque(dommages); }
            }
        }
    }

    void Donjon::deposer(obj::IObjet_S objet, const hex::Coordonnees& position)
    {
        // Obtient la case (en s'assurant qu'elle existe) et y met l'objet (s'il
        // n'est pas null).
        if (objet == nullptr) { return; }
        ICase_S iCase(nullptr);
        try
        {
            iCase = (*m_carte)(position);
        }
        catch (const std::out_of_range& exception)
        {
            throw std::invalid_argument("Donjon::deposer : Case inaccessible");
        }
        if (iCase != nullptr) { iCase->deposer(objet); }
    }

    obj::IObjet_S Donjon::ramasser(const hex::Coordonnees& position)
    {
        // Obtient la case en s'assurant qu'elle existe.
        ICase_S iCase(nullptr);
        try
        {
            iCase = (*m_carte)(position);
        }
        catch (const std::out_of_range& exception)
        {
            throw std::invalid_argument("Donjon::ramasser : Case inaccessible");
        }
        if (iCase == nullptr) { throw std::runtime_error("Donjon::ramasser : Pointeur null pour la case"); }
        // Récupère l'objet et le renvoie.
        IObjet_S objet = iCase->ramasser();
        return objet;
    }

    vector<Coordonnees> Donjon::getCaseVide() const
    {
        vector<Coordonnees> casesVide;
        Coordonnees c;
        auto itr = m_carte->iterateur();
        while (itr->aSuite())
        {
            c = itr->suite();
            ICase_S iCase(nullptr);
            iCase = (*m_carte)(c);
            if (iCase->estPraticable() && !iCase->aObjet() && !estOccupee(c)) { casesVide.push_back(c); }
        }
        return casesVide;
    }

    size_t Donjon::getNbPersonnages() const { return m_personnages.size(); }

    APersonnage_SC Donjon::getPersonnage(size_t indice) const
    {
        APersonnage_SC personnage = m_personnages.at(indice);
        return personnage;
    }

    APersonnage_S Donjon::getPersonnage(size_t indice)
    {
        APersonnage_S personnage = m_personnages.at(indice);
        return personnage;
    }

    APersonnage_SC Donjon::getPersonnageParId(size_t id) const
    {
        auto itrFin = m_personnages.end();
        auto itr = find_if(m_personnages.begin(), itrFin, [&](const APersonnage_S& e) { return e->getId() == id; });
        if (itr == itrFin) { throw runtime_error("Donjon::getPersonnageParId : Pas de personnage avec l'id donnée."); }
        APersonnage_SC personnage = *itr;
        return personnage;
    }

    APersonnage_S Donjon::getPersonnageParId(size_t id)
    {
        auto itrFin = m_personnages.end();
        auto itr = find_if(m_personnages.begin(), itrFin, [&](const APersonnage_S& e) { return e->getId() == id; });
        if (itr == itrFin) { throw runtime_error("Donjon::getPersonnageParId : Pas de personnage avec l'id donnée."); }
        APersonnage_S personnage = *itr;
        return personnage;
    }

    APersonnage_S Donjon::trouver(const Coordonnees& position) const
    {
        for (APersonnage_S personnage : m_personnages)
        {
            // Verifie que le pointeur ne soit pas null (dans ce cas, on regarde
            // le suivant) et test la position.
            if (personnage == nullptr) { continue; }
            Coordonnees coordonnees = personnage->getPosition();
            if (coordonnees == position) { return personnage; }
        }
        // On a pas trouvé de personnage -> On lève une exception.
        throw std::runtime_error("Donjon::trouver : Pas de personnage à cette position");
    }

    bool Donjon::estOccupee(const Coordonnees& position) const
    {
        try
        {
            trouver(position);
        }
        catch (const std::runtime_error& e)
        {
            return false;
        }
        return true;
    }

    void Donjon::pousse(const APersonnage_S& personnage, hex::Direction direction, size_t distance)
    {
        Coordonnees perPos = personnage->getPosition();
        bool estArrete = false;
        for (size_t deplacement = 1; deplacement <= distance && !estArrete; deplacement++)
        {
            Coordonnees cible = perPos.translate(direction, deplacement);
            ICase_S iCase(nullptr);
            try
            {
                iCase = (*m_carte)(cible);
            }
            catch (const out_of_range& exception)
            {
                // On est sortie de la carte. On ne quitte pas la case
                // précédante.
                personnage->subitAttaque(1);
                break;
            }
            if (!iCase->estTransparent())
            {
                // Le personnage se heurte à un obstacle. On ne quitte pas
                // la case précédante.
                personnage->subitAttaque(1);
                break;
            }
            else if (!iCase->estPraticable())
            {
                // Le personnage "tombe" sur cette case.
                estArrete = true;
            }
            else if (estOccupee(cible))
            {
                // Un personnage se trouve déjà sur cette case. On ne quitte
                // pas la case précédante.
                break;
            }
            // On déplace le personnage vers la nouvelle case.
            personnage->deplacer(Deplacement::Forcer, cible);
            iCase->enEntree(*personnage);
        }
    }

    void Donjon::actualiser()
    {
        for (auto itr = m_personnages.begin(); itr != m_personnages.end(); itr++)
        {
            if (!(*itr)->estVivant())
            {
                itr = m_personnages.erase(itr);
                itr--;
            }
        }
    }
} // namespace donjon
