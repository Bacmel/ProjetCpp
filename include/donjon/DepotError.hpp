#ifndef __DEPOTERROR_H__
#define __DEPOTERROR_H__

#include <stdexcept>
#include <string>

namespace donjon
{
    class DepotError : public std::runtime_error
    {
    public:
        /**
         * @brief Construit une nouvelle exception.
         *
         * @param message Le descriptif de l'erreur.
         */
        DepotError(const std::string& message);

        virtual ~DepotError();
    };
} // namespace donjon

#endif // __DEPOTERROR_H__
