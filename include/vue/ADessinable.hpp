#ifndef __ADESSINATEUR_HPP__
#define __ADESSINATEUR_HPP__

#include <SFML/Graphics.hpp>
#include <memory>
#include <stdexcept>
#include "hex/Coordonnees.hpp"
#include "vue/TextureGest.hpp"

namespace vue
{
    template <typename T>
    class ADessinable : public sf::Drawable, public sf::Transformable
    {
    protected:
        float m_cote;
        std::shared_ptr<T> m_element;

    public:
        /**
         * @brief Construit un nouveau dessinateur.
         *
         * @param cote Le cote de l'hexagone (en pixels).
         */
        ADessinable(float cote) : m_cote(cote), m_element(nullptr) {}

        /**
         * @brief Construit un nouveau dessinateur.
         *
         * @param cote Le cote de l'hexagone (en pixels).
         * @param element L'élément a dessiner.
         *
         * @throw std::invalid_argument Quand element est null.
         */
        ADessinable(float cote, std::shared_ptr<T> element) : m_cote(cote), m_element(element)
        {
            if (element == nullptr) { throw std::invalid_argument("ADessinable::ADessinable : element est nul!"); }
        }

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
        virtual std::shared_ptr<T> getElement() { return m_element; }
        /**
         * @brief Obtient l'élément dessiné.
         *
         * @return L'élément dessiné (nullptr si aucun élément n'est dessiné).
         */
        virtual std::shared_ptr<const T> getElement() const { return m_element; }

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
        virtual void setElement(std::shared_ptr<T> element) = 0;
    };
} // namespace vue
#endif // __ADESSINATEUR_HPP__
