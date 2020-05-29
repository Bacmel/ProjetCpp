#ifndef __ADESSINATEUR_H__
#define __ADESSINATEUR_H__

#include <SFML/Graphics.hpp>
#include "hex/Coordonnees.hpp"

namespace vue
{
    template <typename T>
    class ADessinateur
    {
    private:
        float m_rayon;

    public:
        /**
         * @brief Construit un nouveau dessinateur.
         *
         * @param rayon Le rayon du cercle circonscrit à l'hexagone (en pixels).
         */
        ADessinateur(float rayon) : m_rayon(rayon) {}
        virtual ~ADessinateur() {}

        /**
         * @brief Obtient le rayon du cercle circonscrit à l'hexagone.
         *
         * @return Le rayon du cercle circonscrit à l'hexagone (en pixels).
         *
         * @see getCote()
         */
        inline float getRayon() const { return m_rayon; }

        /**
         * @brief Défini le rayon du cercle circonscrit à l'hexagone.
         *
         * @param rayon Le rayon du cercle circonscrit à l'hexagone (en pixels).
         *
         * @see setCote()
         */
        inline void setRayon(size_t rayon) { m_rayon = rayon; }

        /**
         * @brief Dessine l'élément.
         *
         * @param hex La position dans le repère hexagonale.
         * @param elem L'élément à dessiner.
         */
        virtual void dessine(const hex::Coordonnees& hex, const T& elem) = 0;
    };
} // namespace vue
#endif // __ADESSINATEUR_H__
