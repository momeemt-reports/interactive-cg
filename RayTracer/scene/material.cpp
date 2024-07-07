#include "material.h"
#include "light.h"
#include "ray.h"

#include "../fileio/imageio.h"

using namespace std;
extern bool debugMode;

// Apply the Phong model to this point on the surface of the object, returning
// the color of that point.
Vec3d Material::shade(Scene *scene, const ray &r, const isect &i) const {
  Vec3d lum = ke(i) + prod(ka(i), scene->ambient());
  Vec3d v = -r.getDirection();

  if (debugMode)
    std::cout << "Debugging the Phong code (or lack thereof...)" << std::endl;

  for (vector<Light *>::const_iterator litr = scene->beginLights();
       litr != scene->endLights(); litr++) {
    Light *pLight = *litr;
    Vec3d ld = pLight->getDirection(r.at(i.t));
    ld.normalize();

    Vec3d lc = pLight->getColor(r.at(i.t));
    Vec3d atten = pLight->distanceAttenuation(r.at(i.t)) *
                  pLight->shadowAttenuation(r.at(i.t));
    Vec3d ldf = kd(i) * max(0.0, i.N * ld);
    Vec3d lsp =
        ks(i) *
        pow(max(0.0, (ld + 2 * (i.N * ld * i.N - ld)) * -r.getDirection()),
            shininess(i));
    lum += prod(atten, prod(lc, ldf + lsp));
  }

  return lum;
}

TextureMap::TextureMap(string filename) {
  data = load(filename.c_str(), width, height);
  if (0 == data) {
    width = 0;
    height = 0;
    string error("Unable to load texture map '");
    error.append(filename);
    error.append("'.");
    throw TextureMapException(error);
  }
}

Vec3d TextureMap::getMappedValue(const Vec2d &coord) const {
  return getPixelAt(coord[0] * width, coord[1] * height);
}

Vec3d TextureMap::getPixelAt(int x, int y) const {
  // This keeps it from crashing if it can't load
  // the texture, but the person tries to render anyway.
  if (0 == data)
    return Vec3d(1.0, 1.0, 1.0);

  if (x >= width)
    x = width - 1;
  if (y >= height)
    y = height - 1;

  // Find the position in the big data array...
  int pos = (y * width + x) * 3;
  return Vec3d(double(data[pos]) / 255.0, double(data[pos + 1]) / 255.0,
               double(data[pos + 2]) / 255.0);
}

Vec3d MaterialParameter::value(const isect &is) const {
  if (0 != _textureMap)
    return _textureMap->getMappedValue(is.uvCoordinates);
  else
    return _value;
}

double MaterialParameter::intensityValue(const isect &is) const {
  if (0 != _textureMap) {
    Vec3d value(_textureMap->getMappedValue(is.uvCoordinates));
    return (0.299 * value[0]) + (0.587 * value[1]) + (0.114 * value[2]);
  } else
    return (0.299 * _value[0]) + (0.587 * _value[1]) + (0.114 * _value[2]);
}
