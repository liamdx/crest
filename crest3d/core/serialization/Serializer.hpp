#pragma once

#include "EngineManager.h"

class Serializer
{
public:

	

	static unsigned int DeserializeUnsignedInt(const char* input)
	{
		std::stringstream s(input);
		unsigned int x = 0;
		s >> x;
		return x;
	}

	static float DeserializeFloat(const char* input)
	{
		std::stringstream s(input);
		float x = 0;
		s >> x;
		return x;
	}

	static glm::vec2 DeserializeVec2(tinyxml2::XMLElement* element)
	{
		glm::vec2 v = glm::vec2(0.0);
		v.x = DeserializeFloat(element->Attribute("x"));
		v.y = DeserializeFloat(element->Attribute("y"));
		return v;
	}
	
	static glm::vec3 DeserializeVec3(tinyxml2::XMLElement* element)
	{
		glm::vec3 v = glm::vec3(0.0);
		v.x = DeserializeFloat(element->Attribute("x"));
		v.y = DeserializeFloat(element->Attribute("y"));
		v.z = DeserializeFloat(element->Attribute("z"));
		return v;
	}

	static glm::quat DeserializeQuaternion(tinyxml2::XMLElement* element)
	{
		glm::quat v;
		v.x = DeserializeFloat(element->Attribute("x"));
		v.y = DeserializeFloat(element->Attribute("y"));
		v.z = DeserializeFloat(element->Attribute("z"));
		v.w = DeserializeFloat(element->Attribute("w"));
		return v;
	}
	
	static tinyxml2::XMLElement* SerializeString(std::string v, std::string name, tinyxml2::XMLDocument* doc)
	{
		auto stringElement = doc->NewElement("String");
		stringElement->SetAttribute("name", name.c_str());
		stringElement->SetAttribute("value", v.c_str());
		return stringElement;
	}

	static tinyxml2::XMLElement* SerializeBool(bool v, std::string name, tinyxml2::XMLDocument* doc)
	{
		auto bElement = doc->NewElement("Boolean");
		bElement->SetAttribute("name", name.c_str());
		bElement->SetAttribute("value", v);
		return bElement;
	}
	
	static tinyxml2::XMLElement *SerializeFloat(float v, std::string name, tinyxml2::XMLDocument *doc)
	{
		auto floatElement = doc->NewElement("Float");
		floatElement->SetAttribute("name", name.c_str());
		floatElement->SetAttribute("value", v);
		return floatElement;
	}

	static tinyxml2::XMLElement* SerializeUnsignedInt(unsigned int v, std::string name, tinyxml2::XMLDocument* doc)
	{
		auto uiElement = doc->NewElement("UnsignedInt");
		uiElement->SetAttribute("name", name.c_str());
		uiElement->SetAttribute("value", v);
		return uiElement;
	}
	
	static tinyxml2::XMLElement *SerializeVec2(glm::vec2 v, std::string name, tinyxml2::XMLDocument *doc)
	{
		auto vecElement = doc->NewElement("Vector2");
		vecElement->SetAttribute("name", name.c_str());
		vecElement->SetAttribute("x", v.x);
		vecElement->SetAttribute("y", v.y);
		return vecElement;
	}

	static tinyxml2::XMLElement *SerializeVec3(glm::vec3 v, std::string name, tinyxml2::XMLDocument *doc)
	{
		auto vecElement = doc->NewElement("Vector3");
		vecElement->SetAttribute("name", name.c_str());
		vecElement->SetAttribute("x", v.x);
		vecElement->SetAttribute("y", v.y);
		vecElement->SetAttribute("z", v.z);
		return vecElement;
	}

	static tinyxml2::XMLElement *SerializeQuat(glm::quat v, std::string name, tinyxml2::XMLDocument *doc)
	{
		auto vecElement = doc->NewElement("Quaternion");
		vecElement->SetAttribute("name", name.c_str());
		vecElement->SetAttribute("x", v.x);
		vecElement->SetAttribute("y", v.y);
		vecElement->SetAttribute("z", v.z);
		vecElement->SetAttribute("w", v.w);
		return vecElement;
	}

	static tinyxml2::XMLElement *SerializeMat3(glm::mat3 v, std::string name, tinyxml2::XMLDocument *doc)
	{
		auto vecElement = doc->NewElement("Matrix4");
		vecElement->SetAttribute("name", name.c_str());
		vecElement->SetAttribute("a1", v[0][0]);
		vecElement->SetAttribute("a2", v[0][1]);
		vecElement->SetAttribute("a3", v[0][2]);
		vecElement->SetAttribute("b1", v[1][0]);
		vecElement->SetAttribute("b2", v[1][1]);
		vecElement->SetAttribute("b3", v[1][2]);
		vecElement->SetAttribute("c1", v[2][0]);
		vecElement->SetAttribute("c2", v[2][1]);
		vecElement->SetAttribute("c3", v[2][2]);
		return vecElement;
	}

	static tinyxml2::XMLElement *SerializeMat4(glm::mat4 v, std::string name, tinyxml2::XMLDocument *doc)
	{
		auto vecElement = doc->NewElement("Matrix4");
		vecElement->SetAttribute("name", name.c_str());
		vecElement->SetAttribute("a1", v[0][0]);
		vecElement->SetAttribute("a2", v[0][1]);
		vecElement->SetAttribute("a3", v[0][2]);
		vecElement->SetAttribute("a4", v[0][3]);
		vecElement->SetAttribute("b1", v[1][0]);
		vecElement->SetAttribute("b2", v[1][1]);
		vecElement->SetAttribute("b3", v[1][2]);
		vecElement->SetAttribute("b4", v[1][3]);
		vecElement->SetAttribute("c1", v[2][0]);
		vecElement->SetAttribute("c2", v[2][1]);
		vecElement->SetAttribute("c3", v[2][2]);
		vecElement->SetAttribute("c4", v[2][3]);
		vecElement->SetAttribute("d1", v[3][0]);
		vecElement->SetAttribute("d2", v[3][1]);
		vecElement->SetAttribute("d3", v[3][2]);
		vecElement->SetAttribute("d4", v[3][3]);
		return vecElement;
	}

	static tinyxml2::XMLElement *SerializeEntity(std::shared_ptr<Entity> e, tinyxml2::XMLDocument *doc)
	{
		auto entityElement = doc->NewElement("Entity");
		// name and id
		entityElement->SetAttribute("name", e->name.c_str());
		entityElement->SetAttribute("id", e->id);
		entityElement->SetAttribute("state", e->state);
		entityElement->LinkEndChild(e->transform->serialize_component(doc));

		auto componentsElement = doc->NewElement("Components");

		for (int i = 0; i < e->components.size(); i++)
		{
			componentsElement->LinkEndChild(e->components.at(i)->serialize_component(doc));
		}

		entityElement->LinkEndChild(componentsElement);

		auto childrenElement = doc->NewElement("Children");

		for (int i = 0; i < e->children.size(); i++)
		{
			childrenElement->LinkEndChild(SerializeEntity(e->children.at(i), doc));
		}

		entityElement->LinkEndChild(childrenElement);

		return entityElement;
	}

	static void SerializeScene(std::shared_ptr<Scene> scene)
	{
		tinyxml2::XMLDocument doc;

		auto passable_doc = doc.GetDocument();
		auto dec = passable_doc->NewDeclaration();
		passable_doc->InsertEndChild(dec);

		auto scene_element = doc.NewElement("Scene");

		auto root = SerializeEntity(scene->rootEntity, passable_doc);
		scene_element->InsertEndChild(root);
		doc.LinkEndChild(scene_element);
		doc.SaveFile("res/test/debug.xml", false);
	}

	static tinyxml2::XMLElement* FindComponentInEntity(tinyxml2::XMLElement* entityElement, const char* elementType)
	{
		if (strcmp(entityElement->Value(), "Entity") == 0)
		{
			if(strcmp(elementType, "TransformComponent") == 0)
			{
				return entityElement->FirstChildElement("TransformComponent");
			}
			else
			{
				auto components = entityElement->FirstChildElement("Components");
				for (tinyxml2::XMLElement* e = components->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
				{
					if (strcmp(e->Value(), elementType) == 0)
					{
						return e;
					}
				}
			}
			
		}
		return nullptr;
	}

	static tinyxml2::XMLElement* FindElementInComponent(tinyxml2::XMLElement* componentElement, const char* elementType, const char* elementName)
	{
		for (tinyxml2::XMLElement* e = componentElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			// if types match
			if(strcmp(elementType, e->Value()) == 0)
			{
				// if element name is correct
				if(strcmp(elementName, e->Attribute("name")))
				{
					return e;
				}
			}
		}
		return nullptr;
	}


	static void LoadEntity(tinyxml2::XMLElement* entityElement, std::shared_ptr<Entity> parent, EngineManager* em)
	{
		auto entity = em->AddEntity();
		if(parent != nullptr)
		{
			em->MoveChild(entity, parent);
		}

		entity->name = entityElement->Attribute("name");
		//  sscanf(str, "%d", &x); 

		sscanf(entityElement->Attribute("id"), "%d", &entity->id);
		
		for (tinyxml2::XMLElement* e = entityElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if(strcmp("Entity", e->Value()) == 0)
			{
				LoadEntity(e, entity, em);
			}
		}

		for (tinyxml2::XMLElement* e = entityElement; e != NULL; e = e->NextSiblingElement())
		{
			if (strcmp("Entity", e->Value()) == 0)
			{
				LoadEntity(e, entity, em);
			}
		}
	}
	static void LookComponent(tinyxml2::XMLElement* element)
	{
		
	}
	
	static void LookEntity(tinyxml2::XMLElement* element, EngineManager* em)
	{
		std::string entityName = element->Attribute("name");
		unsigned int entityId = DeserializeFloat(element->Attribute("id"));
	}

	static void DeserializeScene(const char *path, EngineManager* em)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(path);

		auto sceneRoot = doc.FirstChildElement("Scene")->FirstChildElement("Entity");

		LoadEntity(sceneRoot, em->scene->rootEntity, em);
		std::cout << "loaded xml" << std::endl;

		auto t = FindComponentInEntity(sceneRoot, "TransformComponent");
		Debug::Log(t->Value());
		em->AddPointLightEntity();
	}
};