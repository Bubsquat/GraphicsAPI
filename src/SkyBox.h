// Skybox model

#ifndef _SkyBox
#define _SkyBox

#include "Matrix.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class SkyBox : public Align16
{
public:

	SkyBox(ID3D11Device* dev, float len);

	SkyBox(const SkyBox&) = delete;					// Copy constructor
	SkyBox(Model&&) = delete;						// Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;	// Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;			// Move assignment operator
	~SkyBox();

	void Render(ID3D11DeviceContext* context);

private:
	Model* pSkybox;
};





#endif _SkyBox

