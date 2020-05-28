#include "err/TextureESErreur.hpp"

namespace err
{
    TextureESErreur::TextureESErreur(const std::string& message, const std::string& chemin) :
        std::runtime_error(message),
        m_chemin(chemin)
    {
    }
} // namespace err
