#ifndef WIN32_HELPER_H
#define WIN32_HELPER_H

// Fills in the usable desktop area (screen minus the taskbar).
// Plain ints only — so this header never needs windows.h,
// which means main.c never has to include windows.h either.
void GetDesktopWorkArea(int *x, int *y, int *width, int *height);

// Fills in the current cursor position, translated into the given
// window's client coordinates. Pass raylib's GetWindowHandle() as
// windowHandle. We query Windows directly (not raylib) so this keeps
// working even while mouse passthrough is active.
void GetCursorPositionInWindow(void *windowHandle, int *x, int *y);

#endif