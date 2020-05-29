#ifndef CARTE_HEXAGONE_HPP
#define CARTE_HEXAGONE_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "hex/ICarte.hpp"
#include "hex/IterateurCarteHexagone.hpp"

namespace hex
{

    template <typename T>
    class CarteHexagone : public ICarte<T>
    {
    protected:
        /** Nombre de cases entre la case centrale et le bord */
        size_t m_rayon;
        T** m_plateau;

    public:
        /**
         * @brief Construit une nouvelle carte hexagonale.
         *
         * Le rayon ne tient pas compte de la case centrale. Un masque de rayon
         * 0 est de diamètre 1. Un masque de rayon 2 est de diamètre 5.
         *
         * @param rayon Le rayon de l'hexagone (ne compte pas le centre).
         */
        explicit CarteHexagone(size_t rayon) : m_rayon(rayon), m_plateau(nullptr)
        {
            // Crée le plateau puis chaque ligne de longueur croissante et décroissante.
            size_t diametre = 2 * m_rayon + 1;
            m_plateau = new T*[diametre]();
            for (size_t i = 1; i <= m_rayon; i++)
            {
                size_t longueur = diametre - i;
                m_plateau[m_rayon + i] = new T[longueur]();
                m_plateau[m_rayon - i] = new T[longueur]();
            }
            // Crée la ligne centrale.
            m_plateau[m_rayon] = new T[diametre]();
        }

        /*====== Constructeurs & opérateurs de copie & destructeur ======*/
        CarteHexagone(const CarteHexagone& autre) : m_rayon(0), m_plateau(nullptr) { *this = autre; }

        CarteHexagone(CarteHexagone&& autre) : m_rayon(0), m_plateau(nullptr) { *this = autre; }

        CarteHexagone& operator=(const CarteHexagone& autre)
        {
            deletePlateau();
            // Copie les valeurs depuis autre vers l'instance.
            m_rayon = autre.m_rayon;
            size_t diametre = 2 * m_rayon + 1;
            m_plateau = new T*[diametre];
            // Copie les lignes de taille croissante et décroissante.
            for (size_t i = 1; i <= m_rayon; i++)
            {
                size_t longueur = diametre - i;
                m_plateau[m_rayon + i] = new T[longueur];
                T* source = autre.m_plateau[m_rayon + i];
                T* destination = m_plateau[m_rayon + i];
                std::copy(source, source + longueur, destination);

                m_plateau[m_rayon - i] = new T[longueur];
                source = autre.m_plateau[m_rayon - i];
                destination = m_plateau[m_rayon - i];
                std::copy(source, source + longueur, destination);
            }
            // Copie la ligne centrale.
            m_plateau[m_rayon] = new T[diametre];
            T* source = autre.m_plateau[m_rayon];
            std::copy(source, source + diametre, m_plateau[m_rayon]);

            return *this;
        }

        CarteHexagone& operator=(CarteHexagone&& autre)
        {
            deletePlateau();
            // Mets le pointeur d'autre à la place de celui de l'instance et met
            // à nullptr celui d'autre. Similaire pour les rayons.
            m_plateau = autre.m_plateau;
            autre.m_plateau = nullptr;
            m_rayon = autre.m_rayon;
            autre.m_rayon = 0;
            return *this;
        }

        virtual ~CarteHexagone() { deletePlateau(); }

        /*====== Méthodes ======*/

        /**
         * @brief Obtient le rayon.
         *
         * Le rayon ne tient pas compte de la case centrale.
         *
         * @return Le rayon.
         */
        size_t getRayon() const { return m_rayon; }

        virtual T& operator()(const Coordonnees& c) override
        {
            // Vérifie que les coordonnees sont dans l'hexagone.
            if (c.longueur() > (int)m_rayon)
            {
                std::stringstream ss;
                ss << c << " est hors de l'hexagone de m_rayon " << m_rayon << ".";
                throw std::out_of_range(ss.str());
            }
            size_t colonne = c.getColonne() + m_rayon;
            size_t ligne = c.getLigne() + m_rayon + std::min(c.getColonne(), 0);
            return m_plateau[colonne][ligne];
        }

        virtual const T& operator()(const Coordonnees& c) const override
        {
            // Vérifie que les coordonnees sont dans l'hexagone.
            if (c.longueur() > (int)m_rayon)
            {
                std::stringstream ss;
                ss << c << " est hors de l'hexagone de m_rayon " << m_rayon << ".";
                throw std::out_of_range(ss.str());
            }
            size_t colonne = c.getColonne() + m_rayon;
            size_t ligne = c.getLigne() + m_rayon + std::min(c.getColonne(), 0);
            return m_plateau[colonne][ligne];
        }

        virtual void remplir(const T& valeur) override
        {
            // On itère sur chaque case et on lui alloue sa nouvelle valeur.
            auto itr = iterateur();
            while (itr->aSuite())
            {
                Coordonnees cCase = itr->suite();
                (*this)(cCase) = valeur;
            }
        }

        virtual void remplir(const ICarte<T>& source, const Coordonnees& centre) override
        {
            // On itère sur chaque case de la source.
            auto iterateur = source.iterateur();
            while (iterateur->aSuite())
            {
                // On calcul les coordonnees de destination (avec un offset du centre).
                Coordonnees cSource = iterateur->suite();
                Coordonnees cThis = cSource + centre;
                // On définit la nouvelle valeur si les coordonnees après offset sont valides.
                try
                {
                    (*this)(cThis) = source(cSource);
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
            }
        }

        virtual void remplir(std::function<T()> fournisseur) override
        {
            // On itère sur chaque case et on lui alloue sa nouvelle valeur.
            auto itr = iterateur();
            while (itr->aSuite())
            {
                Coordonnees cCase = itr->suite();
                (*this)(cCase) = fournisseur();
            }
        }

        virtual IIterator_S<Coordonnees> iterateur() const override
        {
            // Crée un itérateur pour l'instance et le retourne.
            IIterator_S<Coordonnees> itr(new IterateurCarteHexagone<T>(this));
            return itr;
        }

    protected:
        /**
         * @brief Libère la mémoire allouée.
         */
        void deletePlateau()
        {
            if (m_plateau != nullptr)
            {
                size_t taille = 2 * m_rayon + 1;
                for (size_t i = 0; i < taille; i++)
                {
                    delete[] m_plateau[i];
                }
                delete[] m_plateau;
            }
        }
    };
}; // namespace hex
#endif
