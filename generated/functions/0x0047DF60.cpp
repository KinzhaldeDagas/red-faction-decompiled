// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047DF60 rf_rfl_prelude_metadata_read
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Cdecl stream. Calls read_section_header into local id/size, stores AL but NEVER tests it, and never validates id/size; continues even at EOF/terminator. Discards int32 and
// RFString; reads RFStrings6FC324 and6FC32C with fallback 'none', discards bool(default1), stores another bool(default1) in BYTE6FCCB8. That byte selects alternate pose-array path in
// section0400 loader.
// Exactly FOUR iterations: reads int32; nonzero consumes/discards float, then consumes vector3 and matrix3 into scratch pose. Matrix helper native ECX is stream, with
// stack(destination,min0,defaultmatrix); file vector order is matrix+24,+0,+12. Does not retain poses, apply orientation, validate consumed section length or seek to section end.
// Temporary RFString destroyed on normal/unwind paths.
void __cdecl rf_rfl_prelude_metadata_read(_DWORD *a1)
{
  float v1[3]; // [esp+8h] [ebp-58h] BYREF
  char v2[36]; // [esp+14h] [ebp-4Ch] BYREF
  int v4; // [esp+3Ch] [ebp-24h] BYREF
  int v5; // [esp+40h] [ebp-20h] BYREF
  int v6[2]; // [esp+44h] [ebp-1Ch] BYREF
  char v7; // [esp+4Fh] [ebp-11h]
  int i; // [esp+50h] [ebp-10h]
  int v9; // [esp+5Ch] [ebp-4h]

  v7 = rf_rfl_read_section_header(a1, &v4, &v5);
  rf_string_construct_empty(v6);
  v9 = 0;
  rf_binary_stream_read_int32_versioned(a1, 0, 0);
  rf_binary_stream_read_string_object_versioned(a1, v6, 0, nullptr);
  rf_binary_stream_read_string_object_versioned(a1, unk_6FC324, 0, "none");
  rf_binary_stream_read_string_object_versioned(a1, unk_6FC32C, 0, "none");
  rf_binary_stream_read_bool_versioned(a1, 0, 1);
  unk_6FCCB8 = rf_binary_stream_read_bool_versioned(a1, 0, 1);
  for ( i = 0; i < 4; ++i )
  {
    if ( rf_binary_stream_read_int32_versioned(a1, 0, 0) )
      rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    rf_vector3_default_construct_noop(v1);
    rf_matrix3_construct(v2);
    rf_binary_stream_read_vector3_versioned(a1, v1, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(v2, 0, (int)unk_1C8FC18);
  }
  v9 = -1;
  rf_string_destroy_buffer(v6);
}

