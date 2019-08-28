#pragma once

//external dependencies
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "ext/stb_image/stb_image.h"
#include "yse.hpp"
#include "pugixml/pugixml.hpp"

// glm stuff *sigh*
#include "ext/glm/glm.hpp"
#include "ext/glm/gtc/matrix_transform.hpp"
#include "ext/glm/gtc/type_ptr.hpp"
#include "ext/glm/gtx/quaternion.hpp"
#include "ext/glm/gtx/string_cast.hpp"


#include "ext/imgui/imgui.h"
#include "ext/imgui/auto.h"
#include "ext/imgui/imconfig.h"
#include "ext/imgui/imgui_impl_glfw.h"
#include "ext/imgui/imgui_impl_opengl3.h"

//physics lib (g'doy)
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

#include "gfx/Model.h"
#include "gfx/Shader.h"