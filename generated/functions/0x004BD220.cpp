// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BD220 rf_object_snapshot_pack_common60
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Pack60-byte common-object snapshot, null owner no-op. Header: stable id+0, deferred owner reference+4; signed health/armor quantized x8 at+8/+10; level-relative current physics position owner+0xE4 at+12; signed velocity x32 at+18; friendliness low byte+24; association slot low byte+25 (owner-1=>255); four signed quaternion components at+26; common flags dword+36; stable association id+40; raw vector owner+0x15C at+44; physics flags owner+0x1A8 at+56. Before packing CLAMP LIVE owner life+0x34 and armor+0x38 in place to[-4095,4095]. Velocity magnitude helper>=1024 writes packed zero vector without clearing live velocity. No fully cleared output/padding or mutation-free guarantee.
void __cdecl rf_object_snapshot_pack_common60(int a1, int a2)
{
  float copy_result[3]; // [esp+Ch] [ebp-28h] BYREF
  float v3[3]; // [esp+18h] [ebp-1Ch] BYREF
  float v4[4]; // [esp+24h] [ebp-10h] BYREF

  if ( a1 )
  {
    rf_quaternion_set_from_matrix3_normalized_legacy(v4, (float *)(a1 + 72));
    *(_DWORD *)a2 = *(_DWORD *)(a1 + 32);
    *(_DWORD *)(a2 + 4) = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(a1 + 48));
    rf_float_clamp_in_place((float *)(a1 + 52), -4095.0, 4095.0);
    *(_WORD *)(a2 + 8) = rf_snapshot_quantize_float_times8(*(float *)(a1 + 52));
    rf_float_clamp_in_place((float *)(a1 + 56), -4095.0, 4095.0);
    *(_WORD *)(a2 + 10) = rf_snapshot_quantize_float_times8(*(float *)(a1 + 56));
    rf_geomod_saved_position_encode_u16(
      (const float *)rf_world_solid,
      (const float *)(a1 + 228),
      (unsigned __int16 *)(a2 + 12));
    rf_snapshot_pack_quaternion_s16_times16383((_WORD *)(a2 + 26), v4);
    *(_BYTE *)(a2 + 24) = *(_BYTE *)(a1 + 504);
    *(_DWORD *)(a2 + 36) = *(_DWORD *)(a1 + 124);
    *(_DWORD *)(a2 + 40) = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(a1 + 512));
    if ( *(_DWORD *)(a1 + 516) == -1 )
      *(_BYTE *)(a2 + 25) = -1;
    else
      *(_BYTE *)(a2 + 25) = *(_BYTE *)(a1 + 516);
    rf_vector_copy((float *)(a2 + 44), copy_result, (const float *)(a1 + 348));
    if ( rf_vector3_length((float *)(a1 + 324)) >= 1024.0 )
    {
      rf_vector3_set_components_return_destination(v3, 0.0, 0.0, 0.0);
      rf_snapshot_pack_vector_s16_times32(v3, (_WORD *)(a2 + 18));
    }
    else
    {
      rf_snapshot_pack_vector_s16_times32((float *)(a1 + 324), (_WORD *)(a2 + 18));
    }
    *(_DWORD *)(a2 + 56) = *(_DWORD *)(a1 + 424);
  }
}

