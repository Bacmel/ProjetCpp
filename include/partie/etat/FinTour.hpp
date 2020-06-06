#ifndef __FINTOUR_HPP__
#define __FINTOUR_HPP__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class FinTour : public IEtat
    {
    protected:
        /** @brief Indice de l'equipe en jeu. */
        size_t m_indiceEquipe;

    public:
        /**
         * @brief Construit un état FinTour.
         *
         * @param indice Indice que l'équipe dont le tour se termine.
         */
        FinTour(size_t indice);

        void afficher() const override;

        inline size_t getEquipeCourante() const override { return m_indiceEquipe; }

        per::APersonnage_SC getPersoSelect() const override;

        obj::IObjet_SC getObjetSelect() const override;

        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;

        void operation(Partie& partie, size_t objet) override;

        void operation(Partie& partie) override;
    };
} // namespace partie::etat

#endif //__FINTOUR_HPP__
