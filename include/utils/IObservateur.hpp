#ifndef __IOBSERVATEUR_H__
#define __IOBSERVATEUR_H__

#include <memory>

namespace utils
{
    template<typename T>
    class IObservateur
    {
    public:
        /**
         * @brief Actualise l'observateur.
         *
         * Cette méthode est appelée par l'observateur quand il notifie ses
         * observateur.
         *
         * @param info Une information transmise par l'observable.
         */
        virtual void actualiser(const T& info) = 0;

        virtual ~IObservateur() = default;
    };
} // namespace utils
#endif // __IOBSERVATEUR_H__
