﻿#pragma once

#define _HAS_STD_BYTE 0		// std::byte 사용 X

#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

// DirectX 관련
#include "d3dx12.h"		// Microsoft의 비공식 라이브러리
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

#include <DirectXTex.h>
#include <DirectXTex.inl>

// Library
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex_release.lib")
#endif

// typedef
using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;
using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;
using Vec2		= XMFLOAT2;
using Vec3		= XMFLOAT3;
using Vec4		= XMFLOAT4;
using Matrix	= XMMATRIX;

enum class CBV_REGISTER : uint8
{
	b0,
	b1,
	b2,
	b3,
	b4,

	END
};

enum class SRV_REGISTER : uint8
{
	t0 = static_cast<uint8>(CBV_REGISTER::END),		// CBV's END와 번호 같음
	t1,
	t2,
	t3,
	t4,

	END
};

enum
{
	SWAP_CHAIN_BUFFER_COUNT = 2,
	CBV_REGISTER_COUNT = CBV_REGISTER::END,
	SRV_REGISTER_COUNT = static_cast<uint8>(SRV_REGISTER::END) - CBV_REGISTER_COUNT,
	REGISTER_COUNT = CBV_REGISTER_COUNT + SRV_REGISTER_COUNT,
};

struct WindowInfo
{
	HWND	hwnd;		// 출력 윈도우
	int32	width;		// 너비
	int32	height;		// 높이
	bool	windowed;	// 창 or 전체화면
};

#define DEVICE				GEngine->GetDevice()->GetDevice()
#define CMD_LIST			GEngine->GetCmdQueue()->GetCmdList()
#define RESOURCE_CMD_LIST	GEngine->GetCmdQueue()->GetResourceCmdList()
#define ROOT_SIGNATURE		GEngine->GetRootSignature()->GetSignature()

#define INPUT				GEngine->GetInput()
#define DELTA_TIME			GEngine->GetTimer()->GetDeltaTime()

extern unique_ptr<class Engine> GEngine;	// 외부 전역 변수 선언

struct Vertex
{
	Vec3 pos;	// x, y, z
	Vec4 color;	// R, G, B, A
	Vec2 uv;
};

struct Transform
{
	Vec4 offset;
};