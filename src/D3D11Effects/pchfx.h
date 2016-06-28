//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) Microsoft Corporation.  All Rights Reserved.
//
//  File:       pchfx.h
//  Content:    D3D shader effects precompiled header
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __D3DX11_PCHFX_H__
#define __D3DX11_PCHFX_H__

#include "d3d11.h"

#ifdef __MINGW32__
	#include "d3dx9.h"
        #include "d3d11-effects-mingw-supplements.h"
#else
	#include "d3dx11.h"
#endif

#ifdef __MINGW32__

    #define __assume(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)
    #define __in
    #define __in_bcount(foo)
    #define __out_bcount(foo)
    #define __in_ecount_opt(foo)
    #define __in_ecount(foo)
    #define __out_ecount(foo)
    #define __in_z
    #define __inout_z
    #define __deref_out_z
    #define __deref_inout_z
    #define __out_ecount_full(foo)
    #define __out_bcount_opt(foo)
    #define __inout(foo)

#endif

#undef DEFINE_GUID
#include "initguid.h"
#include "d3dx11effect.h"

#define UNUSED -1

//////////////////////////////////////////////////////////////////////////

#define offsetof_fx( a, b ) (UINT)offsetof( a, b )

#include "d3dxGlobal.h"

#include <stddef.h>
#include <strsafe.h>


#include "Effect.h"
#include "EffectStateBase11.h"
#include "EffectLoad.h"

#include "d3dcompiler.h"

//////////////////////////////////////////////////////////////////////////

namespace D3DX11Effects
{
} // end namespace D3DX11Effects

#endif // __D3DX11_PCHFX_H__
