//
// triangleBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your
// brush implementations will look like the file with the different GL primitive
// calls.
//

#include "lineBrush.h"
#include "OpenGL/OpenGL.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <math.h>

#define PI 3.1415

extern float frand();

LineBrush::LineBrush(ImpressionistDoc *pDoc, const char *name)
    : ImpBrush(pDoc, name) {}

void LineBrush::BrushBegin(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  int size = pDoc->getSize();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPointSize((float)size);

  BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  // スライダーつけたあと

  if (pDoc == NULL) {
    printf("PointBrush::BrushMove  document is NULL\n");
    return;
  }

  int size = pDoc->getSize();
  int angle = pDoc->getAngle();
  float Ax = target.x + size * cos(PI * angle / 180);
  float Ay = target.y + size * sin(PI * angle / 180);
  float Bx = target.x - size * cos(PI * angle / 180);
  float By = target.y - size * sin(PI * angle / 180);

  // SetColorAlpha( source, alpha );
  SetColor(source);
  glBegin(GL_LINES);
  glVertex2f(Ax, Ay);
  glVertex2f(Bx, By);
  glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target) {
  // do nothing so far
  glDisable(GL_BLEND);
}
