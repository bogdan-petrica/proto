

#include "conv.h"

struct PointBase
{
};

template<typename Sys>
struct Point : PointBase
{
    template <typename Oth>
    Point<Sys> & operator=(const Point<Oth>& oth)
    {
        return *this;
    }
};

struct One;
struct Two;

template<typename Src, typename Dest>
struct ScaledSystem;

template <typename Dest, typename Src>
void doConv(Point<Dest>& dest, const Point<Src>&src);

struct One
{
    static
        Point<One> convert(const Point<Two> &)
    {
        return Point<One>();
    }

};

struct Two
{
    static
        Point<Two> convert(const Point<One> &)
    {
        return Point<Two>();
    }

};

template<typename Src, typename Dest>
struct ScaledSystem
{
    template<typename ConvertSrc>
    static
        Point< Dest > convert(const Point<ConvertSrc> & src)
    {
        Point< Src > temp;
        doConv(temp, src);

        Point<Dest> result; // = temp * Dest::factor
        return result;
    }

};

struct ScaledByTwo : ScaledSystem< Two, ScaledByTwo >
{
    typedef  ScaledSystem< One, ScaledByTwo > Base;

    enum {
        factor = 2
    };
};

template <typename Dest, typename Src>
void doConv(Point<Dest>& dest, const Point<Src>&src)
{
    dest = Dest::convert(src);
}

template <typename Src>
void doConv(Point<Src>& dest, const Point<Src>&src)
{
    dest = src;
}

template <typename Src>
void doConv(Point<One>& dest, const Point<Src>&src)
{
    static_assert(false, "False");
}

void convRun()
{
    Point<One> one;
    Point<ScaledByTwo> scaledByTwo;
    doConv(scaledByTwo, one);

    one = one;
}