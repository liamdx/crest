#include "Model.h"

void Model::loadModel(std::string _path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_path, aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace |
		aiProcess_GenSmoothNormals );

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	path = _path;
	directory = path.substr(0, path.find_last_of('/'));
	name = path.substr(path.find_last_of('/') + 1, path.find_last_of('.') - 1);
	std::cout << directory << std::endl;
	globalMeshInverse = aiMatrix4x4();
	processNode(scene->mRootNode, scene);

	std::cout << "done" << std::endl;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	debugMatrices.emplace_back(node->mTransformation);
	globalMeshInverse *= node->mTransformation;
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh2(mesh, node, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::vector<Face> faces;

	aiMatrix4x4 inv = currentTransformation.Inverse();

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		aiVector3D pos = mesh->mVertices[i];
		aiTransformVecByMatrix4(&pos, &inv);
		//vertex
		Vertex vert;
		vert.position.x = pos.x;
		vert.position.y = pos.y;
		vert.position.z = pos.z;

		if (mesh->HasNormals())
		{
			vert.normal.x = mesh->mNormals[i].x;
			vert.normal.y = mesh->mNormals[i].y;
			vert.normal.z = mesh->mNormals[i].z;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			vert.tangent.x = mesh->mTangents[i].x;
			vert.tangent.y = mesh->mTangents[i].y;
			vert.tangent.z = mesh->mTangents[i].z;
		}
		else {
			vert.tangent = glm::vec3(0.0f);
		}

		if (mesh->mTextureCoords[0])
		{
			vert.TexCoords.x = mesh->mTextureCoords[0][i].x;
			vert.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			vert.TexCoords = glm::vec2(0.0f);
		}

		vertices.push_back(vert);
	}

	//indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		Face _face;
		_face.numIndices = face.mNumIndices;

		for (unsigned int k = 0; k < face.mNumIndices; k++)
		{
			_face.indices.emplace_back(face.mIndices[k]);
			indices.push_back(face.mIndices[k]);
		}
		faces.push_back(_face);
	}

	//material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		//Assimp throws issues when importing reflection maps correctly, nano model stores
		//Reflection maps as ambient maps, this will obviously need corrected when PBR is implemented
		std::vector<Texture> reflectionMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "reflection");
		textures.insert(textures.end(), reflectionMaps.begin(), reflectionMaps.end());

		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	}

	return Mesh(vertices, indices, textures, faces);
}

std::shared_ptr<Mesh> Model::processMesh2(aiMesh* mesh, aiNode* node, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::vector<Face> faces;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		//vertex
		aiVector3D pos = mesh->mVertices[i];
		aiTransformVecByMatrix4(&pos, &globalMeshInverse);

		Vertex vert;
		/*
		vert.position.x = mesh->mVertices[i].x;
		vert.position.y = mesh->mVertices[i].y;
		vert.position.z = mesh->mVertices[i].z;
		*/

		vert.position.x = pos.x;
		vert.position.y = pos.y;
		vert.position.z = pos.z;

		if (mesh->HasNormals())
		{
			vert.normal.x = mesh->mNormals[i].x;
			vert.normal.y = mesh->mNormals[i].y;
			vert.normal.z = mesh->mNormals[i].z;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			vert.tangent.x = mesh->mTangents[i].x;
			vert.tangent.y = mesh->mTangents[i].y;
			vert.tangent.z = mesh->mTangents[i].z;
		}
		else {
			vert.tangent = glm::vec3(0.0f);
		}

		if (mesh->mTextureCoords[0])
		{
			vert.TexCoords.x = mesh->mTextureCoords[0][i].x;
			vert.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			vert.TexCoords = glm::vec2(0.0f);
		}

		vertices.push_back(vert);
	}

	//indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		Face _face;
		_face.numIndices = face.mNumIndices;

		for (unsigned int k = 0; k < face.mNumIndices; k++)
		{
			_face.indices.emplace_back(face.mIndices[k]);
			indices.push_back(face.mIndices[k]);
		}
		faces.push_back(_face);
	}

	//material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		//Assimp throws issues when importing reflection maps correctly, nano model stores
		//Reflection maps as ambient maps, this will obviously need corrected when PBR is implemented
		std::vector<Texture> reflectionMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "reflection");
		textures.insert(textures.end(), reflectionMaps.begin(), reflectionMaps.end());

		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	}

	return std::shared_ptr<Mesh>(new Mesh(vertices, indices, textures, faces));
}

TextureType Model::convertTextureType(aiTextureType t)
{
	if (t == aiTextureType_HEIGHT)
	{
		return TextureType::normal;
	}
	else if (t == aiTextureType::aiTextureType_AMBIENT)
	{
		return TextureType::reflection;
	}
	else if (t == aiTextureType::aiTextureType_DIFFUSE)
	{
		return TextureType::diffuse;
	}
	else if (t == aiTextureType::aiTextureType_SPECULAR)
	{
		return TextureType::specular;
	}
	else if (t == aiTextureType::aiTextureType_DISPLACEMENT)
	{
		return TextureType::ao;
	}
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		std::cout << &str << std::endl;

		bool shouldSkip = false;

		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].t_Path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				shouldSkip = true;
				break;
			}
		}

		if (!shouldSkip)
		{
			Texture texture;
			std::string textureLoadPath = directory + "/" + str.C_Str();

			texture.t_Id = TextureFromFile(textureLoadPath.c_str(), directory);
			texture.t_Type = convertTextureType(type);
			std::cout << typeName << std::endl;
			texture.t_Path = str.C_Str();
			std::cout << texture.t_Path << std::endl;
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

int Model::TextureFromFile(char const* path, const std::string& directory)
{
	unsigned int id;
	std::cout << path << std::endl;
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	std::cout << path << std::endl;

	if (data != nullptr)
	{
		GLenum format;

		if (nrChannels == 1)
		{
			format = GL_RED;
		}

		else if (nrChannels == 3)
		{
			format = GL_RGB;
		}

		else if (nrChannels == 4)
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

		return id;
	}
	else
	{
		std::cout << "Failed to load texture " << path << std::endl;
		stbi_image_free(data);
		return NULL;
	}
}

unsigned int Model::CommonTextureLoad(std::string path)
{
	unsigned int id;
	std::cout << path << std::endl;
	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(false);
	const char* _path = path.c_str();
	unsigned char* data = stbi_load(_path, &width, &height, &nrChannels, 0);
	std::cout << path << std::endl;

	if (data != nullptr)
	{
		GLenum format;

		if (nrChannels == 1)
		{
			format = GL_RED;
		}

		else if (nrChannels == 3)
		{
			format = GL_RGB;
		}

		else if (nrChannels == 4)
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

		return id;
	}
	else
	{
		std::cout << "Failed to load texture " << path << std::endl;
		stbi_image_free(data);
		return NULL;
	}
}

std::shared_ptr<Entity> Model::loadModelAsEntity(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return nullptr;
	}

	std::cout << path.substr(0, path.find_last_of('/')) << std::endl;

	processNodeForEntity(scene->mRootNode, scene, nullptr);

	return nullptr;
}

void Model::processNodeForEntity(aiNode* node, const aiScene* scene, std::shared_ptr<Entity> previousEntity)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
	}
}

tinyxml2::XMLElement* Model::serialize(tinyxml2::XMLDocument* doc)
{
	auto modelElement = doc->NewElement("Model");
	modelElement->SetAttribute("filepath", path.c_str());
	return modelElement;
}
