#ifndef __SANSOBJETERROR_H__
#define __SANSOBJETERROR_H__

#include <stdexcept>
#include <string>

namespace err
{
    class SansObjetErreur : public std::runtime_error
    {
    public:
        SansObjetErreur(const std::string& message);

        virtual ~SansObjetErreur();
    };
} // namespace err

#endif // __SANSOBJETERROR_H__
