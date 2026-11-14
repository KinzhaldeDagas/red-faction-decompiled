// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00480D60 rf_rfl_moving_solids_section_load
// UNREALRED VERIFIED [mission-mover-geometry-20261013] Loads the live RFL section 0x00002000: count then UID, vec3 position, serialized orientation, full geometry via 0x545B30, and three trailing object metadata dwords (the geometry itself consumes its version180 legacy tail). Creates type9 via 0x48A2B0. The four bytes after the 48-byte pose are NOT another transform float: the geometry starts with a length-prefixed name and flags. Do not confuse this live object section with editor/cache section 0x02000000.
int __cdecl rf_rfl_moving_solids_section_load(void **a1)
{
  int result; // eax
  float v2[3]; // [esp+Ch] [ebp-40h] BYREF
  int int32; // [esp+18h] [ebp-34h]
  int v4; // [esp+1Ch] [ebp-30h]
  float v5[9]; // [esp+20h] [ebp-2Ch] BYREF
  char *v6; // [esp+44h] [ebp-8h]
  int i; // [esp+48h] [ebp-4h]

  rf_vector3_default_construct_noop(v2);
  rf_matrix3_construct((char *)v5);
  result = rf_stream_adapter_read_int32(a1);
  v4 = result;
  for ( i = 0; i < v4; ++i )
  {
    int32 = rf_stream_adapter_read_int32(a1);
    rf_stream_adapter_read_vector3_versioned(a1, v2, 0, unk_1C8FBDC);
    rf_binary_stream_read_orientation(a1, v5, 0, unk_1C8FC18);
    v6 = rf_level_geometry_deserialize((int)a1, nullptr);
    rf_stream_adapter_read_int32(a1);
    rf_stream_adapter_read_int32_versioned(a1, 122, 0);
    rf_stream_adapter_read_int32(a1);
    if ( !rf_moving_solid_create(int32, (int)v6, (int)v2, (int)v5) )
    {
      if ( v6 )
        rf_solid_destroy(v6, 1);
    }
    result = i + 1;
  }
  return result;
}

