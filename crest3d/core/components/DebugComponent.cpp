#include "DebugComponent.h"
#include "Common.h"
void DebugComponent::start() {

	std::cout << "DebugComponent: Override function executing on start()" << std::endl;

}

void DebugComponent::earlyUpdate() {
	std::cout << "DebugComponent: Override function executing on eaylyUpdate()" << std::endl;
}

void DebugComponent::update() {
	std::cout << "DebugComponent: Override function executing on update()" << std::endl;
}

void DebugComponent::ui() {
	std::cout << "DebugComponent: Override function executing on ui" << std::endl;
}