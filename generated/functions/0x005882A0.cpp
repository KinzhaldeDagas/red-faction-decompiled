// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005882A0 rf_character_import_primary_bones
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Rejects NULL reader or an already-positive primary-bone count. Reads count into owner+72 and rejects<=0. For each fixed76-byte record at+76: reads name with max24, lowercases via CRT, reads/postprocesses quaternion through5832E0 and reads position, creates affine at+24, reads parent index at+72. Parent==-1 stores this index as owner root+6740 (last root wins). Postprocesses bone array via5883D0(owner+3876,count,array). Returns1. No check that count fits50 fixed records; no parent-index/root uniqueness validation here.
char __thiscall rf_character_import_primary_bones(int *this, void **a2)
{
  char *String; // [esp+4h] [ebp-24h]
  float v5[4]; // [esp+8h] [ebp-20h] BYREF
  float v6[3]; // [esp+18h] [ebp-10h] BYREF
  int i; // [esp+24h] [ebp-4h]

  if ( !a2 )
    return 0;
  if ( *(this + 18) > 0 )
    return 0;
  *(this + 18) = rf_stream_adapter_read_int32(a2);
  if ( *(this + 18) <= 0 )
    return 0;
  for ( i = 0; i < *(this + 18); ++i )
  {
    String = (char *)(this + 19 * i + 19);
    rf_stream_adapter_read_bytes((int **)a2, String, 0x18u);
    _strlwr(String);
    rf_vector3_default_construct_noop(v6);
    rf_float4_construct_zero_zero_zero_one(v5);
    rf_stream_adapter_read_float4_versioned(a2, v5, 0, unk_1C8FC3C);
    rf_quaternion_normalize_in_place_unchecked(v5);
    rf_stream_adapter_read_vector3_versioned(a2, v6, 0, unk_1C8FBDC);
    rf_affine3x4_set_quaternion_translation((float *)String + 6, v5, v6);
    *((_DWORD *)String + 18) = rf_stream_adapter_read_int32(a2);
    if ( *((_DWORD *)String + 18) == -1 )
      *(this + 1685) = i;
  }
  rf_character_build_bone_order_by_depth((int)(this + 969), *(this + 18), (int)(this + 19));
  return 1;
}

