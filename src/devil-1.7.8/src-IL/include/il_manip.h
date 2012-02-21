//-----------------------------------------------------------------------------
//
// ImageLib Sources
// Copyright (C) 2001-2002 by Denton Woods
// Last modified: 05/25/2001 <--Y2K Compliant! =]
//
// Filename: src-IL/include/il_manip.h
//
// Description: Image manipulation
//
//-----------------------------------------------------------------------------

#ifndef MANIP_H
#define MANIP_H

#ifdef _cplusplus
extern "C" {
#endif

ILboolean ilFlipImage(void);
ILboolean ilMirrorImage(void);	//@JASON New routine created 03/28/2001

//-----------------------------------------------
// Overflow handler for float-to-half conversion;
// generates a hardware floating-point overflow,
// which may be trapped by the operating system.
//-----------------------------------------------
#ifndef NOINLINE

ILfloat /*ILAPIENTRY*/ ilFloatToHalfOverflow();

//-----------------------------------------------------
// Float-to-half conversion -- general case, including
// zeroes, denormalized numbers and exponent overflows.
//-----------------------------------------------------
INLINE ILushort ILAPIENTRY ilFloatToHalf(ILuint i);
// Taken from OpenEXR
INLINE ILuint ILAPIENTRY ilHalfToFloat (ILushort y);
#endif //NOINLINE

#ifdef _cplusplus
}
#endif

#endif//MANIP_H
