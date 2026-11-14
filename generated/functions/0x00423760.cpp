// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00423760 rf_entity_info_parse_definition
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Raw423965/423992/4239A4 writes EntityInfo+0x94 kind3 for original authored $V3D Filename .vfx, kind2 for .vcm, otherwise kind1, using case-insensitive extension comparison. Preserve this before VCM resource resolution/fallback; bAnimatedSource/humanoid are not substitutes.423AA7 writes separate $Corpse V3D Filename to class+24. Flags table661320 index25 nano_shield and table661390 index4 ignore_fire are distinct class words.
// UNREALRED VERIFIED [combat-panic-bounds-20261104]: Combat class metadata: literal $Movemode string is parsed before material; flags parse28 names at661320 into+724,optional Flags2 parse8 at661390 into+728. Table meanings include fighter0x800,apc0x200,jeep0x400000; Flags2 linked_eye0x40. Movement-mode name/flags are separate from entity class alias.
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Movement source fields: exact mandatory $Movemode: ->class+30; mandatory $Max Vel: ->+50; optional +slow factor: ->+54, absent1; optional +fast factor: ->+58, absent1; mandatory $Acceleration: ->+5C. Named flags array661320 indices0=walk/bit1,11=fighter/bit800,17=humanoid/bit20000. Walk admission is distinct from humanoid. Host may retain partial legacy documents, but strict movement requires the mandatory source fields; animation-derived speeds are not native defaults.
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Entity gameplay class+6F4 persona ID is explicitly reset-1 before optional $Persona parse. Authored name is resolved through441110; missing/empty/unknown name yields native no-persona-1 as established by its lookup. Do not infer persona from animation class/model fallback, HUD persona index, faction, or class name.
// UNREALRED VERIFIED [combat-reaction-target-wait-20261111]: Class+724 starts0 and required$Flags ORs the named flag mask from661320,count28. Tableentry23 at66137C points631A74 to exact bytes ambient\0, so bit800000 is the authored ambient flag; it is not inferred from humanoid or animation availability.
// UNREALRED VERIFIED [combat-reaction-literal-names-20261111]: Default primary/secondary/optional melee fields use quoted579FB0 with retained interior whitespace, test strlen>0, then pass the exact buffer to50FB80. Default names with leading/trailing spaces are distinct native identities; only actual empty defaults skip lookup. Preserve these strings through constructor grant/selected-slot resolution instead of trimming at the host consumer.
// UNREALRED VERIFIED [combat-ai-view-prerequisites-20261111] Reached $FOV branch requires the authored value, performs angle conversion with binary32 pi promoted in the shown arithmetic, stores FLOAT radians before rf_cos_float, and stores class764 at423D25. Preserve input/conversion/store order; a generic0..360 cone validation is not the native reached parser behavior.
// UNREALRED VERIFIED [combat-native-view-fov-20261112]: Reached mandatory$FOV parser rounds authored number tofloat423CEF. Arithmetic then multiplies literal double631080 bytes00000060fb210940 (EXACT3.1415927410125732, binary32 pi promoted), divides double180 then2, rounds angle tofloat423D07 BEFORE __CIcos4108A0 wrapper, storesfloat class764 at423D25. No0..360 admission or profile substitution exists in this reached branch; missing native required token is parser failure, not a default cone.
// UNREALRED VERIFIED [combat-native-view-fov-correction-20261112]: Corrected only our preceding cosine-wrapper address transcription. Fresh disassembly423D17 calls rf_cos_float at4108A0; degree arithmetic, float angle store423D07 and class764 output remain unchanged. No production source used the incorrect textual address.
// UNREALRED VERIFIED [combat-signed-rotation-20261112]: Mandatory$Max Rot Vel and$Rot Acceleration parser calls store raw single-precision values in class60 and64 respectively (fresh423FF9..424032); this reached path has NO sign-range rejection/clamp. Negative operands are native source data, not a malformed-class condition. Missing required native token differs from host partial-table absence; preserve per-operand known state instead of treating storagezero as an authored value.
// UNREALRED VERIFIED [combat-named-sphere-binding-20261112]: 423760 stores each authored collision-sphere override as a48-byte source-order record: strncpy(name+24,source,24), SPfloat+8 and MPfloat+12 are BOTH unconditionally read/stored; optional radius+0 defaults-1 and has no sign rejection. Optional springconstant+16 defaults-1; present constant requires springlength+20. Do not discard the name, infer MPfactor from SP, or reject nonpositive radius before the consumer. A24-byte nonterminated name has unresolved overread semantics; do not silently truncate it into a different match.
int __cdecl rf_entity_info_parse_definition(_DWORD *parser)
{
  char *v2; // eax
  char *last_dot_or_empty_literal; // eax
  char *v4; // eax
  int v5; // eax
  double v6; // st7
  double v7; // st7
  char v8; // al
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  char *v15; // eax
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  char *v23; // eax
  char *v24; // eax
  int v25; // eax
  char *v26; // eax
  int v27; // eax
  char *v28; // eax
  int v29; // eax
  char *v30; // eax
  int v31; // eax
  const char *v32; // eax
  int name_case_sensitive; // eax
  char *v34; // eax
  char *v35; // eax
  const char *v36; // eax
  double v37; // st7
  int v38; // eax
  double v39; // st7
  int v40; // eax
  double v41; // st7
  double v42; // st7
  double v43; // st7
  char *v44; // eax
  int v45; // eax
  char *v46; // eax
  int v47; // eax
  char *v48; // eax
  int v49; // eax
  char *v50; // eax
  int v51; // eax
  char *v52; // eax
  int v53; // eax
  char *v54; // eax
  int v55; // eax
  char *v56; // eax
  int v57; // eax
  char *v58; // eax
  char *v59; // eax
  char *v60; // eax
  int v61; // eax
  char *v62; // eax
  char *v63; // eax
  int v64; // eax
  char *v65; // eax
  int v66; // eax
  char *v67; // eax
  int v68; // eax
  char *v69; // eax
  int v70; // eax
  char *v71; // eax
  int v72; // eax
  char *v73; // eax
  int v74; // eax
  char *v75; // eax
  int v76; // eax
  char *v77; // eax
  int v78; // eax
  char *v79; // eax
  int v80; // eax
  double v81; // st7
  char *v82; // eax
  double v83; // st7
  double v84; // st7
  char *v85; // eax
  int v86; // eax
  char *v87; // eax
  const char *v88; // eax
  double v89; // st7
  double v90; // st7
  double v91; // st7
  char *v92; // eax
  int v93; // eax
  const char *v94; // eax
  int signed_decimal_or_hex_integer; // eax
  int v96; // eax
  double v97; // st7
  int v98[15]; // [esp-24h] [ebp-398h] BYREF
  char *v99; // [esp+18h] [ebp-35Ch]
  char *v100; // [esp+1Ch] [ebp-358h]
  char *v101; // [esp+20h] [ebp-354h]
  char *v102; // [esp+24h] [ebp-350h]
  int v103; // [esp+28h] [ebp-34Ch]
  int v104; // [esp+2Ch] [ebp-348h]
  std::exception *v105; // [esp+30h] [ebp-344h]
  std::exception *v106; // [esp+34h] [ebp-340h]
  _DWORD *v107; // [esp+38h] [ebp-33Ch]
  _DWORD *v108; // [esp+3Ch] [ebp-338h]
  const void **v109; // [esp+40h] [ebp-334h]
  const void **v110; // [esp+44h] [ebp-330h]
  char v111; // [esp+4Bh] [ebp-329h]
  char *v112; // [esp+4Ch] [ebp-328h]
  char *v113; // [esp+50h] [ebp-324h]
  const char *v114; // [esp+54h] [ebp-320h]
  std::exception *v115; // [esp+58h] [ebp-31Ch]
  std::exception *v116; // [esp+5Ch] [ebp-318h]
  _DWORD *v117; // [esp+60h] [ebp-314h]
  _DWORD *v118; // [esp+64h] [ebp-310h]
  const void **v119; // [esp+68h] [ebp-30Ch]
  const void **v120; // [esp+6Ch] [ebp-308h]
  float v121; // [esp+70h] [ebp-304h]
  int v122; // [esp+74h] [ebp-300h]
  char *v123; // [esp+78h] [ebp-2FCh]
  char *v124; // [esp+7Ch] [ebp-2F8h]
  char *v125; // [esp+80h] [ebp-2F4h]
  char *v126; // [esp+84h] [ebp-2F0h]
  char *v127; // [esp+88h] [ebp-2ECh]
  char *v128; // [esp+8Ch] [ebp-2E8h]
  char *v129; // [esp+90h] [ebp-2E4h]
  char *v130; // [esp+94h] [ebp-2E0h]
  int *v131; // [esp+98h] [ebp-2DCh]
  _BYTE v132[8]; // [esp+9Ch] [ebp-2D8h] BYREF
  _BYTE v133[8]; // [esp+A4h] [ebp-2D0h] BYREF
  _DWORD v134[2]; // [esp+ACh] [ebp-2C8h] BYREF
  bool v135; // [esp+B7h] [ebp-2BDh]
  _BYTE v136[8]; // [esp+B8h] [ebp-2BCh] BYREF
  _BYTE v137[8]; // [esp+C0h] [ebp-2B4h] BYREF
  _DWORD v138[2]; // [esp+C8h] [ebp-2ACh] BYREF
  bool v139; // [esp+D3h] [ebp-2A1h]
  float v140[12]; // [esp+DCh] [ebp-298h] BYREF
  int v141; // [esp+110h] [ebp-264h]
  int v142; // [esp+114h] [ebp-260h]
  int v143; // [esp+118h] [ebp-25Ch]
  int v144; // [esp+11Ch] [ebp-258h]
  int v145; // [esp+120h] [ebp-254h]
  int v146; // [esp+124h] [ebp-250h]
  int v147; // [esp+128h] [ebp-24Ch]
  int material_or_invalid; // [esp+12Ch] [ebp-248h]
  int v149; // [esp+130h] [ebp-244h]
  int v150; // [esp+134h] [ebp-240h]
  float number_with_optional_decimal_fraction; // [esp+138h] [ebp-23Ch]
  char name[4]; // [esp+13Ch] [ebp-238h] BYREF
  int v153; // [esp+140h] [ebp-234h]
  std::exception *v154; // [esp+144h] [ebp-230h]
  char v155[516]; // [esp+148h] [ebp-22Ch] BYREF
  float v156; // [esp+34Ch] [ebp-28h]
  int parenthesized_rfstring_list_unbounded; // [esp+350h] [ebp-24h]
  void *v158; // [esp+354h] [ebp-20h]
  int i; // [esp+358h] [ebp-1Ch]
  int parenthesized_named_flag_mask; // [esp+35Ch] [ebp-18h]
  _DWORD destination[2]; // [esp+360h] [ebp-14h] BYREF
  int v162; // [esp+370h] [ebp-4h]

  rf_string_construct_empty(name);
  v162 = 0;
  if ( rf_text_parser_find_substring_before_optional_stop((char **)parser, "$Name:", nullptr) )
  {
    if ( dword_681E14 < 75 )
    {
      v154 = (std::exception *)&rf_entity_info_definitions[5396 * dword_681E14];
      *((_DWORD *)v154 + 457) = 0;
      for ( i = 0; i < 10; ++i )
        *((_DWORD *)v154 + i + 94) = -1;
      for ( i = 0; i < 3; ++i )
        *((_DWORD *)v154 + i + 104) = -1;
      *((_DWORD *)v154 + 107) = -1;
      for ( i = 0; i < 64; ++i )
        *((float *)v154 + i + 1285) = 0.0;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
      rf_text_parser_read_delimited_rfstring(parser, v154, 34, 34);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$V3D Filename:");
      rf_text_parser_read_delimited_rfstring(parser, (char *)v154 + 8, 34, 34);
      v2 = (char *)rf_string_object_c_str_or_empty((char *)v154 + 8);
      last_dot_or_empty_literal = rf_path_find_last_dot_or_empty_literal(v2);
      rf_string_assign_from_cstr(name, last_dot_or_empty_literal);
      if ( rf_string_equals_case_insensitive((int)name, ".vfx") )
      {
        *((_DWORD *)v154 + 37) = 3;
      }
      else if ( rf_string_equals_case_insensitive((int)name, ".vcm") )
      {
        *((_DWORD *)v154 + 37) = 2;
      }
      else
      {
        *((_DWORD *)v154 + 37) = 1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Debris Filename:") )
        rf_text_parser_read_delimited_rfstring(parser, (char *)v154 + 16, 34, 34);
      else
        rf_string_assign_from_cstr((_DWORD *)v154 + 4, (char *)&byte_63198E);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$LOD Distances:") )
      {
        *((_DWORD *)v154 + 1262) = 0;
        rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "{");
        while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "}") )
        {
          number_with_optional_decimal_fraction = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
          if ( *((int *)v154 + 1262) < 4 )
            *((float *)v154 + (*((_DWORD *)v154 + 1262))++ + 1263) = number_with_optional_decimal_fraction;
        }
      }
      else
      {
        *((_DWORD *)v154 + 1262) = 0;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Corpse V3D Filename:") )
        rf_text_parser_read_delimited_rfstring(parser, (char *)v154 + 24, 34, 34);
      else
        rf_string_assign_from_cstr((_DWORD *)v154 + 6, (char *)&byte_63198F);
      *((_DWORD *)v154 + 10) = -1;
      *((float *)v154 + 11) = -1.0;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Corpse Emitter:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v4 = (char *)rf_string_object_c_str_or_empty(name);
        v5 = rf_particle_emitter_definition_find_name(v4);
        *((_DWORD *)v154 + 10) = v5;
        if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Corpse Emitter Lifetime:") )
        {
          v6 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
          *((float *)v154 + 11) = v6;
        }
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Movemode:");
      rf_text_parser_read_delimited_rfstring(parser, (char *)v154 + 48, 34, 34);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Mass:");
      v7 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 26) = v7;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Material:");
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v8 = rf_material_name_to_index(name);
      *((_BYTE *)v154 + 152) = v8;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Flags:");
      parenthesized_named_flag_mask = rf_text_parser_read_parenthesized_named_flag_mask(
                                        (_BYTE **)parser,
                                        (int)&off_661320,
                                        28);
      *((_DWORD *)v154 + 457) |= parenthesized_named_flag_mask;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Flags2:") )
      {
        parenthesized_named_flag_mask = rf_text_parser_read_parenthesized_named_flag_mask(
                                          (_BYTE **)parser,
                                          (int)off_661390,
                                          8);
        *((_DWORD *)v154 + 458) |= parenthesized_named_flag_mask;
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Collision Radius:");
      v9 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 16) = v9;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Collision Damage Given:");
      v10 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 19) = v10;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Movement Radius:") )
      {
        v11 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)v154 + 467) = v11;
      }
      else
      {
        *((float *)v154 + 467) = 0.0;
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$FOV:");
      v156 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      v121 = v156 * 3.141592741012573 / 180.0 / 2.0;
      v12 = rf_cos_float(v121);
      *((float *)v154 + 473) = v12;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Envirosuit:");
      v13 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 18) = v13;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Life:");
      v14 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 17) = v14;
      for ( i = 0; i < 11; ++i )
        *((float *)v154 + i + 1274) = 1.0;
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Damage Type Factor:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v15 = (char *)rf_string_object_c_str_or_empty(name);
        i = sub_4BCFF0(v15);
        if ( i == -1 )
          rf_fatal_error_show_message_and_exit(
            "D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp",
            1958,
            "Entity.tbl error!  Cannot set damage factor for damage type 'undefined'!");
        v16 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)v154 + i + 1274) = v16;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Min Relative Eye PHB:") )
      {
        rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)v154 + 27);
        *((float *)v154 + 27) = *((float *)v154 + 27) * 3.141592741012573 / 180.0;
        *((float *)v154 + 28) = *((float *)v154 + 28) * 3.141592741012573 / 180.0;
        *((float *)v154 + 29) = *((float *)v154 + 29) * 3.141592741012573 / 180.0;
        rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Max Relative Eye PHB:");
        rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)v154 + 30);
        *((float *)v154 + 30) = *((float *)v154 + 30) * 3.141592741012573 / 180.0;
        *((float *)v154 + 31) = *((float *)v154 + 31) * 3.141592741012573 / 180.0;
        *((float *)v154 + 32) = *((float *)v154 + 32) * 3.141592741012573 / 180.0;
      }
      else
      {
        rf_vector3_set_components_thiscall((float *)v154 + 27, -1.5707964, 0.0, 0.0);
        rf_vector3_set_components_thiscall((float *)v154 + 30, 1.5707964, 0.0, 0.0);
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Max Vel:");
      v17 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 20) = v17;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+slow factor:") )
      {
        v18 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)v154 + 21) = v18;
      }
      else
      {
        *((float *)v154 + 21) = 1.0;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+fast factor:") )
      {
        v19 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)v154 + 22) = v19;
      }
      else
      {
        *((float *)v154 + 22) = 1.0;
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Acceleration:");
      v20 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 23) = v20;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Max Rot Vel:");
      v21 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 24) = v21;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Rot Acceleration:");
      v22 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 25) = v22;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Allowed Weapons:");
      `eh vector constructor iterator'(
        v155,
        8u,
        64,
        (void (__thiscall *)(void *))rf_string_construct_empty,
        rf_string_destroy_buffer);
      LOBYTE(v162) = 1;
      parenthesized_rfstring_list_unbounded = rf_text_parser_read_parenthesized_rfstring_list_unbounded(
                                                (_BYTE **)parser,
                                                (int)v155,
                                                64);
      for ( i = 0; i < 64; ++i )
        *((_BYTE *)v154 + i + 180) = 0;
      for ( i = 0; i < parenthesized_rfstring_list_unbounded; ++i )
      {
        v23 = (char *)rf_string_object_c_str_or_empty(&v155[8 * i]);
        if ( sub_50FB80(v23) != -1 )
          *((_BYTE *)v154 + i + 180) = 1;
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Default Primary:");
      *((_DWORD *)v154 + 34) = -1;
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
      {
        v24 = (char *)rf_string_object_c_str_or_empty(name);
        v25 = sub_50FB80(v24);
        *((_DWORD *)v154 + 34) = v25;
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Default Secondary:");
      *((_DWORD *)v154 + 35) = -1;
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
      {
        v26 = (char *)rf_string_object_c_str_or_empty(name);
        v27 = sub_50FB80(v26);
        *((_DWORD *)v154 + 35) = v27;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Force Launch Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v28 = (char *)rf_string_object_c_str_or_empty(name);
        v29 = rf_foley_definition_find_name(v28);
        *((_DWORD *)v154 + 468) = v29;
      }
      else
      {
        *((_DWORD *)v154 + 468) = -1;
      }
      *((_DWORD *)v154 + 36) = -1;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Default Melee:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
        {
          v30 = (char *)rf_string_object_c_str_or_empty(name);
          v31 = sub_50FB80(v30);
          *((_DWORD *)v154 + 36) = v31;
        }
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Primary Muzzle Glare Name:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v32 = rf_string_object_c_str_or_empty(name);
        name_case_sensitive = rf_glare_definition_find_name_case_sensitive(v32);
        *((_DWORD *)v154 + 63) = name_case_sensitive;
      }
      else
      {
        *((_DWORD *)v154 + 63) = -1;
      }
      rf_string_assign_from_cstr((_DWORD *)v154 + 465, (char *)&byte_63199A);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Primary Warmup FX:") )
        rf_text_parser_read_delimited_rfstring(parser, (char *)v154 + 1860, 34, 34);
      *((_DWORD *)v154 + 413) = 0;
      for ( i = 1; ; ++i )
      {
        v120 = (const void **)rf_string_format_int32_decimal(v138, i);
        v119 = v120;
        LOBYTE(v162) = 2;
        v118 = rf_string_concat_cstr_object(v137, "$Thruster VFX ", v120);
        v117 = v118;
        LOBYTE(v162) = 3;
        v116 = (std::exception *)rf_string_concat_object_cstr(v136, v118, ":");
        v115 = v116;
        LOBYTE(v162) = 4;
        v34 = (char *)rf_string_object_c_str_or_empty(v116);
        v139 = rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, v34);
        LOBYTE(v162) = 3;
        rf_string_destroy_buffer(v136);
        LOBYTE(v162) = 2;
        rf_string_destroy_buffer(v137);
        LOBYTE(v162) = 1;
        rf_string_destroy_buffer(v138);
        if ( !v139 )
          break;
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        if ( (int)rf_string_length_from_cstr((const char **)name) <= 0 )
        {
          *((_BYTE *)v154 + 32 * *((_DWORD *)v154 + 413) + 628) = 0;
        }
        else
        {
          v114 = rf_string_object_c_str_or_empty(name);
          v113 = (char *)v154 + 32 * *((_DWORD *)v154 + 413) + 628;
          v112 = v113;
          do
          {
            v111 = *v114;
            *v113 = v111;
            ++v114;
            ++v113;
          }
          while ( v111 );
        }
        ++*((_DWORD *)v154 + 413);
      }
      for ( i = 1; ; ++i )
      {
        v110 = (const void **)rf_string_format_int32_decimal(v134, i);
        v109 = v110;
        LOBYTE(v162) = 5;
        v108 = rf_string_concat_cstr_object(v133, "$Corona (Glare) ", v110);
        v107 = v108;
        LOBYTE(v162) = 6;
        v106 = (std::exception *)rf_string_concat_object_cstr(v132, v108, ":");
        v105 = v106;
        LOBYTE(v162) = 7;
        v35 = (char *)rf_string_object_c_str_or_empty(v106);
        v135 = rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, v35);
        LOBYTE(v162) = 6;
        rf_string_destroy_buffer(v132);
        LOBYTE(v162) = 5;
        rf_string_destroy_buffer(v133);
        LOBYTE(v162) = 1;
        rf_string_destroy_buffer(v134);
        if ( !v135 )
          break;
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        if ( (int)rf_string_length_from_cstr((const char **)name) <= 0 )
        {
          v150 = -1;
          rf_inline_dword8_append_unless_exact_full((_DWORD *)v154 + 423, -1);
        }
        else
        {
          v36 = rf_string_object_c_str_or_empty(name);
          v150 = rf_glare_definition_find_name_case_sensitive(v36);
          if ( v150 < 0 )
            rf_fatal_error_show_message_and_exit(
              "D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp",
              2078,
              "Invalid Corona in entity.tbl!");
          rf_inline_dword8_append_unless_exact_full((_DWORD *)v154 + 423, v150);
        }
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        if ( rf_string_equals_case_insensitive((int)name, "headlamp") && v150 != -1 )
          rf_inline_dword8_append_unless_exact_full((_DWORD *)v154 + 432, v150);
      }
      rf_string_assign_from_cstr((_DWORD *)v154 + 14, (char *)&byte_63199B);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Helmet V3D Filename:") )
        rf_text_parser_read_delimited_rfstring(parser, (char *)v154 + 56, 34, 34);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Unholster Delay:") )
      {
        v37 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)v154 + 990) = v37;
      }
      else
      {
        *((float *)v154 + 990) = 0.0;
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Attack Style:");
      rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
      v38 = rf_ai_behavior_name_to_code((int)name);
      *((_DWORD *)v154 + 456) = v38;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Blind Pursuit Time:");
      v39 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 454) = v39;
      *((_DWORD *)v154 + 445) = -1;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Persona:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v131 = &v98[10];
        rf_string_copy_construct_from_object(&v98[10], (char **)name);
        v104 = v40;
        v103 = sub_441110(v98[10]);
        *((_DWORD *)v154 + 445) = v103;
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$FlySnd:");
      rf_text_parser_read_delimited_rfstring(parser, (char *)v154 + 260, 34, 34);
      if ( (int)rf_string_length_from_cstr((const char **)v154 + 65) <= 0 )
      {
        *((_DWORD *)v154 + 64) = -1;
      }
      else
      {
        v41 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)v154 + 67) = v41;
        v42 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)v154 + 68) = v42;
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Min FlySnd Volume:");
      v43 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)v154 + 108) = v43;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Move Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v44 = (char *)rf_string_object_c_str_or_empty(name);
        v45 = rf_foley_definition_find_name(v44);
        *((_DWORD *)v154 + 79) = v45;
      }
      else
      {
        *((_DWORD *)v154 + 79) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Engine Rev Fwd Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v46 = (char *)rf_string_object_c_str_or_empty(name);
        v47 = rf_foley_definition_find_name(v46);
        *((_DWORD *)v154 + 77) = v47;
      }
      else
      {
        *((_DWORD *)v154 + 77) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Engine Rev Back Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v48 = (char *)rf_string_object_c_str_or_empty(name);
        v49 = rf_foley_definition_find_name(v48);
        *((_DWORD *)v154 + 78) = v49;
      }
      else
      {
        *((_DWORD *)v154 + 78) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$StartleSnd:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v50 = (char *)rf_string_object_c_str_or_empty(name);
        v51 = rf_foley_definition_find_name(v50);
        *((_DWORD *)v154 + 90) = v51;
      }
      else
      {
        *((_DWORD *)v154 + 90) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$AttachSnd:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v52 = (char *)rf_string_object_c_str_or_empty(name);
        v53 = rf_foley_definition_find_name(v52);
        *((_DWORD *)v154 + 69) = v53;
      }
      else
      {
        *((_DWORD *)v154 + 69) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$DetachSnd:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v54 = (char *)rf_string_object_c_str_or_empty(name);
        v55 = rf_foley_definition_find_name(v54);
        *((_DWORD *)v154 + 70) = v55;
      }
      else
      {
        *((_DWORD *)v154 + 70) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$RotateSnd:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v56 = (char *)rf_string_object_c_str_or_empty(name);
        v57 = rf_foley_definition_find_name(v56);
        *((_DWORD *)v154 + 71) = v57;
      }
      else
      {
        *((_DWORD *)v154 + 71) = -1;
      }
      for ( i = 0; i < 10; ++i )
        *((_DWORD *)v154 + i + 94) = -1;
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Footstep Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v58 = (char *)rf_string_object_c_str_or_empty(name);
        v149 = rf_foley_definition_find_name(v58);
        if ( v149 == -1 )
          rf_fatal_error_show_message_and_exit(
            "D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp",
            2189,
            "Invalid name specified for $Footstep Sound!");
        material_or_invalid = rf_foley_get_material_or_invalid(v149);
        *((_DWORD *)v154 + material_or_invalid + 94) = v149;
      }
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Climb Footstep Sounds:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v59 = (char *)rf_string_object_c_str_or_empty(name);
        v147 = rf_foley_definition_find_name(v59);
        if ( v147 == -1 )
          rf_fatal_error_show_message_and_exit(
            "D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp",
            2199,
            "Invalid name specified for $Climb Footstep Sounds!");
        v146 = rf_foley_get_material_or_invalid(v147);
        if ( v146 )
        {
          if ( v146 != 1 && v146 != 2 )
            rf_fatal_error_show_message_and_exit(
              "D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp",
              2205,
              "Invalid material specified for climb footstep sound type!");
        }
        else
        {
          v146 = 0;
        }
        *((_DWORD *)v154 + v146 + 104) = v147;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Crawl Footstep Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v60 = (char *)rf_string_object_c_str_or_empty(name);
        v61 = rf_foley_definition_find_name(v60);
        *((_DWORD *)v154 + 107) = v61;
      }
      for ( i = 0; i < 10; ++i )
        *((_DWORD *)v154 + i + 80) = -1;
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$LandSnd:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v62 = (char *)rf_string_object_c_str_or_empty(name);
        v145 = rf_foley_definition_find_name(v62);
        if ( v145 == -1 )
          rf_fatal_error_show_message_and_exit(
            "D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp",
            2226,
            "Invalid name specified for $LandSnd!");
        v144 = rf_foley_get_material_or_invalid(v145);
        *((_DWORD *)v154 + v144 + 80) = v145;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Impact Death Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v63 = (char *)rf_string_object_c_str_or_empty(name);
        v64 = rf_foley_definition_find_name(v63);
        *((_DWORD *)v154 + 74) = v64;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$JumpSnd:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v65 = (char *)rf_string_object_c_str_or_empty(name);
        v66 = rf_foley_definition_find_name(v65);
        *((_DWORD *)v154 + 72) = v66;
      }
      else
      {
        *((_DWORD *)v154 + 72) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$HeadLamp On Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v67 = (char *)rf_string_object_c_str_or_empty(name);
        v68 = rf_foley_definition_find_name(v67);
        *((_DWORD *)v154 + 75) = v68;
      }
      else
      {
        *((_DWORD *)v154 + 75) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$HeadLamp Off Sound:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v69 = (char *)rf_string_object_c_str_or_empty(name);
        v70 = rf_foley_definition_find_name(v69);
        *((_DWORD *)v154 + 76) = v70;
      }
      else
      {
        *((_DWORD *)v154 + 76) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Low_Pain Sounds:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v71 = (char *)rf_string_object_c_str_or_empty(name);
        v72 = rf_foley_definition_find_name(v71);
        *((_DWORD *)v154 + 91) = v72;
      }
      else
      {
        *((_DWORD *)v154 + 91) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Med_Pain Sounds:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v73 = (char *)rf_string_object_c_str_or_empty(name);
        v74 = rf_foley_definition_find_name(v73);
        *((_DWORD *)v154 + 92) = v74;
      }
      else
      {
        *((_DWORD *)v154 + 92) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Squash Sounds:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v75 = (char *)rf_string_object_c_str_or_empty(name);
        v76 = rf_foley_definition_find_name(v75);
        *((_DWORD *)v154 + 93) = v76;
      }
      else
      {
        *((_DWORD *)v154 + 93) = -1;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$DeathSnd:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v77 = (char *)rf_string_object_c_str_or_empty(name);
        v78 = rf_foley_definition_find_name(v77);
        *((_DWORD *)v154 + 73) = v78;
      }
      else
      {
        *((_DWORD *)v154 + 73) = -1;
      }
      *((_DWORD *)v154 + 446) = -1;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Explode Anim:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v79 = (char *)rf_string_object_c_str_or_empty(name);
        v80 = sub_507610(v79);
        *((_DWORD *)v154 + 446) = v80;
        if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Explode Anim Radius:") )
        {
          v81 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
          *((float *)v154 + 447) = v81;
        }
        if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Explode Offset:") )
          rf_text_parser_read_angle_bracket_vector3((int)parser, (float *)v154 + 448);
        else
          rf_vector3_zero_return_destination((float *)v154 + 448);
      }
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$emitter:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v82 = (char *)rf_string_object_c_str_or_empty(name);
        i = rf_particle_emitter_definition_find_name(v82);
        if ( i > -1 )
          rf_inline_dword2_append_unless_exact_full((_DWORD *)v154 + 451, i);
      }
      *((_DWORD *)v154 + 469) = 0;
      *((_DWORD *)v154 + 470) = 0;
      *((_DWORD *)v154 + 471) = 0;
      *((_DWORD *)v154 + 472) = 0;
      rf_string_construct_empty(destination);
      LOBYTE(v162) = 8;
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+State:") )
      {
        if ( !*((_DWORD *)v154 + 471) )
        {
          v129 = (char *)operator new(0x4B0u);
          LOBYTE(v162) = 9;
          if ( v129 )
          {
            *(_DWORD *)v129 = 23;
            `eh vector constructor iterator'(
              v129 + 4,
              0x34u,
              23,
              (void (__thiscall *)(void *))rf_entity_definition_record52_construct_strings,
              (void (__thiscall *)(void *))rf_record_destroy_strings0_8_and_pair24);
            v102 = v129 + 4;
          }
          else
          {
            v102 = nullptr;
          }
          v130 = v102;
          LOBYTE(v162) = 8;
          *((_DWORD *)v154 + 471) = v102;
          for ( i = 0; i < 23; ++i )
            *(_DWORD *)(*((_DWORD *)v154 + 471) + 52 * i + 20) = 0;
        }
        rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
        {
          rf_string_assign_from_object(
            (_DWORD *)(*((_DWORD *)v154 + 471) + 52 * *((_DWORD *)v154 + 469)),
            (int)destination);
          rf_string_assign_from_object(
            (_DWORD *)(*((_DWORD *)v154 + 471) + 52 * *((_DWORD *)v154 + 469) + 8),
            (int)name);
          ++*((_DWORD *)v154 + 469);
        }
        while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Footstep Trigger:") )
        {
          v143 = *((_DWORD *)v154 + 469) - 1;
          rf_string_assign_from_cstr(
            (_DWORD *)(52 * v143
                     + *((_DWORD *)v154 + 471)
                     + 12 * *(_DWORD *)(*((_DWORD *)v154 + 471) + 52 * v143 + 20)
                     + 24),
            "footstep_left");
          v83 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
          *(float *)(*((_DWORD *)v154 + 471)
                   + 52 * v143
                   + 12 * (*(_DWORD *)(*((_DWORD *)v154 + 471) + 52 * v143 + 20))++
                   + 32) = v83;
          rf_string_assign_from_cstr(
            (_DWORD *)(52 * v143
                     + *((_DWORD *)v154 + 471)
                     + 12 * *(_DWORD *)(*((_DWORD *)v154 + 471) + 52 * v143 + 20)
                     + 24),
            "footstep_right");
          v84 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
          *(float *)(*((_DWORD *)v154 + 471)
                   + 52 * v143
                   + 12 * (*(_DWORD *)(*((_DWORD *)v154 + 471) + 52 * v143 + 20))++
                   + 32) = v84;
        }
      }
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Action:") )
      {
        if ( !*((_DWORD *)v154 + 472) )
        {
          v127 = (char *)operator new(0x928u);
          LOBYTE(v162) = 10;
          if ( v127 )
          {
            *(_DWORD *)v127 = 45;
            `eh vector constructor iterator'(
              v127 + 4,
              0x34u,
              45,
              (void (__thiscall *)(void *))rf_entity_definition_record52_construct_strings,
              (void (__thiscall *)(void *))rf_record_destroy_strings0_8_and_pair24);
            v101 = v127 + 4;
          }
          else
          {
            v101 = nullptr;
          }
          v128 = v101;
          LOBYTE(v162) = 8;
          *((_DWORD *)v154 + 472) = v101;
          for ( i = 0; i < 45; ++i )
            *(_DWORD *)(*((_DWORD *)v154 + 472) + 52 * i + 16) = -1;
        }
        rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
        {
          rf_string_assign_from_object(
            (_DWORD *)(*((_DWORD *)v154 + 472) + 52 * *((_DWORD *)v154 + 470)),
            (int)destination);
          rf_string_assign_from_object(
            (_DWORD *)(*((_DWORD *)v154 + 472) + 52 * *((_DWORD *)v154 + 470) + 8),
            (int)name);
          ++*((_DWORD *)v154 + 470);
        }
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v85 = (char *)rf_string_object_c_str_or_empty(name);
        v86 = rf_foley_definition_find_name(v85);
        *(_DWORD *)(*((_DWORD *)v154 + 472) + 52 * (*((_DWORD *)v154 + 470) - 1) + 16) = v86;
      }
      for ( i = 0; i < 64; ++i )
      {
        *((_DWORD *)v154 + i + 474) = 0;
        *((_DWORD *)v154 + i + 538) = 0;
        *((_DWORD *)v154 + i + 602) = 0;
        *((_DWORD *)v154 + i + 666) = 0;
      }
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Weapon Specific:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v87 = (char *)rf_string_object_c_str_or_empty(name);
        v142 = sub_50FB80(v87);
        if ( v142 == -1 )
        {
          v98[11] = v153;
          v98[10] = *(_DWORD *)name;
          v88 = rf_string_object_c_str_or_empty(v154);
          sprintf(
            "Entity.tbl parsing error for '%s'.  Cannot find weapon type '%s' needed for weapon specific animations,\n",
            v88);
          rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\entity\\entity.cpp", 2387, &unk_18CD828);
        }
        v125 = (char *)operator new(0x4B0u);
        LOBYTE(v162) = 11;
        if ( v125 )
        {
          *(_DWORD *)v125 = 23;
          `eh vector constructor iterator'(
            v125 + 4,
            0x34u,
            23,
            (void (__thiscall *)(void *))rf_entity_definition_record52_construct_strings,
            (void (__thiscall *)(void *))rf_record_destroy_strings0_8_and_pair24);
          v100 = v125 + 4;
        }
        else
        {
          v100 = nullptr;
        }
        v126 = v100;
        LOBYTE(v162) = 8;
        *((_DWORD *)v154 + v142 + 602) = v100;
        for ( i = 0; i < 23; ++i )
          *(_DWORD *)(*((_DWORD *)v154 + v142 + 602) + 52 * i + 20) = 0;
        if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Spine Adjustment:") )
        {
          v89 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
          *((float *)v154 + v142 + 1285) = v89;
        }
        while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+State:") )
        {
          rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
          rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
          if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
          {
            rf_string_assign_from_object(
              (_DWORD *)(*((_DWORD *)v154 + v142 + 602) + 52 * *((_DWORD *)v154 + v142 + 474)),
              (int)destination);
            rf_string_assign_from_object(
              (_DWORD *)(*((_DWORD *)v154 + v142 + 602) + 52 * *((_DWORD *)v154 + v142 + 474) + 8),
              (int)name);
            ++*((_DWORD *)v154 + v142 + 474);
          }
          while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Footstep Trigger:") )
          {
            v141 = *((_DWORD *)v154 + v142 + 474) - 1;
            v98[11] = (int)"footstep_left";
            rf_string_assign_from_cstr(
              (_DWORD *)(52 * v141
                       + *((_DWORD *)v154 + v142 + 602)
                       + 12 * *(_DWORD *)(*((_DWORD *)v154 + v142 + 602) + 52 * v141 + 20)
                       + 24),
              "footstep_left");
            v90 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
            *(float *)(*((_DWORD *)v154 + v142 + 602)
                     + 52 * v141
                     + 12 * (*(_DWORD *)(*((_DWORD *)v154 + v142 + 602) + 52 * v141 + 20))++
                     + 32) = v90;
            v98[11] = (int)"footstep_right";
            rf_string_assign_from_cstr(
              (_DWORD *)(52 * v141
                       + *((_DWORD *)v154 + v142 + 602)
                       + 12 * *(_DWORD *)(*((_DWORD *)v154 + v142 + 602) + 52 * v141 + 20)
                       + 24),
              "footstep_right");
            v91 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
            *(float *)(*((_DWORD *)v154 + v142 + 602)
                     + 52 * v141
                     + 12 * (*(_DWORD *)(*((_DWORD *)v154 + v142 + 602) + 52 * v141 + 20))++
                     + 32) = v91;
          }
        }
        v123 = (char *)operator new(0x928u);
        LOBYTE(v162) = 12;
        if ( v123 )
        {
          *(_DWORD *)v123 = 45;
          `eh vector constructor iterator'(
            v123 + 4,
            0x34u,
            45,
            (void (__thiscall *)(void *))rf_entity_definition_record52_construct_strings,
            (void (__thiscall *)(void *))rf_record_destroy_strings0_8_and_pair24);
          v99 = v123 + 4;
        }
        else
        {
          v99 = nullptr;
        }
        v124 = v99;
        LOBYTE(v162) = 8;
        *((_DWORD *)v154 + v142 + 666) = v99;
        for ( i = 0; i < 45; ++i )
          *(_DWORD *)(*((_DWORD *)v154 + v142 + 666) + 52 * i + 16) = -1;
        while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Action:") )
        {
          rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
          rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
          if ( (int)rf_string_length_from_cstr((const char **)name) > 0 )
          {
            rf_string_assign_from_object(
              (_DWORD *)(*((_DWORD *)v154 + v142 + 666) + 52 * *((_DWORD *)v154 + v142 + 538)),
              (int)destination);
            rf_string_assign_from_object(
              (_DWORD *)(*((_DWORD *)v154 + v142 + 666) + 52 * *((_DWORD *)v154 + v142 + 538) + 8),
              (int)name);
            ++*((_DWORD *)v154 + v142 + 538);
          }
          rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
          v92 = (char *)rf_string_object_c_str_or_empty(name);
          v93 = rf_foley_definition_find_name(v92);
          *(_DWORD *)(*((_DWORD *)v154 + v142 + 666) + 52 * (*((_DWORD *)v154 + v142 + 538) - 1) + 16) = v93;
        }
      }
      rf_text_parse_optional_use_classification((int)parser, (_DWORD *)v154 + 109, (float *)v154 + 110);
      while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Collision Sphere:") )
      {
        rf_text_parser_read_delimited_rfstring(parser, name, 34, 34);
        v98[11] = 24;
        v94 = rf_string_object_c_str_or_empty(name);
        strncpy((char *)&v140[6], v94, v98[11]);
        v140[2] = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        v140[3] = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+radius:") )
          v140[0] = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        else
          v140[0] = -1.0;
        if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+spring constant:") )
        {
          v140[4] = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
          rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+spring length:");
          v140[5] = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        }
        else
        {
          v140[4] = -1.0;
        }
        qmemcpy(v98, v140, 0x30u);
        sub_43CCA0(
          (_DWORD *)v154 + 730,
          v98[0],
          v98[1],
          v98[2],
          v98[3],
          v98[4],
          v98[5],
          v98[6],
          v98[7],
          v98[8],
          v98[9],
          v98[10],
          v98[11]);
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Num Skins:");
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
      *((_DWORD *)v154 + 991) = signed_decimal_or_hex_integer;
      for ( i = 0; i < *((_DWORD *)v154 + 991); ++i )
      {
        v158 = (char *)v154 + 108 * i + 3968;
        rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Skin:");
        rf_text_parser_read_delimited_rfstring(parser, v158, 34, 34);
        v96 = rf_text_parser_read_parenthesized_rfstring_list_unbounded((_BYTE **)parser, (int)v158 + 12, 12);
        *((_DWORD *)v158 + 2) = v96;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Cockpit VFX:") )
        rf_text_parser_read_delimited_rfstring(parser, (char *)v154 + 5068, 34, 34);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Body Temperature(F):") )
      {
        v97 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)v154 + 1273) = v97;
      }
      else
      {
        *((float *)v154 + 1273) = 0.0;
      }
      v122 = 0;
      LOBYTE(v162) = 1;
      rf_string_destroy_buffer(destination);
      LOBYTE(v162) = 0;
      `eh vector destructor iterator'(v155, 8u, 64, rf_string_destroy_buffer);
      v162 = -1;
      rf_string_destroy_buffer(name);
      return v122;
    }
    else
    {
      v162 = -1;
      rf_string_destroy_buffer(name);
      return -1;
    }
  }
  else
  {
    rf_text_parser_find_substring_before_optional_stop((char **)parser, "#End", nullptr);
    v162 = -1;
    rf_string_destroy_buffer(name);
    return -1;
  }
}

