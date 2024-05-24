{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/23.11";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {
          inherit system;
          config.allowBroken = true;
        };
      in {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            nil
            alejandra
            llvmPackages.clang-unwrapped
            python311Packages.compiledb
            gnumake
            cmake
          ] ++ pkgs.lib.optionals pkgs.stdenv.isDarwin (with pkgs.darwin.apple_sdk.frameworks; [
            ApplicationServices
            Carbon
            Cocoa
            CoreFoundation
            CoreGraphics
            OpenGL
            GLUT
            UniformTypeIdentifiers
          ]);
          LIBC_INCLUDES_FLAGS="-I${pkgs.lib.getDev pkgs.clangStdenv.cc.libc}/include -I${pkgs.llvmPackages.clang-unwrapped.lib}/lib/clang/16/include";
          LIBCPP_INCLUDES_FLAGS="-I${pkgs.llvmPackages.libcxx.dev}/include/c++/v1 -I${pkgs.llvmPackages.libcxxabi.dev}/include/c++/v1";
          FLTK_INCLUDES_DIR="${pkgs.fltk}/include";
          NIX_CFLAGS_COMPILE="-F${pkgs.darwin.apple_sdk.frameworks.CoreFoundation}/Library/Frameworks -F${pkgs.darwin.apple_sdk.frameworks.CoreGraphics}/Library/Frameworks";
          NIX_LDFLAGS="-F${pkgs.darwin.apple_sdk.frameworks.CoreFoundation}/Library/Frameworks -F${pkgs.darwin.apple_sdk.frameworks.CoreGraphics}/Library/Frameworks -framework CoreFoundation -framework CoreGraphics -framework ApplicationServices -framework Carbon -framework Cocoa -framework OpenGL -framework GLUT -framework UniformTypeIdentifiers";
        };
      }
    );
}

