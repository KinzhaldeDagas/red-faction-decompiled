// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528680 rf_light_build_active_list_for_aabb_query
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl optionalRoom,minXYZ,maxXYZ,includeCategoryBYTE,includeCommonBYTE. Suppression663B0C or masterdisabled returns0 leaving prior active count/validity untouched. Globalallow663B10zero forces includeCategory0. Get527EB0 candidates; mark validity1/count0 even for NULLcache. In candidate order require enabled76, at least one RGB component nonzero OR NaN, same category truth table(0,0)none,(1,0)nonzero,(0,1)zero,(1,1)both. Increment diagnosticD035F4 for each filter-admitted candidate BEFORE type switch (unlike sphereD035F8). Type1 append;types2/3 inclusive original position12 within queryAABB expanded componentwise by range60, spot cone ignored;type4 original endpoints12/24 finite segment against
// expandedAABB. Unknown type skip. No Euclidean sphere/AABB distance, transforms, sort,dedup,32 cap or storage bound check. Return count, preserve order.
unsigned int __cdecl rf_light_build_active_list_for_aabb_query(int a1, float *a2, float *a3, char a4, char a5)
{
  float v6[3]; // [esp+10h] [ebp-34h] BYREF
  float v7[3]; // [esp+1Ch] [ebp-28h] BYREF
  float v8[3]; // [esp+28h] [ebp-1Ch] BYREF
  int v9; // [esp+34h] [ebp-10h]
  _DWORD *cached_room_candidates_or_global_fallback; // [esp+38h] [ebp-Ch]
  int i; // [esp+3Ch] [ebp-8h]
  int first_dword; // [esp+40h] [ebp-4h]

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
    v9 = *(_DWORD *)sub_552200(cached_room_candidates_or_global_fallback, i);
    if ( *(_BYTE *)(v9 + 76)
      && (*(float *)(v9 + 64) != 0.0 || *(float *)(v9 + 68) != 0.0 || *(float *)(v9 + 72) != 0.0)
      && (a4 || !*(_BYTE *)(v9 + 77))
      && (a5 || *(_BYTE *)(v9 + 77)) )
    {
      ++unk_D035F4;
      switch ( *(_DWORD *)(v9 + 8) )
      {
        case 1:
          rf_light_active_world_records[rf_light_active_world_count++] = v9;
          break;
        case 2:
          if ( rf_point_within_expanded_aabb((float *)(v9 + 12), *(float *)(v9 + 60), a2, a3) )
            rf_light_active_world_records[rf_light_active_world_count++] = v9;
          break;
        case 3:
          if ( rf_point_within_expanded_aabb((float *)(v9 + 12), *(float *)(v9 + 60), a2, a3) )
            rf_light_active_world_records[rf_light_active_world_count++] = v9;
          break;
        case 4:
          rf_vector3_copy_return_destination(v8, a2);
          rf_vector3_copy_return_destination(v6, a3);
          rf_vector3_subtract_scalar_in_place(v8, *(float *)(v9 + 60));
          rf_vector3_add_scalar_in_place(v6, *(float *)(v9 + 60));
          rf_vector3_default_construct_noop(v7);
          if ( rf_segment_intersects_aabb(v8, v6, (float *)(v9 + 12), (float *)(v9 + 24), v7) )
            rf_light_active_world_records[rf_light_active_world_count++] = v9;
          break;
        default:
          continue;
      }
    }
  }
  return rf_light_active_world_count;
}

