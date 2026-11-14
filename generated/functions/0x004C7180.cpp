// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C7180 rf_glass_radial_damage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl(origin,queryMin,queryMax,damage,radius). First walks ALL keyed shard buckets, any STRICT ORDERED radius>fast_distance(origin,shard.center8):
// budget96=floor(random[3,5]),launch73B0(modeBYTE1,speed10). Includes moving/delayed/resting/attached shards; does NOT clear attachment100,damage flags196,change room/bucket or
// require same room. Side effects precede geometry-health/authority checks. Next snapshots count of worldSolid array168 and scans its pointers. Only object BYTE152==0 and strict
// ordered object AABB8/20 overlap query bounds. Computes center=(min+max)*.5,F32distance=length(center-origin),F32falloff=(radius-distance)/radius; ordered falloff>0 subtracts
// damage*falloff from health148 (F32store). No radius-zero/finite/line-of-sight/negative-damage guard.
// Then tests resulting health148 STRICT ORDERED <0, even when this call subtracted nothing: already-negative health can trigger break with nonpositive falloff. Equality0/NaN do not
// break. Gets FIRST face from owner list40; if present calls nondirectional break5760(face,origin,force0), then ALWAYS exits face loop after that one attempt. Does not walk all owner
// faces, directly delete geometry or enforce multiplayer authority before health write/relaunch; delegate controls break authority/registry. EAX incidental last lookup/FPU
// status/mode, not affected count or status.
int __cdecl rf_glass_radial_damage(float *rhs, float *a2, float *a3, float a4, float a5)
{
  int result; // eax
  float *v6; // eax
  __int16 v7; // fps
  double v8; // st7
  bool v9; // c0
  char v10; // c2
  bool v11; // c3
  float value; // [esp+4h] [ebp-48h]
  int v13; // [esp+8h] [ebp-44h]
  float sum_result[3]; // [esp+Ch] [ebp-40h] BYREF
  int v15; // [esp+18h] [ebp-34h]
  float v16; // [esp+1Ch] [ebp-30h]
  float out_vector[3]; // [esp+20h] [ebp-2Ch] BYREF
  float lhs[3]; // [esp+2Ch] [ebp-20h] BYREF
  float v19; // [esp+38h] [ebp-14h]
  int v20; // [esp+3Ch] [ebp-10h]
  int v21; // [esp+40h] [ebp-Ch]
  int j; // [esp+44h] [ebp-8h]
  int i; // [esp+48h] [ebp-4h]

  for ( i = 0; i < rf_glass_shard_bucket_count; ++i )
  {
    for ( j = rf_glass_shard_bucket_heads[2 * i]; j; j = v13 )
    {
      if ( a5 > rf_vector_fast_distance(rhs, (const float *)(j + 8)) )
      {
        value = rf_random_float_range(3.0, 5.0);
        *(_DWORD *)(j + 96) = (int)rf_floor_float(value);
        rf_glass_shard_launch_radial(j, (int)rhs, 1);
      }
      if ( *(_DWORD *)j == rf_glass_shard_bucket_heads[2 * i] )
        v13 = 0;
      else
        v13 = *(_DWORD *)j;
    }
  }
  result = rf_receiver_get_first_dword((void *)(rf_world_solid + 168));
  v21 = result;
  for ( i = 0; i < v21; ++i )
  {
    v20 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 168), i);
    result = *(unsigned __int8 *)(v20 + 152);
    if ( !*(_BYTE *)(v20 + 152) )
    {
      LOBYTE(result) = rf_aabb_overlap_strict_ordered(a2, a3, (float *)(v20 + 8), (float *)(v20 + 20));
      if ( (unsigned __int8)result == 1 )
      {
        v6 = rf_vector_add((const float *)(v20 + 8), sum_result, (const float *)(v20 + 20));
        rf_vector_multiply_scalar(v6, lhs, 0.5);
        rf_vector_subtract(lhs, out_vector, rhs);
        v16 = rf_vector3_length(out_vector);
        v19 = (a5 - v16) / a5;
        if ( v19 > 0.0 )
        {
          HIWORD(result) = HIWORD(v20);
          *(float *)(v20 + 148) = *(float *)(v20 + 148) - a4 * v19;
        }
        v8 = *(float *)(v20 + 148);
        v9 = v8 < 0.0;
        v10 = 0;
        v11 = v8 == 0.0;
        LOWORD(result) = v7;
        if ( v8 < 0.0 )
        {
          result = rf_receiver_get_first_dword((void *)(v20 + 40));
          v15 = result;
          if ( result )
            rf_glass_face_break_nondirectional(v15, rhs, 0);
        }
      }
    }
  }
  return result;
}

