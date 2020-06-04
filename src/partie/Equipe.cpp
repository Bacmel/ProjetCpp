#include "partie/Equipe.hpp"
#include <algorithm>
#include <stdexcept>

namespace partie
{
    Equipe::Equipe(strat::IStrategie_U& strategie) : m_membres(), m_strategie(std::move(strategie)) {}

    void Equipe::ajouterMembre(per::APersonnage_S personnage)
    {
        if (personnage == nullptr) { throw std::invalid_argument("Equipe::ajouterMembre : Le membre est null."); }
        // Vérifie que le personnage n'est pas un membre de l'équipe.
        size_t idPersonnage = personnage->getId();
        auto itr = std::find_if(m_membres.begin(), m_membres.end(), [&](const per::APersonnage_S& membre) {
            return membre->getId() == idPersonnage;
        });
        // S'il est absent, on l'ajoute.
        if (itr != m_membres.end()) { m_membres.push_back(personnage); }
    }

    void Equipe::retirerMembre(per::APersonnage_SC personnage)
    {
        // Vérifie que le personnage est pas un membre de l'équipe.
        size_t idPersonnage = personnage->getId();
        auto itr = std::find_if(m_membres.begin(), m_membres.end(), [&](const per::APersonnage_S& membre) {
            return membre->getId() == idPersonnage;
        });
        // S'il est présent, on le supprime.
        if (itr != m_membres.end()) { m_membres.erase(itr); }
    }

    bool Equipe::estMembre(size_t idPersonnage) const
    {
        // On cherche un personnage avec le même identifiant.
        for (const per::APersonnage_S& personnage : m_membres)
        {
            if (personnage->getId() == idPersonnage) { return true; }
        }
        return false;
    }

    bool Equipe::estMembre(const per::APersonnage& personnage) const
    {
        // Utilise la fonction pour les entiers.
        size_t id = personnage.getId();
        return estMembre(id);
    }

    size_t Equipe::compterSurvivant() const
    {
        // Itère sur les personnages et incrémente le compteur s'ils sont vivant.
        size_t cptSurvivants(0);
        for (const per::APersonnage_S& personnage : m_membres)
        {
            if (personnage->estVivant()) { cptSurvivants++; }
        }
        return cptSurvivants;
    }

    per::APersonnage_SC Equipe::getMembre(size_t indice) const { return m_membres.at(indice); }

    per::APersonnage_S Equipe::getMembre(size_t indice) { return m_membres.at(indice); }

    void Equipe::jouer(partie::Partie& partie) { m_strategie->mettreEnOeuvre(partie, *this); }

    void Equipe::retirerMorts()
    {
        // Retire de l'équipe les personnages morts.
        std::remove_if(m_membres.begin(), m_membres.end(), [](per::APersonnage_S personnage) {
            return !personnage->estVivant();
        });
    }
} // namespace partie
