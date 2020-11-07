FROM gitpod/workspace-full

RUN sudo apt-get update \
    && sudo apt-get dist-upgrade -y \
    && sudo apt-get install -y \
        strace netcat-openbsd \
    && sudo rm -rf /var/lib/apt/lists/* \
    && brew update \
    && brew upgrade \
    && brew install \
        lazygit \

# Install custom tools, runtimes, etc.
# For example "bastet", a command-line tetris clone:
# RUN brew install bastet
#
# More information: https://www.gitpod.io/docs/config-docker/
