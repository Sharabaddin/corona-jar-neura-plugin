// ----------------------------------------------------------------------------
// 
// re.cpp
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
  0,  0,  0,  0,  0,  0,  0,  0,  0,  2, 45,185,  1,  0,  0,  5,  0,  0,  0, 69,
 64,  0,  0,133,128,  0,  0,197,192,  0,  0,  5,  1,  1,  0, 69, 65,  1,  0,129,
129,  1,  0, 92,129,  0,  1,128,  1,128,  2,197,193,  1,  0,  6,  2, 66,  3, 65,
 66,  2,  0, 28,  2,  0,  1,220,129,  0,  0,  5,130,  2,  0, 23,192, 66,  4, 22,
 64,  0,128, 67,  2,128,  4, 71,  2,  3,  0, 70,  2,194,  2,129, 66,  3,  0, 92,
130,  0,  1,138, 66,  0,  0,198,  2,194,  2,  1,195,  3,  0,220,130,  0,  1,137,
194,  2,135,195,  2,128,  6,164,  3,  0,  0,  0,  0,  0,  3,  0,  0,  0,  5,  0,
  0,128,  4,  0,  0,128,  5,  0,  0,  0,  6,  0,  0,128,  6,  0,  0,  0,  2,192,
  3,  0,  7,220, 67,128,  0,198,  3,194,  2, 36, 68,  0,  0,  0,  0,  0,  1,220,
131,  0,  1, 36,132,  0,  0,  0,  0,128,  1,100,196,  0,  0,  0,  0,128,  1,164,
  4,  1,  0,  0,  0,  0,  3,228, 68,  1,  0,  0,  0,128,  0,  6,  5,196,  2, 65,
 69,  4,  0, 28,133,  0,  1, 70,133, 67,  5, 77, 69,133,  4, 81, 69,194, 10, 78,
 69,  5,137, 12, 69,  5, 10, 17, 69, 66, 10, 70,197,196,  2,129,  5,  5,  0,193,
 69,  5,  0, 92,133,128,  1,134,197,196,  2,193,  5,  5,  0,  1, 70,  5,  0, 65,
134,  5,  0,129,198,  5,  0,156,133,128,  2,145, 69, 66, 11, 78,133,133, 10,142,
  5, 70, 10,198,  5,194,  2,  1, 70,  6,  0,220,133,  0,  1,204,133,198, 11,204,
197,198, 11,204,  5,199, 11,204, 69,199, 11, 14,134,133, 10,204,  5,134, 11,204,
133,199, 11,  6,198,199,  2, 64,  6,128, 10, 28,134,  0,  1, 64,  5,  0, 12,  6,
  6,200,  2, 65, 70,  3,  0, 28,134,  0,  1, 14,  6,134, 10, 70,198,199,  2,134,
198,196,  2,193,198,  5,  0,156,134,  0,  1,145, 70, 67, 13, 92,134,  0,  1, 78,
  6,133, 12, 79,  6,128, 12,134,198,199,  2,205, 70,200,  4,209, 70,194, 13,156,
134,  0,  1,142,134,134,144,142, 70, 72, 13,198,198,199,  2, 13,135,200,  4, 17,
 71, 66, 14,220,134,  0,  1,206,198,  6,145,206,134,200, 13,140,198,  6, 13,206,
  6,134,145, 36,135,  1,  0,  0,  0,  0,  5,  0,  0,128,  1,207,  6,135, 13,  6,
  7,201,  2, 70,  7,194,  2,129, 71,  9,  0, 92,135,  0,  1, 79,135,201, 14, 78,
 71,135,  4,141,199,201,  4, 78,135,135, 14, 28,135,  0,  1, 70,199, 68,  3, 15,
 71,  7, 14, 76,  7,135, 13,134,199,199,  2,192,  7,128,  4,156,135,  0,  1, 76,
135,135, 14,134,199,199,  2,198,  7,194,  2,  1, 72, 10,  0,220,135,  0,  1,209,
135,199, 15,156,135,  0,  1,142,135,  7,148,198,135,202,  2, 13,200,201, 14, 17,
 72, 66, 16, 14,  8,136, 14, 70,200,202,  3,220,135,128,  1,142,199,  7, 15,228,
199,  1,  0,  0,  0,128,  4,143,199,  7, 15,142,199, 73, 15,228,  7,  2,  0,  0,
  0,128,  1, 36, 72,  2,  0,  0,  0,128, 15, 70,  8,194,  2,138,200,129,  0,193,
  8, 11,  0,  6, 73,203,  2, 65,137, 11,  0, 28,137,  0,  1, 70,137,202,  2,134,
 73,203,  2,193,201, 11,  0,156,137,  0,  1,206,  9,133,140,  6, 74,203,  2, 65,
202, 11,  0, 28,138,  0,  1,206,  9,138, 19,209, 73,194, 19,142,201,  9, 19,198,
201,202,  3, 92,137,128,  1, 12, 73,  9, 18, 14,  9,  9, 10,137,  8,  9,150,  6,
137,202,  2, 70,  9,204,  2,134,  9,194,  2,193,137,  9,  0,156,  9,  0,  1, 92,
137,  0,  0,134, 73,203,  2,193, 73, 12,  0,156,137,  0,  1,145, 73, 66, 19, 78,
137,137, 18,134,137,204,  3, 28,137,128,  1, 84,  9,128, 11, 76, 73,132, 18, 14,
 73,  9, 18,137,  8,137,151, 14,  9,133,153, 70, 73,203,  2,129, 73, 12,  0, 92,
137,  0,  1, 14, 73,  9, 18, 70,  9,205,  3, 15, 73,  9, 18, 78,  9,133,154,134,
 73,203,  2,193, 73, 12,  0,156,137,  0,  1, 78,137,137, 18,134,137,205,  3, 79,
137,137, 18, 12, 73,  9, 18, 70, 73,203,  2,129,201, 13,  0, 92,137,  0,  1, 12,
 73,  9, 18,137,  8,137,152,  6,137,202,  2, 70, 73,203,  2,129,  9, 14,  0, 92,
137,  0,  1, 78,  9,133, 18,134,  9,194,  2,193, 73, 14,  0,156,137,  0,  1,198,
  9,204,  2,  1, 74,  3,  0, 70,138,206,  3,220,137,128,  1,142,201,  9, 19,198,
  9,194,  2,  1,202, 14,  0,220,137,  0,  1,  6, 10,204,  2, 65, 74,  2,  0,134,
138,206,  3, 28,138,128,  1,206,  9,138, 19,140,201,  9, 19,198,  9,194,  2,  1,
 10, 15,  0,220,137,  0,  1,  6, 10,204,  2, 65,138,  7,  0,134,138,206,  3, 28,
138,128,  1,206,  9,138, 19,140,201,  9, 19,198, 73,207,  2,  6, 10,204,  2, 64,
 10,  0,  9, 28,138,  0,  1, 14, 10,138, 12,220,137,  0,  1,  6, 74,207,  2, 70,
202,199,  2,134, 10,196,  2,193,138, 15,  0,156,138,  0,  1,198,202,196,  2,  1,
203,  5,  0,220,138,  0,  1,209, 74,195, 21,142,202, 10, 21, 92,138,  0,  1,134,
 10,204,  2,198,138,206,  3,156,138,  0,  1, 78,138,138, 20, 28,138,  0,  1,204,
  9,138, 19,206,201,137,148,140,201,  9, 19,206,  9,133,159,  6, 74,207,  2, 70,
 10,204,  2,134, 10,208,  3, 92,138,  0,  1, 78, 74, 10, 13, 28,138,  0,  1, 70,
 10,194,  2,129, 74, 16,  0, 92,138,  0,  1,134, 10,204,  2,195, 10,128, 21,  6,
139,208,  2,156,138,128,  1, 78,138,138, 20, 12, 74, 10, 20, 70, 74,207,  2,143,
 10,  4, 12,198, 10,204,  2,  6, 11,208,  3,220,138,  0,  1,142,202, 10, 21, 92,
138,  0,  1, 12, 74, 10, 20,206,  9,138, 19,140,201,  9, 19,206,  9,133,161,  6,
 74,207,  2, 79, 10,  4, 12,134, 10,204,  2,198, 10,209,  2,156,138,  0,  1, 78,
138,138, 20, 28,138,  0,  1,206,  9,138, 19,140,201,  9, 19,142,  9,  5, 19,145,
 73, 66, 19, 78,137,137, 18,164,137,  2,  0, 28,137,128,  1,137,  8,137,155,  6,
 73,203,  2, 65,  9, 11,  0, 28,137,  0,  1, 14,  9,137,162, 14,137, 70, 18, 70,
  9, 66,  3, 79, 73,  9, 13, 12, 73,  9, 18, 12,137,  7, 18, 12,201,  6, 18, 78,
201,209, 10,134,  9,204,  2,195,  9,128, 19,156,137,  0,  1, 76,137,137, 18, 78,
 73,  9,163,134, 73,203,  2,193,  9, 11,  0,156,137,  0,  1, 78,137,137, 18, 78,
  9,199, 18,164,201,  2,  0,  0,  0,  0,  3, 79,137,137, 18, 12, 73,  9, 18, 78,
 73,  5,164,164,  9,  3,  0,  0,  0,  0,  3,  0,  0,128,  9, 79,137,137, 18, 12,
 73,  9, 18, 70,  9,194,  2,129, 73, 16,  0, 92,137,  0,  1,134, 73, 82,  3, 79,
137,137, 18, 12, 73,  9, 18, 70, 73,203,  2,129,  9, 11,  0, 92,137,  0,  1, 78,
 73,  9,165, 78, 73,199, 18,134,  9, 73,  3, 79,137,137, 18, 12, 73,  9, 18, 70,
 73,203,  2,129,  9, 11,  0, 92,137,  0,  1, 78, 73,137,165, 78,201,198, 18,134,
201, 71,  3, 79,137,137, 18, 12, 73,  9, 18, 70,  9,194,  2,129,  9, 19,  0, 92,
137,  0,  1,134,  9,204,  2,192,  9,128,  4,156,137,  0,  1, 78,137,137, 18, 12,
 73,  9, 18, 82,  9,  0, 11, 78, 73,137, 10,134, 73, 75,  3, 79,137,137, 18, 12,
 73,  9, 18, 78, 73,133,166, 78,137,211, 18,134, 73, 75,  3, 79,137,137, 18, 12,
 73,  9, 18,137,  8,  9,156, 14,137,  5, 12, 70, 73,203,  2,129,  9, 11,  0, 92,
137,  0,  1, 14, 73,  9, 18,137,  8,137,167,  6,137,202,  2, 70, 73,203,  2,129,
201, 19,  0, 92,137,  0,  1, 79,  9,136, 18,134, 73,207,  2,198, 73,203,  2,  1,
202, 19,  0,220,  9,  0,  1,156,137,  0,  0,145, 73, 66, 19, 78,137,137, 18,128,
  9,128, 15, 28,137,128,  1, 70,  9, 66,  3, 15, 73,  9, 18,137,  8,  9,151,162,
 72,128,  0, 92,136,  0,  1,142, 72,  8, 10,198,  8, 66,  3,143,200,  8, 17,210,
  8,128,  4,204, 72,132, 17,142,200,  8, 17,228, 72,  3,  0,  0,  0,  0,  3,  0,
  0,  0, 17,  0,  0,128,  1, 36,137,  3,  0,  0,  0,128,  5,  0,  0,128, 17,100,
201,  3,  0,  0,  0,  0,  6,  0,  0,128, 17,  0,  0,  0,  3,164,  9,  4,  0,  0,
  0,128,  6,  0,  0,128, 17,  0,  0,  0,  3,202, 73,  1,  0,201,201,  8,168,201,
  9,137,168,201, 73,  9,169,201,137,137,169,201,137,  3,170, 23, 64, 85,  4, 22,
 64,  0,128,  5,138, 21,  0,  9,202,137,171,222,  9,  0,  1, 30,  0,128,  0, 88,
  0,  0,  0,  4,  9,  0,  0,  0,116,111,110,117,109, 98,101,114,  0,  4,  5,  0,
  0,  0,116,121,112,101,  0,  4,  6,  0,  0,  0,112,114,105,110,116,  0,  4,  6,
  0,  0,  0,101,114,114,111,114,  0,  4, 13,  0,  0,  0,115,101,116,109,101,116,
 97,116, 97, 98,108,101,  0,  4,  8,  0,  0,  0,114,101,113,117,105,114,101,  0,
  4,  5,  0,  0,  0,108,112,101,103,  0,  4, 13,  0,  0,  0,103,101,116,109,101,
116, 97,116, 97, 98,108,101,  0,  4,  2,  0,  0,  0, 80,  0,  3,  0,  0,  0,  0,
  0,  0,  0,  0,  4,  9,  0,  0,  0, 95, 86, 69, 82, 83, 73, 79, 78,  0,  4,  8,
  0,  0,  0, 76,117, 97, 32, 53, 46, 50,  0,  4,  5,  0,  0,  0, 95, 69, 78, 86,
  0,  3,  0,  0,  0,  0,  0,  0,240, 63,  4,  3,  0,  0,  0,110,108,  0,  4,  2,
  0,  0,  0, 10,  0,  4,  2,  0,  0,  0, 83,  0,  4,  7,  0,  0,  0, 32, 12, 10,
 13,  9, 11,  0,  4,  3,  0,  0,  0, 45, 45,  0,  4,  2,  0,  0,  0, 82,  0,  4,
  3,  0,  0,  0, 65, 90,  0,  4,  3,  0,  0,  0, 97,122,  0,  4,  3,  0,  0,  0,
 95, 95,  0,  4,  3,  0,  0,  0, 48, 57,  0,  4,  3,  0,  0,  0, 60, 45,  0,  4,
  2,  0,  0,  0, 47,  0,  4,  2,  0,  0,  0, 41,  0,  4,  2,  0,  0,  0,125,  0,
  4,  3,  0,  0,  0, 58,125,  0,  4,  3,  0,  0,  0,126,125,  0,  3,  0,  0,  0,
  0,  0,  0,240,191,  4,  2,  0,  0,  0, 67,  0,  4,  5,  0,  0,  0, 67, 97,114,
103,  0,  4,  2,  0,  0,  0, 39,  0,  4,  2,  0,  0,  0, 34,  0,  4,  2,  0,  0,
  0, 37,  0,  4,  3,  0,  0,  0, 67,115,  0,  4,  2,  0,  0,  0, 45,  0,  4,  1,
  0,  0,  0,  0,  4,  2,  0,  0,  0, 93,  0,  4,  2,  0,  0,  0, 91,  0,  4,  2,
  0,  0,  0, 94,  0,  4,  3,  0,  0,  0, 67,102,  0,  4,  6,  0,  0,  0, 95, 95,
 97,100,100,  0,  4,  4,  0,  0,  0, 69,120,112,  0,  4,  2,  0,  0,  0, 86,  0,
  4,  8,  0,  0,  0, 71,114, 97,109,109, 97,114,  0,  4,  4,  0,  0,  0, 83,101,
113,  0,  4,  3,  0,  0,  0, 67, 99,  0,  4,  7,  0,  0,  0, 80,114,101,102,105,
120,  0,  4,  6,  0,  0,  0, 95, 95,109,117,108,  0,  4,  2,  0,  0,  0, 38,  0,
  4,  6,  0,  0,  0, 95, 95,108,101,110,  0,  4,  2,  0,  0,  0, 33,  0,  4,  6,
  0,  0,  0, 95, 95,117,110,109,  0,  4,  7,  0,  0,  0, 83,117,102,102,105,120,
  0,  4,  8,  0,  0,  0, 80,114,105,109, 97,114,121,  0,  4,  2,  0,  0,  0, 43,
  0,  4,  6,  0,  0,  0, 95, 95,112,111,119,  0,  4,  2,  0,  0,  0, 42,  0,  4,
  2,  0,  0,  0, 63,  0,  4,  3,  0,  0,  0, 67,103,  0,  4,  3,  0,  0,  0, 43,
 45,  0,  4,  3,  0,  0,  0, 45, 62,  0,  4,  6,  0,  0,  0, 95, 95,100,105,118,
  0,  4,  3,  0,  0,  0,123,125,  0,  4,  3,  0,  0,  0, 67,116,  0,  4,  3,  0,
  0,  0, 61, 62,  0,  4,  4,  0,  0,  0, 67,109,116,  0,  4,  2,  0,  0,  0, 40,
  0,  4,  3,  0,  0,  0,123, 58,  0,  4,  2,  0,  0,  0, 58,  0,  4,  2,  0,  0,
  0, 61,  0,  4,  3,  0,  0,  0, 67,112,  0,  4,  3,  0,  0,  0,123,126,  0,  4,
  2,  0,  0,  0,123,  0,  4,  2,  0,  0,  0, 46,  0,  4,  2,  0,  0,  0, 60,  0,
  4,  2,  0,  0,  0, 62,  0,  4, 11,  0,  0,  0, 68,101,102,105,110,105,116,105,
111,110,  0,  4,  8,  0,  0,  0, 99,111,109,112,105,108,101,  0,  4,  6,  0,  0,
  0,109, 97,116, 99,104,  0,  4,  5,  0,  0,  0,102,105,110,100,  0,  4,  5,  0,
  0,  0,103,115,117, 98,  0,  4, 13,  0,  0,  0,117,112,100, 97,116,101,108,111,
 99, 97,108,101,  0,  4,  8,  0,  0,  0, 76,117, 97, 32, 53, 46, 49,  0,  4,  3,
  0,  0,  0, 95, 71,  0,  4,  3,  0,  0,  0,114,101,  0, 17,  0,  0,  0,  0,  0,
  0,  0, 35,  0,  0,  0, 64,  0,  0,  0,  7,  0,  0,  4,125,  0,  0,  0,  4,  0,
  0,  0,  6,  0, 64,  0, 68,  0,128,  0, 28, 64,  0,  1,  4,  0,128,  0, 68,  0,
128,  0, 70,128,192,  0,  9, 64,128,128,  4,  0,128,  0, 68,  0,128,  0, 70,  0,
193,  0,  9, 64,128,129,  4,  0,128,  0, 68,  0,128,  0, 70,128,193,  0,  9, 64,
128,130,  4,  0,128,  0, 68,  0,128,  0, 70,  0,194,  0,  9, 64,128,131,  4,  0,
128,  0, 68,  0,128,  0, 70,128,194,  0,  9, 64,128,132,  4,  0,128,  0, 68,  0,
128,  0, 70,  0,195,  0,  9, 64,128,133,  4,  0,128,  0, 68,  0,128,  0, 70,128,
195,  0,  9, 64,128,134,  4,  0,128,  0, 68,  0,128,  0, 70,  0,196,  0,  9, 64,
128,135,  4,  0,128,  0, 68,  0,128,  0, 70,128,196,  0,  9, 64,128,136,  4,  0,
128,  0, 68,  0,128,  0, 70,  0,197,  0,  9, 64,128,137,  4,  0,128,  0, 68,  0,
  0,  1,132,  0,128,  0,134, 64, 64,  1, 77,128,128,  0,  9, 64,128,138,  4,  0,
128,  0, 68,  0,  0,  1,132,  0,128,  0,134,192, 64,  1, 77,128,128,  0,  9, 64,
  0,139,  4,  0,128,  0, 68,  0,  0,  1,132,  0,128,  0,134, 64, 65,  1, 77,128,
128,  0,  9, 64,128,139,  4,  0,128,  0, 68,  0,  0,  1,132,  0,128,  0,134,192,
 65,  1, 77,128,128,  0,  9, 64,  0,140,  4,  0,128,  0, 68,  0,  0,  1,132,  0,
128,  0,134, 64, 66,  1, 77,128,128,  0,  9, 64,128,140,  4,  0,128,  0, 68,  0,
  0,  1,132,  0,128,  0,134,192, 66,  1, 77,128,128,  0,  9, 64,  0,141,  4,  0,
128,  0, 68,  0,  0,  1,132,  0,128,  0,134, 64, 67,  1, 77,128,128,  0,  9, 64,
128,141,  4,  0,128,  0, 68,  0,  0,  1,132,  0,128,  0,134,192, 67,  1, 77,128,
128,  0,  9, 64,  0,142,  4,  0,128,  0, 68,  0,  0,  1,132,  0,128,  0,134, 64,
 68,  1, 77,128,128,  0,  9, 64,128,142,  4,  0,128,  0, 68,  0,  0,  1,132,  0,
128,  0,134,192, 68,  1, 77,128,128,  0,  9, 64,  0,143, 10,  0,  0,  0,  8,  0,
128,  1, 10,  0,  0,  0,  8,  0,  0,  2, 10,  0,  0,  0,  8,  0,128,  2, 10, 64,
  0,  0,  9,  0,200,143, 68,  0,  0,  3,132,  0,128,  1,192,  0,  0,  0, 92, 64,
128,  1, 68,  0,  0,  3,132,  0,  0,  2,192,  0,  0,  0, 92, 64,128,  1, 68,  0,
  0,  3,132,  0,128,  2,192,  0,  0,  0, 92, 64,128,  1, 30,  0,128,  0, 33,  0,
  0,  0,  4,  7,  0,  0,  0,108,111, 99, 97,108,101,  0,  4,  2,  0,  0,  0, 97,
  0,  4,  6,  0,  0,  0, 97,108,112,104, 97,  0,  4,  2,  0,  0,  0, 99,  0,  4,
  6,  0,  0,  0, 99,110,116,114,108,  0,  4,  2,  0,  0,  0,100,  0,  4,  6,  0,
  0,  0,100,105,103,105,116,  0,  4,  2,  0,  0,  0,103,  0,  4,  6,  0,  0,  0,
103,114, 97,112,104,  0,  4,  2,  0,  0,  0,108,  0,  4,  6,  0,  0,  0,108,111,
119,101,114,  0,  4,  2,  0,  0,  0,112,  0,  4,  6,  0,  0,  0,112,117,110, 99,
116,  0,  4,  2,  0,  0,  0,115,  0,  4,  6,  0,  0,  0,115,112, 97, 99,101,  0,
  4,  2,  0,  0,  0,117,  0,  4,  6,  0,  0,  0,117,112,112,101,114,  0,  4,  2,
  0,  0,  0,119,  0,  4,  6,  0,  0,  0, 97,108,110,117,109,  0,  4,  2,  0,  0,
  0,120,  0,  4,  7,  0,  0,  0,120,100,105,103,105,116,  0,  4,  2,  0,  0,  0,
 65,  0,  4,  2,  0,  0,  0, 67,  0,  4,  2,  0,  0,  0, 68,  0,  4,  2,  0,  0,
  0, 71,  0,  4,  2,  0,  0,  0, 76,  0,  4,  2,  0,  0,  0, 80,  0,  4,  2,  0,
  0,  0, 83,  0,  4,  2,  0,  0,  0, 85,  0,  4,  2,  0,  0,  0, 87,  0,  4,  2,
  0,  0,  0, 88,  0,  4,  7,  0,  0,  0, 95, 95,109,111,100,101,  0,  4,  2,  0,
  0,  0,118,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0, 71,  0,  0,  0, 71,  0,  0,  0,  1,  2,  0,  8,  9,  0,  0,  0,
132,  0,  0,  0,192,  0,128,  0, 11,  1, 64,  0,129, 65,  0,  0,205, 65,192,  0,
 28,  1,  0,  2,156, 64,  0,  0, 94,  0,  0,  1, 30,  0,128,  0,  2,  0,  0,  0,
  4,  4,  0,  0,  0,115,117, 98,  0,  3,  0,  0,  0,  0,  0,  0,240, 63,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 74,  0,
  0,  0, 78,  0,  0,  0,  1,  2,  0,  6, 12,  0,  0,  0,155,  0,128,  0, 22,  0,
  0,128,134,  0,128,  0,154, 64,  0,  0, 22,  0,  1,128,196,  0,  0,  0,  1,  1,
  0,  0, 64,  1,  0,  0, 21, 65,  1,  2,220, 64,  0,  1,158,  0,  0,  1, 30,  0,
128,  0,  1,  0,  0,  0,  4, 17,  0,  0,  0,117,110,100,101,102,105,110,101,100,
 32,110, 97,109,101, 58, 32,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0, 81,  0,  0,  0, 86,  0,  0,  0,  1,  2,  0,  6,
 25,  0,  0,  0,148,  0,  0,  0,204,  0,192,  0, 24,192,  0,  1, 22,  0,  1,128,
139, 64, 64,  0,  0,  1,128,  0,156,128,128,  1,154, 64,  0,  0, 22, 64,  1,128,
139, 64, 64,  0,  0,  1,128,  0, 76,  1,192,  0,156,128,  0,  2,193,128,  0,  0,
149,192,  0,  1,193,192,  0,  0,203,  0,193,  1, 64,  1,  0,  1,220,128,128,  1,
128,  0,128,  1,196,  0,  0,  0,  0,  1,  0,  1, 65, 65,  1,  0,220, 64,128,  1,
 30,  0,128,  0,  6,  0,  0,  0,  3,  0,  0,  0,  0,  0,  0, 52, 64,  4,  4,  0,
  0,  0,115,117, 98,  0,  4,  4,  0,  0,  0, 46, 46, 46,  0,  4, 24,  0,  0,  0,
112, 97,116,116,101,114,110, 32,101,114,114,111,114, 32,110,101, 97,114, 32, 39,
 37,115, 39,  0,  4,  7,  0,  0,  0,102,111,114,109, 97,116,  0,  3,  0,  0,  0,
  0,  0,  0,  0, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0, 88,  0,  0,  0, 96,  0,  0,  0,  1,  2,  0,  4, 15,  0,  0,
  0,132,  0,  0,  0,134,  0, 64,  1,194,  0,128,  0,156,128,  0,  1, 25, 64,128,
128, 22,128,  1,128,208,128,192,  0, 25,192,128,128, 22,  0,  0,128,142,  0,  0,
  1, 14,  0,  0,  0, 79,128,192,  0, 22,128,253,127,158,  0,  0,  1, 30,  0,128,
  0,  3,  0,  0,  0,  4,  2,  0,  0,  0, 80,  0,  3,  0,  0,  0,  0,  0,  0,240,
 63,  3,  0,  0,  0,  0,  0,  0,  0, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 98,  0,  0,  0,102,  0,  0,  0,  1,  3,
  0,  8, 20,  0,  0,  0,196,  0,  0,  0,  0,  1,  0,  1,220,128,  0,  1, 87,  0,
192,  1, 22, 64,  0,128,195,  0,128,  1,222,  0,  0,  1,212,  0,  0,  1,204, 64,
128,  1, 11, 65, 64,  0,128,  1,128,  0,205,129,192,  1, 28,129,  0,  2, 23,128,
  0,  2, 22, 64,  0,128,222,  0,  0,  1, 22, 64,  0,128,  3,  1,  0,  2, 30,  1,
  0,  1, 30,  0,128,  0,  3,  0,  0,  0,  4,  7,  0,  0,  0,115,116,114,105,110,
103,  0,  4,  4,  0,  0,  0,115,117, 98,  0,  3,  0,  0,  0,  0,  0,  0,240, 63,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
125,  0,  0,  0,129,  0,  0,  0,  2,  2,  0,  7, 17,  0,  0,  0, 90,  0,  0,  0,
 22,128,  0,128,134,  0,128,  0,154, 64,  0,  0, 22, 64,  0,128,132,  0,  0,  0,
134,  0,  0,  1,154, 64,  0,  0, 22, 64,  1,128,196,  0,128,  0,  1,  1,  0,  0,
 64,  1,  0,  0,129, 65,  0,  0, 21,129,  1,  2,220, 64,  0,  1,158,  0,  0,  1,
 30,  0,128,  0,  2,  0,  0,  0,  4,  7,  0,  0,  0,110, 97,109,101, 32, 39,  0,
  4, 12,  0,  0,  0, 39, 32,117,110,100,101,102,105,110,101,100,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,139,  0,  0,
  0,139,  0,  0,  0,  1,  2,  0,  3,  9,  0,  0,  0, 23,  0, 64,  0, 22,192,  0,
128,132,  0,  0,  0,141, 64,  0,  1,154, 64,  0,  0, 22,  0,  0,128,128,  0,128,
  0,158,  0,  0,  1, 30,  0,128,  0,  1,  0,  0,  0,  4,  2,  0,  0,  0, 94,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
142,  0,  0,  0,149,  0,  0,  0,  1,  4,  0,  8, 13,  0,  0,  0,  6, 65,  0,  0,
 26,  1,  0,  0, 22,128,  1,128,  4,  1,  0,  0, 65,  1,  0,  0,128,  1,128,  0,
193, 65,  0,  0, 85,193,129,  2, 28, 65,  0,  1, 22,  0,  0,128,  9,192,128,  0,
 30,  0,  0,  1, 30,  0,128,  0,  2,  0,  0,  0,  4,  2,  0,  0,  0, 39,  0,  4,
 28,  0,  0,  0, 39, 32, 97,108,114,101, 97,100,121, 32,100,101,102,105,110,101,
100, 32, 97,115, 32, 97, 32,114,117,108,101,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,151,  0,  0,  0,151,  0,  0,  0,
  1,  3,  0,  8, 10,  0,  0,  0,196,  0,  0,  0, 10,  1,128,  0, 64,  1,  0,  0,
 34, 65,128,  0, 64,  1,  0,  0,128,  1,128,  0,192,  1,  0,  1,221,  0,128,  2,
222,  0,  0,  0, 30,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,176,  0,  0,  0,176,  0,  0,  0,
  0,  3,  0,  6,  6,  0,  0,  0,192,  0,  0,  1,  0,  1,  0,  0, 64,  1,128,  0,
221,  0,128,  1,222,  0,  0,  0, 30,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,182,  0,  0,  0,
182,  0,  0,  0,  1,  2,  0,  5,  7,  0,  0,  0,132,  0,  0,  0,134,  0, 64,  1,
192,  0,128,  0,  0,  1,  0,  0,157,  0,128,  1,158,  0,  0,  0, 30,  0,128,  0,
  1,  0,  0,  0,  4,  3,  0,  0,  0, 67,103,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,183,  0,  0,  0,183,  0,  0,  0,
  2,  1,  0,  4, 10,  0,  0,  0, 68,  0,  0,  0, 70,  0,192,  0,132,  0,  0,  0,
134, 64, 64,  1,192,  0,  0,  0,156,128,  0,  1,196,  0,128,  0, 93,  0,128,  1,
 94,  0,  0,  0, 30,  0,128,  0,  2,  0,  0,  0,  4,  4,  0,  0,  0, 67,109,116,
  0,  4,  3,  0,  0,  0, 67, 98,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,198,  0,  0,  0,203,  0,  0,  0,  3,  2,  0,
  7, 21,  0,  0,  0,132,  0,  0,  0,134,  0, 64,  1,192,  0,  0,  0,156,128,  0,
  1, 23, 64, 64,  1, 22,  0,  0,128, 30,  0,  0,  1,132,  0,128,  0,139,128, 64,
  1,  0,  1,  0,  0, 65,193,  0,  0,128,  1,128,  0,156,128,128,  2,154, 64,  0,
  0, 22,192,  0,128,196,  0,  0,  1,  1,  1,  1,  0, 65, 65,  1,  0,220, 64,128,
  1,158,  0,  0,  1, 30,  0,128,  0,  6,  0,  0,  0,  4,  5,  0,  0,  0,116,121,
112,101,  0,  4,  8,  0,  0,  0,112, 97,116,116,101,114,110,  0,  4,  6,  0,  0,
  0,109, 97,116, 99,104,  0,  3,  0,  0,  0,  0,  0,  0,240, 63,  4, 18,  0,  0,
  0,105,110, 99,111,114,114,101, 99,116, 32,112, 97,116,116,101,114,110,  0,  3,
  0,  0,  0,  0,  0,  0,  8, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,205,  0,  0,  0,212,  0,  0,  0,  2,  3,  0,  8,
 18,  0,  0,  0,196,  0,  0,  0,198, 64,128,  1,218, 64,  0,  0, 22, 64,  1,128,
  4,  1,128,  0, 64,  1,128,  0, 28,129,  0,  1,192,  0,  0,  2,  4,  1,  0,  0,
  9,193,128,  0, 11,  1,192,  1,128,  1,  0,  0,219, 65,  0,  1, 22,  0,  0,128,
193, 65,  0,  0, 29,  1,  0,  2, 30,  1,  0,  0, 30,  0,128,  0,  2,  0,  0,  0,
  4,  6,  0,  0,  0,109, 97,116, 99,104,  0,  3,  0,  0,  0,  0,  0,  0,240, 63,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
214,  0,  0,  0,222,  0,  0,  0,  3,  3,  0,  9, 34,  0,  0,  0,196,  0,  0,  0,
198, 64,128,  1,218, 64,  0,  0, 22, 64,  5,128,  4,  1,128,  0, 64,  1,128,  0,
 28,129,  0,  1,192,  0,  0,  2,  4,  1,  0,  1,  6,  1, 64,  2, 74,  1,128,  0,
132,  1,  0,  1,134, 65, 64,  3,156,129,128,  0,142,193,  0,  3,196,  1,  0,  1,
198,129,192,  3,  1,194,  0,  0,220,129,  0,  1,206,193,129,129,140,193,  1,  3,
 98, 65,128,  0, 28,129,  0,  1,192,  0,  0,  2,  4,  1,  0,  0,  9,193,128,  0,
 11,  1,193,  1,128,  1,  0,  0,219, 65,  0,  1, 22,  0,  0,128,193,193,  0,  0,
 29,  1,  0,  2, 30,  1,  0,  0, 30,  0,128,  0,  5,  0,  0,  0,  4,  2,  0,  0,
  0, 80,  0,  4,  3,  0,  0,  0, 67,112,  0,  4,  2,  0,  0,  0, 86,  0,  3,  0,
  0,  0,  0,  0,  0,240, 63,  4,  6,  0,  0,  0,109, 97,116, 99,104,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,  0,
  0,  0,234,  0,  0,  0,  3,  3,  0,  8, 27,  0,  0,  0,196,  0,  0,  0,198, 64,
128,  1,218, 64,  0,  0, 22,  0,  0,128,202,  0,  0,  0,  4,  1,  0,  0,  9,193,
128,  0,  6,129,128,  1, 26, 65,  0,  0, 22,192,  2,128, 68,  1,128,  0,128,  1,
128,  0, 92,129,  0,  1,  0,  1,128,  2, 68,  1,  0,  1, 70,  1,192,  2,143,129,
  0,  2,140, 65, 64,  3,145,129, 64,  3, 92,129,  0,  1,  0,  1,128,  2,201,  0,
  1,  1, 75,193, 64,  2,192,  1,  0,  0, 93,  1,128,  1, 94,  1,  0,  0, 30,  0,
128,  0,  4,  0,  0,  0,  4,  3,  0,  0,  0, 67,115,  0,  3,  0,  0,  0,  0,  0,
  0,240, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  4,  6,  0,  0,  0,109, 97,116,
 99,104,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
};

LUAOPEN_API int
luaload_re(lua_State *L)
{
	return luaL_loadbuffer(L,(const char*)B1,sizeof(B1),"re");
}

// ----------------------------------------------------------------------------

} // namespace Rtt

// ----------------------------------------------------------------------------
