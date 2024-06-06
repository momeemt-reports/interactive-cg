{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/23.11";
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
          config.allowBroken = true;
        };
        libcIncludeDir =
          if pkgs.stdenv.isDarwin
          then "${pkgs.darwin.Libsystem}/include"
          else "${pkgs.glibc.dev}/include";
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
          FLTK_INCLUDES_DIR = "${pkgs.fltk}/include";
          NIX_CFLAGS_COMPILE = "-F${pkgs.darwin.apple_sdk.frameworks.CoreFoundation}/Library/Frameworks -F${pkgs.darwin.apple_sdk.frameworks.CoreGraphics}/Library/Frameworks -I${pkgs.lib.getDev pkgs.clangStdenv.cc.libc}/include -I${pkgs.llvmPackages.clang-unwrapped.lib}/lib/clang/16/include -I${libcIncludeDir} -I${pkgs.llvmPackages.libcxx.dev}/include/c++/v1 -I${pkgs.llvmPackages.libcxxabi.dev}/include/c++/v1 -I${pkgs.libpng.dev}/include -I${pkgs.xorg.libX11.dev}/include -I${pkgs.libjpeg.dev}/include";
          NIX_LDFLAGS = "-F${pkgs.darwin.apple_sdk.frameworks.CoreFoundation}/Library/Frameworks -F${pkgs.darwin.apple_sdk.frameworks.CoreGraphics}/Library/Frameworks -framework CoreFoundation -framework CoreGraphics -framework ApplicationServices -framework Carbon -framework Cocoa -framework OpenGL -framework GLUT -framework UniformTypeIdentifiers -L${pkgs.libpng}/lib -lpng -L${pkgs.xorg.libX11}/lib -lX11 -L${pkgs.libjpeg}/lib -ljpeg";
        };
      }
    );
}
