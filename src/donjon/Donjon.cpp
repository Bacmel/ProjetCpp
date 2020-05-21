#include "donjon/Donjon.hpp"
#include <algorithm>
#include "donjon/SansObjetError.hpp"

using namespace hex;
using namespace per;
using namespace obj;
using namespace donjon::cases;

namespace donjon
{
    Donjon::Donjon(const hex::ICarte_S<ICase_S>& carte) : m_personnages(), m_carte(carte) {}

    Donjon::~Donjon() {}

    void Donjon::invoquer(per::APersonnage_S personnage, const hex::Coordonnees& position)
    {
        if (personnage == nullptr) { return; }
        deplace(*personnage, position);
        m_personnages.push_back(personnage);
    }

    void Donjon::deplace(const hex::Coordonnees& position)
    {
        APersonnage_S personnage = *m_personnageActif;
        deplace(*personnage, position);
        finirTour();
    }

    void Donjon::deplace(per::APersonnage& personnage, const hex::Coordonnees& position)
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
        if (iCase == nullptr) { throw std::runtime_error("Donjon::deplace : Case nulle"); }
        if (!iCase->estPraticable()) { throw std::runtime_error("Donjon::deplace : Case non praticable"); }
        // Vérifie qu'aucun joueur ne soit à ces coordonnées.
        for (const APersonnage_S& perPresent : m_personnages)
        {
            if (perPresent->getPosition() == position)
            { throw std::invalid_argument("Donjon::deplace : Coordonnées invalides (déjà occupées)"); }
        }
        // Met à jour la position du joueur et notifie la case.
        personnage.setPosition(position);
        iCase->enEntree(personnage);
    }

    void Donjon::degat(const hex::Coordonnees& centre, const hex::ICarte<bool>& zone, size_t degats)
    {
        IIterator_S<Coordonnees> iterateur = zone.iterateur();
        for (Coordonnees pos; iterateur->aSuite(); pos = centre + iterateur->suite())
        {
            // Itération sur les positions dans le donjon
            for (APersonnage_S personnage : m_personnages)
            {
                // Vérifie si un personnage se trouve sur une case de l'AOE
                Coordonnees personnagePos = personnage->getPosition();
                if (pos == personnagePos) { personnage->subitAttaque(degats); }
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

    void Donjon::finirTour()
    {
        // Recherche le personnage vivant suivant.
        size_t i;
        for (i = 0; i < m_personnages.size(); i++)
        {
            // Sélectionne le prochain personnage actif en prennant le suivant
            // dans la liste des personnages. Si on est à la fin de la liste, on
            // reprend depuis le début.
            if (m_personnageActif == m_personnages.end()) { m_personnageActif = m_personnages.begin(); }
            else
            {
                m_personnageActif++;
            }
            // Si le personnage est vivant, on le garde et on arrête la recherche.
            if ((*m_personnageActif)->estVivant()) { break; }
        }
        // S'il n'y a plus de personnage en vie, on lève une exception.
        if (i == m_personnages.size()) { throw std::runtime_error("Donjon::finirTour : Plus de personnage en vie"); }
    }
} // namespace donjon
