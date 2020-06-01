#ifndef __PARTIECONT_H__
#define __PARTIECONT_H__

#include "controlleur/IControlleur.hpp"
#include "utils/HexPixelConvertisseur.hpp"
#include "vue/PartieDessinable.hpp"

namespace controlleur
{
    class PartieCont : public IControlleur
    {
    private:
        const vue::PartieDessinable* m_dessinable;
        utils::HexPixelConvertisseur m_convertisseur;

    public:
        PartieCont(const vue::PartieDessinable& dessinable);
        ~PartieCont();

        virtual void enEvenement(const vue::Fenetre& source, sf::Event& even) override;
    };
} // namespace controlleur
#endif // __PARTIECONT_H__
