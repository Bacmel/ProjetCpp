#ifndef __DEPLACEMENTERROR_H__
#define __DEPLACEMENTERROR_H__

#include <stdexcept>
#include <string>

namespace err
{
    class DeplacementError : public std::runtime_error
    {
    public:
        /**
         * @brief Construit une nouvelle exception.
         *
         * @param message Le descriptif de l'erreur.
         */
        DeplacementError(const std::string& message);

        virtual ~DeplacementError();
    };
} // namespace err

#endif // __DEPLACEMENTERROR_H__