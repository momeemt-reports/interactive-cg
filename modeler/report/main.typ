#set text(font: "Hiragino Kaku Gothic ProN")

#align(center)[
  = GB22401 インタラクティブCG Modeler課題
]

#v(5pt)
#align(right)[
  202210897 情報科学類 浅田睦葉
]

== 課題概要
本課題では、以下の要件を満たした階層的モデリング・アニメーションを作成することである。

- 全体で7種類以上のプリミティブを組み込む
- 各部位が動く3階層以上の階層構造を組み込む
- モデルをフレーム番号のスライダと対応付け、アニメーションで動くようにする

=== 作成したモデル
以下に、作成したモデルを示す。完全なアニメーションについてはGoogle Classroomで別途提出する。

#figure(
  image("./fig/model.png", width: 50%),
  caption: "作成したモデル",
)

モデルはスーパーマリオをモチーフにしており、以下のプリミティブを組み込んでいる。

- box
  - 床の描画に利用している
  - マリオを構成する各プリミティブの作成に利用している
- star
  - OpenGLで作成した星型のプリミティブ
  - 床の模様として利用している
- cap
  - マリオの帽子を構成するプリミティブ
  - boxを組み合わせることで作成している
- head
  - マリオの頭を構成するプリミティブ
  - boxを組み合わせることで作成している
- arm
  - マリオの腕を構成するプリミティブ
  - boxを組み合わせることで作成している
- body
  - マリオの体を構成するプリミティブ
  - boxを組み合わせることで作成している
- foot
  - マリオの足を構成するプリミティブ
  - boxを組み合わせることで作成している

このモデルは以上7種類によって構成されている。なお、実装としては既存のプリミティブとしてcylinder、sphere、triangleの3種類が加えて含まれている。

=== 3階層以上の階層構造
作成したモデルは、以下の3階層以上の階層構造を持っている。

- マリオ全体
  - マリオの顔（`head`）
    - マリオの帽子（`cap`）
  - マリオの身体（`body`）
    - マリオの腕（`arm`）
    - マリオの足（`foot`）

これらは親のオブジェクトの回転・移動・拡大縮小が子にも反映される。マリオ全体〜マリオの帽子、マリオ全体〜マリオの腕、足がそれぞれ3階層の階層構造を持っている。

#figure(
  image("./fig/move.png", width: 50%),
  caption: "手や足を振って歩いている様子",
)

=== スライダと対応付け、アニメーションで動くようにする
作成したモデルは、フレーム番号のスライダと対応付け、アニメーションで動くようにしている。具体的には、マリオの手や足を振って歩いている様子を表現している。

```cpp
enum CONTROLLERS {
  FRAME_CONTROLS,
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
void SetController(ModelerControl *controls) {
  controls[FRAME_CONTROLS] =
      ModelerControl("Frame Number", 0, (float)max_frame_count, 1, 0);

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
```

上記のコードによって、マリオの座標、マリオの体の角度、マリオの手や足の角度、床の星の模様の角度がスライダに対応づけられている。

```cpp
void SetAutomaticAnimation() {
  double t = frame_count / 30.0;
  double run_distance = t * 0.8;

  const double PI = 3.14159;

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

  if (frame_count >= 150) {
    double jump_height = 1.0 * sin((t - 5.0) * 3.14159);
    SetSliderValue(MARIO_Y, 2.5 + jump_height);
  } else {
    SetSliderValue(MARIO_Y, 2.5);
  }
}

void SetManualAnimation() { SetAutomaticAnimation(); }
```

また、上記のコードによってアニメーションを実装している。
マリオの手や足の角度、マリオの体の角度、マリオの座標、床の星の模様の角度がフレーム番号に応じて変化するように設定している。
マリオの腕は45度、足は30度、体は10度、星の模様は360度の振幅で変化するようにした。
マリオのY座標は1.0の振幅で3秒ごとに変化するように設定することで、ジャンプモーションを表現している。
手動アニメーションでも同等のコードを呼び出すことで変更できるようにしている。
