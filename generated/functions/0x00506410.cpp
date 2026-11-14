// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00506410 rf_trigger_snapshot_restore
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] For each existing trigger, first saved-id match restores position to current+0xE4,published+0x3C,predicted+0xF0; raw flags/float/dword and two deadlines; queue stable-id fixup into+0x2E4. Missing trigger is deferred-delete, not recreated. Exact exception: missing saved id12183 in case-insensitive L19S3.rfl first looks up movers saved ids9295/9298, copies key1 position into current/predicted fields, ORs mover+0x318 mask1, sets+0x2F8=1 and composes child transforms(1), then still deletes missing trigger. No vector bounds guard for key1 in this body.
int __cdecl rf_trigger_snapshot_restore(int a1, int a2)
{
  int result; // eax
  int v3; // eax
  float v4[3]; // [esp+0h] [ebp-54h] BYREF
  float v5[3]; // [esp+Ch] [ebp-48h] BYREF
  float v6[3]; // [esp+18h] [ebp-3Ch] BYREF
  float copy_result[3]; // [esp+24h] [ebp-30h] BYREF
  float source[3]; // [esp+30h] [ebp-24h] BYREF
  int k; // [esp+3Ch] [ebp-18h]
  _DWORD v10[2]; // [esp+40h] [ebp-14h]
  unsigned __int8 v11; // [esp+4Bh] [ebp-9h]
  int i; // [esp+4Ch] [ebp-8h]
  int j; // [esp+50h] [ebp-4h]

  result = rf_trigger_runtime_list_head;
  for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = *(_DWORD *)(i + 652) )
  {
    v11 = 0;
    for ( j = 0; j < a2; ++j )
    {
      if ( *(_DWORD *)(i + 32) == *(_DWORD *)(a1 + 36 * j) )
      {
        rf_geomod_saved_position_decode_u16(
          (const float *)rf_world_solid,
          (const unsigned __int16 *)(a1 + 36 * j + 4),
          (float *)(i + 228));
        rf_vector_copy((float *)(i + 60), copy_result, (const float *)(i + 228));
        rf_vector_copy((float *)(i + 240), v6, (const float *)(i + 228));
        *(_DWORD *)(i + 672) = *(_DWORD *)(a1 + 36 * j + 12);
        *(float *)(i + 680) = *(float *)(a1 + 36 * j + 16);
        *(_DWORD *)(i + 688) = *(_DWORD *)(a1 + 36 * j + 20);
        rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a1 + 36 * j + 24), i + 740);
        rf_snapshot_unpack_replicator_remaining((int *)(i + 756), (int *)(a1 + 36 * j + 28));
        rf_snapshot_unpack_replicator_remaining((int *)(i + 764), (int *)(a1 + 36 * j + 32));
        v11 = 1;
        break;
      }
    }
    result = v11;
    if ( !v11 )
    {
      if ( *(_DWORD *)(i + 32) == 12183 && rf_string_equals_case_insensitive((int)unk_6FC31C, "L19S3.rfl") )
      {
        v10[0] = rf_mover_find_by_saved_identifier(9295);
        v10[1] = rf_mover_find_by_saved_identifier(9298);
        for ( k = 0; k < 2; ++k )
        {
          if ( v10[k] )
          {
            v3 = sub_552200((_DWORD *)(v10[k] + 668), 1);
            rf_vector3_copy_return_destination(source, (float *)(*(_DWORD *)v3 + 4));
            rf_vector_copy((float *)(v10[k] + 228), v5, source);
            rf_vector_copy((float *)(v10[k] + 240), v4, source);
            *(_DWORD *)(v10[k] + 792) |= 1u;
            *(_DWORD *)(v10[k] + 760) = 1;
          }
        }
        rf_mover_compose_child_transforms(1);
      }
      result = rf_object_mark_for_deferred_delete(i);
    }
  }
  return result;
}

