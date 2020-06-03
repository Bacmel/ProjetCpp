#ifndef IOBJET_HPP
#define IOBJET_HPP

#include <memory>
#include "hex/Coordonnees.hpp"
#include "utils/IActualisable.hpp"

namespace donjon
{
    class IDonjon;
}

namespace obj
{
    class IObjetVisiteur;

    class IObjet : public utils::IActualisable
    {
    public:
        virtual ~IObjet() {}

        /**
         * @brief Indique si l'objet peut être utilisé.
         *
         * @return true si l'objet peut être utilisé.
         */
        virtual bool estUtilisable() const = 0;

        /**
         * @brief Utilise l'objet sur un personnage.
         *
         * @param donjon Le donjon.
         * @param cible La cible de l'utilisation.
         *
         * @throw invalid_argument Quand la cible n'est pas valide.
         * @throw logic_error Quand l'objet ne peut être utilisé.
         */
        virtual void utiliser(donjon::IDonjon& donjon,
                              const hex::Coordonnees& origine,
                              const hex::Coordonnees& cible) = 0;

        /**
         * @brief Accepte le visiteur.
         *
         * @param visiteur Le visiteur à accepter.
         */
        virtual void accepter(IObjetVisiteur& visiteur) const = 0;
    };

    using IObjet_S = std::shared_ptr<IObjet>;
    using IObjet_SC = std::shared_ptr<const IObjet>;

}; // namespace obj

#endif
