#ifndef __TEXTUREMANQUANTEERREUR_H__
#define __TEXTUREMANQUANTEERREUR_H__

#include <stdexcept>
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
#endif // __TEXTUREMANQUANTEERREUR_H__
