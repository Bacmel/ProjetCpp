#ifndef __JOUEURHUMAIN_HPP__
#define __JOUEURHUMAIN_HPP__

#include "partie/strat/IStrategie.hpp"

namespace partie::strat
{
    class JoueurHumain : public IStrategie
    {
    public:
        /**
         * @brief Crée un JoueurHumain.
         *
         * L'instance peut être partagée par plusieurs équipes.
         */
        JoueurHumain();
        ~JoueurHumain() = default;

        void mettreEnOeuvre(partie::Partie& partie, partie::Equipe& equipe) override;
    };
} // namespace partie::strat
#endif // __JOUEURHUMAIN_HPP__
