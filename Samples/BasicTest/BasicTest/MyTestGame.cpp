#include "MyTestGame.h"
#include "ShadowMapShader.h"
#include "btBulletDynamicsCommon.h"

MyTestGame::MyTestGame() {
}

void MyTestGame::Start() {
	VPtr<Mesh> Sphere = new OBJMesh( "assets/hand/hand.obj" );

	// Sphere
	SphereInstance = new MeshInstance( Sphere );
	SphereInstance->Position = { 0.2f, 2.f, -0.2f };
	SphereInstance->Scale = { 0.1f, 0.1f, 0.1f };
	SphereInstance->UpdateTransform();

	// Cameras and shaders
	Cam = new Camera( fPI / 4,				/*field-of-view*/
		(float)LVP::App->Width / LVP::App->Height,					/*aspect ratio*/
		.2f,								/*z-near plane (everything closer will be clipped/removed)*/
		100.0f, true );
	Cam->MoveTo( { 0, 0, 5 } );

	// Shadow stuff
	ShadowMapBuffer = new DXFrameBuffer( LVP::App->Width * 1.4f, LVP::App->Height * 1.4f, true, false, true );
	ShadowCam = new Camera( 0, 0, 0.2f, 100.0f, false );
	ShadowCam->MoveTo( { 4, 11, 1 } );
	ShadowCam->Look( -3.14 / 2, -1.6f );
	ShadowShader = new ShadowMapShader();

	Shader = new PhongShader( ShadowMapBuffer, ShadowCam );





	// Build the broadphase
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher( collisionConfiguration );

	// The actual physics solver
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	// The world.
	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, broadphase, solver, collisionConfiguration );
	dynamicsWorld->setGravity( btVector3( 0, -10, 0 ) );


	// Clean up behind ourselves like good little programmers
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;

}

void MyTestGame::Update( float delta ) {

	if ( LVP::Input->IsKeyDown( VK_ESCAPE ) )
		LVP::Input->SetCatchMouse( false );

	static float speed = 0;
	if ( LVP::Input->IsKeyDown( VK_SHIFT ) ) {
		speed = 10.f;
	} else {
		speed = 4.5f;
	}

	if ( LVP::Input->IsKeyDown( 'S' ) ) {
		Cam->MoveForward( -delta * speed );
	}
	if ( LVP::Input->IsKeyDown( 'W' ) ) {
		Cam->MoveForward( delta * speed );
	}
	if ( LVP::Input->IsKeyDown( 'A' ) ) {
		Cam->MoveSideways( -delta * speed );
	}
	if ( LVP::Input->IsKeyDown( 'D' ) ) {
		Cam->MoveSideways( delta * speed );
	}
	if ( LVP::Input->IsKeyDown( 'Q' ) ) {
		Cam->MoveVertical( -delta * speed );
	}
	if ( LVP::Input->IsKeyDown( 'E' ) ) {
		Cam->MoveVertical( delta * speed );
	}

	Cam->Look( LVP::Input->GetMouseDeltaX() * delta, -LVP::Input->GetMouseDeltaY() *delta );

	Cam->UpdateFrustrum();
	ShadowCam->UpdateFrustrum();

}

void MyTestGame::Render() {
	LVP::Graphics->ClearScreen( 0.0f, 0.6f, 0.95f );

	// Render Target

	ShadowMapBuffer->Clear( 0, 0, 0 );
	ShadowMapBuffer->Bind();
	{
		ShadowShader->Begin( *ShadowCam );
		{
			RenderScene( ShadowShader );
		}
		ShadowShader->End();
	}
	ShadowMapBuffer->Unbind();


	Shader->Begin( *Cam );
	{
		RenderScene( Shader );
	}
	Shader->End();

}

void MyTestGame::RenderScene( ShaderProgram& shader ) {
	SphereInstance->Render( shader );
}

void MyTestGame::Resize() {
	Cam->SetAspectRatio( LVP::App->Width / (float)LVP::App->Height );
}