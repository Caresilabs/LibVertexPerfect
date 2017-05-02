#pragma once

#include "ApplicationListener.h"
#include "LVP.h"
#include "entityx/entityx.h"
#include "Graphics/MeshInstance.h"

class MyTestGame : public ApplicationListener {
public:
	MyTestGame();

	virtual void			Start() override;
	virtual void			Update( float delta ) override;
	virtual void			Render() override;
	virtual void			Resize() override;

	void					RenderScene( ShaderProgram& shader );

private:

	entityx::EntityX			Ecs;

	VPtr<MeshInstance>		SphereInstance;
	VPtr<MeshInstance>		WorldInstance;

};

