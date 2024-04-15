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
        };
      in {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            nil
            alejandra
            llvmPackages.clang-unwrapped
            python311Packages.compiledb
            fltk
          ];
          LIBC_INCLUDES_FLAGS="-I${pkgs.lib.getDev pkgs.clangStdenv.cc.libc}/include -I${pkgs.llvmPackages.clang-unwrapped.lib}/lib/clang/16/include";
          LIBCPP_INCLUDES_FLAGS="-I${pkgs.llvmPackages.libcxx.dev}/include/c++/v1 -I${pkgs.llvmPackages.libcxxabi.dev}/include/c++/v1";
        };
      }
    );
}

