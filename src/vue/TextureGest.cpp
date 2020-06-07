#include "vue/TextureGest.hpp"
#include <iostream>
#include <stdexcept>
#include "err/TextureESErreur.hpp"

using namespace std;
using namespace sf;

namespace vue
{
    TextureGest::TextureGest() : m_textures() {}

    TextureGest& TextureGest::getInstance()
    {
        static TextureGest instance; // Crée une unique instance.
        return instance;
    }

    Texture_S TextureGest::obtenir(const string& chemin)
    {
        map<string, Texture_S>::iterator itr = m_textures.find(chemin);
        // Si la texture n'est pas encore chargée.
        if (itr == m_textures.end())
        {
            // Charge la texture.
            Texture_S texture = make_shared<Texture>();
            if (!texture->loadFromFile(chemin))
            { throw err::TextureESErreur("TextureGest::obtenir : N'a pas pu charger une texture.", chemin); }
            // Stocke la texture et met à jour l'itérateur.
            auto res = m_textures.insert(pair<string, Texture_S>(chemin, texture));
            if (!res.second) { throw runtime_error("TextureGest::obtenir : N'a pas pu conserver la texture."); }
            itr = res.first;
        }
        return itr->second;
    }

    void TextureGest::retirer(const std::string& chemin) { m_textures.erase(chemin); }
} // namespace vue
