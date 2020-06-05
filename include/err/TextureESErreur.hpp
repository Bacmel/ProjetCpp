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
        TextureESErreur(const std::string& message, const std::string& chemin);
        inline const std::string& getChemin() { return m_chemin; }
    };
} // namespace err
#endif // __TEXTUREMANQUANTEERREUR_HPP__
