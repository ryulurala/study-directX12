#include "pch.h"
#include "Mesh.h"

#include "Engine.h"
#include "Device.h"
#include "CommandQueue.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"

void Mesh::Init(vector<Vertex>& vec)
{
	_vertexCount = static_cast<uint32>(vec.size());		// for. Render
	uint32 bufferSize = _vertexCount * sizeof(Vertex);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty, 
		D3D12_HEAP_FLAG_NONE, 
		&desc, 
		D3D12_RESOURCE_STATE_GENERIC_READ, 
		nullptr, 
		IID_PPV_ARGS(&_vertexBuffer)
	);

	// �ﰢ�� ������ Vertex Buffer(in. GPU)�� ����
	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0);
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &vec[0], bufferSize);
	_vertexBuffer->Unmap(0, nullptr);

	// Vertex Buffer View �ʱ�ȭ
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.StrideInBytes = sizeof(Vertex);	// ���� 1�� ũ��
	_vertexBufferView.SizeInBytes = bufferSize;			// ������ ũ��
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView);	// Slot: (0~15)

	{
		// 1) Buffer�� Data ����
		D3D12_CPU_DESCRIPTOR_HANDLE handle = GEngine->GetConstantBuffer()->PushData(0, &_transform, sizeof(_transform));
		
		// 2) Table Descriptor Heap�� CBV ����
		GEngine->GetTableDescHeap()->SetCBV(handle, CBV_REGISTER::b0);
	}

	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = GEngine->GetConstantBuffer()->PushData(0, &_transform, sizeof(_transform));
		GEngine->GetTableDescHeap()->SetCBV(handle, CBV_REGISTER::b1);
	}

	// 3) Table Descriptor Heap Ŀ��
	// GPU Registers�� ����� �� �ֵ��� �ø��� �۾�
	GEngine->GetTableDescHeap()->CommitTable();

	CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0);
}
