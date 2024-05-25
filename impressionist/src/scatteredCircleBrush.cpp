//
// triangleBrush.cpp
//
// The implementation of ScatteredCircle Brush. It is a kind of ImpBrush. All
// your brush implementations will look like the file with the different GL
// primitive calls.
//

#include "scatteredCircleBrush.h"
#include "OpenGL/OpenGL.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <math.h>

#define PI 3.1415

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc *pDoc,
                                           const char *name)
    : ImpBrush(pDoc, name) {}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  int size = pDoc->getSize();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPointSize((float)size);

  BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  // スライダーつけたあと

  if (pDoc == NULL) {
    printf("PointBrush::BrushMove  document is NULL\n");
    return;
  }

  int size = pDoc->getSize();
  int scatteringNum = pDoc->getScatteringNum();
  int div = 12;
  float radius = size / 2.0;
  float Ax, Ay;

  // SetColorAlpha( source, alpha );
  SetColor(source);
  for (int n = 0; n < scatteringNum; n++) {
    glBegin(GL_POLYGON);
    float tAx = target.x + rand() % (size * 5);
    float tAy = target.y + rand() % (size * 5);
    for (int i = 0; i < div; i++) {
      Ax = tAx + radius * cos(2 * PI * i / div);
      Ay = tAy + radius * sin(2 * PI * i / div);
      glVertex2f(Ax, Ay);
    }
    glEnd();
  }
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target) {
  // do nothing so far
  glDisable(GL_BLEND);
}
