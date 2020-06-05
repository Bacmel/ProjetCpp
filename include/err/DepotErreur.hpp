#ifndef __DEPOTERREUR_HPP__
#define __DEPOTERREUR_HPP__

#include <stdexcept>
#include <string>

namespace err
{
    class DepotErreur : public std::runtime_error
    {
    public:
        /**
         * @brief Construit une nouvelle exception.
         *
         * @param message Le descriptif de l'erreur.
         */
        DepotErreur(const std::string& message);

        virtual ~DepotErreur();
    };
} // namespace err

#endif // __DEPOTERREUR_HPP__
