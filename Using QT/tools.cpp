#include "tools.h"
#include "cstring"
#define pixmap_dir ":/images/main_texture_pack/"


template <typename T> T min(T a, T b)
{
    return (a > b) ? b : a;
};

template <typename T> T min(T a, T b, T c)
{
    T mab = min<T>(a,b);
    return (mab > c) ? c : mab;
};


template <typename T> T max(T a,T b)
{
    return (a < b) ? b : a;
};

template <typename T> T max_of(pair p)
{
    return (p.x < p.y) ? p.y : p.x;
};

template <typename T> bool same_sign(T a, T b)
{
    return ((a > 0 && b > 0) || (a < 0 && b < 0));
};

template <typename T> T abs(T a)
{
    return (a<0) ? -a : a;
};

const char* add_dir(const char* image)
{
    const unsigned int length = strlen(pixmap_dir) + strlen(image) + 1;

    char* pixmap = new char[length];

    strcpy(pixmap,pixmap_dir);

    strcat(pixmap,image);

    return pixmap;
};
