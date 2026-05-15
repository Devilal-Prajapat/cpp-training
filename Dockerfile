FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    gdb \
    cmake \
    ninja-build \
    clang \
    clangd \
    lldb \
    git \
    make \
    pkg-config \
    curl \
    wget \
    unzip \
    zip \
    python3 \
    python3-pip \
    sudo \
    vim \
    nano \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER vscode
WORKDIR /workspace