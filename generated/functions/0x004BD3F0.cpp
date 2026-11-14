// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BD3F0 rf_object_snapshot_restore_common60
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Restore common60-byte header into non-null owner: stable id, signed x8 life/armor, decoded position into current+0xE4 and published+0x3C/secondary+0x6C/predicted+0xF0; quaternion-derived orientation setup; zero-extended friendliness; slot255=>-1 else unsigned byte. If owner currently hidden0x4000 and snapshot not hidden, call reactivation BEFORE replacing common flags. Queue references for owner+0x30/+0x200 via stable-id fixups. Rebuild physics setup using CURRENT owner mass/inertia/material fields, saved raw vector+44 divided by mass, signed velocity and saved physics flags; assign saved vector/velocity and flags then OR common mask0x06000000. Does not restore every physical coefficient from snapshot or immediately resolve queued references.
void __cdecl rf_object_snapshot_restore_common60(int a1, int a2)
{
  float *v2; // eax
  float v3[3]; // [esp+8h] [ebp-108h] BYREF
  float v4[3]; // [esp+14h] [ebp-FCh] BYREF
  float v5[3]; // [esp+20h] [ebp-F0h] BYREF
  int v6[3]; // [esp+2Ch] [ebp-E4h] BYREF
  float v7[3]; // [esp+38h] [ebp-D8h] BYREF
  float v8[3]; // [esp+44h] [ebp-CCh] BYREF
  float copy_result[3]; // [esp+50h] [ebp-C0h] BYREF
  float v10[4]; // [esp+5Ch] [ebp-B4h] BYREF
  void *v11[38]; // [esp+6Ch] [ebp-A4h] BYREF
  int v12; // [esp+10Ch] [ebp-4h]

  if ( a1 )
  {
    rf_float4_construct_zero_zero_zero_one(v10);
    rf_snapshot_unpack_quaternion_s16(v10, (__int16 *)(a2 + 26));
    *(_DWORD *)(a1 + 32) = *(_DWORD *)a2;
    *(float *)(a1 + 52) = rf_snapshot_dequantize_s16_div8(*(_WORD *)(a2 + 8));
    *(float *)(a1 + 56) = rf_snapshot_dequantize_s16_div8(*(_WORD *)(a2 + 10));
    rf_geomod_saved_position_decode_u16(
      (const float *)rf_world_solid,
      (const unsigned __int16 *)(a2 + 12),
      (float *)(a1 + 228));
    rf_vector_copy((float *)(a1 + 60), copy_result, (const float *)(a1 + 228));
    rf_vector_copy((float *)(a1 + 108), v8, (const float *)(a1 + 228));
    rf_vector_copy((float *)(a1 + 240), v7, (const float *)(a1 + 228));
    rf_quaternion_to_matrix3_rows(v10, (float *)(a1 + 252));
    rf_matrix3_rebuild_basis_from_forward_in_place((char *)(a1 + 252));
    rf_matrix3_copy((float *)(a1 + 72), (const float *)(a1 + 252));
    *(_DWORD *)(a1 + 504) = *(unsigned __int8 *)(a2 + 24);
    if ( (*(_DWORD *)(a1 + 124) & 0x4000) != 0 && (*(_DWORD *)(a2 + 36) & 0x4000) == 0 )
      rf_object_reactivate_from_respawn((_DWORD *)a1);
    *(_DWORD *)(a1 + 124) = *(_DWORD *)(a2 + 36);
    rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 4), a1 + 48);
    rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a2 + 40), a1 + 512);
    if ( *(unsigned __int8 *)(a2 + 25) == 255 )
      *(_DWORD *)(a1 + 516) = -1;
    else
      *(_DWORD *)(a1 + 516) = *(unsigned __int8 *)(a2 + 25);
    rf_object_setup152_construct_members((char *)v11);
    v12 = 0;
    memset(v11, 0, sizeof(v11));
    v2 = rf_vector_divide((float *)(a2 + 44), (float *)v6, *(float *)(a1 + 152));
    rf_vector_copy((float *)&v11[30], v5, v2);
    rf_matrix3_copy((float *)&v11[6], (const float *)(a1 + 156));
    v11[3] = *(void **)(a1 + 140);
    v11[5] = *(void **)(a1 + 152);
    v11[4] = *(void **)(a1 + 508);
    rf_matrix3_copy((float *)&v11[18], (const float *)(a1 + 252));
    v11[37] = *(void **)(a2 + 56);
    rf_vector_copy((float *)&v11[15], v4, (const float *)(a1 + 228));
    v11[33] = *(void **)(a1 + 120);
    v11[2] = nullptr;
    rf_pointer_array_release_storage(&v11[34]);
    rf_snapshot_unpack_vector_s16_div32((__int16 *)(a2 + 18), (float *)&v11[27]);
    rf_physics_state_copy_setup(a1 + 136, (int)v11, 1);
    rf_vector_copy((float *)(a1 + 348), v3, (const float *)(a2 + 44));
    rf_snapshot_unpack_vector_s16_div32((__int16 *)(a2 + 18), (float *)(a1 + 324));
    *(_DWORD *)(a1 + 424) = *(_DWORD *)(a2 + 56);
    *(_DWORD *)(a1 + 124) |= 0x6000000u;
    v12 = -1;
    rf_object_setup152_destroy_array_backing(v11);
  }
}

