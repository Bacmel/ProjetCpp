#ifndef __JAUGEERREUR_H__
#define __JAUGEERREUR_H__

#include <stdexcept>
#include <string>

namespace err
{
    class JaugeErreur : public std::runtime_error
    {
    public:
        /**
         * @brief Construit une nouvelle exception.
         *
         * @param message Le descriptif de l'erreur.
         */
        JaugeErreur(const std::string& message);

        virtual ~JaugeErreur();
    };
} // namespace err

#endif // __JAUGEERREUR_H__