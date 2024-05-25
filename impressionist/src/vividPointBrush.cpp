#include "vividPointBrush.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <algorithm>

extern float frand();

VividPointBrush::VividPointBrush(ImpressionistDoc *pDoc, const char *name)
    : ImpBrush(pDoc, name) {}

void VividPointBrush::BrushBegin(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  int size = pDoc->getSize();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPointSize((float)size);

  BrushMove(source, target);
}

void VividPointBrush::BrushMove(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  if (pDoc == NULL) {
    printf("VividPointBrush::BrushMove  document is NULL\n");
    return;
  }

  SetVividColor(source);
  glBegin(GL_POINTS);
  glVertex2d(target.x, target.y);
  glEnd();
}

void VividPointBrush::BrushEnd(const Point source, const Point target) {
  glDisable(GL_BLEND);
}

void VividPointBrush::SetVividColor(const Point source) {
  ImpressionistDoc *pDoc = GetDocument();
  GLubyte color[3];

  memcpy(color, pDoc->GetOriginalPixel(source), 3);

  float r = color[0] / 255.0f;
  float g = color[1] / 255.0f;
  float b = color[2] / 255.0f;

  float h, s, l;
  RGBtoHSL(r, g, b, h, s, l);

  s = 1.0f;
  l = std::min(l * 1.2f, 1.0f);

  HSLtoRGB(h, s, l, r, g, b);

  glColor3f(r, g, b);
}

void VividPointBrush::RGBtoHSL(float r, float g, float b, float &h, float &s,
                               float &l) {
  float max = std::max({r, g, b});
  float min = std::min({r, g, b});

  l = (max + min) / 2.0f;

  if (max == min) {
    h = s = 0.0f;
  } else {
    float d = max - min;
    s = l > 0.5 ? d / (2.0f - max - min) : d / (max + min);

    if (max == r) {
      h = (g - b) / d + (g < b ? 6.0f : 0.0f);
    } else if (max == g) {
      h = (b - r) / d + 2.0f;
    } else if (max == b) {
      h = (r - g) / d + 4.0f;
    }
    h /= 6.0f;
  }
}

void VividPointBrush::HSLtoRGB(float h, float s, float l, float &r, float &g,
                               float &b) {
  if (s == 0.0f) {
    r = g = b = l;
  } else {
    auto hue2rgb = [](float p, float q, float t) {
      if (t < 0.0f)
        t += 1.0f;
      if (t > 1.0f)
        t -= 1.0f;
      if (t < 1.0f / 6.0f)
        return p + (q - p) * 6.0f * t;
      if (t < 1.0f / 2.0f)
        return q;
      if (t < 2.0f / 3.0f)
        return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
      return p;
    };

    float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
    float p = 2.0f * l - q;

    r = hue2rgb(p, q, h + 1.0f / 3.0f);
    g = hue2rgb(p, q, h);
    b = hue2rgb(p, q, h - 1.0f / 3.0f);
  }
}
