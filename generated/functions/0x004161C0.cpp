// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004161C0 rf_clutter_snapshot_restore
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Existing clutter only: skip carryover-mask0x800 owners when0x446190()==10, otherwise match24-byte saved stable id or mark missing owner deferred-delete. Decode position to owner+0xE4; when squared difference from current published+0x3C<literal~1e-4, preserve original published point to suppress quantization jitter. Copy admitted point to published+0x3C,secondary+0x6C,predicted+0xF0 and call0x4BC210(owner,0). Restore both timers/raw dword, SIGN-extend entry state byte+4 to owner+0x2BC, and hide when saved byte+5 nonzero. Saved false does not explicitly reactivate a hidden owner. No missing-clutter recreation pass.
void __cdecl rf_clutter_snapshot_restore(int a1, int a2)
{
  float v2[3]; // [esp+0h] [ebp-48h] BYREF
  float v3[3]; // [esp+Ch] [ebp-3Ch] BYREF
  float v4[3]; // [esp+18h] [ebp-30h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-24h] BYREF
  float out_vector[3]; // [esp+30h] [ebp-18h] BYREF
  char v7; // [esp+3Fh] [ebp-9h]
  int j; // [esp+40h] [ebp-8h]
  float *i; // [esp+44h] [ebp-4h]

  for ( i = (float *)rf_clutter_list_head; i != (float *)&unk_666D18; i = *((float **)i + 163) )
  {
    if ( ((_DWORD)i[31] & 0x800) == 0 || rf_ui_panel_stack_current_id() != 10 )
    {
      v7 = 0;
      for ( j = 0; j < a2; ++j )
      {
        if ( *((_DWORD *)i + 8) == *(_DWORD *)(a1 + 24 * j) )
        {
          rf_geomod_saved_position_decode_u16(
            (const float *)rf_world_solid,
            (const unsigned __int16 *)(a1 + 24 * j + 6),
            i + 57);
          rf_vector_subtract(i + 15, out_vector, i + 57);
          if ( rf_vector_length_squared(out_vector) < 0.00009999999747378752 )
            rf_vector_copy(i + 57, copy_result, i + 15);
          rf_vector_copy(i + 15, v4, i + 57);
          rf_vector_copy(i + 27, v3, i + 57);
          rf_vector_copy(i + 60, v2, i + 57);
          rf_object_set_room_and_cache_position(i, 0);
          rf_snapshot_unpack_replicator_remaining((int *)i + 169, (int *)(a1 + 24 * j + 12));
          i[170] = *(float *)(a1 + 24 * j + 16);
          rf_snapshot_unpack_replicator_remaining((int *)i + 172, (int *)(a1 + 24 * j + 20));
          *((_DWORD *)i + 175) = *(char *)(a1 + 24 * j + 4);
          if ( *(_BYTE *)(a1 + 24 * j + 5) )
            rf_object_mark_hidden_inactive((int)i);
          v7 = 1;
          break;
        }
      }
      if ( !v7 )
        rf_object_mark_for_deferred_delete((int)i);
    }
  }
}

