#ifndef __IOBSERVATEUR_HPP__
#define __IOBSERVATEUR_HPP__

namespace utils
{
    template<typename T>
    class IObservateur
    {
    public:
        virtual ~IObservateur() = default;

        /**
         * @brief Actualise l'observateur.
         *
         * Cette méthode est appelée par l'observateur quand il notifie ses
         * observateur.
         *
         * @param info Une information transmise par l'observable.
         */
        virtual void actualiser(const T& info) = 0;
    };
} // namespace utils
#endif // __IOBSERVATEUR_HPP__
