#ifndef __CREATIONERREUR_HPP__
#define __CREATIONERREUR_HPP__

#include <stdexcept>
#include <string>

namespace err
{
    class CreationErreur : public std::runtime_error
    {
    public:
        /**
         * @brief Construit une nouvelle exception.
         *
         * @param message Le descriptif de l'erreur.
         */
        CreationErreur(const std::string& message);
    };
} // namespace err

#endif // __CREATIONERREUR_HPP__
