{
  description = "hello";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
    ...
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};
  in {
    devShells."${system}".default = pkgs.mkShell {
      packages = with pkgs; [
        vulkan-tools
        vulkan-loader
        vulkan-headers
        vulkan-validation-layers
        glfw
        glfw-wayland
        wayland
        glm
        shaderc
        libxkbcommon
      ];
    };
  };
}
