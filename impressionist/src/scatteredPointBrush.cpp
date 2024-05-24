//
// scatteredPointBrush.cpp
//
// The implementation of scattered point Brush. It is a kind of ImpBrush. All
// your brush implementations will look like the file with the different GL
// primitive calls.
//

#include "scatteredPointBrush.h"
#include "OpenGL/OpenGL.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc *pDoc,
                                         const char *name)
    : ImpBrush(pDoc, name) {}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  int size = pDoc->getSize();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPointSize((float)size);

  BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  // スライダーつけたあと

  if (pDoc == NULL) {
    printf("PointBrush::BrushMove  document is NULL\n");
    return;
  }

  int size = pDoc->getSize();
  glPointSize(1.0);
  int Ax, Ay;

  // SetColorAlpha( source, alpha );
  SetColor(source);
  glBegin(GL_POINTS);
  for (int i = 0; i < 10; i++) {
    Ax = target.x - size / 2 + rand() % size;
    Ay = target.y - size / 2 + rand() % size;
    glVertex2i(Ax, Ay);
  }
  glEnd();
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target) {
  // do nothing so far
  glDisable(GL_BLEND);
}
