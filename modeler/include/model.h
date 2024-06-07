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
#include "controller.h"
#include "modelerdraw.h"

// フレーム番号の最大値
int max_frame_count = 450;

// Modelクラスの定義（ModelerViewクラスを継承）
class Model : public ModelerView {
private:
  // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
  // 第3週課題
  //---------------------------------------------------------------------

  // フレーム番号
  int frame_count;

  //-------------------------------------------------------------------------
  // 制御変数
  //-------------------------------------------------------------------------

  // 〜〜〜変数を追加〜〜〜
  double r, posX, posY;

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
    r = 4.0f;
    posX = r;
    posY = 0.0;

    // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
  }

  // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
  // 第3週課題
  //---------------------------------------------------------------------

  // 自動アニメーションの設定
  void SetAutomaticAnimation() {
    //-----------------------------------------------------------------
    // アニメーション
    //-----------------------------------------------------------------

    // 〜〜〜プログラムを記述〜〜〜
    double theta = frame_count * M_PI / 50;
    posX = r * cos(theta);
    posY = r * sin(theta);

    //-----------------------------------------------------------------
  }

  // 手動アニメーションの設定
  void SetManualAnimation() {
    //-----------------------------------------------------------------
    // アニメーション
    //-----------------------------------------------------------------

    // 〜〜〜プログラムを記述〜〜〜
    double theta = frame_count * M_PI / 50;
    posX = r * cos(theta);
    posY = r * sin(theta);

    //-----------------------------------------------------------------
  }

  // 〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜A

  void drawEye() {
    setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
    drawSphere(0.25);
    glPushMatrix();
    setDiffuseColor(0.2f, 0.1f, 0.0f, 1.0f);
    glTranslated(0.0, 0.2, 0.0);
    drawSphere(0.1);
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

    // 描画開始
    BeginPaint();

    //---------------------------------------------------------------------
    // オブジェクトを描画
    //---------------------------------------------------------------------
    /* setAmbientColor(0.5f, 0.5f, 0.5f); */
    /* setSpecularColor(1.0f, 1.0f, 1.0f); */
    /* setShininess(20.0f); */

    /* glPushMatrix(); */
    /* setDiffuseColor(0.5f, 0.3f, 0.0f, 1.0f); */
    /* drawBox(4, 0.3, 4); */
    /* glTranslated(2, 0, 2); */

    /* glRotated(GetSliderValue(ARM1_ANGLE), 1, 0, 0); */
    /* setDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f); */
    /* drawBox(0.2, 4, 0.2); */
    /* glTranslated(0, 4, 0); */

    /* glRotated(GetSliderValue(ARM2_ANGLE), 1, 0, 0); */
    /* setDiffuseColor(1.0f, 1.0f, 0.0f, 1.0f); */
    /* drawBox(0.2, 2, 0.2); */
    /* glTranslated(-0.5, 2, 0); */

    /* glPushMatrix(); */
    /* setDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f); */
    /* glRotated(GetSliderValue(ARM3_ANGLE), 1, 0, 0); */
    /* drawBox(1, 1, 0.2); */

    /* glPopMatrix(); */
    /* setDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f); */
    /* glRotated(GetSliderValue(ARM4_ANGLE), 1, 0, 0); */
    /* drawBox(1, 1, 0.2); */

    /* glRotated(-60.0f, 1, 0, 0); */
    /* glTranslated(0.0, 0.0, -0.5f); */
    /* glPushMatrix(); */
    /* glTranslated(0.2f, 0.0, 0.0); */
    /* drawEye(); */
    /* glPopMatrix(); */

    /* glTranslated(0.8f, 0.0, 0.0); */
    /* drawEye(); */
    /* glPopMatrix(); */

    glTranslated(posX, posY, 0);
    drawSphere(0.5);
    //---------------------------------------------------------------------

    // 描画終了
    EndPaint();
  }
};

// __MODEL_H__
#endif
