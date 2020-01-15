#include "components/LuaComponent.h"
#include "RigidbodyComponent.h"
#include "Debug.h"
#include "Entity.h"
#include "EngineManager.h"
#include "serialization/Serializer.hpp"

LuaScript::LuaScript(const char* _filepath)
{
	std::ifstream ifs(_filepath);
	script = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
	filepath = _filepath;
}

void LuaScript::reload()
{
	script.empty();
	std::ifstream ifs(filepath);
	script = std::string((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
}

tinyxml2::XMLElement* LuaScript::serialize(tinyxml2::XMLDocument* doc)
{
	auto lElement = doc->NewElement("LuaScript");
	lElement->SetAttribute("id", scriptID);
	lElement->LinkEndChild(Serializer::SerializeString(filepath, "filepath", doc));
	return lElement;
}
 

void LuaComponent::BindCrestToLua()
{
	lua.stack_clear();
	lua.open_libraries(sol::lib::base, sol::lib::math);
	
	// this needs separated and managed somehow...
	// glm::vec3
	auto vec3_mult_overloads = sol::overload(
		[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
		[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 * f; },
		[](float f, const glm::vec3& v1) -> glm::vec3 { return f * v1; },
		[](glm::quat& v1, glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
		[](glm::vec3& v1, glm::quat& v2) -> glm::vec3 { return v1 * v2; }
	);

	auto vec3_add_overloads = sol::overload(
		[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 + v2; },
		[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 + f; },
		[](float f, const glm::vec3& v1) -> glm::vec3 { return f + v1; }
	);

	auto vec3_sub_overloads = sol::overload(
		[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 + v2; },
		[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 + f; },
		[](float f, const glm::vec3& v1) -> glm::vec3 { return f + v1; }
	);
	
	lua.new_usertype<glm::vec3>("vec3",
		sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z,
		sol::meta_function::multiplication, vec3_mult_overloads,
		sol::meta_function::addition, vec3_add_overloads,
		sol::meta_function::subtraction, vec3_sub_overloads
		);

	auto quat_mult_overloads = sol::overload(
		[](const glm::quat& v1, const glm::quat& v2) -> glm::quat { return v1 * v2; },
		[](const glm::quat& v1, float f) -> glm::quat { return v1 * f; },
		[](float f, const glm::quat& v1) -> glm::quat { return f * v1; },
		[](glm::quat& v1, glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
		[](glm::vec3& v1, glm::quat& v2) -> glm::vec3 { return v1 * v2; }
	);

	auto quat_add_overloads = sol::overload(
		[](const glm::quat& v1, const glm::quat& v2) -> glm::quat { return v1 + v2; }

	);

	auto quat_sub_overloads = sol::overload(
		[](const glm::quat& v1, const glm::quat& v2) -> glm::quat { return v1 + v2; }

	);
	
	lua.new_usertype<glm::quat>("quat",
		sol::constructors<glm::quat(), glm::quat(glm::vec3)>(),
		"w", &glm::quat::w,
		"x", &glm::quat::x,
		"y", &glm::quat::y,
		"z", &glm::quat::z,
		sol::meta_function::multiplication, quat_mult_overloads,
		sol::meta_function::addition, quat_add_overloads,
		sol::meta_function::subtraction, quat_sub_overloads);
	
	glm::vec3 a = glm::vec3(1.0);
	glm::vec3 b = glm::vec3(1.0);
	glm::quat c = glm::quat();

	auto d = c * a + b;
	
	// Debug Namespace
	auto dbg = lua["Debug"].get_or_create<sol::table>();
	dbg.set_function("Log", sol::resolve<void(const char*, unsigned int)>(&Debug::Log<LuaComponent>));
	dbg.set_function("Warn", sol::resolve<void(const char*, unsigned int)>(&Debug::Warn<LuaComponent>));
	dbg.set_function("Message", sol::resolve<void(const char*, unsigned int)>(&Debug::Message<LuaComponent>));
	dbg.set_function("Error", sol::resolve<void(const char*, unsigned int)>(&Debug::Error<LuaComponent>));

	// input
	{

		auto linput = lua["Input"].get_or_create<sol::table>();
		linput.set_function("KeyA", [&]() { return attachedEntity->engineManager->input->GetKeyA(); });
		linput.set_function("KeyB", [&]() { return attachedEntity->engineManager->input->GetKeyB(); });
		linput.set_function("KeyC", [&]() { return attachedEntity->engineManager->input->GetKeyC(); });
		linput.set_function("KeyD", [&]() { return attachedEntity->engineManager->input->GetKeyD(); });
		linput.set_function("KeyE", [&]() { return attachedEntity->engineManager->input->GetKeyE(); });
		linput.set_function("KeyF", [&]() { return attachedEntity->engineManager->input->GetKeyF(); });
		linput.set_function("KeyG", [&]() { return attachedEntity->engineManager->input->GetKeyG(); });
		linput.set_function("KeyH", [&]() { return attachedEntity->engineManager->input->GetKeyH(); });
		linput.set_function("KeyI", [&]() { return attachedEntity->engineManager->input->GetKeyI(); });
		linput.set_function("KeyJ", [&]() { return attachedEntity->engineManager->input->GetKeyJ(); });
		linput.set_function("KeyK", [&]() { return attachedEntity->engineManager->input->GetKeyK(); });
		linput.set_function("KeyL", [&]() { return attachedEntity->engineManager->input->GetKeyL(); });
		linput.set_function("KeyM", [&]() { return attachedEntity->engineManager->input->GetKeyM(); });
		linput.set_function("KeyN", [&]() { return attachedEntity->engineManager->input->GetKeyN(); });
		linput.set_function("KeyO", [&]() { return attachedEntity->engineManager->input->GetKeyO(); });
		linput.set_function("KeyP", [&]() { return attachedEntity->engineManager->input->GetKeyP(); });
		linput.set_function("KeyQ", [&]() { return attachedEntity->engineManager->input->GetKeyQ(); });
		linput.set_function("KeyR", [&]() { return attachedEntity->engineManager->input->GetKeyR(); });
		linput.set_function("KeyS", [&]() { return attachedEntity->engineManager->input->GetKeyS(); });
		linput.set_function("KeyT", [&]() { return attachedEntity->engineManager->input->GetKeyT(); });
		linput.set_function("KeyU", [&]() { return attachedEntity->engineManager->input->GetKeyU(); });
		linput.set_function("KeyV", [&]() { return attachedEntity->engineManager->input->GetKeyV(); });
		linput.set_function("KeyW", [&]() { return attachedEntity->engineManager->input->GetKeyW(); });
		linput.set_function("KeyX", [&]() { return attachedEntity->engineManager->input->GetKeyX(); });
		linput.set_function("KeyY", [&]() { return attachedEntity->engineManager->input->GetKeyY(); });
		linput.set_function("KeyZ", [&]() { return attachedEntity->engineManager->input->GetKeyZ(); });

		linput.set_function("KeyLeftShift", [&]() { return attachedEntity->engineManager->input->GetKeyLeftShift(); });
		linput.set_function("KeyLeftAlt", [&]() { return attachedEntity->engineManager->input->GetKeyLeftAlt(); });
		linput.set_function("KeyLeftControl", [&]() { return attachedEntity->engineManager->input->GetKeyLeftControl(); });
		linput.set_function("KeyRightShift", [&]() { return attachedEntity->engineManager->input->GetKeyRightShift(); });
		linput.set_function("KeyRightAlt", [&]() { return attachedEntity->engineManager->input->GetKeyRightAlt(); });
		linput.set_function("KeyRightControl", [&]() { return attachedEntity->engineManager->input->GetKeyRightControl(); });
		linput.set_function("KeySpace", [&]() { return attachedEntity->engineManager->input->GetKeySpace(); });
		linput.set_function("KeyTab", [&]() { return attachedEntity->engineManager->input->GetKeyTab(); });
		linput.set_function("KeyEscape", [&]() { return attachedEntity->engineManager->input->GetKeyEscape(); });

		linput.set_function("LeftClick", [&]() { return attachedEntity->engineManager->input->GetLeftClick(); });
		linput.set_function("MiddleClick", [&]() { return attachedEntity->engineManager->input->GetMiddleClick(); });
		linput.set_function("RightClick", [&]() { return attachedEntity->engineManager->input->GetRightClick(); });

		linput.set_function("Controller1A", [&]() -> bool { return attachedEntity->engineManager->input->controller1.a_button; });
		linput.set_function("Controller1B", [&]() -> bool { return attachedEntity->engineManager->input->controller1.b_button; });
		linput.set_function("Controller1X", [&]() -> bool { return attachedEntity->engineManager->input->controller1.x_button; });
		linput.set_function("Controller1Y", [&]() -> bool { return attachedEntity->engineManager->input->controller1.y_button; });
		linput.set_function("Controller1Up", [&]() -> bool { return attachedEntity->engineManager->input->controller1.up_button; });
		linput.set_function("Controller1Down", [&]() -> bool { return attachedEntity->engineManager->input->controller1.down_button; });
		linput.set_function("Controller1Left", [&]() -> bool { return attachedEntity->engineManager->input->controller1.left_button; });
		linput.set_function("Controller1Right", [&]() -> bool { return attachedEntity->engineManager->input->controller1.right_button; });
		linput.set_function("Controller1LB", [&]() -> bool { return attachedEntity->engineManager->input->controller1.left_bumper; });
		linput.set_function("Controller1RB", [&]()-> bool { return attachedEntity->engineManager->input->controller1.right_bumper; });
		linput.set_function("Controller1LeftClick", [&]() -> bool { return attachedEntity->engineManager->input->controller1.left_click; });
		linput.set_function("Controller1RightClick", [&]() -> bool { return attachedEntity->engineManager->input->controller1.right_click; });
		linput.set_function("Controller1Start", [&]() -> bool { return attachedEntity->engineManager->input->controller1.start_button; });
		linput.set_function("Controller1Back", [&]() -> bool { return attachedEntity->engineManager->input->controller1.back_button; });
		linput.set_function("Controller1LX", [&]() { return attachedEntity->engineManager->input->controller1.left_x_input; });
		linput.set_function("Controller1LY", [&]() { return attachedEntity->engineManager->input->controller1.left_y_input; });
		linput.set_function("Controller1RX", [&]() { return attachedEntity->engineManager->input->controller1.right_x_input; });
		linput.set_function("Controller1RY", [&]() { return attachedEntity->engineManager->input->controller1.right_y_input; });
		linput.set_function("Controller1LT", [&]() { return attachedEntity->engineManager->input->controller1.right_trigger; });
		linput.set_function("Controller1RT", [&]() { return attachedEntity->engineManager->input->controller1.left_trigger; });

		linput.set_function("Controller2A", [&]() { return attachedEntity->engineManager->input->controller2.a_button; });
		linput.set_function("Controller2B", [&]() { return attachedEntity->engineManager->input->controller2.b_button; });
		linput.set_function("Controller2X", [&]() { return attachedEntity->engineManager->input->controller2.x_button; });
		linput.set_function("Controller2Y", [&]() { return attachedEntity->engineManager->input->controller2.y_button; });
		linput.set_function("Controller2Up", [&]() { return attachedEntity->engineManager->input->controller2.up_button; });
		linput.set_function("Controller2Down", [&]() { return attachedEntity->engineManager->input->controller2.down_button; });
		linput.set_function("Controller2Left", [&]() { return attachedEntity->engineManager->input->controller2.left_button; });
		linput.set_function("Controller2Right", [&]() { return attachedEntity->engineManager->input->controller2.right_button; });
		linput.set_function("Controller2LB", [&]() { return attachedEntity->engineManager->input->controller2.left_bumper; });
		linput.set_function("Controller2RB", [&]() { return attachedEntity->engineManager->input->controller2.right_bumper; });
		linput.set_function("Controller2LeftClick", [&]() { return attachedEntity->engineManager->input->controller2.left_click; });
		linput.set_function("Controller2RightClick", [&]() { return attachedEntity->engineManager->input->controller2.right_click; });
		linput.set_function("Controller2Start", [&]() { return attachedEntity->engineManager->input->controller2.start_button; });
		linput.set_function("Controller2Back", [&]() { return attachedEntity->engineManager->input->controller2.back_button; });
		linput.set_function("Controller2LX", [&]() { return attachedEntity->engineManager->input->controller2.left_x_input; });
		linput.set_function("Controller2LY", [&]() { return attachedEntity->engineManager->input->controller2.left_y_input; });
		linput.set_function("Controller2RX", [&]() { return attachedEntity->engineManager->input->controller2.right_x_input; });
		linput.set_function("Controller2RY", [&]() { return attachedEntity->engineManager->input->controller2.right_y_input; });
		linput.set_function("Controller2LT", [&]() { return attachedEntity->engineManager->input->controller2.right_trigger; });
		linput.set_function("Controller2RT", [&]() { return attachedEntity->engineManager->input->controller2.left_trigger; });

		linput.set_function("Controller3A", [&]() { return attachedEntity->engineManager->input->controller3.a_button; });
		linput.set_function("Controller3B", [&]() { return attachedEntity->engineManager->input->controller3.b_button; });
		linput.set_function("Controller3X", [&]() { return attachedEntity->engineManager->input->controller3.x_button; });
		linput.set_function("Controller3Y", [&]() { return attachedEntity->engineManager->input->controller3.y_button; });
		linput.set_function("Controller3Up", [&]() { return attachedEntity->engineManager->input->controller3.up_button; });
		linput.set_function("Controller3Down", [&]() { return attachedEntity->engineManager->input->controller3.down_button; });
		linput.set_function("Controller3Left", [&]() { return attachedEntity->engineManager->input->controller3.left_button; });
		linput.set_function("Controller3Right", [&]() { return attachedEntity->engineManager->input->controller3.right_button; });
		linput.set_function("Controller3LB", [&]() { return attachedEntity->engineManager->input->controller3.left_bumper; });
		linput.set_function("Controller3RB", [&]() { return attachedEntity->engineManager->input->controller3.right_bumper; });
		linput.set_function("Controller3LeftClick", [&]() { return attachedEntity->engineManager->input->controller3.left_click; });
		linput.set_function("Controller3RightClick", [&]() { return attachedEntity->engineManager->input->controller3.right_click; });
		linput.set_function("Controller3Start", [&]() { return attachedEntity->engineManager->input->controller3.start_button; });
		linput.set_function("Controller3Back", [&]() { return attachedEntity->engineManager->input->controller3.back_button; });
		linput.set_function("Controller3LX", [&]() { return attachedEntity->engineManager->input->controller3.left_x_input; });
		linput.set_function("Controller3LY", [&]() { return attachedEntity->engineManager->input->controller3.left_y_input; });
		linput.set_function("Controller3RX", [&]() { return attachedEntity->engineManager->input->controller3.right_x_input; });
		linput.set_function("Controller3RY", [&]() { return attachedEntity->engineManager->input->controller3.right_y_input; });
		linput.set_function("Controller3LT", [&]() { return attachedEntity->engineManager->input->controller3.right_trigger; });
		linput.set_function("Controller3RT", [&]() { return attachedEntity->engineManager->input->controller3.left_trigger; });

		linput.set_function("Controller4A", [&]() { return attachedEntity->engineManager->input->controller4.a_button; });
		linput.set_function("Controller4B", [&]() { return attachedEntity->engineManager->input->controller4.b_button; });
		linput.set_function("Controller4X", [&]() { return attachedEntity->engineManager->input->controller4.x_button; });
		linput.set_function("Controller4Y", [&]() { return attachedEntity->engineManager->input->controller4.y_button; });
		linput.set_function("Controller4Up", [&]() { return attachedEntity->engineManager->input->controller4.up_button; });
		linput.set_function("Controller4Down", [&]() { return attachedEntity->engineManager->input->controller4.down_button; });
		linput.set_function("Controller4Left", [&]() { return attachedEntity->engineManager->input->controller4.left_button; });
		linput.set_function("Controller4Right", [&]() { return attachedEntity->engineManager->input->controller4.right_button; });
		linput.set_function("Controller4LB", [&]() { return attachedEntity->engineManager->input->controller4.left_bumper; });
		linput.set_function("Controller4RB", [&]() { return attachedEntity->engineManager->input->controller4.right_bumper; });
		linput.set_function("Controller4LeftClick", [&]() { return attachedEntity->engineManager->input->controller4.left_click; });
		linput.set_function("Controller4RightClick", [&]() { return attachedEntity->engineManager->input->controller4.right_click; });
		linput.set_function("Controller4Start", [&]() { return attachedEntity->engineManager->input->controller4.start_button; });
		linput.set_function("Controller4Back", [&]() { return attachedEntity->engineManager->input->controller4.back_button; });
		linput.set_function("Controller4LX", [&]() { return attachedEntity->engineManager->input->controller4.left_x_input; });
		linput.set_function("Controller4LY", [&]() { return attachedEntity->engineManager->input->controller4.left_y_input; });
		linput.set_function("Controller4RX", [&]() { return attachedEntity->engineManager->input->controller4.right_x_input; });
		linput.set_function("Controller4RY", [&]() { return attachedEntity->engineManager->input->controller4.right_y_input; });
		linput.set_function("Controller4LT", [&]() { return attachedEntity->engineManager->input->controller4.right_trigger; });
		linput.set_function("Controller4RT", [&]() { return attachedEntity->engineManager->input->controller4.left_trigger; });

	}
	lua.new_usertype<EngineComponent>("Component");
	
	lua.new_usertype<TransformComponent>("TransformComponent", 
		sol::base_classes, sol::bases<EngineComponent>(),
		"new", [&]() {return new TransformComponent(); },
		"position", &TransformComponent::position,
		"rotation", &TransformComponent::rotation,
		"eulerAngles", &TransformComponent::eulerAngles,
		"scale", &TransformComponent::scale,
		"forward", &TransformComponent::forward,
		"up", &TransformComponent::up,
		"right", &TransformComponent::right,
		"LookAt", &TransformComponent::LookAt);

	lua.new_usertype<RigidbodyComponent>("RigidbodyComponent",
		sol::base_classes, sol::bases<EngineComponent>(),
		"new", [&]() {return new RigidbodyComponent(nullptr); }
		,"ApplyForce", &RigidbodyComponent::applyCentralForce,
		"SetCubeShape", &RigidbodyComponent::SetCubeShape,
		"SetSphereShape", &RigidbodyComponent::SetSphereShape,
		"SetCapsuleShape", &RigidbodyComponent::SetCapsuleShape,
		"cubeDimensions", &RigidbodyComponent::cubeDimensions,
		"capsuleRadius", &RigidbodyComponent::capsuleRadius,
		"capsuleHeight", &RigidbodyComponent::capsuleHeight,
		"sphereRadius", &RigidbodyComponent::sphereRadius,
		"collisionScale", &RigidbodyComponent::collisionScale,
		"centerOffset", &RigidbodyComponent::centerOffset,
		"linearFactor", &RigidbodyComponent::linearFactor,
		"angularFactor", &RigidbodyComponent::angularFactor);
	
	lua.new_usertype<Entity>("Entity",
		"new", [&]() {return attachedEntity->engineManager->AddEntity(); },
		"AddComponent", & Entity::AddComponent,
		"GetComponent", &Entity::GetComponent<RigidbodyComponent>,
		"Transform", &Entity::transform);

	auto _this = lua["this"].get_or_create<sol::table>();
	_this.set_function("Transform", [&]() {return attachedEntity->transform; });
	_this.set_function("Entity", [&]() {return attachedEntity; });


	auto _cm = lua["CrestMaths"].get_or_create<sol::table>();
	auto magnitude_overloads = sol::overload(
		[](const glm::vec3& v) -> float { return glm::length(v); },
		[](const glm::quat& v) -> float { return glm::length(v); }
	);
	auto degrees_overloads = sol::overload(
		[](const glm::vec3& v)->glm::vec3 {return glm::degrees(v); });
	
	_cm.set_function("QuatToEuler", [](glm::quat q) -> glm::vec3 { return glm::eulerAngles(q); });
	_cm.set_function("EulerToQuat", [](glm::vec3 v) -> glm::quat { return glm::quat(glm::radians(v)); });
	_cm.set_function("Magnitude", magnitude_overloads);
	_cm.set_function("Degrees", degrees_overloads);
	// lua.new_usertype<>()

	try
	{
		sol::environment env(lua, sol::create, lua.globals());
		auto result = lua.safe_script(script->script,[](lua_State*, sol::protected_function_result pfr) {
			// pfr will contain things that went wrong, for either loading or executing the script
			// the user can do whatever they like here, including throw. Otherwise...
			sol::error err = pfr;
			std::cout << "An error (an expected one) occurred: " << err.what() << std::endl;
			// ... they need to return the protected_function_result
			return pfr;
		});

		// didnt get a result
		if(result.valid() == false)
		{
			std::cout <<" boom yes skeeeat\n"; 
		}

		init_func = lua["init"];
		start_func = lua["start"];
		early_update_func = lua["earlyUpdate"];
		update_func = lua["update"];
		fixed_update_func = lua["fixedUpdate"];
		render_func = lua["render"];
		ui_func = lua["ui"];
	}
	catch(std::runtime_error e)
	{
		std::cout << e.what();
	}
	
	
	// update_function_proxy = lua["update"];

}

void my_panic(sol::optional<std::string> maybe_msg) {
	if (maybe_msg) {
		const std::string& msg = maybe_msg.value();
		std::cout << msg << std::endl;
		Debug::Error<LuaComponent>(msg.c_str());
	}
	// When this function exits, Lua will exhibit default behavior and abort()
}

int my_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
	// L is the lua state, which you can wrap in a state_view if necessary
	// maybe_exception will contain exception, if it exists
	// description will either be the what() of the exception or a description saying that we hit the general-case catch(...)
	std::cout << "An exception occurred in a function, here's what it says ";
	if (maybe_exception) {
		std::cout << "(straight from the exception): ";
		const std::exception& ex = *maybe_exception;
		std::cout << ex.what() << std::endl;
	}
	else {
		std::cout << "(from the description parameter): ";
		std::cout.write(description.data(), description.size());
		std::cout << std::endl;
	}

	// you must push 1 element onto the stack to be 
	// transported through as the error object in Lua
	// note that Lua -- and 99.5% of all Lua users and libraries -- expects a string
	// so we push a single string (in our case, the description of the error)
	return sol::stack::push(L, description);
}

LuaComponent::LuaComponent(std::shared_ptr<Entity> _attachedEntity)
{
	lua = sol::state(sol::c_call<decltype(&my_panic), &my_panic>);
	lua.set_exception_handler(&my_exception_handler);
	script = std::make_shared<LuaScript>("res/scripts/debug.lua");
	attachedEntity = _attachedEntity;
	shouldRun = true;
}

LuaComponent::LuaComponent(std::shared_ptr<Entity> _attachedEntity, std::shared_ptr<LuaScript> _script)
{
	lua = sol::state(sol::c_call<decltype(&my_panic), &my_panic>);
	lua.set_exception_handler(&my_exception_handler);
	script = _script;
	attachedEntity = _attachedEntity;
	shouldRun = true;
}


LuaComponent::~LuaComponent()
{
	lua.stack_clear();
}

void LuaComponent::reload()
{
	script->reload();
	shouldRun = true;
	init();
	start();
}

void LuaComponent::init()
{
	BindCrestToLua();
	if (shouldRun)
	{
		sol::protected_function_result init_result = init_func();
		if (!init_result.valid())
		{
			sol::error err = init_result;
			std::string error = err.what();
			Debug::Error<LuaComponent>(error.c_str());
			shouldRun = false;
		}
	}
	
}

void LuaComponent::start()
{
	if (shouldRun)
	{
		sol::protected_function_result start_result = start_func();
		if (!start_result.valid())
		{
			sol::error err = start_result;
			std::string error = err.what();
			Debug::Error<LuaComponent>(error.c_str());
			shouldRun = false;
		}
	}
}

void LuaComponent::earlyUpdate(float deltaTime)
{
	if (shouldRun)
	{
		sol::protected_function_result early_update_result = early_update_func();
		if (!early_update_result.valid())
		{
			sol::error err = early_update_result;
			std::string error = err.what();
			Debug::Error<LuaComponent>(error.c_str());
			shouldRun = false;
		}
	}
}

void LuaComponent::update(float deltaTime)
{
	if (shouldRun)
	{
		update_result = update_func(deltaTime);
		if (!update_result.valid())
		{
			sol::error err = update_result;
			std::string error = err.what();
			Debug::Error<LuaComponent>(error.c_str());
			shouldRun = false;
		}
	}
}

void LuaComponent::fixedUpdate()
{
	if (shouldRun)
	{
		sol::protected_function_result fixed_update_result = fixed_update_func();
		if (!fixed_update_result.valid())
		{
			sol::error err = fixed_update_result;
			std::string error = err.what();
			Debug::Error<LuaComponent>(error.c_str());
			shouldRun = false;
		}
	}
}

void LuaComponent::render(float deltaTime, glm::mat4 view)
{
	if (shouldRun)
	{
		sol::protected_function_result render_result = render_func();
		if (!render_result.valid())
		{
			sol::error err = render_result;
			std::string error = err.what();
			Debug::Error<LuaComponent>(error.c_str());
			shouldRun = false;
		}
	}
}

void LuaComponent::ui(float deltaTime)
{
	if (shouldRun)
	{
		sol::protected_function_result ui_result = ui_func();
		if (!ui_result.valid())
		{
			sol::error err = ui_result;
			std::string error = err.what();
			Debug::Error<LuaComponent>(error.c_str());
			shouldRun = false;
		}
	}
}

tinyxml2::XMLElement* LuaComponent::serialize_component(tinyxml2::XMLDocument* doc)
{
	auto lcElement = doc->NewElement("LuaComponent");
	auto lsElement = script->serialize(doc);
	lcElement->LinkEndChild(lsElement);
	return lcElement;
}

void LuaComponent::deserialize_component(tinyxml2::XMLElement* e)
{
	
}
