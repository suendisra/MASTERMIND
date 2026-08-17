/**
  @file     mastermind-draw.c
  @brief    Source file for MASTERMIND game graphics and drawing control
*/
#include "mastermind.h"
#include "resource.h"

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
static SPRITE   sprite = NULL;
static QUAD     spos = {0};

/* draw the scene */
void Draw(void)
{
    ClearGL(GBLACK);

    // TODO - draw the scene
    SpriteDraw(view, spos, sprite);

    PresentGL();
}

/* load or destroy the graphics */
BOOL Graphics(const BOOL load)
{
    const COLORREF  beta = SPRITE_ALPHA;
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
                if(Sprite(IDB_COLORS, ALPHA_OPAQUE, &beta, SPRITE_ROWS, SPRITE_COLS, SPRITE_CX, SPRITE_CY, &sprite))
                {
                    SpriteAnim(ANIMATE_NONE, 0.0, sprite);
                    QuadCentered(wnd.client.mx, wnd.client.my, SPRITE_CX, SPRITE_CY, &spos);
                    success = TRUE;
                }
            }
        }
    }else{
        // destroy the graphics
        SpriteKill(&sprite);
        ViewKill(&view);
        KillGL();
    }

    return(success);
}
