#ifndef __INFOERREUR_HPP__
#define __INFOERREUR_HPP__

#include <stdexcept>
#include <string>

namespace err
{
    class InfoErreur : public std::runtime_error
    {
    public:
        /**
         * @brief Construit une nouvelle exception.
         *
         * @param message Le descriptif de l'erreur.
         */
        InfoErreur(const std::string& message);

        virtual ~InfoErreur();
    };
} // namespace err

#endif // __INFOERREUR_HPP__
