#include <windows.h>
#include "win32_helper.h"

void GetDesktopWorkArea(int *x, int *y, int *width, int *height) {
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    *x = workArea.left;
    *y = workArea.top;
    *width  = workArea.right  - workArea.left;
    *height = workArea.bottom - workArea.top;
}

void GetCursorPositionInWindow(void *windowHandle, int *x, int *y) {
    POINT p;
    GetCursorPos(&p);                        // absolute screen position
    ScreenToClient((HWND)windowHandle, &p);  // convert to window-local
    *x = p.x;
    *y = p.y;
}