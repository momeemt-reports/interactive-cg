#include <cmath>

#include "light.h"



using namespace std;

double DirectionalLight::distanceAttenuation( const Vec3d& P ) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


Vec3d DirectionalLight::shadowAttenuation( const Vec3d& P ) const
{
  Vec3d d = getDirection(P);
  d.normalize();
  ray r(P, d, ray::SHADOW);
  isect i;

  if (getScene()->intersect(r, i)) {
    return Vec3d(0.0, 0.0, 0.0);
  } else {
    return Vec3d(1.0, 1.0, 1.0);
  }
}

Vec3d DirectionalLight::getColor( const Vec3d& P ) const
{
	// Color doesn't depend on P 
	return color;
}

Vec3d DirectionalLight::getDirection( const Vec3d& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation( const Vec3d& P ) const
{
  Vec3d dv = this->position - P;
  double d = dv.length();
  double f = 1.0 / (constantTerm + linearTerm * d + quadraticTerm * d * d);
  if (f > 1.0) {
    f = 1.0;
  } else if (f <= 0.0) {
    f = 0.0;
  }
  return f;
}

Vec3d PointLight::getColor( const Vec3d& P ) const
{
	// Color doesn't depend on P 
	return color;
}

Vec3d PointLight::getDirection( const Vec3d& P ) const
{
	Vec3d ret = position - P;
	ret.normalize();
	return ret;
}


Vec3d PointLight::shadowAttenuation(const Vec3d& P) const
{
  Vec3d d = getDirection(P);
  d.normalize();
  ray r(P, d, ray::SHADOW);
  isect i;
  Vec3d dv = position - P;
  double dist = dv.length();

  if (getScene()->intersect(r, i)) {
    Vec3d new_dv = r.at(i.t) - P;
    if (new_dv.length() > dist) {
      return Vec3d(1.0, 1.0, 1.0);
    }
    return Vec3d(0.0, 0.0, 0.0);
  }
  return Vec3d(1.0, 1.0, 1.0);
}
