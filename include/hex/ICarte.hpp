#ifndef __ICARTE_HPP__
#define __ICARTE_HPP__

#include <functional>
#include <memory>
#include <ostream>
#include "hex/Coordonnees.hpp"
#include "hex/IIterateur.hpp"

namespace hex
{
    template <typename T>
    class ICarte
    {
    public:
        virtual ~ICarte() = default;

        /**
         * @brief Obtient une référence vers la valeur aux coordonnées indiquée.
         *
         * @param c Les coordonnées à visiter.
         * @return Une référence vers la valeur aux coordonnées indiquée.
         * @throw std::out_of_range Quand les coordonnées sont hors de la carte.
         */
        virtual T& operator()(const Coordonnees& c) = 0;

        /**
         * @brief Obtient une référence vers la valeur aux coordonnées indiquée.
         *
         * @param c Les coordonnées à visiter.
         * @return Une référence vers la valeur aux coordonnées indiquée.
         * @throw std::out_of_range Quand les coordonnées sont hors de la carte.
         */
        virtual const T& operator()(const Coordonnees& c) const = 0;

        /**
         * @brief Rempli la carte avec la valeur indiquée.
         *
         * @param valeur La valeur à mettre dans chaque case.
         */
        virtual void remplir(const T& valeur) = 0;

        /**
         * @brief Rempli la carte avec une autre carte et un décallage.
         *
         * NOTE: La source peut dépasser de l'instance. Dans ce cas, les valeurs
         * hors de l'instance ne sont pas copiées.
         *
         * @param source La carte contenant les valeurs à copier.
         * @param centre Le décallage entre le centre de la carte et de la
         * source.
         */
        virtual void remplir(const ICarte& source, const Coordonnees& centre) = 0;

        /**
         * @brief Rempli la carte avec le fournisseur indiquée.
         *
         * @param valeur Le fournisseur à utiliser pour peupler chaque case.
         */
        virtual void remplir(std::function<T()> fournisseur) = 0;

        /**
         * @brief Crée un itérateur sur les coordonnées.
         *
         * @return Un itérateur sur les coordonnées.
         */
        virtual IIterator_S<Coordonnees> iterateur() const = 0;
    };

    template <class T>
    using ICarte_S = std::shared_ptr<ICarte<T>>;

    template <class T>
    using ICarte_SC = std::shared_ptr<const ICarte<T>>;

    template <class T>
    std::ostream& operator<<(std::ostream& os, const ICarte<T> carte)
    {
        auto itr = carte.iterateur();
        while (itr->aSuite())
        {
            hex::Coordonnees cItr = itr->suite();
            os << cItr << '\t' << carte(cItr) << std::endl;
        }
        return os;
    }

}; // namespace hex
#endif // __ICARTE_HPP__
