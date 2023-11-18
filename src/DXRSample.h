#pragma once
#include "Application.h"

#include <dxcapi.h>
#include <vector>

#include "nv_helpers_dx12/TopLevelASGenerator.h"
#include "nv_helpers_dx12/ShaderBindingTableGenerator.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

struct AccelerationStructureBuffers
{
	ComPtr<ID3D12Resource> pScratch;      // Scratch memory for AS builder
	ComPtr<ID3D12Resource> pResult;       // Where the AS is
	ComPtr<ID3D12Resource> pInstanceDesc; // Hold the matrices of the instances
};

class DXRSample : public Application
{
public:
	DXRSample(UINT width, UINT height, std::string name);

	virtual void OnInit();
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnDestroy();

private:
	void LoadPipeline();
	void LoadAssets();
	void PopulateCommandList();
	void WaitForPreviousFrame();

	void CheckRaytracingSupport();

	AccelerationStructureBuffers CreateBottomLevelAS(
		std::vector<std::pair<ComPtr<ID3D12Resource>, uint32_t>> vVertexBuffers,
		std::vector<std::pair<ComPtr<ID3D12Resource>, uint32_t>> vIndexBuffers =
		{});

	void CreateTopLevelAS(
		const std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX>>
		& instances,
		bool updateOnly = false);

	void CreateAccelerationStructures();

	ComPtr<ID3D12RootSignature> CreateRayGenSignature();
	ComPtr<ID3D12RootSignature> CreateMissSignature();
	ComPtr<ID3D12RootSignature> CreateHitSignature();
	void CreateRaytracingPipeline();

	void CreateRaytracingOutputBuffer();
	void CreateShaderResourceHeap();

	void CreateShaderBindingTable();

	virtual void OnKeyUp(UINT8 key);

private:
	static const UINT FrameCount = 2;
	bool m_raster = true;

	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	// Pipeline objects.
	CD3DX12_VIEWPORT m_viewport;
	CD3DX12_RECT m_scissorRect;
	ComPtr<IDXGISwapChain3> m_swapChain;
	ComPtr<ID3D12Device5> m_device;
	ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12RootSignature> m_rootSignature;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12PipelineState> m_pipelineState;
	ComPtr<ID3D12GraphicsCommandList4> m_commandList;
	UINT m_rtvDescriptorSize;

	// App resources.
	ComPtr<ID3D12Resource> m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	// Synchronization objects.
	UINT m_frameIndex;
	HANDLE m_fenceEvent;
	ComPtr<ID3D12Fence> m_fence;
	UINT64 m_fenceValue;

	// DXR
	ComPtr<ID3D12Resource> m_bottomLevelAS; // Storage for the bottom Level AS
	nv_helpers_dx12::TopLevelASGenerator m_topLevelASGenerator;
	AccelerationStructureBuffers m_topLevelASBuffers;
	std::vector<std::pair<ComPtr<ID3D12Resource>, DirectX::XMMATRIX >> m_instances;

	ComPtr<IDxcBlob> m_rayGenLibrary;
	ComPtr<IDxcBlob> m_hitLibrary;
	ComPtr<IDxcBlob> m_missLibrary;

	ComPtr<ID3D12RootSignature> m_rayGenSignature;
	ComPtr<ID3D12RootSignature> m_hitSignature;
	ComPtr<ID3D12RootSignature> m_missSignature;

	ComPtr<ID3D12StateObject> m_rtStateObject;
	ComPtr<ID3D12StateObjectProperties> m_rtStateObjectProps;

	ComPtr<ID3D12Resource> m_outputResource;
	ComPtr<ID3D12DescriptorHeap> m_srvUavHeap;

	nv_helpers_dx12::ShaderBindingTableGenerator m_sbtHelper;
	ComPtr<ID3D12Resource> m_sbtStorage;
};
