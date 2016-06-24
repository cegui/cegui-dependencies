/***********************************************************************
    created:    6/6/2016
    author:     Yaron Cohen-Tal

    purpose:    Defines Direct3D stuff missing from some MinGW-w64 versions.
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2016 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/

#ifndef _d3d11_effects_mingw_supplements_h_
#define _d3d11_effects_mingw_supplements_h_

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif
#include <windef.h>

#ifdef __MINGW64_VERSION_MAJOR

#if __MINGW64_VERSION_MAJOR < 5

    typedef enum _D3D_SHADER_VARIABLE_FLAGS
    {   D3D_SVF_USERPACKED	= 1,
        D3D_SVF_USED	= 2,
        D3D_SVF_INTERFACE_POINTER	= 4,
        D3D_SVF_INTERFACE_PARAMETER	= 8,
        D3D10_SVF_USERPACKED	= D3D_SVF_USERPACKED,
        D3D10_SVF_USED	= D3D_SVF_USED,
        D3D11_SVF_INTERFACE_POINTER	= D3D_SVF_INTERFACE_POINTER,
        D3D11_SVF_INTERFACE_PARAMETER	= D3D_SVF_INTERFACE_PARAMETER,
        D3D_SVF_FORCE_DWORD	= 0x7fffffff
    } D3D_SHADER_VARIABLE_FLAGS;

#endif

#define D3DX11INLINE inline
#define D3D11_SHVER_GET_TYPE(_Version) \
    (((_Version) >> 16) & 0xffff)
#define	D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT	( 32 )
#define	D3D11_KEEP_UNORDERED_ACCESS_VIEWS	( 0xffffffff )
#define	D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL	( 0xffffffff )
#define D3D11_DEFAULT_BORDER_COLOR_COMPONENT	( 0.0f )

typedef enum D3D11_SHADER_VERSION_TYPE
{
    D3D11_SHVER_PIXEL_SHADER    = 0,
    D3D11_SHVER_VERTEX_SHADER   = 1,
    D3D11_SHVER_GEOMETRY_SHADER = 2,

    // D3D11 Shaders
    D3D11_SHVER_HULL_SHADER     = 3,
    D3D11_SHVER_DOMAIN_SHADER   = 4,
    D3D11_SHVER_COMPUTE_SHADER  = 5,
} D3D11_SHADER_VERSION_TYPE;

typedef enum D3D11_BUFFEREX_SRV_FLAG
{
    D3D11_BUFFEREX_SRV_FLAG_RAW	= 0x1
} D3D11_BUFFEREX_SRV_FLAG;

typedef enum D3D11_BUFFER_UAV_FLAG
{
    D3D11_BUFFER_UAV_FLAG_RAW	= 0x1,
    D3D11_BUFFER_UAV_FLAG_APPEND	= 0x2,
    D3D11_BUFFER_UAV_FLAG_COUNTER	= 0x4
} D3D11_BUFFER_UAV_FLAG;

#define INTSAFE_E_ARITHMETIC_OVERFLOW   ((HRESULT)0x80070216L)  // 0x216 = 534 = ERROR_ARITHMETIC_OVERFLOW
inline HRESULT UIntAdd(UINT uAugend, UINT uAddend, UINT *puResult)
{
    UINT result = uAugend +uAddend;
    if (result < uAugend)
        return INTSAFE_E_ARITHMETIC_OVERFLOW;
    *puResult = result;
    return S_OK;
}

#if !defined( D3D11_NO_HELPERS ) && defined( __cplusplus )

    struct CD3D11_DEPTH_STENCIL_DESC : public D3D11_DEPTH_STENCIL_DESC
    {
        CD3D11_DEPTH_STENCIL_DESC()
        {}
        explicit CD3D11_DEPTH_STENCIL_DESC( const D3D11_DEPTH_STENCIL_DESC& o ) :
            D3D11_DEPTH_STENCIL_DESC( o )
        {}
        explicit CD3D11_DEPTH_STENCIL_DESC( CD3D11_DEFAULT )
        {
            DepthEnable = TRUE;
            DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
            DepthFunc = D3D11_COMPARISON_LESS;
            StencilEnable = FALSE;
            StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
            StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
            const D3D11_DEPTH_STENCILOP_DESC defaultStencilOp =
            { D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS };
            FrontFace = defaultStencilOp;
            BackFace = defaultStencilOp;
        }
        explicit CD3D11_DEPTH_STENCIL_DESC(
            BOOL depthEnable,
            D3D11_DEPTH_WRITE_MASK depthWriteMask,
            D3D11_COMPARISON_FUNC depthFunc,
            BOOL stencilEnable,
            UINT8 stencilReadMask,
            UINT8 stencilWriteMask,
            D3D11_STENCIL_OP frontStencilFailOp,
            D3D11_STENCIL_OP frontStencilDepthFailOp,
            D3D11_STENCIL_OP frontStencilPassOp,
            D3D11_COMPARISON_FUNC frontStencilFunc,
            D3D11_STENCIL_OP backStencilFailOp,
            D3D11_STENCIL_OP backStencilDepthFailOp,
            D3D11_STENCIL_OP backStencilPassOp,
            D3D11_COMPARISON_FUNC backStencilFunc )
        {
            DepthEnable = depthEnable;
            DepthWriteMask = depthWriteMask;
            DepthFunc = depthFunc;
            StencilEnable = stencilEnable;
            StencilReadMask = stencilReadMask;
            StencilWriteMask = stencilWriteMask;
            FrontFace.StencilFailOp = frontStencilFailOp;
            FrontFace.StencilDepthFailOp = frontStencilDepthFailOp;
            FrontFace.StencilPassOp = frontStencilPassOp;
            FrontFace.StencilFunc = frontStencilFunc;
            BackFace.StencilFailOp = backStencilFailOp;
            BackFace.StencilDepthFailOp = backStencilDepthFailOp;
            BackFace.StencilPassOp = backStencilPassOp;
            BackFace.StencilFunc = backStencilFunc;
        }
        ~CD3D11_DEPTH_STENCIL_DESC() {}
        operator const D3D11_DEPTH_STENCIL_DESC&() const { return *this; }
    };

#endif

extern "C"
{
    struct ID3DX11ThreadPump;
    HRESULT WINAPI D3DX11CompileFromMemory(LPCSTR pSrcData, SIZE_T SrcDataLen, LPCSTR pFileName, CONST D3D10_SHADER_MACRO* pDefines, LPD3D10INCLUDE pInclude, 
LPCSTR pFunctionName, LPCSTR pProfile, UINT Flags1, UINT Flags2, ID3DX11ThreadPump* pPump, ID3D10Blob** ppShader, ID3D10Blob** ppErrorMsgs, HRESULT* pHResult);
}

#endif

#endif
