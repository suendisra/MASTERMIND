/**
  @file     mastermind.h
  @brief    Header file for MASTERMIND game
*/
#ifndef _MASTERMIND_H_
#define _MASTERMIND_H_

#include <util-std.h>
#include <win-std.h>

// bring in appropriate version of library
#ifndef _DEBUG
#pragma comment(lib, "UTIL.lib")
#pragma comment(lib, "GPH.lib")
#pragma comment(lib, "WIN.lib")
#pragma comment(lib, "OGL.lib")
#else
#pragma comment(lib, "UTILD.lib")
#pragma comment(lib, "GPHD.lib")
#pragma comment(lib, "WIND.lib")
#pragma comment(lib, "OGLD.lib")
#endif

struct
{
    BOOL    over;
}app;

WNDW    wnd;

/**
  @fn               void Draw(void)
  @brief            draw the scene
*/
void Draw(void);

/**
  @fn               BOOL Graphics(const BOOL load)
  @brief            load or destroy the graphics
  @param[in]        load if TRUE, loads the graphics; if FALSE, destroys them
  @return           TRUE if loading/destruction was successful; FALSE otherwise
*/
BOOL Graphics(const BOOL load);

#endif
