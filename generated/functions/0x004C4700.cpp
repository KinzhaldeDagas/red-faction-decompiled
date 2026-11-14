// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C4700 rf_geomod_impact_fragment_spawn
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl(origin,radius,direction,bitmapArg,fallbackRoom). Before ANY room resolution/spawn admission, traverses existing active chunk list; each owner104==NULL and STRICT ORDERED
// radius>fast_distance(origin,chunk.position8) receives bounceCount100=floor(random[3,5]) then new randomized motion about ORIGINAL origin. No age112/lifetime116/flags120 reset on
// these existing chunks; these side effects survive later return0.
// Sets F32offset=radius*DOUBLE0.1000000014901161; tries room at origin+direction*offset (direction not normalized here). If unresolved, samples random unit directions at same offset
// radius, checking j>5 AFTER each lookup: up to SEVEN random retries j0..6, not six. Still unresolved ->position=origin and room=fallbackRoom. If roomNULL returns AL0. Calls14-ray
// estimator4C5140(destination,radius,FULL roomDWORD); estimator result exactly0 returns0; NEGATIVE result bypasses signed j<count loop and returns AL1 without allocating new chunks.
// For each signed j<count: samples random unit vector times F32(random[0,.5]*radius), allocates bounded chunk (no NULLcheck), flags120=0, position8=destination+offset,
// room108=resolved room. Calls segment helper4C4460(destination,newPosition,&room,out20,0), copies returned point into position ONLY when AL exactly1, including original backward
// liquid extrapolation. Sets matrix20 identity. Samples unit U once, stores F32(U*U*U) without intermediate F32 U-squared store, then
// radius56=F32(cube*DOUBLE0.20000000298023224+DOUBLE0.05000000074505806). Ordered radius56<DOUBLE0.15000000596046448 sets flag2; NaN does not. Stores scalar60=F32((radius56-.05)*5),
// bounceCount100=rand()%3+3, RGBA64=all255,owner104=NULL,bitmap68=bitmapArg,random unit axis84,spin96=random[pi,2pi]. Mesh builder supplies age/lifetime/local mesh then motion init
// uses RESOLVED destination as launch origin. AL1 after loop. No mesh/material failure rollback, radius/finite validation or independent global payload zeroing.
char __cdecl rf_geomod_impact_fragment_spawn(float *source, float radius, float *vector, _DWORD *a4, int a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v9; // eax
  double v10; // st7
  float value; // [esp+4h] [ebp-BCh]
  float v12; // [esp+8h] [ebp-B8h]
  float v13[3]; // [esp+Ch] [ebp-B4h] BYREF
  float v14[3]; // [esp+18h] [ebp-A8h] BYREF
  float v15[3]; // [esp+24h] [ebp-9Ch] BYREF
  float v16[3]; // [esp+30h] [ebp-90h] BYREF
  float copy_result[3]; // [esp+3Ch] [ebp-84h] BYREF
  float sum_result[3]; // [esp+48h] [ebp-78h] BYREF
  float v19[3]; // [esp+54h] [ebp-6Ch] BYREF
  float scaled_result[3]; // [esp+60h] [ebp-60h] BYREF
  float *v21; // [esp+6Ch] [ebp-54h]
  float rhs[3]; // [esp+70h] [ebp-50h] BYREF
  float v23; // [esp+7Ch] [ebp-44h]
  float outResult[2]; // [esp+80h] [ebp-40h] BYREF
  float v25[3]; // [esp+88h] [ebp-38h] BYREF
  float v26[3]; // [esp+94h] [ebp-2Ch] BYREF
  int i; // [esp+A0h] [ebp-20h]
  int v28; // [esp+A4h] [ebp-1Ch]
  int room; // [esp+A8h] [ebp-18h]
  int j; // [esp+ACh] [ebp-14h]
  float destination[3]; // [esp+B0h] [ebp-10h] BYREF
  float v32; // [esp+BCh] [ebp-4h]

  for ( i = rf_geomod_impact_chunk_active_head; (_DWORD *)i != &rf_geomod_impact_chunk_active_head; i = *(_DWORD *)i )
  {
    if ( !*(_DWORD *)(i + 104) && radius > rf_vector_fast_distance(source, (const float *)(i + 8)) )
    {
      value = rf_random_float_range(3.0, 5.0);
      *(_DWORD *)(i + 100) = (int)rf_floor_float(value);
      rf_geomod_impact_chunk_motion_init(i, (int)source);
    }
  }
  v32 = radius * 0.1000000014901161;
  v5 = rf_vector_multiply_scalar(vector, scaled_result, v32);
  rf_vector_add(source, destination, v5);
  room = (int)rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, destination, destination, 0);
  for ( j = 0; !room; ++j )
  {
    rf_vector3_default_construct_noop(v26);
    rf_random_unit_vector_from_z_and_azimuth(v26);
    v6 = rf_vector_multiply_scalar(v26, v19, v32);
    v7 = rf_vector_add(source, sum_result, v6);
    rf_vector_copy(destination, copy_result, v7);
    room = (int)rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, destination, destination, 0);
    if ( j > 5 )
      break;
  }
  if ( !room )
  {
    rf_vector_copy(destination, v16, source);
    room = a5;
  }
  if ( !room )
    return 0;
  v28 = rf_geomod_fragment_count_from_fourteen_rays(destination, radius, room);
  if ( !v28 )
    return 0;
  for ( j = 0; j < v28; ++j )
  {
    rf_vector3_default_construct_noop(rhs);
    rf_random_unit_vector_from_z_and_azimuth(rhs);
    v12 = rf_random_float_range(0.0, 0.5) * radius;
    rf_vector3_scale_in_place_return_self(rhs, v12);
    v21 = (float *)rf_geomod_impact_chunk_allocate();
    v21[30] = 0.0;
    rf_geomod_intersection24_construct_noop((char *)outResult);
    v9 = rf_vector_add(destination, v15, rhs);
    rf_vector_copy(v21 + 2, v14, v9);
    *((_DWORD *)v21 + 27) = room;
    if ( rf_geomod_segment_hit_or_liquid_crossing(destination, v21 + 2, (int)(v21 + 27), outResult, 0) )
      rf_vector_copy(v21 + 2, v13, v25);
    rf_identity_orientation_matrix(v21 + 5);
    v23 = sub_567730();
    v23 = v23 * v23 * v23;
    v21[14] = v23 * 0.2000000029802322 + 0.05000000074505806;
    if ( v21[14] < 0.1500000059604645 )
      *((_DWORD *)v21 + 30) |= 2u;
    v21[15] = (v21[14] - 0.05000000074505806) * 5.0;
    *((_DWORD *)v21 + 25) = rand() % 3 + 3;
    rf_color4_set_bytes_return_destination((_BYTE *)v21 + 64, 255, 255, 255, 255);
    v21[26] = 0.0;
    *((_DWORD *)v21 + 17) = a4;
    rf_random_unit_vector(v21 + 21);
    v10 = rf_random_float_range(3.1415927, 6.2831855);
    v21[24] = v10;
    rf_geomod_impact_chunk_mesh_build((int)v21);
    rf_geomod_impact_chunk_motion_init((int)v21, (int)destination);
  }
  return 1;
}

