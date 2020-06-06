#ifndef __PARTIECONT_HPP__
#define __PARTIECONT_HPP__

#include "controlleur/IControlleur.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "vue/PartieDessinable.hpp"
#include "partie/Partie.hpp"

namespace controlleur
{
    class PartieCont : public IControlleur
    {
    private:
        const vue::PartieDessinable* m_dessinable;
        partie::Partie* m_partie;
        utils::HexPixelConvertisseur m_convertisseur;

    public:
        PartieCont(const vue::PartieDessinable& dessinable, partie::Partie& partie);

        virtual void enEvenement(const vue::Fenetre& source, sf::Event& even) override;

    protected:
        bool clicObjet(const sf::Vector2f& coordonneesClic);
        void clicCase(const sf::Vector2f& coordonneesClic, const vue::Fenetre& source);
    };
} // namespace controlleur
#endif // __PARTIECONT_HPP__
