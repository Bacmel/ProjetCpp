#ifndef CARTE_HEXAGONE_HPP
#define CARTE_HEXAGONE_HPP

#include <cmath>
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
        explicit CarteHexagone(size_t rayon) : m_rayon(rayon), m_plateau(nullptr)
        {
            size_t diametre = 2 * m_rayon + 1;
            m_plateau = new T*[diametre];
            for (size_t i = 1; i <= m_rayon; i++)
            {
                m_plateau[m_rayon + i] = new T[diametre - i];
                m_plateau[m_rayon - i] = new T[diametre - i];
            }
            m_plateau[m_rayon] = new T[diametre];
        }

        virtual ~CarteHexagone()
        {
            size_t diametre = 2 * m_rayon + 1;
            for (size_t i = 0; i < diametre; i++)
            {
                delete[] m_plateau[i];
            }
            delete[] m_plateau;
        }

        size_t getRayon() const { return m_rayon; }

        virtual T& operator()(Coordonnees& c) override
        {
            if (abs(c.getLigne()) > (int)m_rayon || abs(c.getColonne()) > (int)m_rayon)
            {
                std::stringstream ss;
                ss << '(' << c.getColonne() << ", " << c.getLigne() << ") est hors de l'hexagone de m_rayon " << m_rayon
                   << ".";
                throw std::out_of_range(ss.str());
            }
            return m_plateau[m_rayon - c.getColonne()][m_rayon - c.getLigne()];
        }

        virtual const T& operator()(Coordonnees& c) const override
        {
            if (abs(c.getLigne()) > (int)m_rayon || abs(c.getColonne()) > (int)m_rayon)
            {
                std::stringstream ss;
                ss << c << " est hors de l'hexagone de rayon " << m_rayon << ".";
                throw std::out_of_range(ss.str());
            }
            return m_plateau[m_rayon - c.getColonne()][m_rayon - c.getLigne()];
        }

        virtual void remplir(const T& valeur) override {
            auto itr = iterateur();
            while(itr->aSuite())
            {
                Coordonnees cCase = itr->suite();
                (*this)(cCase) = valeur;
            }
        }

        virtual void remplir(const ICarte<T>& source, const Coordonnees& centre) override
        {
            auto iterateur = source.iterateur();
            while (iterateur->aSuite())
            {
                Coordonnees cSource = iterateur->suite();
                Coordonnees cThis = cSource + centre;
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

        virtual IIterator_S<Coordonnees> iterateur() const override
        {
            IIterator_S<Coordonnees> itr(new IterateurCarteHexagone<T>(this));
            return itr;
        }
    };

}; // namespace hex
#endif
