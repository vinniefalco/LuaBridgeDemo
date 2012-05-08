/*
  ==============================================================================

  Copyright (c) 2012, Vinnie Falco <vinnie.falco@gmail.com>

  This file is provided under the terms of the MIT License:

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ==============================================================================
*/

#include "AppConfig.h"

#if _MSC_VER
#pragma push_macro("_CRT_SECURE_NO_WARNINGS")
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* luaconf.h only declares some things if it is being included
   from certain source files. We define all the relevant macros
   and include luaconf.h once so we get all the declarations.
*/
#define lobject_c
#define lvm_c
#define LUA_CORE
#define LUA_LIB
#include "Lua_5_2/luaconf.h"
#undef lobject_c
#undef lvm_c
#undef LUA_CORE
#undef LUA_LIB

#if _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4244) /* Possible loss of data */
#pragma warning (disable: 4702) /* Unreachable code */
#endif

/* Include this early to prevent the conflict with luai_hashnum
   and supress the warning caused by #define lua_assert
*/
#include "Lua_5_2/ltable.c"

#include "Lua_5_2/lauxlib.c"
#include "Lua_5_2/lbaselib.c"

#include "Lua_5_2/lbitlib.c"
#include "Lua_5_2/lcorolib.c"
#include "Lua_5_2/ldblib.c"
#include "Lua_5_2/linit.c"
#include "Lua_5_2/liolib.c"
#include "Lua_5_2/lmathlib.c"
#include "Lua_5_2/loslib.c"
#include "Lua_5_2/lstrlib.c"
#include "Lua_5_2/ltablib.c"

#include "Lua_5_2/lapi.c"
#include "Lua_5_2/lcode.c"
#include "Lua_5_2/lctype.c"
#include "Lua_5_2/ldebug.c"
#include "Lua_5_2/ldo.c"
#include "Lua_5_2/ldump.c"
#include "Lua_5_2/lfunc.c"
#include "Lua_5_2/lgc.c"
#include "Lua_5_2/llex.c"
#include "Lua_5_2/lmem.c"
#include "Lua_5_2/lobject.c"
#include "Lua_5_2/lopcodes.c"
#include "Lua_5_2/lparser.c"
#include "Lua_5_2/lstate.c"
#include "Lua_5_2/lstring.c"
#include "Lua_5_2/ltm.c"
#include "Lua_5_2/lundump.c"
#include "Lua_5_2/lvm.c"
#include "Lua_5_2/lzio.c"

/* loadlib.c includes Windows.h, which defines the LoadString macro,
   so include it last to prevent errors.
*/
#include "Lua_5_2/loadlib.c"

#if _MSC_VER
#pragma warning (pop)
#endif

#ifdef __cplusplus
}
#endif

#if _MSC_VER
#pragma pop_macro("_CRT_SECURE_NO_WARNINGS")
#endif
