#set text(font: "Hiragino Kaku Gothic ProN")

#align(center)[
  = GB22401 インタラクティブCG Impressionist課題
]

#v(5pt)
#align(right)[
  202210897 情報科学類 浅田睦葉
]

== 課題1
本課題は、インターネットから入手した画像に対して、以下のブラシを用いた動作例の結果画像と、そのブラシによる効果を示した画像を挙げるものである。

- Scattered Circle Brush
- 独自に実装した、Vivid Scattered Line Brush

=== Scattered Circle Brush
まずは、以下に編集前の元画像を示す。元画像は、線香花火をしている人物が撮影された画像である。

#figure(
  image("./fig/hanabi.jpg", width: 70%),
  caption: "編集前の元画像",
);

==== 結果画像
以下に、Scattered Circle Brushを用いて編集した画像の結果を示す。

#figure(
  image("./fig/scattered-circle-brush-result.png", width: 70%),
  caption: "Scattered Circle Brushを用いて編集した画像",
)

まずキャンバスに画像をコピーし、その後ブラシを使って編集した。
円のサイズ（`size`）を10、円の個数（`scatteredNum`）を10に設定した。
また、円の色はマウスで選択したピクセルの色を、円の半径は（`size`） になるように実装で固定している。

==== 効果を示した画像
次に、Scattered Circle Brushの効果が分かる画像を下記に示す。

#figure(
  image("./fig/scattered-circle-brush.png", width: 70%),
  caption: "Scattered Circle Brushの効果が分かる画像",
)

こちらではキャンバスに画像をコピーせず、4通りのパラメータでブラシ編集を行った。
パラメータは以下の通りである。

- 左上
  - `size = 25`
  - `scatteredNum = 100`
- 右上
  - `size = 20`
  - `scatteredNum = 10`
- 左下
  - `size = 10`
  - `scatteredNum = 10`
- 右下
  - `size = 40`
  - `scatteredNum = 10`

=== Vivid Scattered Line Brush
独自に実装したブラシである、Vivid Scattered Line Brushについて説明する。
授業で実装したLine Brushに対して、ランダムに周囲に複数の線を描画するように書き換え（Scttered）、元画像から得られた色を鮮やかにする（Vivid）機能を持つブラシである。

具体的には、得られた色をRGB形式からHSL形式に変更し、彩度を最大にし、輝度を1.2倍してから、HSL形式からRGB形式に戻している。

```cpp
void VividScatteredLineBrush::SetVividColor(const Point source) {
  ImpressionistDoc *pDoc = GetDocument();
  GLubyte color[3];

  memcpy(color, pDoc->GetOriginalPixel(source), 3);

  float r = color[0] / 255.0f;
  float g = color[1] / 255.0f;
  float b = color[2] / 255.0f;

  float h, s, l;
  RGBtoHSL(r, g, b, h, s, l);

  s = 1.0f;
  l = std::min(l * 1.2f, 1.0f);

  HSLtoRGB(h, s, l, r, g, b);

  glColor3f(r, g, b);
}
```

==== 結果画像
以下に、Vivid Scattered Line Brushを用いて編集した画像の結果を示す。

#figure(
  image("./fig/line.png", width: 70%),
  caption: "Vivid Scattered Line Brushを用いて編集した画像",
)

キャンバスに画像をコピーせず、線香花火の近くではサイズ（`size`）を2に、人や背景などの近くではサイズ（`size`）を7に設定した。また、線の個数（`scatteredNum`）はどちらも20に設定した。線の角度（`angle`）は55に設定した。

線香花火の近くでは細かい線が描かれるように設定しており、リアルな印象絵のように編集することができた。

==== 効果を示した画像
次に、Vivid Scattered Line Brushの効果が分かる画像を下記に示す。

#figure(
  image("./fig/ship.png", width: 70%),
  caption: "Vivid Scattered Line Brushの効果が分かる画像",
)

こちらはインターネットからダウンロードした画像ではなく、ソフトウェアに元々含まれていた船の画像であるが、花火の画像と比較して効果がわかりやすかったため採用した。

元画像はくすんだ青い海、淡い水色の空によって構成されているが、ブラシ編集の結果、鮮やかな水色、青に変わっていることがわかる。
この画像はサイズ（`size`）を7に、線の角度（`angle`）を55に、線の個数（`scatteredNum`）を20に設定した。

== 課題2
本課題は、インターネットから入手した画像に対して以下のフィルタリングを行い、その際のフィルタカーネルの値を示すものである。また、フィルタリングの結果、画像がどう変化したかを説明した。

- Sobel横フィルタ
- 自分で設定した、ガウシアンフィルタ

=== Sobel横フィルタ
以下に、Sobel横フィルタをかけた結果を示す。

#figure(
  image("./fig/sobel.png", width: 70%),
  caption: "Sobel横フィルタ",
)

フィルタカーネルは以下の通りである。また、全体は1で割るように、オフセットは3に設定している。

```
[
  [-1, 0, 1],
  [-2, 0, 2],
  [-1, 0, 1],
]
```

Sobel横フィルタを適用した結果、画像の水平方向のエッジを強調した。これにより、花火の画像内に存在するエッジの検出をすることができ、人や火花の輪郭が鮮明になった。

=== ガウシアンフィルタ
以下に、自分で設定したフィルタであるガウシアンフィルタをかけた結果を示す。

#figure(
  image("./fig/gauss.png", width: 70%),
  caption: "ガウシアンフィルタ",
)

フィルタカーネルは以下の通りである。また、全体は256で割るように、オフセットは0に設定している。

```
[
  [1, 4, 6, 4, 1],
  [4, 16, 24, 16, 4],
  [6, 24, 36, 24, 6],
  [4, 16, 24, 16, 4],
  [1, 4, 6, 4, 1],
]
```

ガウシアンフィルタを適用した結果、画像がぼけた。これは、周囲のピクセルを距離に応じて平均化しているためで、画像に含まれているノイズを軽減することができた。

== 課題3
以下に、コンテストに提出するために用いたオリジナルの画像と、実際に提出した編集済みの画像を示す。

#figure(
  image("./fig/ajisai.jpg", width: 70%),
  caption: "元画像",
)

#figure(
  image("./fig/submitted.png", width: 70%),
  caption: "コンテストに提出した画像",
)

この画像は、Vivid Scattered Line BrushとScattered Point Brushを組み合わせて編集した。
中心に近づくにつれて線のサイズ（`size`）を細かくし、外側に行くにつれて線のサイズを大きくすることで印象派の絵画に近いタッチを行った。これにより、人のような細かい造形は鮮明に描写され、背景は粗くぼんやりとした描写になるので、コントラストを出すことができた。
