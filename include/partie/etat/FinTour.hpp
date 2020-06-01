#ifndef __FINTOUR_H__
#define __FINTOUR_H__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class FinTour : public IEtat
    {
    protected:
        /* indice de l'equipe en jeu. */
        size_t m_indiceEquipe;

    public:
        FinTour(size_t indice);

        /**
         * @brief Operation de l'etat courant sur la partie.
         *
         * @param partie la Partie.
         */
        void operation(Partie& partie);

        void afficher() const override;

        inline size_t getEquipeCourante() const override { return m_indiceEquipe; }

        per::APersonnage_SC getPersoSelect() const override;

        obj::IObjet_SC getObjetSelect() const override;

        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;

        void operation(Partie& partie, size_t objet) override;
    };
} // namespace partie::etat

#endif //__FINTOUR_H__
