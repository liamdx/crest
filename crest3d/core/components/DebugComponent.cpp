#include "DebugComponent.h"
#include "Common.h"
void DebugComponent::start() {
	std::cout << "DebugComponent: Override function executing on start()" << std::endl;
}

void DebugComponent::earlyUpdate(float deltaTime) {
	std::cout << "DebugComponent: Override function executing on eaylyUpdate()" << std::endl;
}

void DebugComponent::update(float deltaTime) {
	std::cout << "DebugComponent: Override function executing on update()" << std::endl;
}

void DebugComponent::ui(float deltaTime) {
	std::cout << "DebugComponent: Override function executing on ui" << std::endl;
}

void DebugComponent::debugPrintSomething(const char* thing)
{
	std::cout << thing << std::endl;
}