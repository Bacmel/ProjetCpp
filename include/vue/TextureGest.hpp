#ifndef __TEXTUREGEST_H__
#define __TEXTUREGEST_H__

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

namespace vue
{
    using Texture_S = std::shared_ptr<sf::Texture>;

    class TextureGest
    {
    private:
        std::map<std::string, Texture_S> m_textures;

        /**
         * @brief Crée une instance du gestionnaire de textures.
         */
        TextureGest();

    public:
        TextureGest(const TextureGest& autre) = delete;
        TextureGest& operator=(const TextureGest& autre) = delete;
        ~TextureGest() = default;

        /**
         * @brief Obtient l'instance du gestionnaire de textures.
         *
         * Le gestionnaire de textures charge une texture sur demande (Lazy
         * loading) et la conserve pour les demandes suivantes. C'est une classe
         * gourmande en RAM et en temps (lors d'un chargement). Il n'y a donc
         * qu'une seule instance de cette classe.
         *
         * NOTE: Le pointeur est géré par la classe et il ne doit pas être
         * libéré.
         *
         * @return L'instance du gestionnaire de textures.
         */
        static TextureGest& getInstance();

        /**
         * @brief Donne une copie du pointeur partagé de la texture demandée.
         *
         * La texture est chargée si ce n'est pas déjà fait.
         *
         * @param chemin Le chemin vers la texture.
         * @return Une copie du pointeur partagé de la texture demandée.
         *
         * @throw err::TextureESErreur Quand le chargement de la texture échoue.
         */
        Texture_S obtenir(const std::string& chemin);

        /**
         * @brief Retire une texture du gestionnaire.
         *
         * Ne fait rien si la texture n'a pas été chargée.
         *
         * NOTE: La suppression du pointeur partagé du gestionnaire n'implique
         * pas la libération de la texture. Tant qu'une copie du pointeur
         * partagé de la texture subsite, elle restera en RAM.
         *
         * @param chemin Le chemin vers la texture à retirer.
         */
        void retirer(const std::string& chemin);

    };
} // namespace vue
#endif // __TEXTUREGEST_H__
