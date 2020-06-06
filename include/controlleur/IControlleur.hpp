#ifndef __ICONTROLLEUR_HPP__
#define __ICONTROLLEUR_HPP__

#include <SFML/Graphics.hpp>
#include <memory>
namespace vue
{
    class Fenetre;
}

namespace controlleur
{
    /**
     * @brief Gestionnaire d'évènements.
     */
    class IControlleur
    {
    public:
        virtual ~IControlleur() = default;

        /**
         * @brief Gère l'évènement provenant de la fenêtre.
         *
         * @param source La fenêtre à l'origine de l'évènement.
         * @param even L'évènement.
         */
        virtual void enEvenement(const vue::Fenetre& source, sf::Event& even) = 0;
    };

    using IControlleur_S = std::shared_ptr<IControlleur>;
    using IControlleur_SC = std::shared_ptr<const IControlleur>;
} // namespace controlleur
#endif // __ICONTROLLEUR_HPP__
