#pragma once

#include "stdafx.h";

#include "math.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <memory>
#include <map>
#include <typeinfo>


//external dependencies
#include "GL/glew.h"
#include "SDL.h"
#include "ext/stb_image/stb_image.h"
#include "yse.hpp"
#include "pugixml/pugixml.hpp"

// glm stuff *sigh*
#define GLM_ENABLE_EXPERIMENTAL
#include "ext/glm/glm.hpp"
#include "ext/glm/gtc/matrix_transform.hpp"
#include "ext/glm/gtc/type_ptr.hpp"
#include "ext/glm/gtx/quaternion.hpp"
#include "ext/glm/gtx/string_cast.hpp"

#include "ext/imgui/imgui.h"
#include "ext/imgui/auto.h"
#include "ext/imgui/imconfig.h"
#include "ext/imgui/imnodes.h"
#include "ext/imgui/ImGuiFileDialog.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "ext/imgui/imgui_impl_opengl3.h"
#include "ext/imgui/imgui_impl_sdl.h"


//physics
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"



#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

#ifndef SYSOUT_F
#define SYSOUT_F(f, ...)      _RPT1( 0, f, __VA_ARGS__ ) // For Visual studio
#endif

#ifndef speedtest__
#define speedtest__(data)   for (long blockTime = NULL; (blockTime == NULL ? (blockTime = clock()) != NULL : false); SYSOUT_F(data "%.9fs", (double) (clock() - blockTime) / CLOCKS_PER_SEC))
#endif
