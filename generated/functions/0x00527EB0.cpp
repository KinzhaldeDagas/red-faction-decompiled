// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00527EB0 rf_light_get_cached_room_candidates_or_global_fallback
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl optionalRoom. NonNULL: if roomDWORD456==global serial return borrowed12-byte array header444 without changes. Else stamp serial BEFORE rebuild, clear array count retaining storage, select common listD03608 when globalBYTE rf_fixed_pool_heap_spill_enabled nonzero, otherwise category1 listD03720. Walk next0 head-to-tail; each type8!=0 increments diagnosticDWORDD035F4. Type1 append unconditionally; types2/3 require inclusive point(original12) within room bounds8/20 expanded range60 (spot cone ignored); type4 finite original segment12/24 intersects range-expanded roomAABB; othersignored. No enabled76, RGB, category77 or master-light gate filtering; no sort/dedup, transform-space92 use or
// bounds-change generation. NULLroom: globalBYTEzero returnsNULL; nonzero returns borrowed global arrayD03714. If its serial663B18 differs, stamp first, RELEASE backing entirely and rebuild from common list appending EVERY type!=0, including unknown types, no diagnostics or spatial/enable/RGB filter. Matching serial leaves cache untouched. No per-object importance rank/cap, allocation-failure rollback, or validity of stale pointers check.
_DWORD *__cdecl rf_light_get_cached_room_candidates_or_global_fallback(int a1)
{
  int *v2; // [esp+10h] [ebp-38h]
  float v3[3]; // [esp+18h] [ebp-30h] BYREF
  float v4[3]; // [esp+24h] [ebp-24h] BYREF
  float v5[3]; // [esp+30h] [ebp-18h] BYREF
  _DWORD *j; // [esp+3Ch] [ebp-Ch]
  int i; // [esp+40h] [ebp-8h]
  int *v8; // [esp+44h] [ebp-4h]

  if ( a1 )
  {
    if ( *(_DWORD *)(a1 + 456) == rf_renderer_light_change_serial )
    {
      return (_DWORD *)(a1 + 444);
    }
    else
    {
      *(_DWORD *)(a1 + 456) = rf_renderer_light_change_serial;
      rf_pointer_array_clear_count_keep_storage((_DWORD *)(a1 + 444));
      if ( rf_fixed_pool_heap_spill_enabled[0] )
        v2 = &rf_renderer_common_light_list_sentinel;
      else
        v2 = &rf_renderer_category1_light_list_sentinel;
      v8 = v2;
      for ( i = *v2; (int *)i != v8; i = *(_DWORD *)i )
      {
        if ( *(_DWORD *)(i + 8) )
        {
          ++unk_D035F4;
          switch ( *(_DWORD *)(i + 8) )
          {
            case 1:
              rf_pointer_array_append_dword((_DWORD *)(a1 + 444), i);
              break;
            case 2:
              if ( rf_point_within_expanded_aabb(
                     (float *)(i + 12),
                     *(float *)(i + 60),
                     (float *)(a1 + 8),
                     (float *)(a1 + 20)) )
              {
                rf_pointer_array_append_dword((_DWORD *)(a1 + 444), i);
              }
              break;
            case 3:
              if ( rf_point_within_expanded_aabb(
                     (float *)(i + 12),
                     *(float *)(i + 60),
                     (float *)(a1 + 8),
                     (float *)(a1 + 20)) )
              {
                rf_pointer_array_append_dword((_DWORD *)(a1 + 444), i);
              }
              break;
            case 4:
              rf_vector3_copy_return_destination(v5, (float *)(a1 + 8));
              rf_vector3_copy_return_destination(v3, (float *)(a1 + 20));
              rf_vector3_subtract_scalar_in_place(v5, *(float *)(i + 60));
              rf_vector3_add_scalar_in_place(v3, *(float *)(i + 60));
              rf_vector3_default_construct_noop(v4);
              if ( rf_segment_intersects_aabb(v5, v3, (float *)(i + 12), (float *)(i + 24), v4) )
                rf_pointer_array_append_dword((_DWORD *)(a1 + 444), i);
              break;
            default:
              continue;
          }
        }
      }
      return (_DWORD *)(a1 + 444);
    }
  }
  else if ( rf_fixed_pool_heap_spill_enabled[0] )
  {
    if ( dword_663B18 != rf_renderer_light_change_serial )
    {
      dword_663B18 = rf_renderer_light_change_serial;
      rf_pointer_array_release_storage((void **)unk_D03714);
      for ( j = (_DWORD *)rf_renderer_common_light_list_sentinel;
            j != &rf_renderer_common_light_list_sentinel;
            j = (_DWORD *)*j )
      {
        if ( j[2] )
          rf_pointer_array_append_dword(unk_D03714, (int)j);
      }
    }
    return unk_D03714;
  }
  else
  {
    return nullptr;
  }
}

