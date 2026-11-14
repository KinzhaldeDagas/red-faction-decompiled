// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00508990 rf_weapon_definition_parse
// UNREALRED VERIFIED [weapon-shell-ejection-20261008] Shell block is distinct from reload clip block: +1188 cached prop=-1; +1192 normalized Base Dir; +1204 Eject Velocity; +1208 model string; +1216 custom contact sound; +1220 Primary Pause Time Before Eject defaults to zero. Clip fields begin +1224. The shell direction must be normalized before applying authored speed.
// UNREALRED VERIFIED [combat-reaction-literal-names-20261111]: Each native weapon row starts by requiring CURRENT case-insensitive prefix $Name: via5797A0, then quoted579FB0. The remaining row is an ordered mandatory/optional cursor program; enumerating all $Name rows from a generic parsed document is not proof of native record acceptance/ordinal mapping. Full raw admission remains a distinct dependency.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Ordered record grammar verified against all133 required/optional prefix occurrences (94 top-level steps). DisplayName, when present, requires XSTR(int,quoted,closing), not plain quote. WeaponType presence requires Icon even if unknown enum. 1stMesh presence requires offsets even empty string. Bitmap byte length>4 gates head/length/tail tokens. +State reads2strings and increments only nonempty file. +Action always reads3strings; empty file does NOT increment but Foley writes index(count-1), overwriting prior action sound (first empty aliases before array). ImpactDelay/AltImpactDelay optional labels appear3times; first2 read numbers, final appearance consumes LABELONLY. Native flags tables663A40[23]/663A9C[11] verified dense; unknown names fatal. 64-record/list/state/action unchecked storage overflow is an unsafe domain, not a native checked rejection. Recover/retain native defaults rather than imposing UI positive/range constraints.
// UNREALRED VERIFIED [combat-native-weapon-layout-20261111]: Qualification of raw grammar/resource boundaries: state/action capacities now independently confirmed by512440 destructor ASM (3/12); +Action firstempty writes+748 thirdstate sound, not out-of-WeaponInfo memory. Damage4BCFF0 table has9names+2NULLslots, so unknown names take CRT invalid-parameter path before any possible-1 return; do not claim all unknown damage names cleanly parse. Resource-independent cursor success alone cannot establish abnormal resolver policy.
void __cdecl rf_weapon_definition_parse(_DWORD *parser, char *destination)
{
  char *v2; // eax
  char *last_dot_or_empty_literal; // eax
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  char *v8; // eax
  const char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  char *v12; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // eax
  int v16; // eax
  char *v17; // eax
  char *v18; // eax
  char *v19; // eax
  char *v20; // eax
  char *v21; // eax
  char *v22; // eax
  char *v23; // eax
  char *v24; // eax
  int v25; // edx
  char *v26; // eax
  char *v27; // eax
  char *v28; // eax
  char *v29; // eax
  char *v30; // eax
  double number_with_optional_decimal_fraction; // st7
  double v32; // st7
  unsigned int v33; // eax
  char *v34; // eax
  int v35; // eax
  char *v36; // eax
  int v37; // eax
  char *v38; // eax
  char *v39; // eax
  char *v40; // eax
  char *v41; // eax
  int v42; // eax
  char *v43; // eax
  int v44; // eax
  char *v45; // eax
  char *v46; // eax
  char *v47; // eax
  char *v48; // eax
  char *v49; // eax
  float v50; // [esp+8h] [ebp-17Ch]
  void *v51; // [esp+Ch] [ebp-178h]
  char **string_pointer_slot; // [esp+14h] [ebp-170h]
  _BYTE v53[8]; // [esp+18h] [ebp-16Ch] BYREF
  float v54; // [esp+20h] [ebp-164h]
  char v55; // [esp+26h] [ebp-15Eh]
  char boolean_word_prefix; // [esp+27h] [ebp-15Dh]
  int v57; // [esp+28h] [ebp-15Ch]
  int v58; // [esp+2Ch] [ebp-158h]
  int v59; // [esp+30h] [ebp-154h]
  int case_insensitive; // [esp+34h] [ebp-150h]
  int v61; // [esp+38h] [ebp-14Ch] BYREF
  int v62; // [esp+3Ch] [ebp-148h] BYREF
  int v63[2]; // [esp+40h] [ebp-144h] BYREF
  int v64[2]; // [esp+48h] [ebp-13Ch] BYREF
  char Destination[260]; // [esp+50h] [ebp-134h] BYREF
  int xstr_id_and_delimited_text; // [esp+158h] [ebp-2Ch]
  int v67; // [esp+15Ch] [ebp-28h]
  char name[8]; // [esp+160h] [ebp-24h] BYREF
  int i; // [esp+168h] [ebp-1Ch]
  int parenthesized_named_flag_mask; // [esp+16Ch] [ebp-18h]
  _DWORD v71[2]; // [esp+170h] [ebp-14h] BYREF
  int v72; // [esp+180h] [ebp-4h]

  rf_string_construct_empty(name);
  v72 = 0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Display Name:") )
  {
    xstr_id_and_delimited_text = rf_text_parser_read_xstr_id_and_delimited_text(parser, Destination, 256, 34, 34);
    if ( xstr_id_and_delimited_text >= 0 )
      string_pointer_slot = (char **)(4 * xstr_id_and_delimited_text + 8967224);
    else
      string_pointer_slot = (char **)rf_localization_get_string_pointer_slot(Destination, xstr_id_and_delimited_text);
    rf_string_assign_from_cstr((_DWORD *)destination + 2, *string_pointer_slot);
  }
  else
  {
    rf_string_assign_from_object((_DWORD *)destination + 2, (int)destination);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$V3D Filename:");
  rf_text_parser_read_delimited_rfstring(parser, destination + 16, 34, 34);
  if ( (int)rf_string_length_from_cstr((const char **)destination + 4) <= 4 )
  {
    *((_DWORD *)destination + 6) = 0;
  }
  else
  {
    v2 = (char *)rf_string_object_c_str_or_empty(destination + 16);
    last_dot_or_empty_literal = rf_path_find_last_dot_or_empty_literal(v2);
    rf_string_construct_from_cstr(v64, last_dot_or_empty_literal);
    LOBYTE(v72) = 1;
    if ( rf_string_equals_case_insensitive((int)v64, ".vfx") )
      *((_DWORD *)destination + 6) = 3;
    else
      *((_DWORD *)destination + 6) = 1;
    LOBYTE(v72) = 0;
    rf_string_destroy_buffer(v64);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Flags:");
  parenthesized_named_flag_mask = rf_text_parser_read_parenthesized_named_flag_mask(
                                    (_BYTE **)parser,
                                    (int)rf_weapon_flags_token_table,
                                    23);
  *((_DWORD *)destination + 153) |= parenthesized_named_flag_mask;
  *((_DWORD *)destination + 154) = 0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Flags2:") )
    *((_DWORD *)destination + 154) = rf_text_parser_read_parenthesized_named_flag_mask(
                                       (_BYTE **)parser,
                                       (int)rf_weapon_flags2_token_table,
                                       11);
  if ( (parenthesized_named_flag_mask & 0x80) != 0 )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Cycle Position:");
    *((_DWORD *)destination + 332) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Pref Position:");
    *((_DWORD *)destination + 333) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Fine Aim Region Size:");
    *((float *)destination + 334) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Fine Aim Region Size SS:");
    *((float *)destination + 335) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  else
  {
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Fine Aim Region Size:") )
      *((float *)destination + 334) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    else
      *((float *)destination + 334) = 0.64999998;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Fine Aim Region Size SS:") )
      *((float *)destination + 335) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    else
      *((float *)destination + 335) = 0.64999998;
    *((_DWORD *)destination + 332) = -1;
    *((_DWORD *)destination + 333) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Weapon Type:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v4 = rf_string_object_c_str_or_empty(name);
    if ( !_stricmp(v4, "close combat") )
    {
      *((_DWORD *)destination + 328) = 0;
    }
    else
    {
      v5 = rf_string_object_c_str_or_empty(name);
      if ( !_stricmp(v5, "semi-auto") )
      {
        *((_DWORD *)destination + 328) = 1;
      }
      else
      {
        v6 = rf_string_object_c_str_or_empty(name);
        if ( !_stricmp(v6, "heavy") )
        {
          *((_DWORD *)destination + 328) = 2;
        }
        else
        {
          v7 = rf_string_object_c_str_or_empty(name);
          if ( !_stricmp(v7, "explosive") )
            *((_DWORD *)destination + 328) = 3;
          else
            *((_DWORD *)destination + 328) = -1;
        }
      }
    }
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Weapon Icon:");
    rf_text_parser_read_delimited_rfstring(parser, destination + 1316, 34, 34);
  }
  else
  {
    *((_DWORD *)destination + 328) = -1;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Damage Type:");
  rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
  v8 = (char *)rf_string_object_c_str_or_empty(name);
  *((_DWORD *)destination + 331) = sub_4BCFF0(v8);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$3rd Person V3D:") )
    rf_text_parser_read_delimited_rfstring(parser, destination + 40, 34, 34);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$3rd Person Muzzle Flash Glare:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v9 = rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 15) = rf_glare_definition_find_name_case_sensitive(v9);
  }
  else
  {
    *((_DWORD *)destination + 15) = -1;
  }
  *((_DWORD *)destination + 25) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$1st Person Mesh:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, destination + 64, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$1st person FOV:") )
      *((float *)destination + 29) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    else
      *((float *)destination + 29) = flt_66157C;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Splitscreen FOV:") )
      *((float *)destination + 30) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    else
      *((float *)destination + 30) = flt_66157C;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$1st Person offset:");
    rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)destination + 19);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$1st Person offset SS:");
    rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)destination + 22);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$1st person muzzle flash bitmap:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v10 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 25) = rf_bitmap_load_with_optional_mipmap_generation(v10, (void *)0xFFFFFFFF, 1);
    rf_renderer_bind_texture_for_level_warmup(*((_DWORD *)destination + 25));
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$1st person muzzle flash radius:");
    *((float *)destination + 26) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$1st person alt muzzle flash bitmap:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v11 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 27) = rf_bitmap_load_with_optional_mipmap_generation(v11, (void *)0xFFFFFFFF, 1);
    rf_renderer_bind_texture_for_level_warmup(*((_DWORD *)destination + 27));
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$1st person alt muzzle flash radius:");
    *((float *)destination + 28) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  *((_DWORD *)destination + 316) = 0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Silencer V3D:") )
    rf_text_parser_read_delimited_rfstring(parser, destination + 1256, 34, 34);
  *((_DWORD *)destination + 320) = 0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Spark VFX:") )
    rf_text_parser_read_delimited_rfstring(parser, destination + 1272, 34, 34);
  *((_DWORD *)destination + 166) = 0;
  *((_DWORD *)destination + 167) = 0;
  rf_string_construct_empty(v71);
  LOBYTE(v72) = 2;
  while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+State:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, v71, 34, 34);
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
    {
      rf_string_assign_from_object(&destination[28 * *((_DWORD *)destination + 166) + 672], (int)v71);
      rf_string_assign_from_object(&destination[28 * *((_DWORD *)destination + 166) + 680], (int)name);
      *(_DWORD *)&destination[28 * (*((_DWORD *)destination + 166))++ + 688] = 0;
    }
  }
  while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Action:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, v71, 34, 34);
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
    {
      rf_string_assign_from_object(&destination[28 * *((_DWORD *)destination + 167) + 756], (int)v71);
      rf_string_assign_from_object(&destination[28 * *((_DWORD *)destination + 167) + 764], (int)name);
      *(_DWORD *)&destination[28 * (*((_DWORD *)destination + 167))++ + 772] = 0;
    }
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v12 = (char *)rf_string_object_c_str_or_empty(name);
    *(_DWORD *)&destination[28 * *((_DWORD *)destination + 167) + 748] = rf_foley_definition_find_name(v12);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Bitmap Filename:");
  rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
  if ( (int)rf_string_length_from_cstr((const char **)name) <= 4 )
  {
    *((_DWORD *)destination + 37) = -1;
  }
  else
  {
    v13 = (char *)rf_string_object_c_str_or_empty(name);
    v14 = rf_path_find_last_dot_or_empty_literal(v13);
    rf_string_construct_from_cstr(v63, v14);
    LOBYTE(v72) = 3;
    if ( rf_string_equals_case_insensitive((int)v63, ".vbm") )
    {
      v15 = (char *)rf_string_object_c_str_or_empty(name);
      v16 = rf_bitmap_vbm_sequence_load(v15, &v61, &v62);
    }
    else
    {
      v17 = (char *)rf_string_object_c_str_or_empty(name);
      v16 = rf_bitmap_load_with_optional_mipmap_generation(v17, (void *)0xFFFFFFFF, 1);
    }
    *((_DWORD *)destination + 37) = v16;
    rf_renderer_bind_texture_for_level_warmup(*((_DWORD *)destination + 37));
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Head Radius:");
    *((float *)destination + 39) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Length:") )
    {
      *((_DWORD *)destination + 153) |= 0x4000000u;
      *((float *)destination + 41) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Tail Radius:");
      *((float *)destination + 40) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    }
    LOBYTE(v72) = 2;
    rf_string_destroy_buffer(v63);
  }
  *((_DWORD *)destination + 145) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$HUD Icon Filename:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    if ( !rf_string_is_empty((int *)name) )
    {
      v18 = (char *)rf_string_object_c_str_or_empty(name);
      *((_DWORD *)destination + 145) = rf_hud_load_frame_zero_bitmap(v18);
    }
  }
  *((_DWORD *)destination + 146) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$HUD Reticle Filename:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    if ( !rf_string_is_empty((int *)name) )
    {
      v19 = (char *)rf_string_object_c_str_or_empty(name);
      *((_DWORD *)destination + 146) = rf_hud_load_frame_zero_bitmap(v19);
    }
  }
  *((_DWORD *)destination + 147) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$HUD Zoomed Reticle Filename:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    if ( !rf_string_is_empty((int *)name) )
    {
      v20 = (char *)rf_string_object_c_str_or_empty(name);
      *((_DWORD *)destination + 147) = rf_hud_load_frame_zero_bitmap(v20);
    }
  }
  *((_DWORD *)destination + 148) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$HUD Locked Reticle Filename:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    if ( !rf_string_is_empty((int *)name) )
    {
      v21 = (char *)rf_string_object_c_str_or_empty(name);
      *((_DWORD *)destination + 148) = rf_hud_load_frame_zero_bitmap(v21);
    }
  }
  *((_DWORD *)destination + 327) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$PS2 Selection Icon Filemame:") )
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Collision Radius:");
  *((float *)destination + 43) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Max Ammo:");
  *((_DWORD *)destination + 150) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
  *((_DWORD *)destination + 151) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Ammo Type:");
  rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
  v22 = (char *)rf_string_object_c_str_or_empty(name);
  *((_DWORD *)destination + 9) = sub_507CE0(v22);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$AI Attack Range:");
  *((float *)destination + 323) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  *((float *)destination + 324) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Clip Size:") )
  {
    *((_DWORD *)destination + 32) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    *((_DWORD *)destination + 33) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
  }
  else
  {
    *((_DWORD *)destination + 32) = 0;
    *((_DWORD *)destination + 33) = 0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Clip Reload Time:") )
    *((float *)destination + 35) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 35) = 2.0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Clip Drain Time:") )
    *((float *)destination + 36) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 36) = 1.0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Mass:");
  *((float *)destination + 47) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Velocity:");
  *((float *)destination + 50) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Velocity Multi:") )
    *((float *)destination + 49) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 49) = *((float *)destination + 50);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Fire Wait:");
  *((float *)destination + 52) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Alt Fire Wait:") )
    *((float *)destination + 53) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 53) = *((float *)destination + 52);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Num Projectiles:") )
    *((_DWORD *)destination + 31) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
  else
    *((_DWORD *)destination + 31) = 1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Spread Degrees:") )
    *((float *)destination + 54) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 54) = 0.0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Spread Degrees Multi:") )
    *((float *)destination + 55) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 55) = *((float *)destination + 54);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$AI Spread Degrees:") )
  {
    *((float *)destination + 60) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 61) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  else
  {
    *((float *)destination + 60) = 0.0;
    *((float *)destination + 61) = 0.0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Alt Spread Degrees:") )
    *((float *)destination + 57) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 57) = 0.0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Alt Spread Degrees Multi:") )
    *((float *)destination + 58) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 58) = *((float *)destination + 57);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$AI Alt Spread Degrees:") )
  {
    *((float *)destination + 63) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 64) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  else
  {
    *((float *)destination + 63) = 0.0;
    *((float *)destination + 64) = 0.0;
  }
  *((_DWORD *)destination + 127) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Start Sound:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v23 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 127) = rf_foley_definition_find_name(v23);
  }
  *((float *)destination + 128) = 0.0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Start Delay:") )
    *((float *)destination + 128) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  *((_DWORD *)destination + 129) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Stop Sound:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v24 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 129) = rf_foley_definition_find_name(v24);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Burst Mode:")
    && rf_text_parser_read_boolean_word_prefix((const char **)parser) == 1 )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Burst Count:");
    *((_DWORD *)destination + 273) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Burst Delay:");
    *((float *)destination + 274) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Burst Launch Sound:");
    *((_DWORD *)destination + 275) = rf_gamesound_parse_direct_sound(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Burst Alt Fire:");
    if ( rf_text_parser_read_boolean_word_prefix((const char **)parser) == 1 )
      v25 = *((_DWORD *)destination + 153) | 0x10000000;
    else
      v25 = *((_DWORD *)destination + 153) | 0x8000000;
    *((_DWORD *)destination + 153) = v25;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Damage:");
  *((float *)destination + 66) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Damage Multi:") )
    *((float *)destination + 67) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 67) = *((float *)destination + 66);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Alt Damage:") )
    *((float *)destination + 68) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 68) = *((float *)destination + 66);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Alt Damage Multi:") )
    *((float *)destination + 69) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 69) = *((float *)destination + 67);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$AI Damage Scale:") )
  {
    *((float *)destination + 70) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((float *)destination + 71) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  else
  {
    *((float *)destination + 70) = 1.0;
    *((float *)destination + 71) = 1.0;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Lifetime:");
  *((float *)destination + 45) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Lifetime Multi:") )
    *((float *)destination + 46) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 46) = *((float *)destination + 45);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Homing:");
  if ( rf_text_parser_read_boolean_word_prefix((const char **)parser) == 1 )
  {
    *((_DWORD *)destination + 153) |= (unsigned int)&unk_800000;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Turn Time:");
    *((float *)destination + 76) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+View Cone:");
    *((float *)destination + 77) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Scanning Range:");
    *((float *)destination + 78) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Wakeup Time:") )
      *((float *)destination + 79) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    else
      *((float *)destination + 79) = 0.0;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Launch:");
  rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
  v26 = (char *)rf_string_object_c_str_or_empty(name);
  *((_DWORD *)destination + 88) = rf_foley_definition_find_name(v26);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Alt Launch:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v27 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 89) = rf_foley_definition_find_name(v27);
  }
  else
  {
    *((_DWORD *)destination + 89) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Silent Launch:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v28 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 90) = rf_foley_definition_find_name(v28);
  }
  else
  {
    *((_DWORD *)destination + 90) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Underwater Launch:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v29 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 91) = rf_foley_definition_find_name(v29);
  }
  else
  {
    *((_DWORD *)destination + 91) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Launch Fail:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v30 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 92) = rf_foley_definition_find_name(v30);
  }
  else
  {
    *((_DWORD *)destination + 92) = -1;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Fly Sound:");
  *((_DWORD *)destination + 93) = rf_gamesound_parse_direct_sound(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Zoom Sound:") )
    *((_DWORD *)destination + 149) = rf_gamesound_parse_direct_sound(parser);
  else
    *((_DWORD *)destination + 149) = -1;
  for ( i = 0; i < 2; ++i )
  {
    *(float *)&destination[4 * i + 336] = 0.0;
    *(float *)&destination[4 * i + 344] = 0.0;
  }
  v67 = 0;
  while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Impact Delay:") )
  {
    if ( v67 < 2 )
    {
      number_with_optional_decimal_fraction = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *(float *)&destination[4 * v67++ + 336] = number_with_optional_decimal_fraction;
    }
  }
  v67 = 0;
  while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Alt Impact Delay:") )
  {
    if ( v67 < 2 )
    {
      v32 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *(float *)&destination[4 * v67++ + 344] = v32;
    }
  }
  while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Impact Sound:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    case_insensitive = rf_string_find_case_insensitive((int *)name, "underwater", 0);
    if ( case_insensitive == -1 )
    {
      v58 = rf_material_name_to_index(name);
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v36 = (char *)rf_string_object_c_str_or_empty(name);
      v37 = rf_foley_definition_find_name(v36);
      *(_DWORD *)&destination[4 * v58 + 376] = v37;
    }
    else
    {
      v33 = rf_string_length_from_cstr((const char **)name);
      v51 = rf_string_left_count((char **)name, v53, v33 - 11);
      LOBYTE(v72) = 4;
      rf_string_assign_from_object(name, (int)v51);
      LOBYTE(v72) = 2;
      rf_string_destroy_buffer(v53);
      v59 = rf_material_name_to_index(name);
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v34 = (char *)rf_string_object_c_str_or_empty(name);
      v35 = rf_foley_definition_find_name(v34);
      *(_DWORD *)&destination[4 * v59 + 416] = v35;
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Near Miss Sound:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v38 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 124) = rf_foley_definition_find_name(v38);
  }
  else
  {
    *((_DWORD *)destination + 124) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Near Miss Underwater:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v39 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 125) = rf_foley_definition_find_name(v39);
  }
  else
  {
    *((_DWORD *)destination + 125) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Geomod Sound:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v40 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 126) = rf_foley_definition_find_name(v40);
  }
  else
  {
    *((_DWORD *)destination + 126) = -1;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Impact Vclips:");
  *((_DWORD *)destination + 276) = rf_text_parser_read_parenthesized_rfstring_list_unbounded(
                                     (_BYTE **)parser,
                                     (int)(destination + 1120),
                                     3);
  for ( i = 0; i < *((_DWORD *)destination + 276); ++i )
  {
    v41 = (char *)rf_string_object_c_str_or_empty(&destination[8 * i + 1120]);
    v42 = sub_507610(v41);
    *(_DWORD *)&destination[4 * i + 1108] = v42;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Impact Vclips Radius:");
  rf_text_parser_read_parenthesized_float_list_unbounded((int)parser, (int)(destination + 1144), 3);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Impact Decal:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Trail emitter:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v43 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 38) = rf_particle_emitter_definition_find_name(v43);
  }
  else
  {
    *((_DWORD *)destination + 38) = -1;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Damage Radius:");
  *((float *)destination + 131) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Damage Radius Multi:") )
    *((float *)destination + 132) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 132) = *((float *)destination + 131);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Crater Radius:") )
    *((float *)destination + 83) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 83) = 0.0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Sticky:");
  if ( rf_text_parser_read_boolean_word_prefix((const char **)parser) == 1 )
  {
    *((_DWORD *)destination + 153) |= (unsigned int)&unk_1000000;
    while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Stick Sound:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v57 = rf_material_name_to_index(name);
      v44 = rf_gamesound_parse_direct_sound(parser);
      *(_DWORD *)&destination[4 * v57 + 456] = v44;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Embedded V3D Filename:") )
      rf_text_parser_read_delimited_rfstring(parser, destination + 28, 34, 34);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Glow:");
  if ( rf_text_parser_read_boolean_word_prefix((const char **)parser) == 1 )
    rf_weapon_parse_light_block(parser, (float *)destination + 133);
  else
    *((float *)destination + 135) = 0.0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Muzzle Flash Light:") )
  {
    if ( rf_text_parser_read_boolean_word_prefix((const char **)parser) == 1 )
      rf_weapon_parse_light_block(parser, (float *)destination + 139);
    else
      *((float *)destination + 141) = 0.0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Drill Time:") )
    *((float *)destination + 80) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Drill Range:") )
    *((float *)destination + 81) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Drill Charge:") )
    *((float *)destination + 82) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Scorch Bitmap:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v45 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 289) = rf_bitmap_load_with_optional_mipmap_generation(v45, (void *)0xFFFFFFFF, 1);
    rf_renderer_bind_texture_for_level_warmup(*((_DWORD *)destination + 289));
  }
  else
  {
    *((_DWORD *)destination + 289) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Scorch Size:") )
    rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)destination + 290);
  else
    rf_vector3_zero_return_destination((float *)destination + 290);
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Glass Decal Bitmap:") )
  {
    rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
    v46 = (char *)rf_string_object_c_str_or_empty(name);
    *((_DWORD *)destination + 293) = rf_bitmap_load_with_optional_mipmap_generation(v46, (void *)0xFFFFFFFF, 1);
    rf_renderer_bind_texture_for_level_warmup(*((_DWORD *)destination + 293));
  }
  else
  {
    *((_DWORD *)destination + 293) = -1;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Glass Decal Size:") )
    rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)destination + 294);
  else
    rf_vector3_zero_return_destination((float *)destination + 294);
  *((float *)destination + 305) = 0.0;
  *((_DWORD *)destination + 297) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Shells Ejected:") )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+V3D:");
    rf_text_parser_read_delimited_rfstring(parser, destination + 1208, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Base Dir:");
    rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)destination + 298);
    rf_vector_normalize_reciprocal_sqrt((float *)destination + 298);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Eject Velocity:");
    *((float *)destination + 301) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Custom Sound Set:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v47 = (char *)rf_string_object_c_str_or_empty(name);
      *((_DWORD *)destination + 304) = rf_material_custom_sound_set_find(v47);
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Primary Pause Time Before Eject:") )
      *((float *)destination + 305) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  else
  {
    rf_string_assign_from_cstr((_DWORD *)destination + 302, (char *)&byte_63E711);
    rf_vector3_zero_return_destination((float *)destination + 298);
    *((float *)destination + 301) = 0.0;
    *((_DWORD *)destination + 304) = 0;
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Clips Ejected:") )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+V3D:");
    rf_text_parser_read_delimited_rfstring(parser, destination + 1228, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Drop Pause Time:");
    *((float *)destination + 309) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Custom Sound Set:") )
    {
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v48 = (char *)rf_string_object_c_str_or_empty(name);
      *((_DWORD *)destination + 310) = rf_material_custom_sound_set_find(v48);
    }
  }
  else
  {
    rf_string_assign_from_cstr((_DWORD *)destination + 307, (char *)&byte_63E712);
    *((_DWORD *)destination + 310) = 0;
  }
  *((_DWORD *)destination + 306) = -1;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Camera Shake:") )
  {
    *((_DWORD *)destination + 153) |= 0x20000000u;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Distance:");
    *((float *)destination + 312) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Time:");
    *((float *)destination + 313) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  }
  else
  {
    *((float *)destination + 312) = 0.0;
    *((float *)destination + 313) = 0.0;
  }
  *((_DWORD *)destination + 338) = 0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Tracers:") )
  {
    boolean_word_prefix = rf_text_parser_read_boolean_word_prefix((const char **)parser);
    if ( boolean_word_prefix == 1 )
    {
      *((_DWORD *)destination + 153) |= 0x40000000u;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Tracer Frequency:");
      *((_DWORD *)destination + 157) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
      *((_DWORD *)destination + 338) = 0;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Tracer Effect:") )
        rf_text_parser_read_delimited_rfstring(parser, destination + 1344, 34, 34);
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Piercing:") )
  {
    v55 = rf_text_parser_read_boolean_word_prefix((const char **)parser);
    if ( v55 == 1 )
    {
      *((_DWORD *)destination + 153) |= 0x80000000;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+Piercing Power:");
      *((float *)destination + 159) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Ricochet Angle:") )
        v54 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      else
        v54 = 180.0;
      v50 = v54 * 3.141592741012573 / 180.0;
      *((float *)destination + 160) = rf_cos_float(v50);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Ricochet Bitmap:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v49 = (char *)rf_string_object_c_str_or_empty(name);
        *((_DWORD *)destination + 161) = rf_bitmap_load_with_optional_mipmap_generation(v49, (void *)0xFFFFFFFF, 1);
        rf_renderer_bind_texture_for_level_warmup(*((_DWORD *)destination + 161));
      }
      else
      {
        *((_DWORD *)destination + 161) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Ricochet Size:") )
        rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)destination + 162);
      else
        rf_vector3_zero_return_destination((float *)destination + 162);
    }
  }
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Thrust Lifetime:") )
    *((float *)destination + 165) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 165) = 0.0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Reload Zero Drain:") )
    *((float *)destination + 311) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 311) = 0.0;
  if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Multi BBox Size Factor:") )
    *((float *)destination + 339) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  else
    *((float *)destination + 339) = 1.0;
  *((_DWORD *)destination + 326) = -1;
  *((_DWORD *)destination + 317) = -1;
  *((_DWORD *)destination + 321) = -1;
  LOBYTE(v72) = 0;
  rf_string_destroy_buffer(v71);
  v72 = -1;
  rf_string_destroy_buffer(name);
}

