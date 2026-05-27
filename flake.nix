{
  # This file configures a environment so Nix based systems can do development
  # on Mina. Simply run 'nix develop' and the nix file will pull all of the
  # dependencies and create a development environment for you.
  inputs.nixpkgs.url = "github:nixos/nixpkgs";

  outputs = { self, nixpkgs }:
  let
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in
  {
    devShells.x86_64-linux.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        cmake
        curl

        qt6.qtbase
        qt6.qtcharts
        qt6.qt5compat
        qt6Packages.qtstyleplugin-kvantum

        # Shell hook.
        qt6.wrapQtAppsHook
        makeWrapper
        bashInteractive
      ];

      shellHook = ''
        bashdir=$(mktemp -d)
        makeWrapper "$(type -p bash)" "$bashdir/bash" "''${qtWrapperArgs[@]}"
        exec "$bashdir/bash"
      '';
    };
  };
}
