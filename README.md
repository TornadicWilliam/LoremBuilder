# LoremBuilder

A CLI-based dummy data generator with support for structured file formats, custom folder hierarchies, and time estimation. Designed for performance testing and automation.

## Features

- Supports the following units: B, KB/KiB, MB/MiB, GB/GiB, TB/TiB, PB/PiB, EB/EiB.
- Choose either to store output at where the application is placed on the folder, or the exact folder for file generation.
- Progress bar with real-time stats
- Windows-only app for now.
- Optimized for performance with large file operations.

## Prerequisites

- C++17 compatible complier (MSYS2 / MinGW / MSVC)
- Git for Windows

## Installation guide

- Open PowerShell (Admin).
- Clone this repository:
  ```bash
  git clone https://github.com/TornadicWilliam/LoremBuilder.git
  cd LoremBuilder
  ```
- Build the app:
  ```bash
  g++ -std=c++17 -O2 -o LoremBuilder.exe main.cpp
  ```
- Now directly run it:
  ```bash
  ./LoremBuilder.exe
  ```
## 
