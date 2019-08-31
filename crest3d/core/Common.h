#pragma once

//core libs

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

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
#include "GLFW/glfw3.h"
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

#define IMGUI_IMPL_OPENGL_LOADER_GLEW

#include "ext/imgui/imgui_impl_glfw.h"
#include "ext/imgui/imgui_impl_opengl3.h"
#include "ext/imgui/imgui_impl_sdl.h"

//physics lib (g'doy)
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

//camera stuff
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

#ifndef SYSOUT_F
#define SYSOUT_F(f, ...)      _RPT1( 0, f, __VA_ARGS__ ) // For Visual studio
#endif

#ifndef speedtest__             
#define speedtest__(data)   for (long blockTime = NULL; (blockTime == NULL ? (blockTime = clock()) != NULL : false); SYSOUT_F(data "%.9fs", (double) (clock() - blockTime) / CLOCKS_PER_SEC))
#endif

static void SetImGuiStyle()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.38f, 0.38f, 0.38f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.28f, 0.28f, 0.28f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(1.00f, 0.72f, 0.72f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.41f, 0.41f, 0.41f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.62f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.38f, 0.94f, 0.99f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.41f, 0.87f, 1.00f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.38f, 0.52f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(1.00f, 0.57f, 0.57f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.88f, 0.16f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.91f, 0.46f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.35f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

}