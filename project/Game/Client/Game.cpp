#include "pch.h"
#include "Game.h"

#include "Engine.h"
#include "Device.h"
#include "CommandQueue.h"
#include "RootSignature.h"

#include "Mesh.h"
#include "Shader.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init(const WindowInfo& window)
{
	GEngine->Init(window);

	vector<Vertex> vec(3);
	vec[0].pos = Vec3(0.f, 0.5f, 0.5f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);	// Red
	vec[1].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);	// Green
	vec[2].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);	// Blue
	mesh->Init(
		vec, 
		GEngine->GetDevice()->GetDevice(), 
		GEngine->GetCmdQueue()->GetCmdList()
	);

	shader->Init(
		L"..\\Resources\\Shader\\default.hlsli", 
		GEngine->GetDevice()->GetDevice(), 
		GEngine->GetCmdQueue()->GetCmdList(),
		GEngine->GetRootSignature()->GetSignature()
	);

	GEngine->GetCmdQueue()->WaitSync();
}

void Game::Update()
{
	GEngine->RenderBegin();

	shader->Update();
	mesh->Render();

	//GEngine->Render();
	
	GEngine->RenderEnd();
}
