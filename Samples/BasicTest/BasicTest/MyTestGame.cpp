#include "MyTestGame.h"
#include "btBulletDynamicsCommon.h"
#include "entityx\entityx.h"
#include "Gameplay/Systems/PhysicsSystem.h"
#include "Gameplay/Components/Physics.h"
#include "Systems\MyRenderSystem.h"
#include "Physics/MeshColliderData.h"

using namespace entityx;

MyTestGame::MyTestGame() {
}

void MyTestGame::Start() {
	VPtr<Mesh> Sphere = new OBJMesh( "assets/sphere.obj" );
	VPtr<Mesh> Landscape = new OBJMesh("assets/world.obj");

	// Sphere
	SphereInstance = new MeshInstance( Sphere );
	//SphereInstance->Position = { 22.f, 50.f, -0.2f };
	//SphereInstance->Scale = { 0.1f, 0.1f, 0.1f };
	//SphereInstance->UpdateTransform();

	// Landscape
	WorldInstance = new MeshInstance(Landscape);
	//WorldInstance->UpdateTransform();

	

	// ECS test
	Ecs.systems.add<PhysicsSystem>();
	Ecs.systems.add<MyRenderSystem>();
	Ecs.systems.configure();


	btCollisionShape* fallShape = new btSphereShape(1);
	
	auto handEntity = Ecs.entities.create();
	handEntity.assign<Transform>();
	handEntity.assign<MeshInstanceComponent>(SphereInstance);
	handEntity.assign<Physics>(vec3f( 0, 20.f, -0.2f ), fallShape, 10.f);
	//handEntity.component<Physics>()->body->applyCentralImpulse(btVector3(0.f, -50.f, -50));


	// Landscape
	btTriangleMesh* smi = new MeshColliderData(dynamic_cast<OBJMesh*>((Mesh*)Landscape));
	btCollisionShape* landscapeShape = new btBvhTriangleMeshShape(smi, true);
	auto worldEntity = Ecs.entities.create();
	worldEntity.assign<Physics>(linalg::vec3f(), landscapeShape, 0.f);
	worldEntity.assign<MeshInstanceComponent>(WorldInstance);
	worldEntity.assign<Transform>();
}

void MyTestGame::Update( float delta ) {

	// Update ECS
	Ecs.systems.update_all(delta);
}

void MyTestGame::Render() {
}

void MyTestGame::RenderScene( ShaderProgram& shader ) {
	//Ecs.entities.each<Physics>([this](Entity entity, Physics & physics) {
	//	// Do things with entity, position and direction.
	//	SphereInstance->Position = physics.GetPosition();
	//	SphereInstance->UpdateTransform();
	//});

	SphereInstance->Render( shader );
	WorldInstance->Render(shader);
}

void MyTestGame::Resize() {
	//Cam->SetAspectRatio( LVP::App->Width / (float)LVP::App->Height );
}