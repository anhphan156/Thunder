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
      shellHook = ''
               #!/usr/bin/env bash

        SOCKET_NAME=VK
              SESSION_NAME=VK
				tmux -L $SOCKET_NAME kill-server
        tmux -L $SOCKET_NAME new-session -d -s $SESSION_NAME
        tmux -L $SOCKET_NAME send-keys -t $SESSION_NAME:0.0 " nvim" Enter
              tmux -L $SOCKET_NAME split-window -v
              tmux -L $SOCKET_NAME select-pane -t 0
              tmux -L $SOCKET_NAME resize-pane -D 6
              tmux -L $SOCKET_NAME attach -t $SESSION_NAME
      '';
    };
  };
}
