#ifndef __SANSOBJETERROR_HPP__
#define __SANSOBJETERROR_HPP__

#include <stdexcept>
#include <string>

namespace err
{
    class SansObjetErreur : public std::runtime_error
    {
    public:
        /**
         * @brief Construit une exception SansObjetErreur.
         *
         * @param message Un message décrivant l'erreur.
         */
        SansObjetErreur(const std::string& message);
    };
} // namespace err

#endif // __SANSOBJETERROR_HPP__
