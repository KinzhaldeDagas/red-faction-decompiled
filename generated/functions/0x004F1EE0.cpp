// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F1EE0 rf_application_apply_command_line_startup_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Calls command-line initialization with TWO native zero DWORDs (existing callee type may hide one). Dedicated option88E4D0 nonzero normalizes BYTE704E83 to1 else0. Port option88E568 nonzero reads signed argument int and stores LOW16 into662868 WITHOUT range check, unlike later ForcePort registry path. All repeated4A6760 probes are constant AL0 in this binary: mod string704EAC becomes empty; resolution candidates640x480/800x600/1024x768/1280x1024 never selected here and selector88E44C becomes-1;88E3FC=201; bytes88E3F2,88E445,88E3F0,88E3F1,88E444,88E3F3,88E446,1DAEDAE all0. Their apparent option-object ECX addresses do not make the stub parse options. Working boolean
// option88E580 EXACT1 constructs parser; if raw CString pointer88E590 has positive strlen, parses THREE ordered signed-int selector/optional comma/number components with optional semicolons between. Each number stored F32 to87C698/69C/6A0, negated ONLY if selector==0 (any nonzero selector, even negative, preserves parsed sign); sets byte87C314=1. Option88E4FC EXACT1 similarly parses raw88E50C into87C650/654/658 and sets87C315. Empty text skips writes/enable byte but still destroys parser. Separator-probe failures ignored; no EOF, selector0/1, range/finite or vector normalization validation. Existing parser syntax controls malformed numeric failures. Timedemo option88E51C EXACT1 calls5157C0(argument pointer88E52C), then independently framerate option88E53C EXACT1 calls515930(pointer88E54C), so both can execute in order. Normal/SEH destroy temporary parsers. Returned AL is incidental final
// probe/delegate value; caller does not use it.
char rf_application_apply_command_line_startup_state()
{
  char *v0; // eax
  char result; // al
  int v2; // [esp+24h] [ebp-240h]
  int v3; // [esp+24h] [ebp-240h]
  int v4; // [esp+24h] [ebp-240h]
  void *v5[69]; // [esp+28h] [ebp-23Ch] BYREF
  int signed_decimal_or_hex_integer; // [esp+13Ch] [ebp-128h]
  void *self[69]; // [esp+140h] [ebp-124h] BYREF
  int v8; // [esp+260h] [ebp-4h]

  rf_command_line_initialize_from_process_string(0);
  byte_704E83 = rf_command_line_bool_option_is_enabled(byte_88E4D0) != 0;
  if ( rf_command_line_bool_option_is_enabled(byte_88E568) )
    word_662868 = rf_command_line_option_argument_as_int((const char **)byte_88E568);
  if ( constant_return_false_al_4A6760() )
  {
    v0 = (char *)rf_vector3_default_construct_noop(&unk_88E554);
    rf_string_assign_from_cstr(dword_704EAC, v0);
  }
  else
  {
    rf_string_assign_from_cstr(dword_704EAC, (char *)&byte_63D3BF);
  }
  if ( constant_return_false_al_4A6760() )
  {
    unk_88E44C = 1;
    *(_DWORD *)byte_88E40C = 640;
    *(_DWORD *)byte_88E418 = 480;
  }
  else if ( constant_return_false_al_4A6760() )
  {
    unk_88E44C = 1;
    *(_DWORD *)byte_88E40C = 800;
    *(_DWORD *)byte_88E418 = 600;
  }
  else if ( constant_return_false_al_4A6760() )
  {
    unk_88E44C = 1;
    *(_DWORD *)byte_88E40C = 1024;
    *(_DWORD *)byte_88E418 = 768;
  }
  else if ( constant_return_false_al_4A6760() )
  {
    unk_88E44C = 1;
    *(_DWORD *)byte_88E40C = 1280;
    *(_DWORD *)byte_88E418 = 1024;
  }
  else
  {
    unk_88E44C = -1;
  }
  unk_88E3FC = 201;
  unk_88E3F2 = constant_return_false_al_4A6760() != 0;
  unk_88E445 = constant_return_false_al_4A6760() != 0;
  unk_88E3F0 = constant_return_false_al_4A6760() != 0;
  unk_88E3F1 = constant_return_false_al_4A6760() != 0;
  unk_88E444 = constant_return_false_al_4A6760() != 0;
  unk_88E3F3 = constant_return_false_al_4A6760() != 0;
  unk_88E446 = constant_return_false_al_4A6760() == 1;
  unk_1DAEDAE = constant_return_false_al_4A6760() == 1;
  if ( rf_command_line_bool_option_is_enabled(byte_88E580) == 1 )
  {
    rf_memory_text_parser_construct_empty(self);
    v8 = 0;
    if ( strlen(unk_88E590) )
    {
      rf_text_parser_load_owned_cstring(self, unk_88E590);
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(self);
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, ",");
      flt_87C698 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
      if ( !signed_decimal_or_hex_integer )
        flt_87C698 = flt_87C698 * -1.0;
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, ";");
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(self);
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, ",");
      unk_87C69C = rf_text_parser_read_number_with_optional_decimal_fraction(self);
      if ( !signed_decimal_or_hex_integer )
        unk_87C69C = unk_87C69C * -1.0;
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, ";");
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(self);
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, ",");
      unk_87C6A0 = rf_text_parser_read_number_with_optional_decimal_fraction(self);
      if ( !signed_decimal_or_hex_integer )
        unk_87C6A0 = unk_87C6A0 * -1.0;
      unk_87C314 = 1;
    }
    v8 = -1;
    rf_memory_text_parser_destroy_buffer_adapter(self);
  }
  if ( rf_command_line_bool_option_is_enabled(byte_88E4FC) == 1 )
  {
    rf_memory_text_parser_construct_empty(v5);
    v8 = 1;
    if ( strlen(unk_88E50C) )
    {
      rf_text_parser_load_owned_cstring(v5, unk_88E50C);
      v2 = rf_text_parser_read_signed_decimal_or_hex_integer(v5);
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)v5, ",");
      flt_87C650 = rf_text_parser_read_number_with_optional_decimal_fraction(v5);
      if ( !v2 )
        flt_87C650 = flt_87C650 * -1.0;
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)v5, ";");
      v3 = rf_text_parser_read_signed_decimal_or_hex_integer(v5);
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)v5, ",");
      unk_87C654 = rf_text_parser_read_number_with_optional_decimal_fraction(v5);
      if ( !v3 )
        unk_87C654 = unk_87C654 * -1.0;
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)v5, ";");
      v4 = rf_text_parser_read_signed_decimal_or_hex_integer(v5);
      rf_text_parser_try_consume_case_insensitive_prefix((const char **)v5, ",");
      unk_87C658 = rf_text_parser_read_number_with_optional_decimal_fraction(v5);
      if ( !v4 )
        unk_87C658 = unk_87C658 * -1.0;
      byte_87C315[0] = 1;
    }
    v8 = -1;
    rf_memory_text_parser_destroy_buffer_adapter(v5);
  }
  if ( rf_command_line_bool_option_is_enabled(byte_88E51C) == 1 )
    rf_timedemo_command_line_state_step(unk_88E52C);
  result = rf_command_line_bool_option_is_enabled(byte_88E53C);
  if ( result == 1 )
    return rf_framerate_test_command_line_state_step(unk_88E54C);
  return result;
}

