// graphic object for terrain 

#ifndef _GraphicObject_Terrain
#define _GraphicObject_Terrain

#include "GraphicObject_Base.h"


class Texture;
class ShaderTextureLightFog;
class TerrainModel;
class ShaderTexture;

class GraphicObject_Terrain : public GraphicObject_Base
{
public:

	GraphicObject_Terrain() = delete;
	GraphicObject_Terrain(ShaderTextureLightFog* shader, TerrainModel* terrain);
	GraphicObject_Terrain(ShaderTexture* shader, TerrainModel* terrain);
	GraphicObject_Terrain(const GraphicObject_Terrain&) = delete;
	GraphicObject_Terrain& operator =(const GraphicObject_Terrain&) = default;
	GraphicObject_Terrain(GraphicObject_Terrain&&) = default;
	GraphicObject_Terrain& operator=(GraphicObject_Terrain&&) = default;
	~GraphicObject_Terrain() = default;

	void SetWorld(const Matrix& m);
	void SetTexture(Texture* tex);
	void SetMaterialProperties(const Vect& amb, const Vect& dif, const Vect& sp);
	void SetTerrainModel(TerrainModel* terrainModel);

	void Render();

	void SetModel(Model*) = delete;

private:

	enum ShaderType {
		LIGHT_TEXTURE,
		TEXTURE
	};

	ShaderType shaderType;

	Texture* myTexture;
	ShaderTextureLightFog* myLightShader;
	ShaderTexture* myTexShader;

	Matrix world;

	Vect amb;
	Vect dif;
	Vect sp;

	TerrainModel* terrainModel;

};




#endif _GraphicObject_Terrain