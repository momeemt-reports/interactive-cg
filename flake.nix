{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/24.05";
    flake-utils.url = "github:numtide/flake-utils";
    flake-compat = {
      url = "github:edolstra/flake-compat";
      flake = false;
    };
  };
  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
        };
        libcIncludeDir =
          if pkgs.stdenv.isDarwin
          then "${pkgs.darwin.Libsystem}/include"
          else "${pkgs.glibc.dev}/include";
        toSingleLine = str: builtins.replaceStrings ["\n"] [" "] str;
      in {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs;
            [
              nil
              alejandra
              llvmPackages.clang-unwrapped
              python311Packages.compiledb
              gnumake
              cmake
              typst
              typstfmt
              typst-lsp
              typst-live
              typst-preview
              xorg.libX11
              xorg.libXext
              xorg.libXrender
              xorg.libXt
              libpng
              libjpeg
              fltk
            ]
            ++ pkgs.lib.optionals pkgs.stdenv.isDarwin (with pkgs.darwin.apple_sdk.frameworks; [
              ApplicationServices
              Carbon
              Cocoa
              CoreFoundation
              CoreGraphics
              OpenGL
              GLUT
              UniformTypeIdentifiers
            ]);

          NIX_CFLAGS_COMPILE = with pkgs;
            toSingleLine ''
              -I${llvmPackages.clang-unwrapped.lib}/lib/clang/16/include
              -I${llvmPackages.libcxx.dev}/include/c++/v1
              -I${llvmPackages.libcxxClang}/resource-root/include
              -I${llvmPackages.libcxxStdenv}
              -I${libpng.dev}/include
              -I${fltk}/include
              -I${libcIncludeDir}
            '';

          NIX_LDFLAGS = with pkgs;
            toSingleLine ''
              -F${darwin.apple_sdk.frameworks.ApplicationServices}/Library/Frameworks
              -F${darwin.apple_sdk.frameworks.CoreFoundation}/Library/Frameworks
              -F${darwin.apple_sdk.frameworks.CoreGraphics}/Library/Frameworks
              -F${darwin.apple_sdk.frameworks.Carbon}/Library/Frameworks
              -F${darwin.apple_sdk.frameworks.Cocoa}/Library/Frameworks
              -F${darwin.apple_sdk.frameworks.OpenGL}/Library/Frameworks
              -F${darwin.apple_sdk.frameworks.GLUT}/Library/Frameworks
              -F${darwin.apple_sdk.frameworks.UniformTypeIdentifiers}/Library/Frameworks
              -framework CoreFoundation
              -framework CoreGraphics
              -framework ApplicationServices
              -framework Carbon
              -framework Cocoa
              -framework OpenGL
              -framework GLUT
              -framework UniformTypeIdentifiers
              -L${libpng}/lib
              -lpng
              -L${fltk}/lib
              -lfltk
              -lfltk_images
              -L${xorg.libX11}/lib
              -lX11
              -lXext
              -ljpeg
              -lfltk_gl
              -lfltk_forms
              -lm
              -lc++
              -lc++abi
            '';
        };
      }
    );
}
