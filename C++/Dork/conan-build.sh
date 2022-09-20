#!/bin/sh
conan install sdl/2.24.0@  --build=missing --profile=Debug
conan install sdl/2.24.0@  --build=missing --profile=Release

conan install box2d/2.4.1@  --build=missing --profile=Debug
conan install box2d/2.4.1@  --build=missing --profile=Release
