#ifndef __SANSOBJETERROR_HPP__
#define __SANSOBJETERROR_HPP__

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

#endif // __SANSOBJETERROR_HPP__
