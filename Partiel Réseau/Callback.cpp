#include "Callback.h"

LRESULT CALLBACK Callback::ServWinProc(HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam) {
    SOCKET Accept;
    switch (wMsg)
    {
    case WM_SOCKET:
        if (WSAGETSELECTERROR(lParam)) {
            closesocket((SOCKET)wParam);
            break;
        }
        switch (WSAGETSELECTEVENT(lParam)) {
        case FD_ACCEPT:
            // Accept an incoming connection
            Accept = accept(wParam, NULL, NULL);
            // Prepare accepted socket for read, write, and close notification
            WSAAsyncSelect(Accept, hDlg, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);

            //SetWindowLongPtr(hDlg, GWLP_USERDATA, Accept);

            break;
        case FD_READ:
            char rBuffer[DEFAULT_BUFLEN];
            recv(wParam, rBuffer, DEFAULT_BUFLEN, 0);
            send(wParam, rBuffer, (int)strlen(rBuffer), 0);
            // Receive data from the socket in wParam
            break;
        case FD_WRITE:
            // The socket in wParam is ready for sending data
            break;
        case FD_CLOSE:
            // The connection is now closed
            closesocket((SOCKET)wParam);
            break;
        }
    default:
        break;
    }
    return DefWindowProc(hDlg, wMsg, wParam, lParam);
}