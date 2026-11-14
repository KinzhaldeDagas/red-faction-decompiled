// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043AEC0 rf_entity_snapshot_restore_registry
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Existing entities: skip carryover(mask0x800) only when0x446190()==10; first stable-id match restores536-byte record via0x43A530. Matched entity now dead/pending-delete plus owner+0x810 mask0x400000 requests0x453B20 using owner name. Unmatched bat/fish are preserved; other unmatched ids in separate inactive list are hidden, remainder deferred-delete. Second saved-entry pass recreates missing entities ONLY when snapshot+0x1D4 mask0x400 set, using signed definition index+62 and decoded position/orientation, then full0x43A530 on successful spawn. No unconditional recreation of every absent saved entity or clearing of old list before merge.
int __cdecl rf_entity_snapshot_restore_registry(int a1, int a2, int a3, int a4)
{
  int result; // eax
  char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  int v8[9]; // [esp+0h] [ebp-58h] BYREF
  int v9; // [esp+24h] [ebp-34h]
  float v10[4]; // [esp+28h] [ebp-30h] BYREF
  float world_position[3]; // [esp+38h] [ebp-20h] BYREF
  char v12; // [esp+47h] [ebp-11h]
  int k; // [esp+48h] [ebp-10h]
  char v14; // [esp+4Dh] [ebp-Bh]
  char v15; // [esp+4Eh] [ebp-Ah]
  unsigned __int8 v16; // [esp+4Fh] [ebp-9h]
  int i; // [esp+50h] [ebp-8h]
  int j; // [esp+54h] [ebp-4h]

  result = unk_68211C;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    v16 = 0;
    if ( (*(_DWORD *)(i + 124) & 0x800) != 0 )
    {
      result = rf_ui_panel_stack_current_id();
      if ( result == 10 )
        continue;
    }
    for ( j = 0; j < a2; ++j )
    {
      if ( *(_DWORD *)(i + 32) == *(_DWORD *)(a1 + 536 * j) )
      {
        rf_entity_snapshot_restore_record(i, a1 + 536 * j);
        v16 = 1;
        break;
      }
    }
    v15 = 0;
    if ( rf_entity_is_dead(i) || (*(_DWORD *)(i + 124) & 2) != 0 )
      v15 = 1;
    result = v16;
    if ( v16 == 1 )
    {
      if ( v15 )
      {
        result = *(_DWORD *)(i + 2064) & 0x400000;
        if ( result )
        {
          v5 = (char *)rf_string_object_c_str_or_empty((const void *)(i + 24));
          result = rf_frontend_request_credits_or_endgame_blackout(v5);
        }
      }
    }
    if ( !v16 )
    {
      v6 = rf_string_object_c_str_or_empty(*(const void **)(i + 660));
      result = _stricmp(v6, off_632FD8);
      if ( result )
      {
        v7 = rf_string_object_c_str_or_empty(*(const void **)(i + 660));
        result = _stricmp(v7, "fish");
        if ( result )
        {
          v14 = 0;
          for ( k = 0; k < a4; ++k )
          {
            if ( *(_DWORD *)(i + 32) == *(_DWORD *)(a3 + 4 * k) )
            {
              v14 = 1;
              break;
            }
          }
          if ( v14 )
            rf_object_mark_hidden_inactive(i);
          else
            result = rf_object_mark_for_deferred_delete(i);
        }
      }
    }
  }
  for ( j = 0; j < a2; ++j )
  {
    result = 536 * j;
    if ( (*(_DWORD *)(a1 + 536 * j + 468) & 0x400) != 0 )
    {
      v12 = 0;
      result = unk_68211C;
      for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
      {
        result = 536 * j;
        if ( *(_DWORD *)(i + 32) == *(_DWORD *)(a1 + 536 * j) )
        {
          v12 = 1;
          break;
        }
      }
      if ( !v12 )
      {
        rf_vector3_default_construct_noop(world_position);
        rf_float4_construct_zero_zero_zero_one(v10);
        rf_matrix3_construct((char *)v8);
        rf_snapshot_unpack_quaternion_s16(v10, (__int16 *)(a1 + 536 * j + 26));
        rf_quaternion_to_matrix3_rows(v10, (float *)v8);
        rf_geomod_saved_position_decode_u16(
          (const float *)rf_world_solid,
          (const unsigned __int16 *)(a1 + 536 * j + 12),
          world_position);
        result = rf_entity_create_runtime(
                   *(__int16 *)(a1 + 536 * j + 62),
                   (char *)byte_631AFE,
                   -1,
                   world_position,
                   (float *)v8,
                   0,
                   -1);
        v9 = result;
        if ( result )
          result = rf_entity_snapshot_restore_record(v9, a1 + 536 * j);
      }
    }
  }
  return result;
}

