// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047E3C0 rf_geomod_georegions_load
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Cdecl binary stream pointer; RFL dispatcher section0x200. Reads signed count, allocates80-byte region per row, invokes no-op ctor if allocation nonnull, then consumes fields with
// no local NULL-allocation rejection. Discards initial int32 id; for stream version<67 reads obsolete name into global RFString6FCCC0. Does not clear existing region registry before
// appending or validate read success/section byte length itself.
// Version>=99 reads packed int32: shape=bits0..2; bit0x10 legacy material-name presence, directional BYTE8=bit0x20 normalized, ice BYTE9=bit0x40 normalized,
// hardnessDWORD4=(packed&0xFF0000)>>16. For versions99..162 explicitly clears BOTH directional and ice bytes, then if material-name presence reads string, loads bitmap(-1,1), sets
// ice iff bitmap_material_to_index returns8 (Ice). It does NOT honor packed directional/ice bits in those versions. For >=163 packed directional remains; nonzero byte8 causes FLOAT
// scalar12 read. Packed bit0x10 has no further material-name read in >=163.
// Version<99 instead discards a versioned bool(default1,minimum-version value from global BYTE6FCCA0), reads obsolete material string to temporary, reads full shape int32, writes
// directional byte8=0 and temporary hardness50. Ice BYTE9 is NOT initialized by this branch or no-op constructor; scalar12 also stays untouched. Later reads legacy hardness int32 and
// overwrites temporary50, then signed-clamps0..100. Modern extracted hardness0..255 is also clamped0..100.
// Shape2 sphere: reads center16; only byte8 EXACT1 reads matrix28 via versioned matrix helper. For version<163 discards one extra float, then reads radiusFLOAT64, zeros dimensions
// vector68. Shape4 box: reads center16,matrix28,full dimensions68,sets radius64=0; <163 discards extra float. Shape3 consumes two vectors into same local scratch and one discarded
// float; after common trailing fields raw-deletes region instead of registry append. Unknown shapes consume no shape-specific fields and still append. No shape-range,
// radius/dimension finite/positive check or matrix normalization here.
// For every version<163 consumes/discards version-gated int32(min132,default64) and packed4-byte field(min133,default global1C8FC4C). Shape3 deletion happens only AFTER this
// compatibility consumption and hardness clamp. Other records append registry pointer in input order. Temporary strings destroyed on exit/unwind; allocation unwind covers current
// constructor failure, not rollback/free of all earlier rows. Boolean region admission/containment happens elsewhere.
void __cdecl rf_geomod_georegions_load(_DWORD *a1)
{
  int v1; // eax
  char *v2; // eax
  int v3; // eax
  int v4; // eax
  double float_versioned; // st7
  double v6; // st7
  int v7; // eax
  int v8; // [esp+8h] [ebp-5Ch]
  char *v9; // [esp+Ch] [ebp-58h]
  int v10; // [esp+14h] [ebp-50h] BYREF
  void *v11; // [esp+18h] [ebp-4Ch]
  char *v12; // [esp+1Ch] [ebp-48h]
  bool v13; // [esp+23h] [ebp-41h]
  int v14; // [esp+24h] [ebp-40h]
  int i; // [esp+28h] [ebp-3Ch]
  int v16[2]; // [esp+2Ch] [ebp-38h] BYREF
  int v17; // [esp+34h] [ebp-30h]
  _DWORD v18[2]; // [esp+38h] [ebp-2Ch] BYREF
  _DWORD v19[2]; // [esp+40h] [ebp-24h] BYREF
  float v20[3]; // [esp+48h] [ebp-1Ch] BYREF
  int int32_versioned; // [esp+54h] [ebp-10h]
  int v22; // [esp+60h] [ebp-4h]

  rf_string_construct_empty(v18);
  v22 = 0;
  rf_string_construct_empty(v19);
  LOBYTE(v22) = 1;
  rf_vector3_default_construct_noop(v20);
  rf_string_construct_empty(v16);
  LOBYTE(v22) = 2;
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    v11 = operator new(0x50u);
    LOBYTE(v22) = 3;
    if ( v11 )
      v9 = rf_geomod_georegion_init((char *)v11);
    else
      v9 = nullptr;
    v12 = v9;
    LOBYTE(v22) = 2;
    v17 = (int)v9;
    rf_binary_stream_read_int32_versioned(a1, 0, 0);
    if ( rf_vfile_get_slot_version(a1) < 67 )
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    if ( rf_vfile_get_slot_version(a1) >= 99 )
    {
      v14 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      *(_DWORD *)v17 = v14 & 7;
      v13 = (v14 & 0x10) != 0;
      *(_BYTE *)(v17 + 8) = (v14 & 0x20) != 0;
      *(_BYTE *)(v17 + 9) = (v14 & 0x40) != 0;
      *(_DWORD *)(v17 + 4) = (int)((unsigned int)&unk_FF0000 & v14) >> 16;
      if ( rf_vfile_get_slot_version(a1) < 163 )
      {
        *(_BYTE *)(v17 + 8) = 0;
        *(_BYTE *)(v17 + 9) = 0;
        if ( v13 )
        {
          rf_binary_stream_read_string_object_versioned(a1, v16, 0, nullptr);
          v2 = (char *)rf_string_object_c_str_or_empty(v16);
          v3 = rf_bitmap_load_with_optional_mipmap_generation(v2, (void *)0xFFFFFFFF, 1);
          v4 = rf_bitmap_material_to_index(v3);
          *(_BYTE *)(v17 + 9) = v4 == 8;
        }
      }
      if ( *(_BYTE *)(v17 + 8) )
      {
        float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
        *(float *)(v17 + 12) = float_versioned;
      }
    }
    else
    {
      rf_binary_stream_read_bool_versioned(a1, unk_6FCCA0, 1);
      rf_binary_stream_read_string_object_versioned(a1, v16, 0, nullptr);
      v1 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      *(_DWORD *)v17 = v1;
      *(_BYTE *)(v17 + 8) = 0;
      *(_DWORD *)(v17 + 4) = 50;
    }
    v8 = *(_DWORD *)v17;
    if ( *(_DWORD *)v17 == 2 )
    {
      rf_binary_stream_read_vector3_versioned(a1, (float *)(v17 + 16), 0, unk_1C8FBDC);
      if ( *(_BYTE *)(v17 + 8) == 1 )
        rf_binary_stream_read_matrix3_vectors_201_versioned((char *)(v17 + 28), 0, (int)unk_1C8FC18);
      if ( rf_vfile_get_slot_version(a1) < 163 )
        rf_binary_stream_read_float_versioned(a1, 0, 0.0);
      v6 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
      *(float *)(v17 + 64) = v6;
      rf_vector3_zero_return_destination((float *)(v17 + 68));
    }
    else if ( v8 == 3 )
    {
      rf_binary_stream_read_vector3_versioned(a1, v20, 0, unk_1C8FBDC);
      rf_binary_stream_read_vector3_versioned(a1, v20, 0, unk_1C8FBDC);
      rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    }
    else if ( v8 == 4 )
    {
      rf_binary_stream_read_vector3_versioned(a1, (float *)(v17 + 16), 0, unk_1C8FBDC);
      rf_binary_stream_read_matrix3_vectors_201_versioned((char *)(v17 + 28), 0, (int)unk_1C8FC18);
      rf_binary_stream_read_vector3_versioned(a1, (float *)(v17 + 68), 0, unk_1C8FBDC);
      *(float *)(v17 + 64) = 0.0;
      if ( rf_vfile_get_slot_version(a1) < 163 )
        rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    }
    if ( rf_vfile_get_slot_version(a1) < 99 )
    {
      v7 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      *(_DWORD *)(v17 + 4) = v7;
    }
    rf_integer_clamp_in_place((_DWORD *)(v17 + 4), 0, 100);
    if ( rf_vfile_get_slot_version(a1) < 163 )
    {
      rf_binary_stream_read_int32_versioned(a1, 132, 64);
      rf_binary_stream_read_packed4bytes_versioned(a1, &v10, 133, &dword_1C8FC4C);
    }
    if ( *(_DWORD *)v17 == 3 )
      operator delete((void *)v17);
    else
      rf_pointer_array_append_dword(rf_geomod_georegion_registry, v17);
  }
  LOBYTE(v22) = 1;
  rf_string_destroy_buffer(v16);
  LOBYTE(v22) = 0;
  rf_string_destroy_buffer(v19);
  v22 = -1;
  rf_string_destroy_buffer(v18);
}

