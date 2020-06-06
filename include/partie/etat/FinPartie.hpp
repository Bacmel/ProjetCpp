#ifndef __FINPARTIE_HPP__
#define __FINPARTIE_HPP__

#include "hex/Coordonnees.hpp"
#include "obj/IObjet.hpp"
#include "partie/etat/IEtat.hpp"

namespace partie::etat
{
    class FinPartie : public IEtat
    {
    private:
        /** @brief L'indice de l'équipe qui a gagnée. */
        size_t m_equipe;

    public:
        /**
         * @brief Construit un état FinPartie
         *
         * @param indice L'indice de l'équipe gagnante.
         */
        FinPartie(size_t indice);

        /* Constructeurs & operateurs de copie & destructeur */
        FinPartie(const FinPartie& autre) = default;
        FinPartie(FinPartie&& autre) = default;
        FinPartie& operator=(const FinPartie& autre) = default;
        FinPartie& operator=(FinPartie&& autre) = default;
        ~FinPartie() = default;

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

#endif //__FINPARTIE_HPP__
