/**
  @file     mastermind.c
  @brief    Primary source file for MASTERMIND game
*/
#include "mastermind.h"
#include "resource.h"

#include <util-file.h>
#include <util-mem.h>
#include <util-str.h>
#include <ogl-std.h>

#define APP_COPYRIGHT   L"© 2026"
#define APP_PATH_DAT    L"master.dat"
#define APP_SCALE       0.95
#define APP_TITLE       L"MASTERMIND"
#define APP_VERSION     L"0.0.0"

BENCH   bench = {0};

// static prototypes
static void Defaults(void);
static void Run(void);
static BOOL Settings(const BOOL read);
static BOOL Start(void);
static void Stop(void);

/* WinMain */
int WINAPI wWinMain(HINSTANCE instance, HINSTANCE previous, LPWSTR cmd, int show)
{
    long    dim = 0;
    wchar_t title[STR_SMALL] = {0};

    // create an almost full-sized window
    WinInit(instance, previous, cmd, show);
    dim = (long)(APP_SCALE * min(win.client.cx, win.client.cy));
    QuadCentered(win.client.mx, win.client.my, dim, dim, &wnd.client);

    StrFormat(title, sizeof(title), L"%s %s", APP_TITLE, APP_VERSION);
    if(Window(title, wnd.client, NULL, &wnd))
    {
        WindowConfig(Start, Run, Stop, &wnd);
        WindowPeek(&app.over, &wnd);
        Loop(wnd);
    }

    return(0);
}

/* set game default configuration for first-time play */
static void Defaults(void)
{
    MemClear(&app, sizeof(app));
}

/* perform game algorithm */
static void Run(void)
{
    Draw();
    // TODO Input();
    // TODO Update();
    // TODO Benchmark(&bench);
}

/* load or save game settings */
static BOOL Settings(const BOOL read)
{
    CFILE   cf = {0};
    wchar_t dir[STR_PATH] = {0};
    long    mode = ((read == TRUE) ? FILE_READ : FILE_WRITE);
    BOOL    success = FALSE;

    if(FolderApp(dir, sizeof(dir), L"%s", APP_PATH_DAT))
    {
        if(FileOpen(mode, dir, &cf))
        {
            if(read)
            {
                success = (FileRead(cf, &app, sizeof(app)) == sizeof(app));
            }else{
                app.over = FALSE;
                success = (FileWrite(cf, &app, sizeof(app)) == sizeof(app));
            }

            FileClose(&cf);
        }
    }

    return(success);
}

/* initialize the game and all the necessary resources */
static BOOL Start(void)
{
    BOOL    success = FALSE;

    // apply application icon to window
    if(WindowIcon(IDI_MASTERMIND, &wnd))
    {
        // set up the game struct based off saved settings
        if(!Settings(TRUE))
        {
            // unable to load saved settings, use defaults
            Defaults();
        }

        // set up graphics, audio, and bluetooth
        if(Graphics(TRUE))
        {
            // TODO Logic();
            success = TRUE;
        }
    }

    return(success);
}

/* perform game cleanup */
static void Stop(void)
{
    // TODO Graphics(FALSE);
    Settings(FALSE);
    WindowKill(&wnd);
}
