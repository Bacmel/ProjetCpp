#ifndef __EQUIPE_H__
#define __EQUIPE_H__

#include <vector>
#include "partie/strat/IStrategie.hpp"
#include "per/APersonnage.hpp"

namespace partie
{
    class Partie;

    class Equipe
    {
    private:
        /** @brief La liste des membres de l'équipe. */
        std::vector<per::APersonnage_S> m_membres;
        /** @brief La stratégie adoptée par l'équipe. */
        strat::IStrategie_U m_strategie;

    public:
        /**
         * @brief Crée une équipe à partir de sa stratégie.
         *
         * @param strategie La stratégie adoptée par l'équipe.
         */
        explicit Equipe(strat::IStrategie_U& strategie);
        ~Equipe() = default;

        /**
         * @brief Ajoute un membre à l'équipe.
         *
         * NOTE: Si le membre est déjà présent, l'appel ne fait rien.
         *
         * @param personnage Le personnage à ajouter.
         * @throw std::invalid_argument Quand le personnage est nullptr.
         */
        void ajouterMembre(per::APersonnage_S personnage);

        /**
         * @brief Retire un membre à l'équipe.
         *
         * NOTE: Si le membre est déjà absent, l'appel ne fait rien.
         *
         * @param personnage Le personnage à retirer.
         */
        void retirerMembre(per::APersonnage_SC personnage);

        /**
         * @brief Indique si un personnage est membre de l'équipe.
         *
         * @param idPersonnage L'identifiant du personnage à tester.
         * @return true Si le personnage fait partie de l'équipe sinon false.
         */
        bool estMembre(size_t idPersonnage) const;

        /**
         * @brief Indique si un personnage est membre de l'équipe.
         *
         * @param personnage Le personnage à tester.
         * @return true Si le personnage fait partie de l'équipe sinon false.
         */
        bool estMembre(const per::APersonnage& personnage) const;

        /**
         * @brief Compte le nombre de membre encore en vie.
         *
         * @return Le nombre de membre encore en vie.
         */
        size_t compterSurvivant() const;

        /**
         * @brief Compte le nombre de membre dans l'équipe (vivant ou non).
         *
         * @return Le nombre de membre dans l'équipe.
         */
        size_t compterMembres() const;

        /**
         * @brief Donne le membre à l'indice demandé.
         *
         * @param indice L'indice du membre dans l'équipe.
         * @return Le membre à l'indice demandé.
         * @throw std::out_of_range Quand il n'y a pas de personnage correspondant.
         */
        per::APersonnage_SC getMembre(size_t indice) const;
        /**
         * @brief Donne le membre à l'indice demandé.
         *
         * @param indice L'indice du membre dans l'équipe.
         * @return Le membre à l'indice demandé.
         * @throw std::out_of_range Quand il n'y a pas de personnage correspondant.
         */
        per::APersonnage_S getMembre(size_t indice);

        /**
         * @brief Laisse l'équipe jouer son tour.
         *
         * @param partie La partie à laquelle l'équipe appartient.
         */
        void jouer(partie::Partie& partie);

        /**
         * @brief Retire les morts de l'équipe.
         */
        void retirerMorts();
    };
} // namespace partie
#endif // __EQUIPE_H__
