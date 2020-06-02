#ifndef __DEPLACEMENTERREUR_H__
#define __DEPLACEMENTERREUR_H__

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

        virtual ~DeplacementErreur();
    };
} // namespace err

#endif // __DEPLACEMENTERREUR_H__