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
        size_t m_equipe;

    public:
        /**
         * @brief Construit un état FinTour.
         *
         * @param indice Indice que l'équipe dont le tour se termine.
         */
        FinTour(size_t indice);

        /* Constructeurs & operateurs de copie & destructeur */
        FinTour(const FinTour& autre) = default;
        FinTour(FinTour&& autre) = default;
        FinTour& operator=(const FinTour& autre) = default;
        FinTour& operator=(FinTour&& autre) = default;
        ~FinTour() = default;

        /* Méthodes IEtat. */
        std::string enTexte() const override;
        inline size_t getEquipeCourante() const override { return m_equipe; }
        inline per::APersonnage_S getPersoSelect() override;
        inline per::APersonnage_SC getPersoSelect() const override;
        inline obj::IObjet_S getObjetSelect() override;
        inline obj::IObjet_SC getObjetSelect() const override;
        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;
        void operation(Partie& partie, size_t indiceObjet) override;
        void operation(Partie& partie) override;
    };
} // namespace partie::etat

#endif //__FINTOUR_HPP__
