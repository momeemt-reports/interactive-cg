#set text(font: "Hiragino Kaku Gothic ProN")

#align(center)[
  = GB22401 インタラクティブCG RayTracer課題
]

#v(5pt)
#align(right)[
  202210897 情報科学類 浅田睦葉
]

= 課題概要
配布された途中まで作成されているレイトレーシングのプログラムを完成させ、シーンファイルを作成した。

== 演習問題 3.2
スケルトンに付属する`trans.ray`を`Depth = 2`でレンダリングした画像を以下に示す。

#figure(
  image("./cube.png", width: 50%),
  caption: "trans.rayをDepth = 2でレンダリングした画像",
)

次に、デバッグウインドウでRayの屈折が確認できる画像を示す。

#figure(
  image("./refraction.png", width: 50%),
  caption: "Rayの屈折が確認できる画像",
)

== 演習問題 3.3
`easy5.ray`を`Depth = 10`でレンダリングした画像を以下に示す。

#figure(
  image("./easy.png", width: 50%),
  caption: "easy5.rayをDepth = 10でレンダリングした画像",
)


== 演習問題 3.4
自分のお気に入りのシーンを作成し、レンダリングした画像を以下に示す。

#figure(
  image("./out.png", width: 50%),
  caption: "お気に入りのシーンをレンダリングした画像",
)

空のシーンを作成し、雨粒を模した球体を配置した。
雲を含む画像を用いてテクスチャマッピングを行った。
また、球体の表面には反射率を設定し、球体の内部には屈折率を設定した。
それに加えて、アンチエイリアシングを行い、レンダリングした。

以下に、シーンを描画するために作成したレイファイルを示す。

```
SBT-raytracer 1.0

camera {
	position = (-4,0.8,-6);
	viewdir = (0.6,-0.2,1);
	aspectratio = 1;
	updir = (0,1,0);
}

directional_light {
	direction = (0, 0, 1);
	colour = (1.0, 1.0, 1.0);
}

point_light {
	position = (-1,4,-0.4);
	colour = (1.0,1.0,1.0);
	constant_attenuation_coeff = 0.25;
	linear_attenuation_coeff = 0.003372407;
	quadratic_attenuation_coeff = 0.000045492;	
}

translate(-2,0,0,
 	scale(0.5,
		sphere { 
			material = { 
				diffuse = (0.4,0.4,0.4);
				specular = (0.8,0.8,0.8);
				shininess = 72.4;
			} 
		}))

translate(1,0.5,2,
 	scale(0.5,
		sphere { 
			material = { 
				diffuse = (0.4,0.4,0.4);
				specular = (0.8,0.8,0.8);
				shininess = 72.4;
			} 
		}))

translate(-1,-0.5,1,
 	scale(0.5,
		sphere { 
			material = { 
				diffuse = (0.4,0.4,0.4);
				specular = (0.8,0.8,0.8);
				shininess = 72.4;
			} 
		}))

translate(0,1,-1,
 	scale(0.5,
		sphere { 
			material = { 
				diffuse = (0.4,0.4,0.4);
				specular = (0.8,0.8,0.8);
				shininess = 72.4;
			} 
		}))

translate(2,-1,-2,
 	scale(0.5,
		sphere { 
			material = { 
				diffuse = (0.4,0.4,0.4);
				specular = (0.8,0.8,0.8);
				shininess = 72.4;
			} 
		}))

translate(3,1,3,
 	scale(0.7,
		sphere { 
			material = { 
				diffuse = (0.5,0.5,0.5);
				specular = (0.9,0.9,0.9);
				shininess = 60.0;
			} 
		}))

translate(-3,-1,-3,
 	scale(0.3,
		sphere { 
			material = { 
				diffuse = (0.6,0.6,0.6);
				specular = (0.7,0.7,0.7);
				shininess = 50.0;
			} 
		}))

translate(0,2,4,
 	scale(0.8,
		sphere { 
			material = { 
				diffuse = (0.7,0.7,0.7);
				specular = (0.6,0.6,0.6);
				shininess = 40.0;
			} 
		}))

translate(-4,3,-2,
 	scale(0.4,
		sphere { 
			material = { 
				diffuse = (0.3,0.3,0.3);
				specular = (0.8,0.8,0.8);
				shininess = 70.0;
			} 
		}))

translate(2,-2,5,
 	scale(0.6,
		sphere { 
			material = { 
				diffuse = (0.2,0.2,0.2);
				specular = (0.9,0.9,0.9);
				shininess = 55.0;
			} 
		}))

translate(0,0,6,
	scale(20,
		rotate(1,0,0,3.1415,
    rotate(0,0,1,3.1415,
    rotate(0,1,0,3.1415,
		square { 
			material = { 
				diffuse = map("sora.png");
			}})))))

translate(0,-3.5,3,
	scale(20,
		rotate(1,0,0,1.57,
			square { 
				material = { 
					diffuse = (0.2,0.2,0.2);
					specular = (0.6,0.6,0.6);
					shininess = 35.4;
			}})))

translate(3.5,0,0,
	scale(20,
		rotate(0,1,0,-1.57,
			square { 
				material = { 
					diffuse = map("sora.png");
			}})))

translate(-4.5,0,0,
	scale(20,
		rotate(0,1,0,1.57,
			square { 
				material = { 
					diffuse = map("sora.png");
			}})))

translate(0,4.5,3,
	scale(20,
		rotate(1,0,0,1.57,
			square { 
				material = { 
					diffuse = (0,0.412,0.667);
					specular = (0.6,0.6,0.6);
					shininess = 35.4;
			}})))

translate(0,0,-6,
	scale(20,
		rotate(1,0,0,3.1415,
		square { 
			material = { 
				diffuse = (0,0.412,0.667);
			}})))
```

== 演習問題 3.5
工夫した点や追加した機能について説明する。

=== テクスチャマッピングの実装
シーンファイルにおいて、雲を含む画像をテクスチャマッピングすることで、壁の表面に雲のような模様を描画した。

```cpp
Vec3d TextureMap::getMappedValue(const Vec2d &coord) const {
  return getPixelAt(coord[0] * width, coord[1] * height);
}
```

`getPixelAt`関数は、テクスチャファイルの座標を受け取り、その座標に対応する色を返す関数である。
`getMappedValue`関数からこの関数を呼び出すことで、テクスチャマッピングを実装した。

=== アンチエイリアシングの実装
アンチエイリアシングを実装することで、レンダリング画像のジャギーを軽減した。

```cpp
Vec3d RayTracer::trace(double x, double y) {
  // Clear out the ray cache in the scene for debugging purposes,
  scene->intersectCache.clear();

  ray r(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);

  scene->getCamera().rayThrough(x, y, r);
  Vec3d ret = traceRay(r, Vec3d(1.0, 1.0, 1.0), 0);
  ret.clamp();

  if ( traceUI->getAntiAliasingEnabled() ) {
    double gridsize = 0.5;

    double x_right = x + gridsize / double(buffer_width);
    if (x_right > 1) {
      x_right = 1;
    }

    double x_left = x - gridsize / double(buffer_width);
    if (x_left < 0) {
      x_left = 0;
    }

    double y_up = y + gridsize / double(buffer_height);
    if (y_up > 1) {
      y_up = 1;
    }

    double y_down = y - gridsize / double(buffer_height);
    if (y_down < 0) {
      y_down = 0;
    }

    ray AA1(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
    scene->getCamera().rayThrough(x_right, y_up, AA1);
    Vec3d retAA1 = traceRay(AA1, Vec3d(1.0, 1.0, 1.0), 0);
    retAA1.clamp();

    ray AA2(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
    scene->getCamera().rayThrough(x_right, y_down, AA2);
    Vec3d retAA2 = traceRay(AA2, Vec3d(1.0, 1.0, 1.0), 0);
    retAA2.clamp();

    ray AA3(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
    scene->getCamera().rayThrough(x_left, y_up, AA3);
    Vec3d retAA3 = traceRay(AA3, Vec3d(1.0, 1.0, 1.0), 0);
    retAA3.clamp();

    ray AA4(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
    scene->getCamera().rayThrough(x_left, y_down, AA4);
    Vec3d retAA4 = traceRay(AA4, Vec3d(1.0, 1.0, 1.0), 0);
    retAA4.clamp();

    ray AA5(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
    scene->getCamera().rayThrough(x_right, y, AA5);
    Vec3d retAA5 = traceRay(AA5, Vec3d(1.0, 1.0, 1.0), 0);
    retAA5.clamp();

    ray AA6(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
    scene->getCamera().rayThrough(x_left, y, AA6);
    Vec3d retAA6 = traceRay(AA6, Vec3d(1.0, 1.0, 1.0), 0);
    retAA6.clamp();

    ray AA7(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
    scene->getCamera().rayThrough(x, y_up, AA7);
    Vec3d retAA7 = traceRay(AA7, Vec3d(1.0, 1.0, 1.0), 0);
    retAA7.clamp();

    ray AA8(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
    scene->getCamera().rayThrough(x, y_down, AA8);
    Vec3d retAA8 = traceRay(AA8, Vec3d(1.0, 1.0, 1.0), 0);
    retAA8.clamp();

    ret = (ret + retAA1 + retAA2 + retAA3 + retAA4 + retAA5 + retAA6 + retAA7 +
          retAA8) /
          9.0;
  }

  return ret;
}
```

表示解像度よりも小さなグリッドを設定し、各グリッドの中心をサンプリングすることで、アンチエイリアシングを実装した。
また、メインUIにアンチエイリアシングのオプションを追加し、ユーザがチェックボックスをクリックすることでオン・オフを切り替えられるようにした。
