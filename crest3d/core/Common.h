#pragma once

// basic C++ stuffs
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
#include "tinyxml2.h"

// glm stuff *sigh*
#define GLM_ENABLE_EXPERIMENTAL
#include "ext/glm/glm.hpp"
#include "ext/glm/gtc/matrix_transform.hpp"
#include "ext/glm/gtc/type_ptr.hpp"
#include "ext/glm/gtx/quaternion.hpp"
#include "ext/glm/gtx/string_cast.hpp"
#include "ext/glm/gtx/norm.hpp"
#include "ext/glm/gtx/euler_angles.hpp"

// Imgui and various extensions
#include "ext/imgui/imgui.h"
#include "ext/imgui/auto.h"
#include "ext/imgui/imconfig.h"
#include "ext/imgui/imnodes.h"
#include "ext/imgui/ImGuiFileDialog.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "ext/imgui/imgui_impl_opengl3.h"
#include "ext/imgui/imgui_impl_sdl.h"

// Bullet physics
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

// Lua and sol2
#include "lua.hpp"
#include "sol/forward.hpp"
#include "sol/sol.hpp"
// ?
// #define SOL_ENABLE_INTEROP
#define SOL_DEFAULT_PASS_ON_ERROR
#define SOL_NO_EXCEPTIONS


