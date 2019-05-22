#include "SimpleExample.h"

SimpleExample::SimpleExample() 
{
	testShader = new Shader("res/shaders/default.vert", "res/shaders/default.frag");
	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	model = new Model("res/models/cyborg/cyborg.obj");
	skybox = new Cubemap(faces);

}

void SimpleExample::startBehaviour()
{

} 

void SimpleExample::earlyUpdateBehaviour()
{

}

void SimpleExample::updateBehaviour()
{
}

void SimpleExample::uiBehaviour()
{

}
