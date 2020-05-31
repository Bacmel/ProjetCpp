#ifndef __PARTIE_HPP__
#define __PARTIE_HPP__

#include <vector>
#include <set>
#include "partie/IEtat.hpp"
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
        /* Arbitre de la partie. */
        donjon::IDonjon_S m_donjon;
        /* Etat courant */
        IEtat_S etat;

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
         * @brief Obtient le donjon.
         *
         * @return donjon::IDonjon_S m_donjon; Le donjon.
         */
        inline donjon::IDonjon_S getDonjon() { return m_donjon; }

        /**
         * @brief Obtient le donjon.
         *
         * @return donjon::IDonjon_SC m_donjon; Le donjon.
         */
        inline donjon::IDonjon_SC getDonjon() const { return m_donjon; }

        /* Méthodes pour generer le jeu. */
        /**
         * @brief Genere une carte.
         *
         * @throw err::CreationErreur
         */
        void genererCarte();

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

        /* Methodes pour gerer le jeu. */

        /**
         * @brief Demande
         *
         * @param coordonnees les coordonnees selectionnees.
         * @param objet l'objet selectionne.
         */
        void demande(hex::Coordonnees coordonnees, obj::IObjet_S objet);

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
    };
} // namespace partie

#endif //__PARTIE_HPP__
