#!/bin/sh
conan install sdl/2.24.0@  --build=missing --profile=Debug
conan install sdl/2.24.0@  --build=missing --profile=Release

conan install box2d/2.4.1@  --build=missing --profile=Debug
conan install box2d/2.4.1@  --build=missing --profile=Release

conan install imgui/1.88@  --build=missing --profile=Debug
conan install imgui/1.88@  --build=missing --profile=Release

conan install glm/0.9.9.8@  --build=missing --profile=Debug
conan install glm/0.9.9.8@  --build=missing --profile=Release
