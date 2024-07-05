#include <cmath>

#include "Sphere.h"

using namespace std;

bool Sphere::intersectLocal(const ray &r, isect &i) const {
  Vec3d p = r.getPosition();
  Vec3d d = r.getDirection();

  double det = (p * d) * (p * d) - p * p + 1.0;
  if (det < 0.0) {
    return false;
  }

  double t1 = -(p * d) - sqrt(det);
  double t2 = -(p * d) + sqrt(det);
  double t;

  if (t1 > RAY_EPSILON) {
    t = t1;
  } else if (t2 > RAY_EPSILON) {
    t = t2;
  } else {
    return false;
  }

  Vec3d intersect = r.at(t);
  if (intersect * intersect - 1.0 < RAY_EPSILON) {
    i.obj = this;
    i.t = t;
    i.N = intersect;
    i.N.normalize();
    return true;
  }

  return false;
}
