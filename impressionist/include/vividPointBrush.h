#ifndef VIVIDPOINTBRUSH_H
#define VIVIDPOINTBRUSH_H

#include "impBrush.h"

class VividPointBrush : public ImpBrush {
public:
  VividPointBrush(ImpressionistDoc *pDoc = NULL, const char *name = NULL);

  void BrushBegin(const Point source, const Point target);
  void BrushMove(const Point source, const Point target);
  void BrushEnd(const Point source, const Point target);

private:
  void SetVividColor(const Point source);
  void RGBtoHSL(float r, float g, float b, float &h, float &s, float &l);
  void HSLtoRGB(float h, float s, float l, float &r, float &g, float &b);
};

#endif
