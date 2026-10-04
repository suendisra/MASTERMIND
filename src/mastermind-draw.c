/**
  @file     mastermind-draw.c
  @brief    Source file for MASTERMIND game graphics and drawing control
*/
#include "mastermind.h"
#include "resource.h"

#include <gph-grid.h>
#include <ogl-shd.h>
#include <ogl-spr.h>
#include <ogl-std.h>
#include <ogl-view.h>

#define SPRITE_ALPHA    GMAGENTA
#define SPRITE_COLS     6
#define SPRITE_CX       64
#define SPRITE_CY       64
#define SPRITE_ROWS     2

static SHADER   shader = NULL;
static VIEW     view = NULL;
static GPH      gph = {0};
static GRID     grid = {0};
static SPRITE   sprite = NULL;

// static prototypes
static BOOL DrawCell(const QUAD cell, const INDEX index, void *userdata);

/* draw the scene */
void Draw(void)
{
    ClearGL(GBLACK);
    GridFunc(grid, NULL, DrawCell);

    PresentGL();
}

/* draw single board piece */
BOOL DrawCell(const QUAD cell, const INDEX index, void *userdata)
{
    if(Clamped(index, -1, (BOARD_COLS * BOARD_ROWS)) && (userdata == NULL) && (cell.cx > 0) && (cell.cy > 0))
    {
        SpriteMove(FALSE, cell.x1, cell.y1, sprite);
        SpriteDraw(view, sprite);
    }

    return(TRUE);
}

/* load or destroy the graphics */
BOOL Graphics(const BOOL load)
{
    const COLORREF  beta = SPRITE_ALPHA;
    QUAD            board = {0};
    BOOL            built = FALSE;
    BOOL            success = FALSE;

    if(load)
    {
        // kick up openGL and create a viewport
        if(OpenGL(wnd.handl, FALSE) && View(wnd.client, FALSE, &view))
        {
            // compile and build the fragment and vertex shaders
            built = Shader(SHADER_TYPE_FRAGMENT, IDR_SHD_FRAG, &shader);
            built &= Shader(SHADER_TYPE_VERTEX, IDR_SHD_VERT, &shader);
            if(built && ShaderBuild(TRUE, shader))
            {
                ShaderSet(shader);
                ShaderMatrix(shader, SHADER_PROJECTION, ViewOrtho(view));
                ShaderLong(shader, SHADER_MODE, SHADER_MODE_TEXTURE);
                ViewSet(view);

                // create the sprite to do the heavy lifting
                if(Sprite(IDB_COLORS, ALPHA_TRANSPARENT, &beta, SPRITE_ROWS, SPRITE_COLS, SPRITE_CX, SPRITE_CY, &sprite))
                {
                    QuadCentered(wnd.client.mx, wnd.client.my, (BOARD_COLS * SPRITE_CX), (BOARD_ROWS * SPRITE_CY), &board);
                    if(Gph(wnd.handl, board, &gph) && Grid(gph, &board, &grid))
                    {
                        GridConfig(&grid, HEADER_NONE, BOARD_ROWS, BOARD_COLS);
                        SpriteAnim(ANIMATE_NONE, 0.0, sprite);
                        success = TRUE;
                    }
                }
            }
        }
    }else{
        // destroy the graphics
        SpriteKill(&sprite);
        ViewKill(&view);
        GphKill(&gph);
        KillGL();
    }

    return(success);
}
