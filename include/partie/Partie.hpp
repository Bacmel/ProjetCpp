#ifndef __PARTIE_HPP__
#define __PARTIE_HPP__

#include <vector>
#include "donjon/IDonjon.hpp"
#include "partie/Equipe.hpp"
#include "partie/etat/IEtat.hpp"
#include "partie/strat/IStrategie.hpp"
#include "per/APersonnage.hpp"

namespace partie
{
    class Partie
    {
    private:
        /** @brief Liste des equipes. */
        std::vector<Equipe> m_equipes;
        /** @brief Arbitre de la partie. */
        donjon::IDonjon_S m_donjon;
        /** @brief Etat courant. */
        etat::IEtat_S m_etat;
        /** @brief Etat précédent. */
        etat::IEtat_S m_etatP;

    public:
        /**
         * @brief Construit une partie à partir de la stratégie pour la première équipe.
         *
         * @param strategie La stratégie pour la première équipe (indice 0).
         */
        Partie(strat::IStrategie_S& strategie);

        /**
         * @brief Obtient l'équipe par son indice.
         *
         * @param indice L'indice de l'équipe.
         * @return La partie à l'indice donnée.
         *
         * @throw std::out_of_range Quand il n'y a pas d'équipe à cet indice.
         */
        Equipe& getEquipe(size_t indice);

        /**
         * @brief Obtient l'équipe par son indice.
         *
         * @param indice L'indice de l'équipe.
         * @return La partie à l'indice donnée.
         *
         * @throw std::out_of_range Quand il n'y a pas d'équipe à cet indice.
         */
        const Equipe& getEquipe(size_t indice) const;

        /**
         * @brief Obtient la liste des equipes.
         *
         * @return std::vector<Equipe> La liste des equipes.
         */
        inline std::vector<Equipe>& getEquipes() { return m_equipes; }

        /**
         * @brief Obtient le donjon.
         *
         * @return donjon::IDonjon_S m_donjon; Le donjon.
         */
        inline donjon::IDonjon_S getDonjon() { return m_donjon; }

        /**
         * @brief Obtient le donjon.
         *
         * @return donjon::IDonjon_SC m_donjon Le donjon.
         */
        inline donjon::IDonjon_SC getDonjon() const { return m_donjon; }

        /**
         * @brief Obtient l'état courant.
         *
         * @return partie::etat::IEtat_SC; l'etat courant.
         */
        inline etat::IEtat_SC getEtat() const { return m_etat; }

        /**
         * @brief Obtient l'etat précédent.
         *
         * @return partie::etat::IEtat_SC; l'etat precedent.
         */
        inline etat::IEtat_SC getEtatPre() const { return m_etatP; }

        /**
         * @brief Obtient l'equipe courante.
         *
         * @return size_t l'equipe courante.
         */
        inline size_t getEquipeCourante() const { return m_etat->getEquipeCourante(); }

        /**
         * @brief Obtient le personnage selectionne.
         *
         * @throw std::invalide_argument ne possede pas d'information.
         * @return per::APersonnage_SC le personnage selestionne.
         */
        inline per::APersonnage_SC getPersoSelect() const { return m_etat->getPersoSelect(); }

        /**
         * @brief Obtient l'objet selectionne.

         * @throw std::invalide_argument ne possede pas d'information.
         * @return obj::IObjet_SC l'objet selectionne.
         */
        inline obj::IObjet_SC getObjetSelect() const { return m_etat->getObjetSelect(); }

        /**
         * @brief Change l'etat courant.
         *
         * NOTE: Cette méthode ne doit être appelée qu'une seule fois par un
         * état. Autrement, il sera détruit.
         *
         * @param etat::IEtat_S le nouvel etat courant.
         */
        void setEtat(etat::IEtat_S etat);

        /**
         * @brief Crée une équipe et donne son indice.
         *
         * @param strategie La stratégie pour l'équipe.
         * @return L'indice de l'équipe crée.
         */
        size_t genererEquipe(strat::IStrategie_S& strategie);

        /**
         * @brief Genere un personnage dans une equipe.
         *
         * @param personnage le personnage.
         * @param indice l'indice de l'equipe.
         * @throw err::CreationErreur Quand la creation n'est pas possible.
         */
        void genererPersonnage(per::APersonnage_S personnage, size_t indice);

        /**
         * @brief Genere un objet abandonner.
         *
         * @param objet l'objet.
         * @throw err::CreationErreur
         */
        void genererObjet(obj::IObjet_S objet);

        /**
         * @brief Demande
         *
         * @param coordonnees les coordonnees selectionnees.
         */
        void demander(hex::Coordonnees coordonnees);

        /**
         * @brief Demande
         *
         * @param indiceObjet l'objet selectionne.
         */
        void demander(size_t indiceObjet);

        /**
         * @brief Demande
         */
        void demander();

        /* Méthodes autres. */

        /**
         * @brief Indique le gagnant de la partie.
         *
         * @return L'indice de l'équipe gagnante. -1 en cas d'egalite.
         * @throw err::InfoErreur Si l'info n'est pas disponible.
         */
        int indiceGagnant() const;

        /**
         * @brief Indique l'equipe du personnage.
         *
         * @param personnage le personnage.
         * @return l'indice de son équipe.
         * @throw err::InfoErreur Si l'info n'est pas disponible.
         */
        size_t indiceEquipe(per::APersonnage_SC personnage) const;

        /**
         * @brief Indique l'indice du personnage dans le vector.
         *
         * @param id l'identifiant du personnage.
         * @return l'indice dans le vector.
         * @throw err::InfoErreur Si l'info n'est pas disponible.
         */
        size_t indicePersonnage(size_t id);

        /**
         * @brief Obtient une coordonnees disponible.
         *
         * @throw err:CreationErreur Quand la carte n'a plus de place.
         */
        hex::Coordonnees coordonneesLibre();

    private:
        /**
         * @brief Genere une carte.
         *
         * @throw err::CreationErreur
         */
        void genererCarte();
    };
} // namespace partie

#endif //__PARTIE_HPP__
