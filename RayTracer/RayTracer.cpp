// The main ray tracer.

#pragma warning(disable : 4786)

#include "RayTracer.h"
#include "scene/light.h"
#include "scene/material.h"
#include "scene/ray.h"

#include "parser/Parser.h"
#include "parser/Tokenizer.h"

#include "ui/TraceUI.h"
#include <algorithm>
#include <cmath>

extern TraceUI *traceUI;

#include <fstream>
#include <iostream>

using namespace std;

// Use this variable to decide if you want to print out
// debugging messages.  Gets set in the "trace single ray" mode
// in TraceGLWindow, for example.
bool debugMode = false;

// Trace a top-level ray through normalized window coordinates (x,y)
// through the projection plane, and out into the scene.  All we do is
// enter the main ray-tracing method, getting things started by plugging
// in an initial ray weight of (0.0,0.0,0.0) and an initial recursion depth of
// 0.
Vec3d RayTracer::trace(double x, double y) {
  // Clear out the ray cache in the scene for debugging purposes,
  scene->intersectCache.clear();

  ray r(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);

  scene->getCamera().rayThrough(x, y, r);
  Vec3d ret = traceRay(r, Vec3d(1.0, 1.0, 1.0), 0);
  ret.clamp();
  return ret;
}

// Do recursive ray tracing!  You'll want to insert a lot of code here
// (or places called from here) to handle reflection, refraction, etc etc.
Vec3d RayTracer::traceRay(const ray &r, const Vec3d &thresh, int depth) {
  isect i;

  if (scene->intersect(r, i)) {
    const Material &m = i.getMaterial();
    Vec3d ret = m.shade(scene, r, i);

    if (depth < traceUI->getDepth()) {
      Vec3d kr = m.kr(i);
      Vec3d kt = m.kt(i);
      Vec3d d = r.getDirection();
      d.normalize();
      Vec3d norm = i.N;
      double n1, n2;

      if (d * i.N > 0.0) {
        norm = -norm;
        n1 = m.index(i);
        n2 = 1;
      } else {
        n1 = 1;
        n2 = m.index(i);
      }
      double nm = n2 / n1;

      Vec3d reflect(0.0, 0.0, 0.0);
      Vec3d dd = -(i.N * d) * i.N + d;
      Vec3d rd = -d + 2 * dd;
      rd.normalize();
      if (!(kr.iszero())) {
        ray rr(r.at(i.t - RAY_EPSILON), rd, ray::REFLECTION);
        reflect = traceRay(rr, thresh, depth + 1);
        ret += prod(kr, reflect);
      }

      Vec3d transmit(0.0, 0.0, 0.0);
      Vec3d td = -norm + dd / sqrt(nm * nm - dd.length2());
      td.normalize();

      if (!kt.iszero()) {
        if (dd.length() > nm) {
          ray rr(r.at(i.t - RAY_EPSILON), rd, ray::REFLECTION);
          transmit = traceRay(rr, thresh, depth + 1);
          ret += prod(kt, transmit);
        } else {
          ray rr(r.at(i.t + RAY_EPSILON), td, ray::REFLECTION);
          transmit = traceRay(rr, thresh, depth + 1);
          ret += prod(kt, transmit);
        }
      }
    }
    return ret;
  }
  return Vec3d(0.0, 0.0, 0.0);
}

RayTracer::RayTracer()
    : scene(0), buffer(0), buffer_width(256), buffer_height(256),
      m_bBufferReady(false) {}

RayTracer::~RayTracer() {
  delete scene;
  delete[] buffer;
}

void RayTracer::getBuffer(unsigned char *&buf, int &w, int &h) {
  buf = buffer;
  w = buffer_width;
  h = buffer_height;
}

double RayTracer::aspectRatio() {
  return sceneLoaded() ? scene->getCamera().getAspectRatio() : 1;
}

bool RayTracer::loadScene(char *fn) {
  ifstream ifs(fn);
  if (!ifs) {
    string msg("Error: couldn't read scene file ");
    msg.append(fn);
    traceUI->alert(msg);
    return false;
  }

  // Strip off filename, leaving only the path:
  string path(fn);
  if (path.find_last_of("\\/") == string::npos)
    path = ".";
  else
    path = path.substr(0, path.find_last_of("\\/"));

  // Call this with 'true' for debug output from the tokenizer
  Tokenizer tokenizer(ifs, false);
  Parser parser(tokenizer, path);
  try {
    delete scene;
    scene = 0;
    scene = parser.parseScene();
  } catch (SyntaxErrorException &pe) {
    traceUI->alert(pe.formattedMessage());
    return false;
  } catch (ParserException &pe) {
    string msg("Parser: fatal exception ");
    msg.append(pe.message());
    traceUI->alert(msg);
    return false;
  } catch (TextureMapException e) {
    string msg("Texture mapping exception: ");
    msg.append(e.message());
    traceUI->alert(msg);
    return false;
  }

  if (!sceneLoaded())
    return false;

  // Initialize the scene's BSP tree
  scene->initBSPTree();

  return true;
}

void RayTracer::traceSetup(int w, int h) {
  if (buffer_width != w || buffer_height != h) {
    buffer_width = w;
    buffer_height = h;

    bufferSize = buffer_width * buffer_height * 3;
    delete[] buffer;
    buffer = new unsigned char[bufferSize];
  }
  memset(buffer, 0, w * h * 3);
  m_bBufferReady = true;
}

void RayTracer::tracePixel(int i, int j) {
  Vec3d col;

  if (!sceneLoaded())
    return;

  double x = double(i) / double(buffer_width);
  double y = double(j) / double(buffer_height);

  col = trace(x, y);

  unsigned char *pixel = buffer + (i + j * buffer_width) * 3;

  pixel[0] = (int)(255.0 * col[0]);
  pixel[1] = (int)(255.0 * col[1]);
  pixel[2] = (int)(255.0 * col[2]);
}
