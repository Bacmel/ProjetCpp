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
        size_t m_indiceGagnant;

    public:
        /**
         * @brief Construit un état FinPartie
         *
         * @param indice L'indice de l'équipe gagnante.
         */
        FinPartie(size_t indice);

        void afficher() const override;

        inline size_t getEquipeCourante() const override { return m_indiceGagnant; }

        per::APersonnage_SC getPersoSelect() const override;

        obj::IObjet_SC getObjetSelect() const override;

        void operation(Partie& partie, const hex::Coordonnees& coordonnees) override;

        void operation(Partie& partie, size_t objet) override;

        void operation(Partie& partie) override;
    };
} // namespace partie::etat

#endif //__FINPARTIE_HPP__
