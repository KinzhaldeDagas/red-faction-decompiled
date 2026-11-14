// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528360 rf_light_build_active_list_for_sphere_query
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl optionalRoom,centerXYZ,queryRadiusF32,includeCategoryBYTE,includeCommonBYTE. If suppressionDWORD663B0C!=0 OR masterenabled==0 return0 BEFORE clearing active count/validity; old selection can remain. If globalallow663B10==0 force includeCategory0. Get room/global candidates527EB0, then set validBYTE D035FC=1 and countD035E8=0 even if candidatesNULL; NULLreturns0. Iterate cached count snapshot in stored order. Require enabledBYTE76 nonzero, at least one RGB64/68/72 compares !=0 (negative OR NaN qualifies; signedzero does not), and(includeCategory||!category77)&&(includeCommon||category77). Flag pairs(0,0)none,(1,0)nonzero category,(0,1)category0,(1,1)both. Increment diagnosticD035F8 AFTER filters
// before type switch. Type1 append unconditional. Types2/3: F32 distanceSquared(originalpos12-center); s=F32(range60+queryRadius),squared=F32(s*s); append ONLY ORDERED squared>distanceSquared, so tangency/unordered rejects. Spot cone ignored. Type4 closest point on original finite segment12/24, discard helper x87 distance, compare same strict squared threshold toF32 point distanceSquared. Unknown type ignored. No normalization, positive radius/range guard, sorting, dedup or capacity32 limit; native storage unchecked. Uses original space regardless of18CD388. Return active count; record array beyond count unchanged.
unsigned int __cdecl rf_light_build_active_list_for_sphere_query(int a1, float *rhs, float a3, char a4, char a5)
{
  float *v6; // eax
  float *v7; // eax
  float v8[3]; // [esp+4h] [ebp-88h] BYREF
  float v9[3]; // [esp+10h] [ebp-7Ch] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-70h] BYREF
  float out_vector[3]; // [esp+28h] [ebp-64h] BYREF
  float v12[3]; // [esp+34h] [ebp-58h] BYREF
  float v13; // [esp+40h] [ebp-4Ch]
  float lhs[3]; // [esp+44h] [ebp-48h] BYREF
  float v15; // [esp+50h] [ebp-3Ch]
  float v16[3]; // [esp+54h] [ebp-38h] BYREF
  float v17; // [esp+60h] [ebp-2Ch]
  float v18; // [esp+64h] [ebp-28h]
  float destination[3]; // [esp+68h] [ebp-24h] BYREF
  float v20; // [esp+74h] [ebp-18h]
  float v21; // [esp+78h] [ebp-14h]
  int v22; // [esp+7Ch] [ebp-10h]
  _DWORD *cached_room_candidates_or_global_fallback; // [esp+80h] [ebp-Ch]
  int i; // [esp+84h] [ebp-8h]
  int first_dword; // [esp+88h] [ebp-4h]

  if ( dword_663B0C || !rf_renderer_lights_enabled )
    return 0;
  if ( !byte_663B10 )
    a4 = 0;
  cached_room_candidates_or_global_fallback = rf_light_get_cached_room_candidates_or_global_fallback(a1);
  unk_D035FC = 1;
  rf_light_active_world_count = 0;
  if ( !cached_room_candidates_or_global_fallback )
    return 0;
  first_dword = rf_receiver_get_first_dword(cached_room_candidates_or_global_fallback);
  for ( i = 0; i < first_dword; ++i )
  {
    v22 = *(_DWORD *)sub_552200(cached_room_candidates_or_global_fallback, i);
    if ( *(_BYTE *)(v22 + 76)
      && (*(float *)(v22 + 64) != 0.0 || *(float *)(v22 + 68) != 0.0 || *(float *)(v22 + 72) != 0.0)
      && (a4 || !*(_BYTE *)(v22 + 77))
      && (a5 || *(_BYTE *)(v22 + 77)) )
    {
      ++unk_D035F8;
      switch ( *(_DWORD *)(v22 + 8) )
      {
        case 1:
          rf_light_active_world_records[rf_light_active_world_count++] = v22;
          break;
        case 2:
          rf_vector3_default_construct_noop(destination);
          v6 = rf_vector_subtract((const float *)(v22 + 12), out_vector, rhs);
          rf_vector_copy(destination, copy_result, v6);
          v21 = rf_vector_length_squared(destination);
          v20 = *(float *)(v22 + 60) + a3;
          v20 = v20 * v20;
          if ( v20 > (double)v21 )
            rf_light_active_world_records[rf_light_active_world_count++] = v22;
          break;
        case 3:
          rf_vector3_default_construct_noop(v16);
          v7 = rf_vector_subtract((const float *)(v22 + 12), v9, rhs);
          rf_vector_copy(v16, v8, v7);
          v18 = rf_vector_length_squared(v16);
          v17 = *(float *)(v22 + 60) + a3;
          v17 = v17 * v17;
          if ( v17 > (double)v18 )
            rf_light_active_world_records[rf_light_active_world_count++] = v22;
          break;
        case 4:
          rf_vector3_default_construct_noop(lhs);
          rf_vector3_closest_point_on_segment(rhs, (const float *)(v22 + 12), (const float *)(v22 + 24), lhs);
          rf_vector_subtract(lhs, v12, rhs);
          v15 = rf_vector_length_squared(v12);
          v13 = *(float *)(v22 + 60) + a3;
          v13 = v13 * v13;
          if ( v13 > (double)v15 )
            rf_light_active_world_records[rf_light_active_world_count++] = v22;
          break;
        default:
          continue;
      }
    }
  }
  return rf_light_active_world_count;
}

