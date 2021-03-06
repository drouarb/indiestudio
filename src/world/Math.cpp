#define _USE_MATH_DEFINES
#include <math.h>
#include "Math.hh"

static double cos_tab[629];
static double sin_tab[629];

void
gauntlet::world::Math::init()
{
    static bool initialized = false;

    if (!initialized)
        for (int a = 0; a <= 628; ++a)
            {
                cos_tab[a] = ::cos((double) a / 100);
                sin_tab[a] = ::sin((double) a / 100);
                initialized = true;
            }
}

double        gauntlet::world::Math::abs(double value)
{
    return ((value < 0) ? -value : value);
}

short
gauntlet::world::Math::getAngle(double rad)
{
    return (simplify((int) (rad * 100)));
}

double
gauntlet::world::Math::cos(short angle)
{
    return (cos_tab[simplify(angle + A_FLAT)]);
}

double
gauntlet::world::Math::sin(short angle)
{
    return (sin_tab[simplify(angle)]);
}

float
gauntlet::world::Math::toRad(short angle)
{
    return ((float) angle / 100);
}

short
gauntlet::world::Math::getAngleFromDegrees(int degrees)
{
    return (getAngle((double) degrees / 180 * M_PI));
}

short
gauntlet::world::Math::simplify(short angle)
{
    angle = angle % 629;
    if (angle < 0)
        angle += 628;
    return (angle);
}

bool
gauntlet::world::Math::isBetween(short ref, short sup, short inf)
{
    ref = simplify(ref);
    sup = simplify(sup);
    inf = simplify(inf);
    if (inf > sup)
        sup += 628;
    if (ref < inf)
        ref += 628;
    return (ref >= inf && ref <= sup);
}

double        gauntlet::world::Math::distBetween(std::pair<double, double> pos1, std::pair<double, double> pos2)
{
    double dist;

    dist = sqrt(pow(pos1.first - pos2.first, 2) + pow(pos1.second - pos2.second, 2));
    return (dist);
}
