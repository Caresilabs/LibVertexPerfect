#pragma once
#include "entityx/entityx.h"
#include "btBulletDynamicsCommon.h"
#include "../Components/MeshInstanceComponent.h"
#include "Gameplay\Components\Transform.h"
#include "../PhongShader.h"
#include "Graphics/MeshInstance.h"
#include "Graphics/DXFrameBuffer.h"
#include "../ShadowMapShader.h"

using namespace entityx;

class MyRenderSystem : public entityx::System<MeshInstanceComponent> {
	VPtr<ShaderProgram>		Shader;
	VPtr<Camera>				Cam;


	VPtr<Camera>				ShadowCam;
	VPtr<ShaderProgram>		ShadowShader;
	VPtr<DXFrameBuffer>		ShadowMapBuffer;

public:
	MyRenderSystem() {
		// Cameras and shaders
		Cam = new Camera(fPI / 4,				/*field-of-view*/
			(float)LVP::App->Width / LVP::App->Height,					/*aspect ratio*/
			.2f,								/*z-near plane (everything closer will be clipped/removed)*/
			100.0f, true);
		Cam->MoveTo({ 0, 0, 5 });

		// Shadow stuff
		ShadowMapBuffer = new DXFrameBuffer(LVP::App->Width * 1.4f, LVP::App->Height * 1.4f, true, false, true);
		ShadowCam = new Camera(0, 0, 0.2f, 100.0f, false);
		ShadowCam->MoveTo({ 30, 15, 30 });
		ShadowCam->Look(-3.14 / 2, -1.9f); //-3.14 / 2
		ShadowShader = new ShadowMapShader();

		Shader = new PhongShader(ShadowMapBuffer, ShadowCam);
	}

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		if (LVP::Input->IsKeyDown(VK_ESCAPE))
			LVP::Input->SetCatchMouse(false);

		static float speed = 0;
		if (LVP::Input->IsKeyDown(VK_SHIFT)) {
			speed = 10.f;
		}
		else {
			speed = 2.5f;
		}

		if (LVP::Input->IsKeyDown('S')) {
			Cam->MoveForward(-dt * speed);
		}
		if (LVP::Input->IsKeyDown('W')) {
			Cam->MoveForward(dt * speed);
		}
		if (LVP::Input->IsKeyDown('A')) {
			Cam->MoveSideways(-dt * speed);
		}
		if (LVP::Input->IsKeyDown('D')) {
			Cam->MoveSideways(dt * speed);
		}
		if (LVP::Input->IsKeyDown('Q')) {
			Cam->MoveVertical(-dt * speed);
		}
		if (LVP::Input->IsKeyDown('E')) {
			Cam->MoveVertical(dt * speed);
		}

		Cam->Look(LVP::Input->GetMouseDeltaX() * dt, -LVP::Input->GetMouseDeltaY() * dt);


		Cam->UpdateFrustrum();
		ShadowCam->UpdateFrustrum();

		LVP::Graphics->ClearScreen(0.0f, 0.6f, 0.95f);

		// Render Target

		ShadowMapBuffer->Clear(0, 0, 0);
		ShadowMapBuffer->Bind();
		{
			ShadowShader->Begin(*ShadowCam);
			{
				RenderScene(es, ShadowShader);
			}
			ShadowShader->End();
		}
		ShadowMapBuffer->Unbind();


		Shader->Begin(*Cam);
		{
			RenderScene(es, Shader);
		}
		Shader->End();

		

	};

	void RenderScene(entityx::EntityManager &es, ShaderProgram* shader) {
		es.each<Transform, MeshInstanceComponent>([shader](Entity entity, Transform& transform, MeshInstanceComponent& mesh) {
			mesh.Instance->Transform = transform.GetMatrix();
			mesh.Instance->Render(*shader);
		});
	}

};

