// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004743F0 rf_item_snapshot_restore
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] First pass existing items: match saved stable id, restore common60 AND item timer/floats/flags tail; unmatched non-carryover(mask0x800 clear) item marked deferred-delete. Second pass each saved80-byte entry absent from current list is recreated from saved definition+76, quantized position/quaternion and definition-specific spawn argument. After spawn call ONLY common60 restore, not saved item timer/floats/flags tail. Thus recreated and matched item paths differ. No explicit spawn-result guard locally; common restore itself accepts null. No item uniqueness or full tail replay for newly created items.
int __cdecl rf_item_snapshot_restore(int a1, int a2)
{
  int result; // eax
  int v3[9]; // [esp+0h] [ebp-50h] BYREF
  float v4[4]; // [esp+24h] [ebp-2Ch] BYREF
  float world_position[3]; // [esp+34h] [ebp-1Ch] BYREF
  int v6; // [esp+40h] [ebp-10h]
  char v7; // [esp+46h] [ebp-Ah]
  char v8; // [esp+47h] [ebp-9h]
  int i; // [esp+48h] [ebp-8h]
  int j; // [esp+4Ch] [ebp-4h]

  result = unk_6FB1C4;
  for ( i = unk_6FB1C4; (_UNKNOWN *)i != &unk_6FAF38; i = *(_DWORD *)(i + 652) )
  {
    v8 = 0;
    for ( j = 0; j < a2; ++j )
    {
      if ( *(_DWORD *)(i + 32) == *(_DWORD *)(a1 + 80 * j) )
      {
        rf_object_snapshot_restore_common60(i, a1 + 80 * j);
        rf_snapshot_unpack_replicator_remaining((int *)(i + 688), (int *)(a1 + 80 * j + 60));
        *(float *)(i + 692) = *(float *)(a1 + 80 * j + 64);
        *(float *)(i + 696) = *(float *)(a1 + 80 * j + 68);
        result = a1;
        *(_DWORD *)(i + 700) = *(_DWORD *)(a1 + 80 * j + 72);
        v8 = 1;
        break;
      }
      result = j + 1;
    }
    if ( !v8 )
    {
      result = i;
      if ( (*(_DWORD *)(i + 124) & 0x800) == 0 )
        result = rf_object_mark_for_deferred_delete(i);
    }
  }
  for ( j = 0; j < a2; ++j )
  {
    v7 = 0;
    for ( i = unk_6FB1C4; (_UNKNOWN *)i != &unk_6FAF38; i = *(_DWORD *)(i + 652) )
    {
      if ( *(_DWORD *)(a1 + 80 * j) == *(_DWORD *)(i + 32) )
      {
        v7 = 1;
        break;
      }
    }
    if ( !v7 )
    {
      rf_vector3_default_construct_noop(world_position);
      rf_float4_construct_zero_zero_zero_one(v4);
      rf_matrix3_construct((char *)v3);
      rf_snapshot_unpack_quaternion_s16(v4, (__int16 *)(a1 + 80 * j + 26));
      rf_quaternion_to_matrix3_rows(v4, (float *)v3);
      rf_geomod_saved_position_decode_u16(
        (const float *)rf_world_solid,
        (const unsigned __int16 *)(a1 + 80 * j + 12),
        world_position);
      v6 = rf_item_instance_spawn(
             *(_DWORD *)(a1 + 80 * j + 76),
             (char *)byte_6380AA,
             unk_6F915C[20 * *(_DWORD *)(a1 + 80 * j + 76)],
             -1,
             world_position,
             (float *)v3,
             -1,
             0,
             0);
      rf_object_snapshot_restore_common60(v6, a1 + 80 * j);
    }
    result = j + 1;
  }
  return result;
}

