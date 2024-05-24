//
// triangleBrush.cpp
//
// The implementation of Triangle Brush. It is a kind of ImpBrush. All your
// brush implementations will look like the file with the different GL primitive
// calls.
//

#include "triangleBrush.h"
#include "OpenGL/OpenGL.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

extern float frand();

TriangleBrush::TriangleBrush(ImpressionistDoc *pDoc, const char *name)
    : ImpBrush(pDoc, name) {}

void TriangleBrush::BrushBegin(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  int size = pDoc->getSize();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPointSize((float)size);

  BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target) {
  ImpressionistDoc *pDoc = GetDocument();
  ImpressionistUI *dlg = pDoc->m_pUI;

  // スライダーつけたあと

  if (pDoc == NULL) {
    printf("PointBrush::BrushMove  document is NULL\n");
    return;
  }

  int size = pDoc->getSize();
  int Ax = target.x - (0.5 * size);
  int Bx = target.x + (0.5 * size);
  int Cx = target.x;
  int Ay = target.y - (0.5 * size);
  int By = target.y - (0.5 * size);
  int Cy = target.y + (0.5 * size);

  // SetColorAlpha( source, alpha );
  SetColor(source);
  glBegin(GL_POLYGON);
  glVertex2i(Ax, Ay);
  glVertex2i(Bx, By);
  glVertex2i(Cx, Cy);
  glEnd();
}

void TriangleBrush::BrushEnd(const Point source, const Point target) {
  // do nothing so far
  glDisable(GL_BLEND);
}
