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

工夫した点としては、OpenGLの図形描画関数を利用して作成した星型のプリミティブが挙げられる。
以下のように実装した。

```cpp
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
```

`drawStar`関数は、中心座標と半径を受け取り、中心座標を中心に半径を持つ星型を描画する関数である。
具体的には、中心座標を中心に半径を持つ円周上の点を交互に結んでいくことで星型を描画している。

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

スライダーの制御内容について説明する。

- `FRAME_CONTROLS`
  - フレーム番号を制御するスライダ
- `MARIO_X`
  - マリオのX座標を制御するスライダ
- `MARIO_Y`
  - マリオのY座標を制御するスライダ
- `MARIO_Z`
  - マリオのZ座標を制御するスライダ
- `BODY_ANGLE`
  - マリオの体の角度を制御するスライダ
- `ARM1_ANGLE`
  - マリオの右腕の角度を制御するスライダ
- `ARM2_ANGLE`
  - マリオの左腕の角度を制御するスライダ
- `FOOT1_ANGLE`
  - マリオの右足の角度を制御するスライダ
- `FOOT2_ANGLE`
  - マリオの左足の角度を制御するスライダ
- `STAR_ANGLE`
  - 床の星の模様の角度を制御するスライダ

```cpp
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
```

また、上記のコードによってアニメーションを実装している。
マリオの手や足の角度、マリオの体の角度、マリオの座標、床の星の模様の角度がフレーム番号に応じて変化するように設定している。
マリオの腕は45度、足は30度、体は10度、星の模様は360度の振幅で変化するようにした。
マリオのY座標は1.0の振幅で3秒ごとに変化するように設定することで、ジャンプモーションを表現している。
手動アニメーションでも同等のコードを呼び出すことで変更できるようにしている。

=== 工夫した点
最低要件を満たすだけでなく、いくつかの工夫を行った。

==== ドリーの実装
マリオが走るアニメーションを再生する前に、カメラがマリオに向かってドリーするように実装した。
具体的には、`SetAutomaticAnimation`関数内で`dolly`変数を用いてカメラの位置を変更している。

150フレームまでは、`dolly = 150 - frame_count`としてカメラの位置を遠くから近くに移動させるための値を設定している。

```cpp
void SetAutomaticAnimation() {
  const double PI = 3.14159;

  if (frame_count >= 150) {
    // 中略
  } else {
    SetSliderValue(MARIO_Y, 3.0);
    dolly = 150 - frame_count;
  }
}
```

その後、y軸とz軸において`dolly`変数の値を加算することで、カメラの位置を遠くから近くに移動させている。

```cpp
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0, 15.0 + dolly, 15.0 + dolly, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
```

==== 複数体のマリオを描画
複数体のマリオが床に並んでいるような構図を描画するために、マリオの描画をループで複数回行うようにした。
また、`z_correction`変数を用いて、マリオの位置が偶数の場合に半分だけz軸方向にずらすことで、複雑な構図になるようにした。

```cpp
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
    // ... （省略）
  }
}
```
