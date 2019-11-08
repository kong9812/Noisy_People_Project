//===================================================================================================================================
//yShaderLoader.cppz
// [ì¬Ò]HALGP12A332 11 ì ÷
// [ì¬ú]2019/09/23
// [XVú]2019/11/07
//===================================================================================================================================

//===================================================================================================================================
//yCN[hz
//===================================================================================================================================
#include "ShaderLoader.h"

//===================================================================================================================================
//yusingé¾z
//===================================================================================================================================
using namespace shaderNS;

//===================================================================================================================================
//yO[oÏz
//===================================================================================================================================
static ShaderLoader* pointerShaderLoader;

//===================================================================================================================================
//yRXgN^z
//===================================================================================================================================
ShaderLoader::ShaderLoader()
{
	pointerShaderLoader					= this;
	shaderName[TOON]					= { "ToonShader.fx" };
	shaderName[BLUR]					= { "BlurShader.fx" };
	shaderName[OCEAN]					= { "Ocean.fx" };
	shaderName[INSTANCE_BILLBOARD]		= { "InstancingBillboard.fx" };
	shaderName[INSTANCE_STATIC_MESH]	= { "InstancingStaticMesh.fx" };
}

//===================================================================================================================================
//yfXgN^z
//===================================================================================================================================
ShaderLoader::~ShaderLoader()
{
	pointerShaderLoader = NULL;
	release();
}

//===================================================================================================================================
//y[hz
//===================================================================================================================================
void ShaderLoader::load(LPDIRECT3DDEVICE9 device)
{
	//VF[_[ðÇÝÞ
	setShaderDirectory();
	HRESULT hr;
	LPD3DXBUFFER err = NULL;
	for (int i = 0; i < MAX_SHADER; i++)
	{
		if (FAILED(hr = D3DXCreateEffectFromFile(device, shaderName[i], NULL, NULL, 0, NULL, &effect[i], &err)))
		{
			MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), shaderName[i], MB_OK);
		}
	}
}

//===================================================================================================================================
//yðúz
//===================================================================================================================================
void ShaderLoader::release()
{
	for (int i = 0; i < MAX_SHADER; i++)
	{
		if (effect[i] != NULL)
		{//GtFNgÌðú
			effect[i]->Release();
			effect[i] = NULL;
		}
	}
}

//===================================================================================================================================
//yOQÆÖz
//===================================================================================================================================
LPD3DXEFFECT* shaderNS::reference(int shaderNo)
{
	return pointerShaderLoader->getEffect(shaderNo);
}
