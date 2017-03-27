#pragma once

#include "ApplicationListener.h"
#include "LVP.h"
#include "PhongShader.h"
#include "Graphics/MeshInstance.h"
#include "Graphics/DXFrameBuffer.h"

class MyTestGame : public ApplicationListener {
public:
	MyTestGame();

	virtual void			Start() override;
	virtual void			Update( float delta ) override;
	virtual void			Render() override;
	virtual void			Resize() override;

	void					RenderScene( ShaderProgram& shader );

private:


	VPtr<MeshInstance>		SphereInstance;

	VPtr<ShaderProgram>		Shader;
	VPtr<Camera>			Cam;


	VPtr<Camera>			ShadowCam;
	VPtr<ShaderProgram>		ShadowShader;
	VPtr<DXFrameBuffer>		ShadowMapBuffer;

};

