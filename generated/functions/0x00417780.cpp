// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417780 rf_monitor_update_record_render_or_remove_stale
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Resolves clutter UID +12 before render admission. Missing clutter exits local monitor view when its selected UID matches, then unlinks/frees the record. Otherwise flags+56 bit2 is required. Mode0 with missing selected entity UID+16 changes mode to2 and exits matching local monitor view. Only mode2 applies camera-forward dot and optional flags4 distance-squared culling: ordered positive dot rejects; ordered distanceSquared>100 rejects; unordered comparisons pass. Full 36-byte view-matrix output defines the forward vector despite split decompiler locals. Admitted records publish player to global0x87C640; flags8 permanently clears flags4; mode0 renders selected entity, mode1 black, mode2 noise, other modes draw nothing. Clears
// global0x87C640 to zero rather than restoring a previous value. No local-player null guard, finite-value guard or unwind restoration.
void __cdecl rf_monitor_update_record_render_or_remove_stale(int a1, int *a2)
{
  int v2; // [esp+0h] [ebp-40h]
  float v3[3]; // [esp+4h] [ebp-3Ch] BYREF
  float v4; // [esp+10h] [ebp-30h]
  _BYTE v5[24]; // [esp+14h] [ebp-2Ch] BYREF
  float v6[3]; // [esp+2Ch] [ebp-14h] BYREF
  int v8; // [esp+3Ch] [ebp-4h]

  v8 = rf_clutter_find_by_uid(a2[3]);
  if ( v8 )
  {
    if ( (a2[14] & 2) != 0 )
    {
      if ( !a2[2] && !rf_entity_resolve_handle(a2[4]) )
      {
        a2[2] = 2;
        if ( *(_DWORD *)(rf_local_fpgun_player + 180) == a2[3] )
          rf_player_exit_monitor_view(rf_local_fpgun_player);
      }
      if ( a2[2] != 2
        || (rf_entity_view_copy_referenced_matrix_2016((int)v5, *(_DWORD **)(a1 + 196)),
            rf_vector_dot(v6, (float *)(v8 + 96)) <= 0.0)
        && ((a2[14] & 4) == 0
         || (rf_entity_view_copy_referenced_position(v3, *(_DWORD *)(a1 + 196)),
             v4 = rf_vector_distance_squared(v3, (const float *)(v8 + 60)),
             v4 <= 100.0)) )
      {
        unk_87C640 = a1;
        if ( (a2[14] & 8) != 0 )
          a2[14] &= ~4u;
        v2 = a2[2];
        if ( v2 )
        {
          if ( v2 == 1 )
          {
            rf_monitor_fill_black_bitmap((int)a2);
          }
          else if ( v2 == 2 )
          {
            rf_monitor_fill_noise_bitmap((int)a2);
          }
        }
        else
        {
          rf_monitor_render_selected_entity_view(a2);
        }
        unk_87C640 = 0;
      }
    }
  }
  else
  {
    if ( *(_DWORD *)(rf_local_fpgun_player + 180) == a2[3] )
      rf_player_exit_monitor_view(rf_local_fpgun_player);
    rf_monitor_unlink_and_destroy_record(a2);
  }
}

