#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "assimp/cimport.h"
#include "Entity.h"

class Model {

public:
	Model(std::string const &path)
	{
		loadModel(path);
	}
	inline void Draw(Shader shader) { for (unsigned int i = 0; i < meshes.size(); i++) { meshes[i]->Draw(shader); } }
	inline void TestDraw(Shader shader) { for (unsigned int i = 0; i < meshes.size(); i++) { meshes[i]->TestDraw(shader); } }
	std::vector<Texture> textures_loaded;
	std::vector<std::shared_ptr<Mesh>> meshes;
	static int TextureFromFile(char const *path, const std::string& directory);

	static int CommonTextureLoad(std::string path);

	std::string directory;
	std::string path;
	std::string name;

	void loadModel(std::string _path);
	static void processNodeForEntity(aiNode *node, const aiScene *scene, std::shared_ptr<Entity>);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::shared_ptr<Mesh> processMesh2(aiMesh *mesh, aiNode* node,  const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	static std::shared_ptr<Entity> loadModelAsEntity(std::string path);

	aiMatrix4x4 currentTransformation;
};
