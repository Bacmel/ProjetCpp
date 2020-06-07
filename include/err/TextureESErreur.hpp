#ifndef __TEXTUREMANQUANTEERREUR_HPP__
#define __TEXTUREMANQUANTEERREUR_HPP__

#include <stdexcept>
#include <string>

namespace err
{
    class TextureESErreur : public std::runtime_error
    {
    private:
        std::string m_chemin;

    public:
        /**
         * @brief Construit une exception TextureESErreur.
         *
         * @param message Un message décrivant l'erreur.
         * @param chemin Le chemin de l'image qui n'a pas pu être chargée.
         */
        TextureESErreur(const std::string& message, const std::string& chemin);

        /**
         * @brief Obtient le chemin de l'image qui n'a pas pu être chargée.
         *
         * @return Le chemin de l'image qui n'a pas pu être chargée.
         */
        inline const std::string& getChemin() { return m_chemin; }
    };
} // namespace err
#endif // __TEXTUREMANQUANTEERREUR_HPP__
