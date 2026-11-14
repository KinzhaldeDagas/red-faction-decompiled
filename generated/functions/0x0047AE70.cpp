// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047AE70 rf_rfl_light_record_parse_pre67
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Thiscall light record plus stream, RET4; caller light_record_parse dispatches here only for stream version<67. Reads idDWORD0, discarded string, position12, name RFString4,
// discarded string and bool(default1). Reads mode-name string: exact case-insensitive 'Off' sets DWORD60=1, every other value=2. Consumes another discarded string, sets
// shapeDWORD64=1(point). Reads packed color and converts first three unsigned bytes /double255.0 into binary32 RGB68/72/76; alpha discarded.
// Reads FLOAT108, FLOAT80, then another float stored binary32 locally before subtracting stored80 into FLOAT84. Reads enabled BYTE132(default1,min0) and BYTE134(default0,min51).
// Calls runtime_initialize unconditionally; does not follow modern parser's renderer-world-lighting gate or a3 defer flag. Runtime delegate may read other scalar/flag/handle fields
// untouched here; constructor initializes only string and no-op pose, so this body is not a full record reset. No finite/radius clamp, local read-status validation or registry
// insertion. Two temporary RFStrings destroyed on normal/unwind exit.
void __thiscall rf_rfl_light_record_parse_pre67(float *this, _DWORD *a2)
{
  char v3[4]; // [esp+18h] [ebp-28h] BYREF
  int v4; // [esp+1Ch] [ebp-24h] BYREF
  int v5[2]; // [esp+20h] [ebp-20h] BYREF
  int v6[2]; // [esp+28h] [ebp-18h] BYREF
  float float_versioned; // [esp+30h] [ebp-10h]
  int v8; // [esp+3Ch] [ebp-4h]

  rf_string_construct_empty(v5);
  v8 = 0;
  rf_rgba8_default_construct_noop(&v4);
  *(_DWORD *)this = rf_binary_stream_read_int32_versioned(a2, 0, 0);
  rf_binary_stream_read_string_object_versioned(a2, v5, 0, nullptr);
  rf_binary_stream_read_vector3_versioned(a2, this + 3, 0, unk_1C8FBDC);
  rf_binary_stream_read_string_object_versioned(a2, (_DWORD *)this + 1, 0, nullptr);
  rf_binary_stream_read_string_object_versioned(a2, v5, 0, nullptr);
  rf_binary_stream_read_bool_versioned(a2, 0, 1);
  rf_string_construct_empty(v6);
  LOBYTE(v8) = 1;
  rf_binary_stream_read_string_object_versioned(a2, v6, 0, nullptr);
  if ( rf_string_equals_case_insensitive((int)v6, (char *)off_6387E4) )
    *((_DWORD *)this + 15) = 1;
  else
    *((_DWORD *)this + 15) = 2;
  rf_binary_stream_read_string_object_versioned(a2, v5, 0, nullptr);
  *((_DWORD *)this + 16) = 1;
  v4 = *rf_binary_stream_read_packed4bytes_versioned(a2, v3, 0, &dword_1C8FC4C);
  *(this + 17) = (double)(unsigned __int8)v4 / 255.0;
  *(this + 18) = (double)BYTE1(v4) / 255.0;
  *(this + 19) = (double)BYTE2(v4) / 255.0;
  *(this + 27) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
  *(this + 20) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
  float_versioned = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
  *(this + 21) = float_versioned - *(this + 20);
  *((_BYTE *)this + 132) = rf_binary_stream_read_bool_versioned(a2, 0, 1);
  *((_BYTE *)this + 134) = rf_binary_stream_read_bool_versioned(a2, 51, 0);
  rf_rfl_light_runtime_initialize((int)this);
  LOBYTE(v8) = 0;
  rf_string_destroy_buffer(v6);
  v8 = -1;
  rf_string_destroy_buffer(v5);
}

