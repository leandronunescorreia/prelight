#ifndef _RENDERPATH_H_
#define _RENDERPATH_H_

#include "rendersystem.h"

/**
\class RenderPath
It's an abstract base class for all different render path class implementions.

RenderPath is an abstract layer for render strategy. 
When RenderSystem calls RenderPath to draw a render resource, RenderSystem will use 
a proper strategy to draw it.

- It hides different features supported by hardwares(e.g. sm 3.0, sm 2.x or fixed pipeline).
For exampler, if you want take advantage from sm3.0 when game running at 9 series video cards, 
and keep the compatibility with MX440 card. You may implement two render path classes named 
RenderPathSM30, RenderPathFPP derived from RenderPathDX9, and RenderPathDX9 class is derived
from RenderPath class.

- It create proper kernel resources for render resources, and use kernel resources and RenderDevice 
to draw render resources.

All interfaces are virtual functions, so RenderSystem can create a proper RenderPath class after detected 
hardware cap at runtime.

\class DrawCallObject
At RenderPath layer, there exists a sort of objects called drawcall objects.
Each drawcall objects may corresponds to a drawcall.
It contains reference to kernel resources like vertex buffer, index buffer, shader, and contain reference
to render resources, then it can get shader parameters from it.

RenderPath should build an drawcall objects queue for a camera, and sort them by using shader, render states.
*/

class RenderPath
{
public:
};

#endif