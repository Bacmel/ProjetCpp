#ifndef __IGESTEVEN_H__
#define __IGESTEVEN_H__

#include <SFML/Graphics.hpp>
#include <memory>

namespace controlleur
{
    /**
     * @brief Gestionnaire d'évènements.
     */
    class IControlleur
    {
    public:
        virtual void enEvenement(sf::Event& even) = 0;
        virtual ~IControlleur() {}
    };

    using IControlleur_S = std::shared_ptr<IControlleur>;
    using IControlleur_SC = std::shared_ptr<const IControlleur>;
} // namespace controlleur
#endif // __IGESTEVEN_H__
