#pragma once
#include "../Base/Win/WinAPI.h"
#include "../Base/BaseCategory.h"
#include "Rectangle.h"
#include "Text.h"


using Microsoft::WRL::ComPtr;
using namespace DirectX;

// Function pointer type for D3DCompile
typedef HRESULT(WINAPI* pD3DCompile)(LPCVOID, SIZE_T, LPCSTR, const D3D_SHADER_MACRO*, ID3DInclude*, LPCSTR, LPCSTR, UINT, UINT, ID3DBlob**, ID3DBlob**);


struct Vertex {
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};

struct floatRectangle {
    XMFLOAT2 Position;
    XMFLOAT2 Size;
    XMFLOAT4 Color;
};


class _Graphics {
public:
    _Graphics(HWND extHwnd, int extWidth, int extHeight)
    {
        hwnd = extHwnd;
        width = extWidth;
        height = extHeight;

        loadD3DCompile();
        initializeD3D();
        initializeD2D();
        createShaders();
        createConstantBuffer();
    }


    ~_Graphics() {
        if (d3dCompilerDll)
            FreeLibrary(d3dCompilerDll);

        if (D2D1Factory) {
            D2D1Factory->Release();
            D2D1Factory = nullptr;
        }

        if (dWriteFactory) {
            dWriteFactory->Release();
            dWriteFactory = nullptr;
        }

        if (D2DRenderTarget) {
            D2DRenderTarget->Release();
            D2DRenderTarget = nullptr;
        }
    }


    void draw(const tl::Rectangle& rectangle)
    {
        DrawableObject obj;
        obj.type = DrawableType::Rectangle;
        obj.rectangle = rectangle;
        drawQueue.push(obj);
    }


    void draw(tl::Text& text)
    {
        DrawableObject obj;
        obj.type = DrawableType::Text;
        obj.text = text;
        drawQueue.push(obj);
    }


    void clear(tl::Color& color)
    {
        float clearColor[4] = { color.r / 255.f, color.g / 255.f, color.b / 255.f, 1.0f };
        context->ClearRenderTargetView(renderTargetView.Get(), clearColor);
        drawQueue.clear();
    }


    void display()
    {
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        context->IASetInputLayout(nullptr);
        context->VSSetShader(vertexShader.Get(), nullptr, 0);
        context->PSSetShader(pixelShader.Get(), nullptr, 0);
        context->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

        D2DRenderTarget->BeginDraw();

        for (const auto& obj : drawQueue)
        {
            if (obj.type == DrawableType::Rectangle)
            {
                floatRectangle rect;
                rect.Color = { FLOAT(obj.rectangle.getColor().r) / 255.f, FLOAT(obj.rectangle.getColor().g) / 255.f, FLOAT(obj.rectangle.getColor().b) / 255.f, 1.0f };
                rect.Position = { FLOAT(obj.rectangle.getPosition().x), FLOAT(obj.rectangle.getPosition().y) };
                rect.Size = { FLOAT(obj.rectangle.getSize().x), FLOAT(obj.rectangle.getSize().y) };
                updateConstantBuffer(rect);
                context->Draw(4, 0);
            }
            else if (obj.type == DrawableType::Text)
            {
                drawText(obj.text);
            }
        }

        D2DRenderTarget->EndDraw();

        HRESULT hr = swapChain->Present(0, 0);
        if (FAILED(hr)) {
            MessageBoxA(nullptr, "Failed to present swap chain", "Error", MB_OK);
        }

        drawQueue.clear();
    }

private:
    HWND hwnd;
    unsigned int width, height;


    wchar_t* asciiToWide(const char* asciiStr) {
        int length = tl::strlen(asciiStr);

        wchar_t* wideStr = new wchar_t[length + 1];

        for (int i = 0; i < length; ++i) {
            wideStr[i] = static_cast<wchar_t>(asciiStr[i]);
        }

        wideStr[length] = L'\0';

        return wideStr;
    }


    void loadD3DCompile() {
        d3dCompilerDll = LoadLibraryA("d3dcompiler_47.dll");
        D3DCompile = (pD3DCompile)GetProcAddress(d3dCompilerDll, "D3DCompile");
    }


    void initializeD3D()
    {
#ifdef NDEBUG
        UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#else
        UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
        swapChainDesc.BufferCount = 1;
        swapChainDesc.BufferDesc.Width = width;
        swapChainDesc.BufferDesc.Height = height;
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.OutputWindow = hwnd;
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
        swapChainDesc.Windowed = TRUE;

        HRESULT hr = D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags,
            featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc,
            &swapChain, &device, nullptr, &context);

        if (FAILED(hr)) {
            MessageBoxA(nullptr, "Failed to create device and swap chain", "Error", MB_OK);
        }


        ComPtr<ID3D11Texture2D> backBuffer;
        hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
        if (FAILED(hr)) {
            MessageBoxA(nullptr, "Failed to get back buffer", "Error", MB_OK);
        }

        hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView);
        if (FAILED(hr)) {
            MessageBoxA(nullptr, "Failed to create render target view", "Error", MB_OK);
        }

        context->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

        D3D11_VIEWPORT viewport = {};
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = static_cast<float>(width);
        viewport.Height = static_cast<float>(height);
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        context->RSSetViewports(1, &viewport);
    }


    void initializeD2D()
    {
        HRESULT result = S_OK;
        D2D1_SIZE_U size = D2D1::SizeU(width, height);

        auto options = D2D1_FACTORY_OPTIONS();
#ifdef NDEBUG
        options.debugLevel = D2D1_DEBUG_LEVEL_NONE;
#else
        options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif
        result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, &D2D1Factory);
        if (FAILED(result)) {
            return;
        }

        result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&dWriteFactory));
        if (FAILED(result)) {
            return;
        }

        if (swapChain == nullptr)
            return;

        ComPtr<IDXGISurface1> d2dRT;
        result = swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgi));
        if (FAILED(result))
        {
            return;
        }
        auto d2dRTProps = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0);
        result = D2D1Factory->CreateDxgiSurfaceRenderTarget(dxgi.Get(), &d2dRTProps, &D2DRenderTarget);

        if (FAILED(result))
        {
            OutputDebugStringA("Didn't make the render target");
            return;
        }
    }


    void createGeometryBuffers()
    {
        tl::Vector<Vertex> vertices;
        vertices.push({ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) });
        vertices.push({ XMFLOAT3(0.0f,  0.5f, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) });
        vertices.push({ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) });

        vertexCount = vertices.getSize();

        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = &vertices[0];

        HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &vertexBuffer);
        if (FAILED(hr)) {
            MessageBoxA(nullptr, "Failed to create vertex buffer", "Error", MB_OK);
        }
    }


    void createShaders()
    {
        const char* vsSource = R"(
            cbuffer ConstantBuffer : register(b0)
            {
                float2 Position;
                float2 Size;
                float4 Color;
                float2 ScreenSize;
            };

            struct VS_OUTPUT { float4 Pos : SV_POSITION; float4 Color : COLOR; };

            VS_OUTPUT VS(uint vertexID : SV_VertexID)
            {
                VS_OUTPUT output;
                float2 pos = Position;
                if (vertexID == 1 || vertexID == 3) pos.x += Size.x;
                if (vertexID == 2 || vertexID == 3) pos.y += Size.y;
                
                // Convert to clip space
                output.Pos = float4(pos.x / ScreenSize.x * 2 - 1, 
                                    1 - pos.y / ScreenSize.y * 2, 
                                    0, 1);
                output.Color = Color;
                return output;
            }
        )";

        ComPtr<ID3DBlob> vsBlob;
        ComPtr<ID3DBlob> errorBlob;
        HRESULT hr = D3DCompile(vsSource, tl::strlen(vsSource), nullptr, nullptr, nullptr, "VS", "vs_4_0", 0, 0, &vsBlob, &errorBlob);
        if (FAILED(hr)) {
            if (errorBlob) {
                MessageBoxA(nullptr, static_cast<char*>(errorBlob->GetBufferPointer()), "Vertex Shader Compilation Error", MB_OK);
            }
        }
        hr = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
        if (FAILED(hr)) {
            MessageBoxA(nullptr, "Failed to create vertex shader", "Error", MB_OK);
        }


        const char* psSource = R"(
            struct PS_INPUT { float4 Pos : SV_POSITION; float4 Color : COLOR; };
            float4 PS(PS_INPUT input) : SV_Target { return input.Color; }
        )";

        ComPtr<ID3DBlob> psBlob;
        hr = D3DCompile(psSource, tl::strlen(psSource), nullptr, nullptr, nullptr, "PS", "ps_4_0", 0, 0, &psBlob, &errorBlob);
        if (FAILED(hr)) {
            if (errorBlob) {
                MessageBoxA(nullptr, static_cast<char*>(errorBlob->GetBufferPointer()), "Pixel Shader Compilation Error", MB_OK);
            }
        }
        hr = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
        if (FAILED(hr)) {
            MessageBoxA(nullptr, "Failed to create pixel shader", "Error", MB_OK);
        }
    }


    void createConstantBuffer() {
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.ByteWidth = ((sizeof(floatRectangle) + sizeof(XMFLOAT2) + 15) / 16) * 16;
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT hr = device->CreateBuffer(&bufferDesc, nullptr, &constantBuffer);
        if (FAILED(hr)) {
            MessageBoxA(nullptr, "Failed to create constant buffer", "Error", MB_OK);
        }
    }


    enum class DrawableType {
        Rectangle,
        Text
    };

    struct DrawableObject {
        DrawableType type;
        union {
            tl::Rectangle rectangle;
            tl::Text text;
        };

        DrawableObject() {}
        ~DrawableObject() {}
    };

    tl::Vector<DrawableObject> drawQueue;

    void drawText(const tl::Text& text)
    {
        ComPtr<IDWriteTextFormat> textFormat;
        dWriteFactory->CreateTextFormat(
            L"Arial", NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL, text.getSize().y / 2.f, L"en-us", &textFormat
        );

        ComPtr<ID2D1SolidColorBrush> pBrush;
        D2DRenderTarget->CreateSolidColorBrush(
            D2D1::ColorF(text.getColor().r / 255.f, text.getColor().g / 255.f, text.getColor().b / 255.f, 1.0f),
            &pBrush
        );

        D2D1_RECT_F textRect = D2D1::RectF(
            text.getPosition().x,
            text.getPosition().y,
            text.getPosition().x + text.getSize().x,
            text.getPosition().y + text.getSize().y
        );

        wchar_t* wideStr = asciiToWide(text.getString());

        D2DRenderTarget->DrawText(
            wideStr,
            tl::strlen(text.getString()),
            textFormat.Get(),
            &textRect,
            pBrush.Get()
        );

        if (wideStr != nullptr)
        {
            delete[] wideStr;
            wideStr = nullptr;
        }
    }


    void updateConstantBuffer(const floatRectangle& rect)
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        HRESULT hr = context->Map(constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        if (SUCCEEDED(hr)) {
            struct CBData {
                floatRectangle rect;
                XMFLOAT2 screenSize;
            };
            CBData* dataPtr = reinterpret_cast<CBData*>(mappedResource.pData);
            dataPtr->rect = rect;
            dataPtr->screenSize = XMFLOAT2(static_cast<float>(width), static_cast<float>(height));
            context->Unmap(constantBuffer.Get(), 0);
        }
    }


    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;
    ComPtr<IDXGISwapChain> swapChain;
    ComPtr<ID3D11RenderTargetView> renderTargetView;
    ComPtr<ID3D11VertexShader> vertexShader;
    ComPtr<ID3D11PixelShader> pixelShader;
    ComPtr<ID3D11Buffer> constantBuffer;
    ComPtr<IDXGISurface> dxgi;

    ID2D1RenderTarget* D2DRenderTarget;
    IDWriteFactory* dWriteFactory;
    ID2D1Factory* D2D1Factory;
    IDWriteTextFormat* textFormat;

    HMODULE d3dCompilerDll;
    pD3DCompile D3DCompile;

    unsigned int vertexCount;
    ComPtr<ID3D11Buffer> vertexBuffer;

    tl::Vector<floatRectangle> rectangles;
};