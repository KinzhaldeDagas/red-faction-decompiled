// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528140 rf_light_get_cached_world_receiver_candidates
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl receiverSolid. NULLreturns0. Cache array864 and generationDWORD876; matching globalserial returns receiver+864. Mismatch stamps serial BEFORE clear-count/rebuild, retaining backing. Select common listD03608 if globalBYTE rf_fixed_pool_heap_spill_enabled nonzero, else category1D03720, walk head-to-tail next0. For nonzero type increment diagnosticD035F4; type1append, types2/3 require original position12 in receiver bounds72/84 expanded by range60 (no spot cone);type4 original finite segment12/24 versus expanded bounds. Unknown types skipped. No enabled/RGB/category/master filtering or sort/dedup/cap. Only light serial invalidates: receiver bounds movement or global list-selector change alone does
// not rebuild on matching generation. Borrowed header, no transform-space selector/coordinates, active-list update or transactional rollback.
int __cdecl rf_light_get_cached_world_receiver_candidates(int a1)
{
  int *v2; // [esp+10h] [ebp-34h]
  float v3[3]; // [esp+18h] [ebp-2Ch] BYREF
  float v4[3]; // [esp+24h] [ebp-20h] BYREF
  float v5[3]; // [esp+30h] [ebp-14h] BYREF
  int i; // [esp+3Ch] [ebp-8h]
  int *v7; // [esp+40h] [ebp-4h]

  if ( !a1 )
    return 0;
  if ( *(_DWORD *)(a1 + 876) == rf_renderer_light_change_serial )
    return a1 + 864;
  *(_DWORD *)(a1 + 876) = rf_renderer_light_change_serial;
  rf_pointer_array_clear_count_keep_storage((_DWORD *)(a1 + 864));
  if ( rf_fixed_pool_heap_spill_enabled[0] )
    v2 = &rf_renderer_common_light_list_sentinel;
  else
    v2 = &rf_renderer_category1_light_list_sentinel;
  v7 = v2;
  for ( i = *v2; (int *)i != v7; i = *(_DWORD *)i )
  {
    if ( *(_DWORD *)(i + 8) )
    {
      ++unk_D035F4;
      switch ( *(_DWORD *)(i + 8) )
      {
        case 1:
          rf_pointer_array_append_dword((_DWORD *)(a1 + 864), i);
          break;
        case 2:
          if ( rf_point_within_expanded_aabb(
                 (float *)(i + 12),
                 *(float *)(i + 60),
                 (float *)(a1 + 72),
                 (float *)(a1 + 84)) )
          {
            rf_pointer_array_append_dword((_DWORD *)(a1 + 864), i);
          }
          break;
        case 3:
          if ( rf_point_within_expanded_aabb(
                 (float *)(i + 12),
                 *(float *)(i + 60),
                 (float *)(a1 + 72),
                 (float *)(a1 + 84)) )
          {
            rf_pointer_array_append_dword((_DWORD *)(a1 + 864), i);
          }
          break;
        case 4:
          rf_vector3_copy_return_destination(v5, (float *)(a1 + 72));
          rf_vector3_copy_return_destination(v3, (float *)(a1 + 84));
          rf_vector3_subtract_scalar_in_place(v5, *(float *)(i + 60));
          rf_vector3_add_scalar_in_place(v3, *(float *)(i + 60));
          rf_vector3_default_construct_noop(v4);
          if ( rf_segment_intersects_aabb(v5, v3, (float *)(i + 12), (float *)(i + 24), v4) )
            rf_pointer_array_append_dword((_DWORD *)(a1 + 864), i);
          break;
        default:
          continue;
      }
    }
  }
  return a1 + 864;
}

