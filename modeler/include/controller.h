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
  ARM1_ANGLE,
  ARM2_ANGLE,
  ARM3_ANGLE,
  ARM4_ANGLE,
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
      ModelerControl("Arm1-Angle", -60.0f, 60.0f, 1.0f, 30.0f);
  controls[ARM2_ANGLE] =
      ModelerControl("Arm2-Angle", 20.0f, 160.0f, 1.0f, 90.0f);
  controls[ARM3_ANGLE] =
      ModelerControl("Arm3-Angle", -60.0f, 60.0f, 1.0f, -30.0f);
  controls[ARM4_ANGLE] =
      ModelerControl("Arm4-Angle", -60.0f, 60.0f, 1.0f, 30.0f);
}

// __CONTROLLER_H__
#endif
