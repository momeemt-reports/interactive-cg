//=============================================================================
// ファイル: controller.h
//=============================================================================
// スライダコントローラの設定
//=============================================================================

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// ヘッダファイルのインクルード
#include "modelerapp.h"

// フレーム番号の最大値
extern int max_frame_count;

// コントローラ識別用の列挙子
enum CONTROLLERS {

  FRAME_CONTROLS, // フレームコントローラ（変更しないこと)
  // 〜〜〜列挙子を追加〜〜〜
  MARIO_X,
  MARIO_Y,
  MARIO_Z,
  BODY_ANGLE,
  ARM1_ANGLE,
  ARM2_ANGLE,
  FOOT1_ANGLE,
  FOOT2_ANGLE,
  STAR_ANGLE,
  NUM_CONTROLS, // コントローラ数（必ず末尾に追加）
};

// コントローラの設定
// （NUM_CONTROLSを除くCONTROLLERS列挙子と１：１に対応付ける）
void SetController(ModelerControl *controls) {
  // フレーム番号の制御用スライダ
  controls[FRAME_CONTROLS] =
      ModelerControl("Frame Number", 0, (float)max_frame_count, 1, 0);

  // 〜〜〜スライダを追加〜〜〜
  controls[ARM1_ANGLE] =
      ModelerControl("Arm1-Angle", -60.0f, 60.0f, 1.0f, 0.0f);
  controls[ARM2_ANGLE] =
      ModelerControl("Arm2-Angle", -60.0f, 60.0f, 1.0f, 0.0f);
  controls[FOOT1_ANGLE] =
      ModelerControl("Foot1-Angle", -60.0f, 60.0f, 1.0f, 0.0f);
  controls[FOOT2_ANGLE] =
      ModelerControl("Foot2-Angle", -60.0f, 60.0f, 1.0f, 0.0f);
  controls[BODY_ANGLE] =
      ModelerControl("Body-Angle", -60.0f, 60.0f, 1.0f, 0.0f);
  controls[STAR_ANGLE] = ModelerControl("Star-Angle", 0.0f, 360.0f, 1.0f, 0.0f);
  controls[MARIO_X] = ModelerControl("Mario-X", -10.0f, 10.0f, 1.0f, 0.0f);
  controls[MARIO_Y] = ModelerControl("Mario-Y", 0.0f, 10.0f, 1.0f, 3.0f);
  controls[MARIO_Z] = ModelerControl("Mario-Z", -10.0f, 10.0f, 1.0f, 0.0f);
}

// __CONTROLLER_H__
#endif
