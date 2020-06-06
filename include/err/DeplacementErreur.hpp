#ifndef __DEPLACEMENTERREUR_HPP__
#define __DEPLACEMENTERREUR_HPP__

#include <stdexcept>
#include <string>

namespace err
{
    class DeplacementErreur : public std::runtime_error
    {
    public:
        /**
         * @brief Construit une nouvelle exception.
         *
         * @param message Le descriptif de l'erreur.
         */
        DeplacementErreur(const std::string& message);
    };
} // namespace err

#endif // __DEPLACEMENTERREUR_HPP__
