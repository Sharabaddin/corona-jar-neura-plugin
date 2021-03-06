// ----------------------------------------------------------------------------
// 
// json.cpp
// Copyright (c) 2016 Corona Labs, Inc. All rights reserved.
// 
// Reviewers:
// 		
// 
// ----------------------------------------------------------------------------

#include "Core/Rtt_Build.h"

#include "Rtt_Lua.h"

#ifndef LUAOPEN_API 
#define LUAOPEN_API 
#endif

// ----------------------------------------------------------------------------

namespace Rtt
{

// ----------------------------------------------------------------------------

static const unsigned char B1[]={
 27, 76,117, 97, 81,  0,  1,  4,  4,  4,  8,  0,  3,  0,  0,  0, 61, 63,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  7, 25,  0,  0,  0,  5,  0,  0,  0, 65,
 64,  0,  0, 28,128,  0,  1, 70,128, 64,  0,129,192,  0,  0, 85,128,128,  0,  9,
 64,  0,129, 70,  0, 65,  0,134, 64, 65,  0,228,  0,  0,  0,  0,  0,128,  0, 36,
 65,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,100,129,  0,  0,  0,  0,128,  0,  0,
  0,  0,  2,164,193,  0,  0,  0,  0,128,  1,  9,192,  0,130,  9,128,  1,131,  9,
  0,129,130,  9, 64,129,131, 30,  0,  0,  1, 30,  0,128,  0,  8,  0,  0,  0,  4,
  8,  0,  0,  0,114,101,113,117,105,114,101,  0,  4,  7,  0,  0,  0,100,107,106,
115,111,110,  0,  4,  8,  0,  0,  0,118,101,114,115,105,111,110,  0,  4,  3,  0,
  0,  0, 45, 49,  0,  4,  7,  0,  0,  0,100,101, 99,111,100,101,  0,  4,  7,  0,
  0,  0,101,110, 99,111,100,101,  0,  4, 11,  0,  0,  0,100,101, 99,111,100,101,
 70,105,108,101,  0,  4,  9,  0,  0,  0,112,114,101,116,116,105,102,121,  0,  4,
  0,  0,  0,  0,  0,  0,  0, 22,  0,  0,  0, 30,  0,  0,  0,  1,  3,  3,  9, 15,
  0,  0,  0, 23,  0, 64,  0, 22,  0,  1,128,  5, 65,  0,  0, 65,129,  0,  0,129,
193,  0,  0, 28, 65,128,  1, 22,128,  1,128,  4,  1,  0,  0, 64,  1,  0,  0,128,
  1,128,  0,192,  1,  0,  1, 37,  2,  0,  0, 29,  1,  0,  0, 30,  1,  0,  0, 30,
  0,128,  0,  4,  0,  0,  0,  0,  4,  6,  0,  0,  0,101,114,114,111,114,  0,  4,
 35,  0,  0,  0,106,115,111,110, 46,100,101, 99,111,100,101, 32, 99, 97,108,108,
101,100, 32,119,105,116,104, 32,110,105,108, 32,115,116,114,105,110,103,  0,  3,
  0,  0,  0,  0,  0,  0,  0, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0, 32,  0,  0,  0, 44,  0,  0,  0,  2,  2,  0,  5,
 16,  0,  0,  0, 23,  0,192,  0, 22, 64,  0,128,138,  0,  0,  0, 64,  0,  0,  1,
134, 64,192,  0, 23,  0, 64,  1, 22,128,  0,128,132,  0,  0,  0,134,128, 64,  1,
 73,128,128,128,132,  0,128,  0,192,  0,  0,  0,  0,  1,128,  0,157,  0,128,  1,
158,  0,  0,  0, 30,  0,128,  0,  3,  0,  0,  0,  0,  4, 10,  0,  0,  0,101,120,
 99,101,112,116,105,111,110,  0,  4, 16,  0,  0,  0,101,110, 99,111,100,101,101,
120, 99,101,112,116,105,111,110,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0, 46,  0,  0,  0, 79,  0,  0,  0,  2,  1,  0,
 10, 79,  0,  0,  0, 23,  0, 64,  0, 22,  0,  1,128,197, 64,  0,  0,  1,129,  0,
  0, 65,193,  0,  0,220, 64,128,  1, 22, 64, 12,128,197,  0,  1,  0,  0,  1,  0,
  0,220,128,  0,  1, 23, 64,193,  1, 22,  0,  7,128,203,128, 65,  0,220,128,  0,
  1,  4,  1,  0,  0, 64,  1,  0,  0, 28,  1,  1,  1,128,  0,  0,  3, 64,  0,128,
  2,  0,  0,  0,  2, 87,  0, 64,  1, 22,128,  2,128,  5, 65,  0,  0, 65,193,  1,
  0,133,  1,  2,  0,192,  1,  0,  1,156,129,  0,  1, 85,129,129,  2,129,193,  0,
  0, 28, 65,128,  1,  3,  1,  0,  2, 30,  1,  0,  1, 22,192,  5,128, 24,192,128,
  0, 22, 64,  5,128,  5, 65,  2,  0, 65,129,  2,  0, 28, 65,  0,  1,  3,  1,  0,
  2, 30,  1,  0,  1, 22,192,  3,128,197,  0,  1,  0,  0,  1,  0,  0,220,128,  0,
  1, 87,192,194,  1, 22,128,  2,128,197, 64,  0,  0,  1,  1,  3,  0, 69,  1,  1,
  0,128,  1,  0,  0, 92,129,  0,  1,129, 65,  3,  0, 21,129,  1,  2, 65,193,  0,
  0,220, 64,128,  1,195,  0,128,  1,222,  0,  0,  1,202,  0,  0,  0,  5,129,  3,
  0, 64,  1,  0,  0, 28,  1,  1,  1, 22,128,  0,128, 84,  2,128,  1, 76,194,195,
  4,201,192,129,  4, 33,129,  0,  0, 22,128,254,127,  5,193,  2,  0,  6,  1, 68,
  2, 64,  1,128,  1, 28, 65,  0,  1,  4,  1,128,  0, 64,  1,  0,  0,138,129,  0,
  0,137,129,196,136,137,193,128,137, 29,  1,128,  1, 30,  1,  0,  0, 30,  0,128,
  0, 20,  0,  0,  0,  0,  4,  6,  0,  0,  0,101,114,114,111,114,  0,  4, 37,  0,
  0,  0,106,115,111,110, 46,112,114,101,116,116,105,102,121, 32, 99, 97,108,108,
101,100, 32,119,105,116,104, 32,110,105,108, 32,115,116,114,105,110,103,  0,  3,
  0,  0,  0,  0,  0,  0,  0, 64,  4,  5,  0,  0,  0,116,121,112,101,  0,  4,  7,
  0,  0,  0,115,116,114,105,110,103,  0,  4,  4,  0,  0,  0,108,101,110,  0,  4,
 31,  0,  0,  0,106,115,111,110, 46,112,114,101,116,116,105,102,121, 58, 32,105,
110,118, 97,108,105,100, 32,105,110,112,117,116, 58, 32,  0,  4,  9,  0,  0,  0,
116,111,115,116,114,105,110,103,  0,  4,  6,  0,  0,  0,112,114,105,110,116,  0,
  4, 50,  0,  0,  0, 87, 97,114,110,105,110,103, 58, 32,106,115,111,110, 46,112,
114,101,116,116,105,102,121, 58, 32,101,120,116,114, 97, 32,100, 97,116, 97, 32,
 97,116, 32,101,110,100, 32,111,102, 32, 74, 83, 79, 78,  0,  4,  6,  0,  0,  0,
116, 97, 98,108,101,  0,  4, 46,  0,  0,  0,106,115,111,110, 46,112,114,101,116,
116,105,102,121, 32,116, 97,107,101,115, 32, 97, 32,115,116,114,105,110,103, 32,
111,114, 32, 97, 32,116, 97, 98,108,101, 32, 40,103,111,116, 32,  0,  4,  2,  0,
  0,  0, 41,  0,  4,  6,  0,  0,  0,112, 97,105,114,115,  0,  3,  0,  0,  0,  0,
  0,  0,240, 63,  4,  5,  0,  0,  0,115,111,114,116,  0,  4,  7,  0,  0,  0,105,
110,100,101,110,116,  0,  1,  1,  4,  9,  0,  0,  0,107,101,121,111,114,100,101,
114,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0, 81,  0,  0,  0, 98,  0,  0,  0,  1,  3,  3, 13, 42,  0,  0,  0, 69,  1,
  0,  0, 70, 65,192,  2,128,  1,  0,  0,193,129,  0,  0, 92,193,128,  1, 90, 65,
  0,  0, 22,  0,  2,128,195,  1,128,  3,  1,194,  0,  0, 65,  2,  1,  0,133, 66,
  1,  0,192,  2,  0,  3,156,130,  0,  1, 85,130,130,  4,222,  1,  0,  2, 22,  0,
  5,128,203,129,193,  2, 65,194,  1,  0,220,129,128,  1, 11,  2,194,  2, 28, 66,
  0,  1,  4,  2,  0,  0, 64,  2,128,  3,128,  2,128,  0,192,  2,  0,  1, 37,  3,
  0,  0, 28,  2,  1,  0,135,130,  2,  0, 71, 66,  2,  0,  0,  1,  0,  4,  5,130,
  2,  0, 87,192, 66,  4, 22,192,  0,128,  3,  2,  0,  4, 69, 66,  2,  0,133,130,
  2,  0, 30,  2,  0,  2,192,  1,  0,  2,  1,194,  0,  0, 67,  2,128,  4,222,  1,
  0,  2, 30,  0,128,  0, 12,  0,  0,  0,  4,  3,  0,  0,  0,105,111,  0,  4,  5,
  0,  0,  0,111,112,101,110,  0,  4,  2,  0,  0,  0,114,  0,  3,  0,  0,  0,  0,
  0,  0,  0,  0,  4, 18,  0,  0,  0, 67, 97,110,110,111,116, 32,111,112,101,110,
 32,102,105,108,101, 32,  0,  4,  9,  0,  0,  0,116,111,115,116,114,105,110,103,
  0,  4,  5,  0,  0,  0,114,101, 97,100,  0,  4,  3,  0,  0,  0, 42, 97,  0,  4,
  6,  0,  0,  0, 99,108,111,115,101,  0,  4,  7,  0,  0,  0,108,105,110,101,110,
111,  0,  4,  9,  0,  0,  0,101,114,114,111,114, 77,115,103,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,
};

LUAOPEN_API int
luaload_json(lua_State *L)
{
	return luaL_loadbuffer(L,(const char*)B1,sizeof(B1),"json");
}

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
