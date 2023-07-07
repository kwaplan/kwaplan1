

extern "C"{
#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"
}

#include <stdio.h>

#include <stdbool.h>
#include <SDL.h>
#include <ctype.h>
#include "kwaplan_logging.h"
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture;

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned char convertToDoomKey(unsigned int key) {
    switch (key)
    {
    case SDLK_RETURN:
        key = DG_KEY_ENTER;
        break;
    case SDLK_ESCAPE:
        key = DG_KEY_ESCAPE;
        break;
    case SDLK_LEFT:
        key = DG_KEY_LEFTARROW;
        break;
    case SDLK_RIGHT:
        key = DG_KEY_RIGHTARROW;
        break;
    case SDLK_UP:
        key = DG_KEY_UPARROW;
        break;
    case SDLK_DOWN:
        key = DG_KEY_DOWNARROW;
        break;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
        key = DG_KEY_FIRE;
        break;
    case SDLK_SPACE:
        key = DG_KEY_USE;
        break;
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
        key = DG_KEY_RSHIFT;
        break;
    case SDLK_LALT:
    case SDLK_RALT:
        key = DG_KEY_LALT;
        break;
    case SDLK_F2:
        key = DG_KEY_F2;
        break;
    case SDLK_F3:
        key = DG_KEY_F3;
        break;
    case SDLK_F4:
        key = DG_KEY_F4;
        break;
    case SDLK_F5:
        key = DG_KEY_F5;
        break;
    case SDLK_F6:
        key = DG_KEY_F6;
        break;
    case SDLK_F7:
        key = DG_KEY_F7;
        break;
    case SDLK_F8:
        key = DG_KEY_F8;
        break;
    case SDLK_F9:
        key = DG_KEY_F9;
        break;
    case SDLK_F10:
        key = DG_KEY_F10;
        break;
    case SDLK_F11:
        key = DG_KEY_F11;
        break;
    case SDLK_EQUALS:
    case SDLK_PLUS:
        key = DG_KEY_EQUALS;
        break;
    case SDLK_MINUS:
        key = DG_KEY_MINUS;
        break;
    default:
        key = tolower(key);
        break;
    }

    return key;
}

static void addKeyToQueue(int pressed, unsigned int keyCode) {
    unsigned char key = convertToDoomKey(keyCode);

    unsigned short keyData = (pressed << 8) | key;

    s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
    s_KeyQueueWriteIndex++;
    s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}
static void handleKeyInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            puts("Quit requested");
            atexit(SDL_Quit);
            exit(1);
        }
        if (e.type == SDL_KEYDOWN) {
            //KeySym sym = XKeycodeToKeysym(s_Display, e.xkey.keycode, 0);
            //printf("KeyPress:%d sym:%d\n", e.xkey.keycode, sym);
            addKeyToQueue(1, e.key.keysym.sym);
        }
        else if (e.type == SDL_KEYUP) {
            //KeySym sym = XKeycodeToKeysym(s_Display, e.xkey.keycode, 0);
            //printf("KeyRelease:%d sym:%d\n", e.xkey.keycode, sym);
            addKeyToQueue(0, e.key.keysym.sym);
        }
    }
}


void DG_Init() {
    window = SDL_CreateWindow("DOOM",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        DOOMGENERIC_RESX,
        DOOMGENERIC_RESY,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Clear winow
    SDL_RenderClear(renderer);
    // Render the rect to the screen
    SDL_RenderPresent(renderer);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, DOOMGENERIC_RESX, DOOMGENERIC_RESY);
}

void DG_DrawFrame()
{
    SDL_UpdateTexture(texture, NULL, DG_ScreenBuffer, DOOMGENERIC_RESX * sizeof(uint32_t));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    handleKeyInput();
}

void DG_SleepMs(uint32_t ms)
{
    SDL_Delay(ms);
}

uint32_t DG_GetTicksMs()
{
    return SDL_GetTicks();
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
    if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex) {
        //key queue is empty
        return 0;
    }
    else {
        unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
        s_KeyQueueReadIndex++;
        s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

        *pressed = keyData >> 8;
        *doomKey = keyData & 0xFF;

        return 1;
    }

    return 0;
}

void DG_SetWindowTitle(const char* title)
{
    if (window != NULL) {
        SDL_SetWindowTitle(window, title);
    }
}

int main(int argc, char** argv)
{
    doomgeneric_Create(argc, argv);

    for (int i = 0; ; i++)
    {
        doomgeneric_Tick();
    }


    return 0;
}

/*
#include <stdio.h>
#include <iostream>

#include <raylib.h>
#include <stdlib.h>
//#include <Windows.h>


#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned char convertToDoomKey(unsigned char key)
{
	
	switch (key)
	{
	case VK_RETURN:
		key = DG_KEY_ENTER;
		break;
	case VK_ESCAPE:
		key = DG_KEY_ESCAPE;
		break;
	case VK_LEFT:
		key = DG_KEY_LEFTARROW;
		break;
	case VK_RIGHT:
		key = DG_KEY_RIGHTARROW;
		break;
	case VK_UP:
		key = DG_KEY_UPARROW;
		break;
	case VK_DOWN:
		key = DG_KEY_DOWNARROW;
		break;
	case VK_CONTROL:
		key = DG_KEY_FIRE;
		break;
	case VK_SPACE:
		key = DG_KEY_USE;
		break;
	case VK_SHIFT:
		key = DG_KEY_RSHIFT;
		break;
	default:
		key = tolower(key);
		break;
	}
	
	return key;
	
}

static void addKeyToQueue(int pressed, unsigned char keyCode)
{
	unsigned char key = convertToDoomKey(keyCode);

	unsigned short keyData = (pressed << 8) | key;

	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
	s_KeyQueueWriteIndex++;
	s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		ExitProcess(0);
		break;
	case WM_KEYDOWN:
		addKeyToQueue(1, wParam);
		break;
	case WM_KEYUP:
		addKeyToQueue(0, wParam);
		break;
	default:
		return DefWindowProcA(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void DG_Init()
{
	InitWindow(640, 400, "kwaplan)))");
}

void DG_DrawFrame()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	StretchDIBits(s_Hdc, 0, 0, DOOMGENERIC_RESX, DOOMGENERIC_RESY, 0, 0, DOOMGENERIC_RESX, DOOMGENERIC_RESY, DG_ScreenBuffer, &s_Bmi, 0, SRCCOPY);

	SwapBuffers(s_Hdc);
	BeginDrawing();
	for (int i = 0; i < sizeof(DG_ScreenBuffer) / sizeof(DG_ScreenBuffer[0]); i+=4) {
		// i/4 = y*width + x
		int x = (i/4) % 640;
		int y = i / 4 - x + 1;
		DrawPixel(x, y, { (unsigned char)DG_ScreenBuffer[i], (unsigned char)DG_ScreenBuffer[i + 1], (unsigned char)DG_ScreenBuffer[i + 2], (unsigned char)DG_ScreenBuffer[i + 3] });
	}
	EndDrawing();
}

void DG_SleepMs(uint32_t ms)
{
	WaitTime(ms / 1000);
}

uint32_t DG_GetTicksMs()
{
	return GetTime() / 1000;
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
	{
		//key queue is empty

		return 0;
	}
	else
	{
		unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
		s_KeyQueueReadIndex++;
		s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

		*pressed = keyData >> 8;
		*doomKey = keyData & 0xFF;

		return 1;
	}
}

void DG_SetWindowTitle(const char * title)
{
	SetWindowTitle(title);
}

int main(int argc, char **argv)
{
    doomgeneric_Create(argc, argv);

    for (int i = 0; ; i++)
    {
        doomgeneric_Tick();
    }
    

    return 0;
}*/