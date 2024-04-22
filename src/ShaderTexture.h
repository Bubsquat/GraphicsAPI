// class for shader texture

#ifndef _ShaderTexture
#define _ShaderTexture

#include "ShaderBase.h"
class Texture;
#include "Matrix.h"
#include "d3dUtil.h"
#include <d3d11.h>

class ShaderTexture : public ShaderBase
{
public:
	ShaderTexture(ID3D11Device* device);
	~ShaderTexture();


	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderTexture::SendWorld(const Matrix& world);

private:
	// add your own material

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct WorldMatrix
	{
		Matrix World;
	};

	ID3D11Buffer* mpBuffWord;

	Texture* currentTexture;

};



#endif _ShaderTexture
