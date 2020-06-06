#ifndef __CASEDESSINABLE_HPP__
#define __CASEDESSINABLE_HPP__

#include "donjon/cases/ICaseVisiteur.hpp"
#include "utils/IObservateur.hpp"
#include "vue/ADessinable.hpp"
#include "vue/ObjetDessinable.hpp"

namespace vue
{
    class CaseDessinable : public vue::ADessinable<donjon::cases::ACase>,
                           public donjon::cases::ICaseVisiteur,
                           public utils::IObservateur<donjon::cases::ACase>
    {
    private:
        sf::CircleShape m_hexagone;
        Texture_S m_textureSol;
        Texture_S m_textureTrou;
        ObjetDessinable m_objDessinable;

    public:
        /**
         * @brief Construit une CaseDessinable.
         *
         * @param cote La longueur du côté de l'hexagone (en px).
         */
        CaseDessinable(float cote);

        /**
         * @brief Construit une CaseDessinable.
         *
         * @param cote La longueur du côté de l'hexagone (en px).
         * @param aCase La case à dessiner.
         *
         * @throw std::invalid_argument Quand aCase est null.
         */
        CaseDessinable(float cote, donjon::cases::ACase_S aCase);

        CaseDessinable(const CaseDessinable& autre);
        CaseDessinable& operator=(const CaseDessinable& autre);
        ~CaseDessinable();

        /**
         * @brief Surligne la case.
         *
         * Quand elle est surlignée, ses bordures sont plus épaisses et jaune.
         * Le fond est jaunie.
         */
        void surligner();

        /* Implémentation de ADessinable */
        void setCote(float cote) override;
        void setElement(donjon::cases::ACase_S aCase) override;
        void visite(const donjon::cases::Sol& sol) override;
        void visite(const donjon::cases::Trou& trou) override;
        /* Implémentation de Drawable */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        /* Implémentation de IObservateur */
        void actualiser(const donjon::cases::ACase& aCase) override;
    };
} // namespace vue
#endif // __CASEDESSINABLE_HPP__
