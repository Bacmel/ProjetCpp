#ifndef __ADESSINATEUR_H__
#define __ADESSINATEUR_H__

#include <SFML/Graphics.hpp>
#include <memory>
#include "hex/Coordonnees.hpp"

namespace vue
{
    template <typename T>
    class ADessinable : public sf::Drawable, public sf::Transformable
    {
    protected:
        float m_cote;
        T* m_element;

    public:
        /**
         * @brief Construit un nouveau dessinateur.
         *
         * @param cote Le cote du cercle circonscrit à l'hexagone (en pixels).
         */
        ADessinable(float cote) : m_cote(cote), m_element(nullptr) {}
        ADessinable(float cote, T& element) : m_cote(cote), m_element(&element) {}
        virtual ~ADessinable() = default;

        /**
         * @brief Obtient le côté des hexagones de la carte.
         *
         * @return Le côté des hexagones de la carte.
         */
        virtual float getCote() const { return m_cote; }

        /**
         * @brief Obtient l'élément dessiné.
         *
         * @return L'élément dessiné (nullptr si aucun élément n'est dessiné).
         */
        virtual T* getElement() { return m_element; }
        /**
         * @brief Obtient l'élément dessiné.
         *
         * @return L'élément dessiné (nullptr si aucun élément n'est dessiné).
         */
        virtual const T* getElement() const { return m_element; }

        /**
         * @brief Définit le côté des hexagones de la carte.
         *
         * @param cote Le côté des hexagones de la carte.
         */
        virtual void setCote(float cote) { m_cote = cote; };

        /**
         * @brief Définit l'élément dessiné.
         *
         * @param personnage L'élément dessiné (nullptr si aucun élément.
         * n'est dessiné).
         */
        virtual void setElement(T& element) = 0;
    };
} // namespace vue
#endif // __ADESSINATEUR_H__
