#include <windows.h>
#include <stdio.h>
#include <wjelement.h>
#include "client/client_linux.h"
#include "sql_lexical_analyzer/lex.yy.h"
#include "json/json_serialization_module.h"

#define PRINT_TO_STDOUT 1

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

wchar_t input[1000];
char command[1000];
HWND hCommandEdit;
HWND hOutputEdit;
struct sql_node *node;
char *json_string;


void AddControls(HWND);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    initialize_client();

    WNDCLASS wc = {0};
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"WindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"WindowClass", L"Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  100, 100, 510, 500,
                  NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void AddControls(HWND hWnd) {

    hCommandEdit = CreateWindowW(L"edit", L"",
                                 WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOHSCROLL,
                                 10, 20, 400, 30,
                                 hWnd, NULL, NULL, NULL);

    CreateWindowW(L"button", L"Send",
                  WS_VISIBLE | WS_CHILD,
                  420, 20, 65, 30,
                  hWnd, (HMENU) PRINT_TO_STDOUT, NULL, NULL);

    hOutputEdit = CreateWindowW(L"edit", L"",
                                WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                                10, 80, 470, 360,
                                hWnd, NULL, NULL, NULL);


}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case PRINT_TO_STDOUT:

                    GetWindowTextW(hCommandEdit, input, 1000);
                    wcstombs(command, input, 100);

                    node = malloc(sizeof(struct sql_node));
                    int status = parse_string(command, node);

                    if (status != 1) {
                        json_string = sql_node_to_json_string(node);
                        WJElement response = NULL;
                        send_and_receive(json_string, &response);
                        char output[2048];
                        handle_response_interface(response, output);
                        SetWindowText(hOutputEdit, output);
                    } else {
                        SetWindowText(hOutputEdit, "The syntax of command is invalid");
                    }

            }
            break;
        case WM_CREATE:
            AddControls(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }

}