// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C4C30 rf_geomod_impact_chunk_mesh_build
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl chunk. Lifetime116=random[1,4] F32,age112=0. Computes F32lo=radius56*DOUBLE0.20000000298023224,F32hi=radius56*DOUBLE1.7999999523162842. For i0..7 draws each XYZ independently
// in that order: bit1/2/4 set ->random(lo,hi), clear ->random(-lo,-hi) with REVERSED bounds retained, no sorting. Twenty-four unconditional range draws after lifetime draw, including
// zero/equal/negative endpoints; shared CRT random stream. Stores eight vec3 at124+12*i.
// Embeds12 triangles at220+36*t; each three12B corners is U0,V4,localPositionPtr8. Vertex indices0..7 correspond offsets124..208. Ordered
// triangles:(0,2,6),(0,6,4),(0,3,2),(0,1,3),(0,1,5),(0,5,4),(7,3,1),(7,1,5),(7,4,6),(7,5,4),(7,2,3),(7,6,2). Pointers reference embedded vertices, not new allocations. Last pointer
// at648 ends652B record.
// Resolves bitmap68 dimensions,width/height outputs; ignores return, computes F32Uscale=32/width,Vscale=32/height with no zero-dimension guard (failed resolution yields zeros). For
// each triangle computes cross(P1-P0,P2-P0), normalizes with unitX fallback, calls projection_axes_select, then stores UV from selected local vertex coordinates times scales. No
// world transform, stored normal field, radius recomputation, texture load failure rejection or allocation. EAX12 loop artifact, not mesh pointer/success.
void *__cdecl rf_geomod_impact_chunk_mesh_build(int a1)
{
  double v1; // st7
  double v2; // st7
  double v3; // st7
  void *result; // eax
  float *v5; // eax
  float *v6; // eax
  float v7; // [esp+0h] [ebp-74h]
  float v8; // [esp+0h] [ebp-74h]
  float v9; // [esp+0h] [ebp-74h]
  float v10; // [esp+4h] [ebp-70h]
  float v11; // [esp+4h] [ebp-70h]
  float v12; // [esp+4h] [ebp-70h]
  float *v13; // [esp+4h] [ebp-70h]
  float copy_result[3]; // [esp+8h] [ebp-6Ch] BYREF
  float v15[3]; // [esp+14h] [ebp-60h] BYREF
  float out_vector[3]; // [esp+20h] [ebp-54h] BYREF
  float v17[3]; // [esp+2Ch] [ebp-48h] BYREF
  int v18; // [esp+38h] [ebp-3Ch] BYREF
  int j; // [esp+3Ch] [ebp-38h]
  int v20; // [esp+40h] [ebp-34h] BYREF
  int v21; // [esp+44h] [ebp-30h]
  int v22; // [esp+48h] [ebp-2Ch] BYREF
  float v23; // [esp+4Ch] [ebp-28h]
  float v24; // [esp+50h] [ebp-24h]
  float destination[3]; // [esp+54h] [ebp-20h] BYREF
  float v26; // [esp+60h] [ebp-14h]
  float v27; // [esp+64h] [ebp-10h]
  int i; // [esp+68h] [ebp-Ch]
  int v29; // [esp+6Ch] [ebp-8h] BYREF
  int v30; // [esp+70h] [ebp-4h] BYREF

  *(float *)(a1 + 116) = rf_random_float_range(1.0, 4.0);
  *(float *)(a1 + 112) = 0.0;
  v26 = *(float *)(a1 + 56) * 0.2000000029802322;
  v24 = *(float *)(a1 + 56) * 1.799999952316284;
  for ( i = 0; i < 8; ++i )
  {
    if ( (i & 1) != 0 )
    {
      v1 = rf_random_float_range(v26, v24);
    }
    else
    {
      v10 = -v24;
      v7 = -v26;
      v1 = rf_random_float_range(v7, v10);
    }
    *(float *)(a1 + 12 * i + 124) = v1;
    if ( (i & 2) != 0 )
    {
      v2 = rf_random_float_range(v26, v24);
    }
    else
    {
      v11 = -v24;
      v8 = -v26;
      v2 = rf_random_float_range(v8, v11);
    }
    *(float *)(a1 + 12 * i + 128) = v2;
    if ( (i & 4) != 0 )
    {
      v3 = rf_random_float_range(v26, v24);
    }
    else
    {
      v12 = -v24;
      v9 = -v26;
      v3 = rf_random_float_range(v9, v12);
    }
    *(float *)(a1 + 12 * i + 132) = v3;
  }
  *(_DWORD *)(a1 + 228) = a1 + 124;
  *(_DWORD *)(a1 + 240) = a1 + 148;
  *(_DWORD *)(a1 + 252) = a1 + 196;
  *(_DWORD *)(a1 + 264) = a1 + 124;
  *(_DWORD *)(a1 + 276) = a1 + 196;
  *(_DWORD *)(a1 + 288) = a1 + 172;
  *(_DWORD *)(a1 + 300) = a1 + 124;
  *(_DWORD *)(a1 + 312) = a1 + 160;
  *(_DWORD *)(a1 + 324) = a1 + 148;
  *(_DWORD *)(a1 + 336) = a1 + 124;
  *(_DWORD *)(a1 + 348) = a1 + 136;
  *(_DWORD *)(a1 + 360) = a1 + 160;
  *(_DWORD *)(a1 + 372) = a1 + 124;
  *(_DWORD *)(a1 + 384) = a1 + 136;
  *(_DWORD *)(a1 + 396) = a1 + 184;
  *(_DWORD *)(a1 + 408) = a1 + 124;
  *(_DWORD *)(a1 + 420) = a1 + 184;
  *(_DWORD *)(a1 + 432) = a1 + 172;
  *(_DWORD *)(a1 + 444) = a1 + 208;
  *(_DWORD *)(a1 + 456) = a1 + 160;
  *(_DWORD *)(a1 + 468) = a1 + 136;
  *(_DWORD *)(a1 + 480) = a1 + 208;
  *(_DWORD *)(a1 + 492) = a1 + 136;
  *(_DWORD *)(a1 + 504) = a1 + 184;
  *(_DWORD *)(a1 + 516) = a1 + 208;
  *(_DWORD *)(a1 + 528) = a1 + 172;
  *(_DWORD *)(a1 + 540) = a1 + 196;
  *(_DWORD *)(a1 + 552) = a1 + 208;
  *(_DWORD *)(a1 + 564) = a1 + 184;
  *(_DWORD *)(a1 + 576) = a1 + 172;
  *(_DWORD *)(a1 + 588) = a1 + 208;
  *(_DWORD *)(a1 + 600) = a1 + 148;
  *(_DWORD *)(a1 + 612) = a1 + 160;
  *(_DWORD *)(a1 + 624) = a1 + 208;
  *(_DWORD *)(a1 + 636) = a1 + 196;
  *(_DWORD *)(a1 + 648) = a1 + 148;
  rf_bitmap_get_resolved_dimensions(*(_DWORD *)(a1 + 68), &v30, &v29);
  v27 = 32.0 / (double)v30;
  v23 = 32.0 / (double)v29;
  result = rf_vector3_default_construct_noop(destination);
  for ( i = 0; i < 12; ++i )
  {
    v21 = a1 + 36 * i + 220;
    v13 = rf_vector_subtract(*(const float **)(a1 + 36 * i + 252), out_vector, *(const float **)(a1 + 36 * i + 228));
    v5 = rf_vector_subtract(*(const float **)(v21 + 20), v17, *(const float **)(v21 + 8));
    v6 = rf_vector_cross(v5, v15, v13);
    rf_vector_copy(destination, copy_result, v6);
    rf_vector_normalize(destination);
    rf_face_projection_axes_select(destination, &v20, &v22, &v18);
    for ( j = 0; j < 3; ++j )
    {
      *(float *)(v21 + 12 * j) = *(float *)(*(_DWORD *)(v21 + 12 * j + 8) + 4 * v22) * v27;
      *(float *)(v21 + 12 * j + 4) = *(float *)(*(_DWORD *)(v21 + 12 * j + 8) + 4 * v18) * v23;
    }
    result = (void *)(i + 1);
  }
  return result;
}

