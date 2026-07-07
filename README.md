# Love Virus

A playful little heart that lives on your desktop — click it to split it into two, watch them bounce and collide, and hear a random sound each time.

## Features
- Transparent, click-through desktop overlay — only the heart itself
  blocks clicks; everywhere else, clicks and keystrokes pass through to
  whatever's behind it
- Click a heart to split it into two, each flying off in a random direction
- Hearts bounce off screen edges and off each other
- A random sound plays every time you click a heart

## Prerequisites
[MSYS2](https://www.msys2.org/), then from an MSYS2 terminal:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-raylib
Make sure `C:\msys64\mingw64\bin` is on your PATH *before* any other gcc install (e.g. Strawberry Perl) — otherwise the build will fail to find raylib's headers.

## Building
From PowerShell, in the project folder:
```powershell
mingw32-make run       # builds and runs, console visible (for debugging)
mingw32-make release   # builds love-virus.exe with no console, for sharing
```

## Adding sounds
`assets/sounds/` holds the `.mp3` files that play on click — one plays at random each time. Personal recordings are excluded via `.gitignore`; only `default.mp3` is tracked in this repo. Drop your own `.mp3` files into that folder before running — they're picked up automatically, no code changes needed.

## Regenerating the heart art (optional)
`tools/generate_heart.py` procedurally generates `assets/sprites/heart.png` from a mathematical heart curve. Requires Python 3 + Pillow (`pip install pillow`) — not needed to build or run the program itself, only if you want to tweak the art. 
python tools/generate_heart.py

## A note on Windows SmartScreen
Since `love-virus.exe` isn't code-signed, Windows may show a "Windows protected
your PC" warning the first time someone runs it. That's expected for an
unsigned indie exe, not a sign anything's wrong — click
**More info → Run anyway**.

## Project structure
Love Virus/
├── src/
│   ├── main.c
│   └── win32_helper.c / .h
├── assets/
│   ├── sprites/heart.png
│   └── sounds/*.mp3
├── tools/
│   └── generate_heart.py
├── resource.rc
├── heart.ico
├── Makefile
└── .gitignore