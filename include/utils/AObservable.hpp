#ifndef __AOBSERVABLE_H__
#define __AOBSERVABLE_H__

#include <list>
#include "utils/IObservateur.hpp"

namespace utils
{
    template <typename T>
    class AObservable
    {
    private:
        std::list<IObservateur<T>*> m_observateurs;

    public:
        /**
         * @brief Construit un nouvel observable.
         */
        AObservable() : m_observateurs() {}

        /**
         * @brief Attache un observateur.
         *
         * NOTE: Ce pointeur n'est pas géré par l'observable.
         *
         * @param observateur L'observateur à attacher.
         */
        void attacher(IObservateur<T>* observateur) { m_observateurs.push_back(observateur); }

        /**
         * @brief Détache un observateur.
         *
         * NOTE: Ce pointeur n'est pas géré par l'observable.
         * S'il l'observateur n'était pas attaché, l'appel ne fait rien.
         *
         * @param observateur L'observateur à détacher.
         */
        void detacher(IObservateur<T>* observateur) { m_observateurs.remove(observateur); }

        /**
         * @brief Informe tous les observateurs qu'il doivent s'actualiser.
         *
         * @param info Une information transmise aux observateurs.
         */
        void notifier(const T& info) const
        {
            // Actualise chaque observateur par ordre d'ajout (du plus ancien au plus récent).
            for (IObservateur<T>* obs : m_observateurs)
            {
                obs->actualiser(info);
            }
        }
    };
} // namespace utils
#endif // __AOBSERVABLE_H__
