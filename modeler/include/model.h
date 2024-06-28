//=============================================================================
// ファイル: model.h
//=============================================================================
// モデルの設定・描画を制御
//=============================================================================

#ifndef __MODEL_H__
#define __MODEL_H__

// ヘッダファイルのインクルード
#include "OpenGL/OpenGL.h"
#include "animator.h"
#include "camera.h"
#include "controller.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include "particleSystem.h"
#include <FL/glu.h>

// フレーム番号の最大値
int max_frame_count = 450;

// Modelクラスの定義（ModelerViewクラスを継承）
class Model : public ModelerView {
private:
  // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
  // 第3週課題
  //---------------------------------------------------------------------

  int frame_count;

  //-------------------------------------------------------------------------
  // 制御変数
  //-------------------------------------------------------------------------

  // 〜〜〜変数を追加〜〜〜
  double dolly;

  // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

public:
  // コンストラクタ（スーパークラスのコンストラクタを呼び出す）
  Model(int x, int y, int w, int h, char *label)
      : ModelerView(x, y, w, h, label) {
    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
    // 第3週課題
    //---------------------------------------------------------------------

    // フレーム番号の初期化
    frame_count = 0;

    //---------------------------------------------------------------------
    // 初期化
    //---------------------------------------------------------------------

    // 〜〜〜変数を初期化〜〜〜
    dolly = 0.0;

    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
  }

  // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
  // 第3週課題
  //---------------------------------------------------------------------

  void SetAutomaticAnimation() {
    const double PI = 3.14159;

    if (frame_count >= 150) {
      double local_frame_count = frame_count - 150;
      double t = local_frame_count / 30.0;
      double run_distance = t * 0.8;

      double jump_height = 1.0 * sin((t - 5.0) * 3.14159);
      SetSliderValue(MARIO_Y, 3.0 + jump_height);

      double arm_angle = 45.0 * sin(t * 4.0 * PI);
      double foot_angle = 30.0 * sin(t * 4.0 * PI);
      double body_angle = 10.0 * sin(t * 4.0 * PI);
      double star_angle = 360.0 * sin(t * 0.2 * PI);

      SetSliderValue(MARIO_X, run_distance);
      SetSliderValue(ARM1_ANGLE, arm_angle);
      SetSliderValue(ARM2_ANGLE, -arm_angle);
      SetSliderValue(FOOT1_ANGLE, foot_angle);
      SetSliderValue(FOOT2_ANGLE, -foot_angle);
      SetSliderValue(BODY_ANGLE, body_angle);
      SetSliderValue(STAR_ANGLE, star_angle);
    } else {
      SetSliderValue(MARIO_Y, 3.0);
      dolly = 150 - frame_count;
    }
  }

  // 手動アニメーションの設定
  void SetManualAnimation() { SetAutomaticAnimation(); }

  // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

  void setDiffuseColorRGB(int r, int g, int b) {
    setDiffuseColor((double)r / 255.0, (double)g / 255.0, (double)b / 255.0,
                    1.0f);
  }

  void drawStar(float centerX, float centerY, float radius) {
    const int numVertices = 10;
    const float angleStep = M_PI / 5;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY);
    for (int i = 0; i <= numVertices; ++i) {
      float angle = i * angleStep;
      float r = (i % 2 == 0) ? radius : radius / 2;
      float x = centerX + r * cos(angle);
      float y = centerY + r * sin(angle);
      glVertex2f(x, y);
    }
    glEnd();
  }

  void drawCap() {
    setDiffuseColorRGB(238, 23, 17);
    drawBox(2.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslated(-0.5f, -0.5f, 0.0f);
    drawBox(5.0f, 0.5f, 0.5f);
    glPopMatrix();
  }

  void drawHead() {
    setDiffuseColorRGB(122, 109, 14);
    drawBox(1.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslated(1.5f, -2.0f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(1.0f, 2.5f, 0.5f);
    glTranslated(1.0f, 1.5f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(0.5f, 1.0f, 0.5f);
    glTranslated(0.5f, 0.5f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(0.5f, 0.5f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.5f, -1.5f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(0.5f, 1.5f, 0.5f);
    glTranslated(0.5f, 0.5f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(0.5f, 1.0f, 0.5f);
    glTranslated(0.5f, 0.0f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(0.5f, 1.0f, 0.5f);
    glTranslated(0.5f, 0.5f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(2.0f, 0.0f, 0.0f);
    drawBox(1.5f, 0.5f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.0f, -1.0f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(1.5f, 0.0f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.5f, 0.0f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.5f, 0.0f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(1.5f, 0.5f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0f, -1.5f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.5f, -0.5f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(2.0f, 1.0f, 0.5f);
    glTranslated(2.0f, 0.5f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(2.0f, 0.5f, 0.5f);
    glTranslated(0.0f, -0.5f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(1.5f, 0.5f, 0.5f);
    glPopMatrix();
  }

  void drawBody() {
    glPushMatrix();
    glTranslated(0.0f, -1.5f, 0.0f);
    setDiffuseColorRGB(238, 23, 17);
    drawBox(0.5f, 1.5f, 0.5f);
    glTranslated(0.5f, 0.0f, 0.0f);
    drawBox(1.5f, 0.5f, 0.5f);
    glTranslated(1.0f, 0.5f, 0.0f);
    drawBox(0.5f, 1.0f, 0.5f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(-1.0f, 1.0f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.5f, -2.0f, 0.0f);
    setDiffuseColorRGB(238, 23, 17);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.5f, 0.0f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.5f, 0.0f, 0.0f);
    setDiffuseColorRGB(238, 23, 17);
    drawBox(1.0f, 0.5f, 0.5f);
    glTranslated(1.0f, 0.0f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.5f, 0.0f, 0.0f);
    setDiffuseColorRGB(238, 23, 17);
    drawBox(0.5f, 0.5f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.5f, -2.5f, 0.0f);
    drawBox(3.0f, 0.5f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-1.0f, -3.5f, 0.0f);
    drawBox(1.5f, 1.0f, 0.5f);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5f, -3.5f, 0.0f);
    drawBox(1.5f, 1.0f, 0.5f);
    glPopMatrix();
  }

  void drawArm() {
    glPushMatrix();
    glTranslated(-2.0f, -1.5f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.0f, -1.5f, 0.0f);
    setDiffuseColorRGB(254, 175, 23);
    drawBox(1.0f, 1.5f, 0.5f);
    glTranslated(1.0f, 0.5f, 0.0f);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.0f, 0.5f, 0.0f);
    setDiffuseColorRGB(122, 109, 14);
    drawBox(0.5f, 0.5f, 0.5f);
    glTranslated(0.0f, 0.5f, 0.0f);
    drawBox(1.0f, 1.5f, 0.5f);
    drawBox(-0.5f, 1.0f, 0.5f);
    glPopMatrix();
  }

  void drawFoot() {
    glPushMatrix();
    setDiffuseColorRGB(122, 109, 14);
    drawBox(-1.5f, -0.5f, 0.5f);
    glTranslated(0.0f, -0.5f, 0.0f);
    drawBox(-2.0f, -0.5f, 0.5f);
    glPopMatrix();
  }

  // 描画の前処理
  void BeginPaint() {
    // 半透明処理を有効化
    glEnable(GL_BLEND);
    // 混合方法の指定
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  // 描画の後処理
  void EndPaint() {
    // 半透明処理を無効化
    glDisable(GL_BLEND);
  }

  // オブジェクトの描画
  void draw() {
    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
    // 第3週課題
    //---------------------------------------------------------------------
    // 自動アニメーションの処理
    if (IsAutomaticAnimation() && frame_count < max_frame_count) {
      // フレーム番号の更新
      SetSliderValue(FRAME_CONTROLS, ++frame_count);
      // 自動アニメーション
      SetAutomaticAnimation();
    }
    // 手動アニメーションの処理
    else {
      // フレーム番号を取得
      frame_count = (int)GetSliderValue(FRAME_CONTROLS);
      // 手動アニメーション
      SetManualAnimation();
    }
    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

    // スーパークラスの描画メソッドをコール（必須）
    ModelerView::draw();
    ParticleSystem *ps = ModelerApplication::Instance()->GetParticleSystem();
    Mat4f CameraTransforms = ps->getModelViewMatrix();

    // 描画開始
    BeginPaint();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 15.0 + dolly, 15.0 + dolly, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    setDiffuseColor(0.5f, 0.3f, 0.0f, 1.0f);
    glTranslated(-20, -5, -20);
    drawBox(100, 0.2, 100);
    glPopMatrix();

    setDiffuseColor(1.0f, 0.3f, 0.0f, 1.0f);
    for (int x = -3; x <= 3; x++) {
      for (int z = -3; z <= 3; z++) {
        glPushMatrix();
        glTranslated(x * 8, -4, z * 8);
        glRotated(GetSliderValue(STAR_ANGLE), 0, 0, 1);
        drawStar(0, 0, 1.0);
        glPopMatrix();
      }
    }

    /* //---------------------------------------------------------------------
     */
    /* // オブジェクトを描画 */
    /* //---------------------------------------------------------------------
     */

    for (int x = -3; x <= 3; x++) {
      for (int z = -3; z <= 3; z++) {
        double z_correction = 0.0;
        if (x % 2 == 0) {
          z_correction = 4.0;
        }
        glPushMatrix();
        glTranslated(GetSliderValue(MARIO_X) + x * 8, GetSliderValue(MARIO_Y),
                     GetSliderValue(MARIO_Z) + z * 8 + z_correction);
        drawCap();
        glTranslated(-0.5f, -1.0f, 0.0);
        drawHead();
        glTranslated(1.0f, -2.0f, 0.0f);

        glRotated(GetSliderValue(BODY_ANGLE), 0, 0, 1);

        glPushMatrix();
        glRotated(GetSliderValue(ARM1_ANGLE), 0, 0, 1);
        drawArm();
        glPopMatrix();

        glTranslated(2.0f, 0.0f, 0.5f);

        glPushMatrix();
        glRotated(180.0f, 0, 1, 0);
        glRotated(GetSliderValue(ARM2_ANGLE), 0, 0, 1);
        drawArm();
        glPopMatrix();

        glTranslated(-2.0f, 0.0f, -0.5f);
        drawBody();
        glTranslated(1.5f, -3.5f, 0.5f);

        glPushMatrix();
        glRotated(GetSliderValue(FOOT1_ANGLE), 0, 0, 1);
        glRotated(180.0f, 0, 1, 0);
        drawFoot();
        glPopMatrix();

        glTranslated(-2.5f, 0.0f, 0.0f);

        glPushMatrix();
        glRotated(GetSliderValue(FOOT2_ANGLE), 0, 0, 1);
        glRotated(180.0f, 0, 1, 0);
        drawFoot();
        glPopMatrix();
        glPopMatrix();
      }
    }

    // ps->SpawnParticles(CameraTransforms);

    //---------------------------------------------------------------------

    // 描画終了
    EndPaint();
  }
};
#endif
