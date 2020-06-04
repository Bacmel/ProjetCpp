#ifndef __JOUEURHUMAIN_H__
#define __JOUEURHUMAIN_H__

#include "partie/strat/IStrategie.hpp"

namespace partie::strat
{
    class JoueurHumain: public IStrategie
    {
    public:
        JoueurHumain();
        ~JoueurHumain() = default;

        void mettreEnOeuvre(partie::Partie& partie, partie::Equipe& equipe) override;
    };
}
#endif // __JOUEURHUMAIN_H__
