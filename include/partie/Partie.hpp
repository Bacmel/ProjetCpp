#ifndef __PARTIE_HPP__
#define __PARTIE_HPP__

#include <set>
#include <vector>
#include "donjon/IDonjon.hpp"
#include "donjon/PersonnageComparateur.hpp"
#include "donjon/cases/ICase.hpp"
#include "hex/ICarte.hpp"
#include "per/APersonnage.hpp"

namespace partie
{
    class Partie
    {
    protected:
        /* Liste des equipes. */
        std::vector<std::set<size_t>> m_equipes;
        /* Liste des personnages. */
        std::vector<per::APersonnage_S> m_personnages;
        /* Carte du terrain. */
        hex::ICarte_S<donjon::cases::ICase_S> m_carte;
        /* Liste des objets abandonnes. */
        std::vector<obj::IObjet_S> m_objets;
        /* Arbitre de la partie. */
        donjon::IDonjon_S m_donjon;
        /* Autre a venir */

    public:
        Partie(size_t joueurs);

        /* Méthodes get. */

        /**
         * @brief Obtient la liste des equipes.
         *
         * @return std::vector<std::set<size_t> > La liste des equipes.
         */
        inline std::vector<std::set<size_t>> getEquipes() const { return m_equipes; }

        /**
         * @brief Obtient la liste des personnages.
         *
         * @return std::set<per::APersonnage_S, donjon::PersonnageComparateur> La liste des personnages.
         */
        inline std::vector<per::APersonnage_S> getPersonnages() const
        {
            return m_personnages;
        }

        /**
         * @brief Obtient la carte du donjon.
         *
         * @return hex::ICarte_S<donjon::cases::ICase_S> La carte du donjon.
         */
        inline hex::ICarte_S<donjon::cases::ICase_S> getCarte() const { return m_carte; }

        /**
         * @brief Obtient la liste des objets abandonnes.
         *
         * @return   std::vector<obj::IObjet_S> La liste des objets.
         */
        inline std::vector<obj::IObjet_S> getObjets() const { return m_objets; }

        /**
         * @brief Obtient le donjon.
         *
         * @return donjon::IDonjon_S m_donjon; Le donjon.
         */
        inline donjon::IDonjon_S getDonjon() const { return m_donjon; }

        /* Méthodes pour generer le jeu. */

        /**
         * @brief Genere une equipe.
         *
         * @throw err::CreationErreur
         */
        void genererEquipe();

        /**
         * @brief Genere un personnage.
         * 
         * @param indice l'indice de l'equipe.
         * @throw err::CreationErreur
         */
        void genererPersonnage(size_t indice);

        /**
         * @brief Genere une carte.
         *
         * @throw err::CreationErreur
         */
        void genererCarte();

        /**
         * @brief Genere un objet abandonner.
         *
         * @throw err::CreationErreur
         */
        void genererObjet();

        /**
         * @brief Initialise le donjon.
         *
         * @throw err::CreationErreur
         */
        void initialiserDonjon();

        /* Methodes pour gerer le jeu. */

        /**
         * @brief Gere une equipe.
         *
         * @param indice de l'equipe.
         * @throw std::out_of_range si l'équipe n'existe pas.
         */
        void gererEquipe(size_t indice);

        /**
         * @brief Gere un personnage.
         *
         * @param indice du joueur.
         * @throw std::out_of_range si le personnage n'existe pas.
         */
        void gererPersonnage(size_t indice);

        /**
         * @brief Gere un objet abandonnes.
         *
         * @param indice de l'objet.
         * @throw std::out_of_range si l'objet n'existe pas.
         */
        void gererObjet(size_t indice);

        /* Méthodes autres. */

        /**
         * @brief Indique le gagnant de la partie.
         *
         * @return L'indice de l'équipe gagnante. -1 en cas d'egalite.
         * @throw err::InfoErreur Si l'info n'est pas disponible.
         */
        int indiceGagnant();

        /**
         * @brief Indique l'equipe du personnage.
         * 
         * @param personnage le personnage.
         * @return l'indice de son équipe.
         * @throw err::InfoErreur Si l'info n'est pas disponible.
         */
        size_t indiceEquipe(APersonnage_S personnage);

        /**
         * @brief Indique l'indice du personnage dans le vector.
         * 
         * @param id l'identifiant du personnage.
         * @return l'indice dans le vector.
         * @throw err::InfoErreur Si l'info n'est pas disponible.
         */
        size_t indicePersonnage(size_t id);
    };
} // namespace partie

#endif //__PARTIE_HPP__