// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510DA0 rf_projectile_snapshot_restore
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] For every152-byte saved record decode position/quaternion and call rf_projectile_create_runtime(saved definition+60,shooter=-1,position,orientation,0,0). Success restores common60 plus projectile tail, ZERO-extends entry byte+124 into owner+0x2E4 and queues saved references into+0x2B0/+0x2E8. Does not match or remove current projectiles, check duplicate saved ids, replay weapon fire animation or charge ammo in this body. Existing projectile cleanup is separate.
void __cdecl rf_projectile_snapshot_restore(int a1, int a2)
{
  float v2[3]; // [esp+0h] [ebp-64h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-58h] BYREF
  float v4[9]; // [esp+18h] [ebp-4Ch] BYREF
  float v5[4]; // [esp+3Ch] [ebp-28h] BYREF
  float *runtime; // [esp+4Ch] [ebp-18h]
  float world_position[3]; // [esp+50h] [ebp-14h] BYREF
  int v8; // [esp+5Ch] [ebp-8h]
  int i; // [esp+60h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    rf_float4_construct_zero_zero_zero_one(v5);
    rf_matrix3_construct((char *)v4);
    rf_vector3_default_construct_noop(world_position);
    v8 = a1 + 152 * i;
    rf_snapshot_unpack_quaternion_s16(v5, (__int16 *)(v8 + 26));
    rf_quaternion_to_matrix3_rows(v5, v4);
    rf_geomod_saved_position_decode_u16(
      (const float *)rf_world_solid,
      (const unsigned __int16 *)(v8 + 12),
      world_position);
    runtime = rf_projectile_create_runtime(*(_DWORD *)(v8 + 60), -1, world_position, v4, 0, 0);
    if ( runtime )
    {
      rf_object_snapshot_restore_common60((int)runtime, a1 + 152 * i);
      runtime[167] = *(float *)(a1 + 152 * i + 64);
      runtime[170] = *(float *)(a1 + 152 * i + 68);
      rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a1 + 152 * i + 72), (int)(runtime + 172));
      rf_vector_copy(runtime + 173, copy_result, (const float *)(a1 + 152 * i + 76));
      rf_matrix3_copy(runtime + 176, (const float *)(a1 + 152 * i + 88));
      *((_DWORD *)runtime + 185) = *(unsigned __int8 *)(a1 + 152 * i + 124);
      rf_restore_queue_object_identifier_fixup(*(_DWORD *)(a1 + 152 * i + 128), (int)(runtime + 186));
      runtime[188] = *(float *)(a1 + 152 * i + 132);
      runtime[189] = *(float *)(a1 + 152 * i + 136);
      rf_vector_copy(runtime + 194, v2, (const float *)(a1 + 152 * i + 140));
    }
  }
}

