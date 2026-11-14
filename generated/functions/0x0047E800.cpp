// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047E800 rf_rfl_lights_section_load
// UNREALRED VERIFIED [rfl-light-decode]: Loads section 0x300 lights, allocating 0x98-byte runtime records and decoding each authored light.
void __cdecl rf_rfl_lights_section_load(_DWORD *a1, int a2)
{
  char *v2; // [esp+8h] [ebp-C8h]
  void *v3; // [esp+14h] [ebp-BCh]
  int i; // [esp+1Ch] [ebp-B4h]
  char *v5; // [esp+20h] [ebp-B0h]
  char v6[156]; // [esp+24h] [ebp-ACh] BYREF
  int int32_versioned; // [esp+C0h] [ebp-10h]
  int v8; // [esp+CCh] [ebp-4h]

  rf_rfl_light_construct((int)v6);
  v8 = 0;
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    if ( a2 )
    {
      v5 = v6;
      rf_rfl_light_record_parse(v6, a1, a2);
    }
    else
    {
      v3 = operator new(0x98u);
      LOBYTE(v8) = 1;
      if ( v3 )
        v2 = (char *)rf_rfl_light_construct((int)v3);
      else
        v2 = nullptr;
      LOBYTE(v8) = 0;
      v5 = v2;
      rf_rfl_light_record_parse(v2, a1, 0);
    }
    if ( !a2 )
    {
      if ( v5[146] == 1 )
      {
        rf_pointer_array_append_dword(rf_rfl_light_registry, (int)v5);
      }
      else if ( v5 )
      {
        rf_rfl_light_scalar_delete(v5, 1);
      }
    }
  }
  v8 = -1;
  rf_rfl_light_destroy_name((int)v6);
}

