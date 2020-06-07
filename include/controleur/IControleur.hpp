#ifndef __ICONTROLEUR_HPP__
#define __ICONTROLEUR_HPP__

#include <SFML/Graphics.hpp>
#include <memory>

namespace vue
{
    class Fenetre;
}

namespace controleur
{
    /**
     * @brief Gestionnaire d'évènements.
     */
    class IControleur
    {
    public:
        virtual ~IControleur() = default;

        /**
         * @brief Gère l'évènement provenant de la fenêtre.
         *
         * @param source La fenêtre à l'origine de l'évènement.
         * @param even L'évènement.
         */
        virtual void enEvenement(const vue::Fenetre& source, sf::Event& even) = 0;
    };

    using IControleur_S = std::shared_ptr<IControleur>;
    using IControleur_SC = std::shared_ptr<const IControleur>;
} // namespace controleur
#endif // __ICONTROLEUR_HPP__
