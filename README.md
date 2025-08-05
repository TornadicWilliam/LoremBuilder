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
## Usage of the app

- Enter the name or the output file path.
- Example if you want the output file to be saved where the .exe is stored:
```bash
loremfile.txt
```
- Or if you want to store your output file somewhere else?
```bash
D:/your/desired/folder
```
- Now enter the file size:
```bash
600TB (or whatever you want)
``` 
Note: There might be some bugs, please report them by contacting me by the email of dataviation42@gmail.com (old email, but ok) ><

## Contributions

Contributions are highly appreciated! Please, feel free to submit a pull request.
