// Snake.cpp : Defines the entry point for the application.
//

#include <string>
#include <ctime>

#include "framework.h"
#include "Snake.h"

#include "Player.h"

#define MAX_LOADSTRING 100
#define IDT_TIMER1 1
#define TIMER_INTERVAL 200
#define ID_EDITBOX 101

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void                LoadImages();
Coords              getValidCoords(int, int);

enum Models {
    PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT,
    BODY,
    FOOD_BANANA, FOOD_APPLE, FOOD_WATERMELON,
    NUM_MODELS
};


HBITMAP modelBitmaps[NUM_MODELS];

Player player;
Food food;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    LoadImages();
    // Seed the random number generator once at the start of your program
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SNAKE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SNAKE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    player.~Player();
    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SNAKE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SNAKE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   SetTimer(hWnd, IDT_TIMER1, TIMER_INTERVAL, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hEdit = nullptr;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: Add any drawing code that uses hdc here...
            RECT window;
            GetClientRect(hWnd, &window);

            // Spawn food if there is none
            if (!food.getSpawned()) {
                player = Player(getValidCoords(window.right, window.bottom));

                Coords newFoodLoc = getValidCoords(window.right, window.bottom);
                int top = newFoodLoc.top + ((player.getSize() - food.getSize()) / 2);
                int left = newFoodLoc.left + ((player.getSize() - food.getSize()) / 2);
                food = Food(top, left);
            }

            // Draw food
            Coords foodLoc = food.getCoord();
            Rectangle(hdc, foodLoc.left, foodLoc.top, foodLoc.right, foodLoc.bottom);

            // Draw player
            Coords loc = player.getCoords();
           
            // Get correct orientation of head
            HBITMAP head;
            switch (player.getDirection()) {
                case UP:
                    head = modelBitmaps[PLAYER_UP];
                    break;
                case DOWN:
                    head = modelBitmaps[PLAYER_DOWN];
                    break;
                case LEFT:
                    head = modelBitmaps[PLAYER_LEFT];
                    break;
                case RIGHT:
                    head = modelBitmaps[PLAYER_RIGHT];
                    break;
                default:
                    head = modelBitmaps[PLAYER_RIGHT];
                    break;
            }

            // Render head
            if (head) {
                HDC hMemDC = CreateCompatibleDC(hdc);
                HBITMAP hOldMap = (HBITMAP)SelectObject(hMemDC, head);

                BITMAP bitmap;
                GetObject(head, sizeof(BITMAP), &bitmap);
                
                StretchBlt(hdc, loc.left, loc.top, player.getSize(), player.getSize(), hMemDC, 0, 0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

                // Clean up
                SelectObject(hMemDC, hOldMap);
                DeleteDC(hMemDC);
            }


            // Display score  & deathMsg
            if (player.getHealth() > 0) {
                // Display score
                std::wstring scoreText = L"Score: " + std::to_wstring(player.getScore()) + L"\n" + 
                                         L"Health: " + std::to_wstring(player.getHealth());
                RECT textRect = { 10, 10, 400, 80 };
                DrawText(hdc, scoreText.c_str(), -1, &textRect, DT_LEFT | DT_TOP | DT_WORDBREAK);
            }
            else {
                std::wstring gameOverText = L"Game Over\nFinal Score: " + std::to_wstring(player.getScore());
                RECT textRect = { window.right / 2 -50, window.bottom / 2 - 10, window.right / 2 + 400, window.bottom / 2 + 80 };
                DrawText(hdc, gameOverText.c_str(), -1, &textRect, DT_LEFT | DT_TOP | DT_WORDBREAK);
            }


            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, IDT_TIMER1);

        // Clean up models
        for (int i = 0; i < NUM_MODELS; i++) {
            if (modelBitmaps[i] != NULL) {
                DeleteObject(modelBitmaps[i]);
                modelBitmaps[i] = NULL;
            }
        }
        PostQuitMessage(0);
        break;

    // Keyboard controls
    case WM_KEYDOWN:
        {
            switch (wParam) {
                case VK_UP:
                    player.movePlayer(UP);
                    break;
                case VK_LEFT:
                    player.movePlayer(LEFT);
                    break;
                case VK_DOWN:
                    player.movePlayer(DOWN);
                    break;
                case VK_RIGHT:
                    player.movePlayer(RIGHT);
                    break;
            }
        }
        break;
    case WM_TIMER:
        {
            RECT window;
            GetClientRect(hWnd, &window);

            if (wParam == IDT_TIMER1) {
                player.movePlayer(player.getDirection());
                if (!player.checkBoundry(window.right, window.bottom)) {
                    player.dealDamage();

                    Coords newPlayerLoc = getValidCoords(window.right, window.bottom);

                    player.resetPlayerLoc(newPlayerLoc.top, newPlayerLoc.left);
                    if (player.getHealth() <= 0) {
                        KillTimer(hWnd, IDT_TIMER1);
                    }
                }
                InvalidateRect(hWnd, nullptr, TRUE);
            }
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void LoadImages() {
    modelBitmaps[PLAYER_UP] = (HBITMAP)LoadImage(NULL, L"images/snake_UP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    modelBitmaps[PLAYER_DOWN] = (HBITMAP)LoadImage(NULL, L"images/snake_DOWN.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    modelBitmaps[PLAYER_LEFT] = (HBITMAP)LoadImage(NULL, L"images/snake_LEFT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    modelBitmaps[PLAYER_RIGHT] = (HBITMAP)LoadImage(NULL, L"images/snake_RIGHT.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    modelBitmaps[BODY] = (HBITMAP)LoadImage(NULL, L"images/snake_body.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    modelBitmaps[FOOD_BANANA] = (HBITMAP)LoadImage(NULL, L"images/banana.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    modelBitmaps[FOOD_APPLE] = (HBITMAP)LoadImage(NULL, L"images/apple.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    modelBitmaps[FOOD_WATERMELON] = (HBITMAP)LoadImage(NULL, L"images/watermelon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

// Get valid coord for respawn
Coords getValidCoords(int windowWidth, int windowHeight) {
    int playerSize = player.getSize();

    // Make sure player doesn't spawn right on edge
    int maxTop = int(windowHeight / playerSize) - 5;
    int minTop = 5;
    int maxLeft = int(windowWidth / playerSize) - 5;
    int minLeft = 5;

    int newTop = (std::rand() % (maxTop - minTop) + minTop) * playerSize;
    int newLeft = (std::rand() % (maxLeft - minLeft) + minLeft) * playerSize;
    Coords coord = { newTop, newLeft, newTop + playerSize, newLeft + playerSize };

    return coord;
}