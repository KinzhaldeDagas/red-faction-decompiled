// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE380 rf_particle_emitter_definition_parse
// UNREALRED VERIFIED [burn-motion-20261029]: Optional $swirliness integer is masked with0xF and packed into particle flags bits24..27. Getter4CBA30 converts that nibble to a cone minimum-dot. This is distinct from push-region wind in bits28..31.
// UNREALRED VERIFIED [combat-particle-range-20261104]: Source range endpoints are direct independent579C20 reads into velocity+0x20/+0x24, spawn delay+0x28/+0x2C, life+0x38/+0x3C and particle radius+0x40/+0x44. No post-parse maximum-to-minimum clamp or range sorting follows.506AF0 reuses this same parser for inline definition+0x38. Preserve raw endpoint order through both Unreal parser routes and sampler; runtime render/lifetime bounds are distinct adapters.
void __cdecl rf_particle_emitter_definition_parse(_DWORD *parser, int a2)
{
  char *v2; // eax
  char *last_dot_or_empty_literal; // eax
  char *v4; // eax
  char *v5; // eax
  int v6[2]; // [esp+4h] [ebp-24h] BYREF
  int destination[2]; // [esp+Ch] [ebp-1Ch] BYREF
  char v8; // [esp+16h] [ebp-12h]
  char boolean_word_prefix; // [esp+17h] [ebp-11h]
  int signed_decimal_or_hex_integer; // [esp+18h] [ebp-10h] BYREF
  int v11; // [esp+24h] [ebp-4h]

  rf_string_construct_empty(destination);
  v11 = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$pos:");
  rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)(a2 + 4));
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$dir:");
  rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)(a2 + 16));
  rf_vector_normalize_reciprocal_sqrt((float *)(a2 + 16));
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$dir_rand:");
  *(float *)(a2 + 28) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$min_vel:");
  *(float *)(a2 + 32) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$max_vel:");
  *(float *)(a2 + 36) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$spawn_radius:");
  *(float *)(a2 + 48) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$min_spawn_delay:") )
  {
    *(float *)(a2 + 40) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$max_spawn_delay:");
    *(float *)(a2 + 44) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  else
  {
    *(float *)(a2 + 44) = 0.0;
    *(float *)(a2 + 40) = 0.0;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$emitter_flags:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  *(_WORD *)(a2 + 52) = 0;
  if ( rf_string_find_case_insensitive(destination, "immediate", 0) >= 0 )
    *(_WORD *)(a2 + 52) |= 2u;
  if ( rf_string_find_case_insensitive(destination, "continuous", 0) >= 0 )
    *(_WORD *)(a2 + 52) |= 4u;
  if ( rf_string_find_case_insensitive(destination, "dirdepend", 0) >= 0 )
    *(_WORD *)(a2 + 52) |= 8u;
  if ( rf_string_find_case_insensitive(destination, "dont_move_with_parent", 0) >= 0 )
    *(_WORD *)(a2 + 52) |= 0x40u;
  if ( rf_string_find_case_insensitive(destination, "accel_with_parent", 0) >= 0 )
    *(_WORD *)(a2 + 52) |= 0x80u;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$initially_on:");
  boolean_word_prefix = rf_text_parser_read_boolean_word_prefix((const char **)parser);
  if ( boolean_word_prefix == 1 )
    *(_WORD *)(a2 + 52) |= 0x10u;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$alternate_states:");
  v8 = rf_text_parser_read_boolean_word_prefix((const char **)parser);
  if ( v8 == 1 )
  {
    *(_WORD *)(a2 + 52) |= 0x20u;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$on_time:");
    *(float *)(a2 + 84) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$on_time_variance:");
    *(float *)(a2 + 88) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$off_time:");
    *(float *)(a2 + 92) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$off_time_variance:");
    *(float *)(a2 + 96) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  else
  {
    *(float *)(a2 + 84) = 1.0;
    *(float *)(a2 + 88) = 0.0;
    *(float *)(a2 + 92) = 1.0;
    *(float *)(a2 + 96) = 0.0;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$min_life_secs:");
  *(float *)(a2 + 56) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$max_life_secs:");
  *(float *)(a2 + 60) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$min_pradius:");
  *(float *)(a2 + 64) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$max_pradius:");
  *(float *)(a2 + 68) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$growth_rate:");
  *(float *)(a2 + 72) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$acceleration:");
  *(float *)(a2 + 76) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$gravity_scale:");
  *(float *)(a2 + 80) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$bitmap:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  v2 = (char *)rf_string_object_c_str_or_empty(destination);
  last_dot_or_empty_literal = rf_path_find_last_dot_or_empty_literal(v2);
  rf_string_construct_from_cstr(v6, last_dot_or_empty_literal);
  LOBYTE(v11) = 1;
  if ( rf_string_equals_case_insensitive((int)v6, ".vbm") )
  {
    v4 = (char *)rf_string_object_c_str_or_empty(destination);
    *(_DWORD *)(a2 + 100) = rf_bitmap_vbm_sequence_load(v4, (_DWORD *)(a2 + 104), &signed_decimal_or_hex_integer);
  }
  else
  {
    v5 = (char *)rf_string_object_c_str_or_empty(destination);
    *(_DWORD *)(a2 + 100) = rf_bitmap_load_with_optional_mipmap_generation(v5, (void *)0xFFFFFFFF, 1);
    *(_DWORD *)(a2 + 104) = 1;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$particle color:");
  rf_text_parser_read_braced_rgba_bytes((int)parser, (_BYTE *)(a2 + 108));
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$particle color dest:") )
    rf_text_parser_read_braced_rgba_bytes((int)parser, (_BYTE *)(a2 + 112));
  else
    *(_DWORD *)(a2 + 112) = *(_DWORD *)(a2 + 108);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$particle flags:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  *(_DWORD *)(a2 + 116) = 0;
  *(_DWORD *)(a2 + 120) = 0;
  if ( rf_string_find_case_insensitive(destination, "glow", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 2u;
  if ( rf_string_find_case_insensitive(destination, "clr_change", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 4u;
  if ( rf_string_find_case_insensitive(destination, "gravity", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 8u;
  if ( rf_string_find_case_insensitive(destination, "collide", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x10u;
  if ( rf_string_find_case_insensitive(destination, "collide_liquid", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x400u;
  if ( rf_string_find_case_insensitive(destination, "collide_and_die", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x800u;
  if ( rf_string_find_case_insensitive(destination, "wind", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0xF0000000;
  if ( rf_string_find_case_insensitive(destination, "accelerate", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x40u;
  if ( rf_string_find_case_insensitive(destination, "loop", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x100u;
  if ( rf_string_find_case_insensitive(destination, "explode", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x80u;
  if ( rf_string_find_case_insensitive(destination, "random_orient", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x200u;
  if ( rf_string_find_case_insensitive(destination, "vel_stretch", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x4000u;
  if ( rf_string_find_case_insensitive(destination, "no_z_check", 0) >= 0 )
    *(_DWORD *)(a2 + 116) |= 0x2000u;
  if ( rf_string_find_case_insensitive(destination, "damages", 0) >= 0 )
    *(_DWORD *)(a2 + 120) |= 1u;
  if ( rf_string_find_case_insensitive(destination, "hold_last_frame", 0) >= 0 )
    *(_DWORD *)(a2 + 120) |= 4u;
  if ( rf_string_find_case_insensitive(destination, "fire_damage", 0) >= 0 )
    *(_DWORD *)(a2 + 120) |= 8u;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$bounciness:") )
  {
    signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    *(_DWORD *)(a2 + 116) |= (signed_decimal_or_hex_integer & 0xF) << 16;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$stickiness:") )
  {
    signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    *(_DWORD *)(a2 + 116) |= (signed_decimal_or_hex_integer & 0xF) << 20;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$swirliness:") )
  {
    signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    *(_DWORD *)(a2 + 116) |= (signed_decimal_or_hex_integer & 0xF) << 24;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$damage_factor:") )
  {
    signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    *(_DWORD *)(a2 + 120) |= (signed_decimal_or_hex_integer & 0xF) << 12;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$age_pct_to_finish_vbm:") )
    *(float *)(a2 + 124) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  LOBYTE(v11) = 0;
  rf_string_destroy_buffer(v6);
  v11 = -1;
  rf_string_destroy_buffer(destination);
}

