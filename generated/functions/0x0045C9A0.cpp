// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045C9A0 rf_multiplayer_level_header_read_display_name
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Corrected native cdecl ABI: OWNED by-value8-byte filename RFString represented by two DWORD
// slots(filename_extent,filename_data),then pointer to existing output RFString. Former char first slot/std::exception* output were false inferred types;native uses &arg0 as RFString
// and arg8 as output. Return AL0 for open<0,magic!=D4BADA55,or signed version outside40..200;output unchanged on these paths. On accepted header:set stream version;discard uint32
// threshold114,two int32 threshold0,two int32 threshold160;read u16 string into256-byte local with threshold170/default "<untitled>". Case-sensitive strstr("XSTR(") ANYWHERE:
// advance5,overwrite LAST byte of WHOLE title withNUL,atoi(tokenTail);negative ID ->"?",nonnegative ->localization pointer88D438[id] with NO upper bound. Otherwise assign raw title.
// Case-insensitive resulting title "Blasted Canyon" gets localized88DFD0. ReturnAL1 without further read-result checks. All normal exits close/destruct local VFile then DESTROY owned
// filename argument;output is assigned,not constructed or destroyed. Caller appends record even onAL0. No full level/chunk validation or output-pointer guard.
char __cdecl rf_multiplayer_level_header_read_display_name(
        unsigned int filename_extent,
        char *filename_data,
        void *out_display_name)
{
  char *v3; // eax
  const char *v5; // eax
  void *v6; // [esp-4h] [ebp-260h]
  char *Source; // [esp+8h] [ebp-254h]
  int v8; // [esp+24h] [ebp-238h]
  int int32_versioned; // [esp+2Ch] [ebp-230h]
  int self[70]; // [esp+30h] [ebp-22Ch] BYREF
  char Str[256]; // [esp+148h] [ebp-114h] BYREF
  char *String; // [esp+24Ch] [ebp-10h]
  int v13; // [esp+258h] [ebp-4h]

  v13 = 0;
  rf_vfile_construct_unopened(self);
  LOBYTE(v13) = 1;
  v6 = (void *)dword_88E430;
  v3 = (char *)rf_string_object_c_str_or_empty(&filename_extent);
  if ( rf_vfile_open_with_extension_cache_control_paths(self, v3, 1, v6) >= 0
    && rf_binary_stream_read_int32_versioned(self, 0, 0) == -725951915
    && (int32_versioned = rf_binary_stream_read_int32_versioned(self, 0, 0), int32_versioned >= 40)
    && int32_versioned <= 200 )
  {
    rf_vfile_set_open_slot_version(self, int32_versioned);
    rf_binary_stream_read_uint32_versioned(self, 114, 0);
    rf_binary_stream_read_int32_versioned(self, 0, 0);
    rf_binary_stream_read_int32_versioned(self, 0, 0);
    rf_binary_stream_read_int32_versioned(self, 160, 0);
    rf_binary_stream_read_int32_versioned(self, 160, 0);
    rf_binary_stream_read_u16_string_to_buffer(self, Str, 256, 170, "<untitled>");
    String = rf_cstring_find_first_substring(Str, "XSTR(");
    if ( String )
    {
      String += 5;
      *((_BYTE *)&self[69] + strlen(Str) + 3) = 0;
      v8 = atoi(String);
      if ( v8 >= 0 )
        Source = (char *)unk_88D438[v8];
      else
        Source = "?";
      rf_string_assign_from_cstr(out_display_name, Source);
    }
    else
    {
      rf_string_assign_from_cstr(out_display_name, Str);
    }
    v5 = rf_string_object_c_str_or_empty(out_display_name);
    if ( !_stricmp("Blasted Canyon", v5) )
      rf_string_assign_from_cstr(out_display_name, unk_88DFD0);
    LOBYTE(v13) = 0;
    rf_vfile_destruct_close_if_open(self);
    v13 = -1;
    rf_string_destroy_buffer(&filename_extent);
    return 1;
  }
  else
  {
    LOBYTE(v13) = 0;
    rf_vfile_destruct_close_if_open(self);
    v13 = -1;
    rf_string_destroy_buffer(&filename_extent);
    return 0;
  }
}

