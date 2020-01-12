#pragma once
#include "Scene.h"

//
//namespace glm
//{
//	static void to_json(json& j, const glm::vec3& v)
//	{
//		j = json{ {"x", v.x}, {"y", v.y}, {"z", v.z} };
//	}
//
//	static void from_json(const json& j, glm::vec3& v)
//	{
//		j.at("x").get_to(v.x);
//		j.at("y").get_to(v.y);
//		j.at("z").get_to(v.z);
//	}
//
//	static void to_json(json& j, const glm::quat& q)
//	{
//		j = json{ {"x", q.x}, {"y", q.y}, {"z", q.z}, {"w", q.w} };
//	}
//
//	static void from_json(const json& j, glm::quat& q)
//	{
//		j.at("x").get_to(q.x);
//		j.at("y").get_to(q.y);
//		j.at("z").get_to(q.z);
//		j.at("w").get_to(q.w);
//	}
//
//	static void to_json(json& j, const glm::mat4& m4)
//	{
//		j = json{ {"a1", m4[0][0]} };
//		j = json{ {"a2", m4[0][1]} };
//		j = json{ {"a3", m4[0][2]} };
//		j = json{ {"a4", m4[0][3]} };
//		j = json{ {"b1", m4[1][0]} };
//		j = json{ {"b2", m4[1][1]} };
//		j = json{ {"b3", m4[1][2]} };
//		j = json{ {"b4", m4[1][3]} };
//		j = json{ {"c1", m4[2][0]} };
//		j = json{ {"c2", m4[2][1]} };
//		j = json{ {"c3", m4[2][2]} };
//		j = json{ {"c4", m4[2][3]} };
//		j = json{ {"d1", m4[3][0]} };
//		j = json{ {"d2", m4[3][1]} };
//		j = json{ {"d3", m4[3][2]} };
//		j = json{ {"d4", m4[3][3]} };
//	}
//
//	static void from_json(const json& j, glm::mat4 m4)
//	{
//		j.at("a1").get_to(m4[0][0]);
//		j.at("a2").get_to(m4[0][1]);
//		j.at("a3").get_to(m4[0][2]);
//		j.at("a4").get_to(m4[0][3]);
//		j.at("b1").get_to(m4[1][0]);
//		j.at("b2").get_to(m4[1][1]);
//		j.at("b3").get_to(m4[1][2]);
//		j.at("b4").get_to(m4[1][3]);
//		j.at("c1").get_to(m4[2][0]);
//		j.at("c2").get_to(m4[2][1]);
//		j.at("c3").get_to(m4[2][2]);
//		j.at("c4").get_to(m4[2][3]);
//		j.at("d1").get_to(m4[3][0]);
//		j.at("d2").get_to(m4[3][1]);
//		j.at("d3").get_to(m4[3][2]);
//		j.at("d4").get_to(m4[3][3]);
//	}
//
//	static void to_json(json& j, const glm::mat3& m4)
//	{
//		j = json{ {"a1", m4[0][0]} };
//		j = json{ {"a2", m4[0][1]} };
//		j = json{ {"a3", m4[0][2]} };
//		j = json{ {"b1", m4[1][0]} };
//		j = json{ {"b2", m4[1][1]} };
//		j = json{ {"b3", m4[1][2]} };
//		j = json{ {"c1", m4[2][0]} };
//		j = json{ {"c2", m4[2][1]} };
//		j = json{ {"c3", m4[2][2]} };
//	}
//
//	static void from_json(const json& j, glm::mat3 m4)
//	{
//		j.at("a1").get_to(m4[0][0]);
//		j.at("a2").get_to(m4[0][1]);
//		j.at("a3").get_to(m4[0][2]);
//		j.at("b1").get_to(m4[1][0]);
//		j.at("b2").get_to(m4[1][1]);
//		j.at("b3").get_to(m4[1][2]);
//		j.at("c1").get_to(m4[2][0]);
//		j.at("c2").get_to(m4[2][1]);
//		j.at("c3").get_to(m4[2][2]);
//	}
//
//}
//
//class Serializer
//{
//public:
//
//	static void to_json(json& j, const std::shared_ptr<TransformComponent>& t)
//	{
//		j = json{ {"id", t->id}, {"position", t->position}, {"eulerAngles", t->eulerAngles}, {"rotation", t->rotation}, {"scale", t->scale} };
//	}
//
//	static void to_json(json& j, const std::shared_ptr<Entity>& e)
//	{
//		j = json{ {"name", e->name}, {"id", e->id}, {"transform", e->transform}, {"children", e->children} };
//	}
//
//
//	static void WriteToFile(const std::shared_ptr<Entity> scene)
//	{
//		// json j = scene;
//
//		json j = "syr";
//		auto s = j.dump();
//		std::ofstream out("res/test/debug.json");
//		out << s;
//		out.close();
//	}
//
//
//};

class Serializer
{
public:
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

	void SerializeScene(std::shared_ptr<Scene> scene)
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

	void LookElement(tinyxml2::XMLElement *element)
	{
		std::cout << element << std::endl;
		
		if (element->FirstChildElement() != NULL)
		{
			auto firstChild = element->FirstChildElement();
			LookElement(firstChild);
			bool hasNext = false;
			if (firstChild->NextSibling() != NULL)
			{
				hasNext = true;
			}
			while (hasNext)
			{
				auto nextChild = firstChild->NextSiblingElement();
				LookElement(nextChild);
				if (nextChild->NextSibling() != NULL)
				{
					hasNext = true;
				}
				firstChild = nextChild;
			}
		}
	}

	void DeserializeScene(const char *path)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(path);
		LookElement(doc.RootElement());
	}
};