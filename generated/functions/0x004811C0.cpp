// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004811C0 rf_rfl_entities_section_load
// UNREALRED VERIFIED [mission-visibility-20261020] RFL v180 initial-inactive is v130 boolean v59, following raw mode byte, another raw byte, legacy list0x4826F0, three int32s and v127 boolean. Any nonzero becomes create option2;0x42CB80 maps that to common+0x7C mask0x4000. The loader finishes by calling0x4BC7D0 if that common flag is set, after creating held clutter. This is not the ready/holstered prefix. Empty legacy list puts the inactive byte at offset18 within the old33-byte post-mode tail. Retail audit94 maps:1610 entities,543 inactive.
// UNREALRED VERIFIED [ai-authored-startup-20261028] RFL waypoint name/method are v81/v93 (first two strings after leading bool and three int32s), not later corpse/skin strings v87/v77. A nonempty name resolves case-insensitively through 0x487150 into entity+0x748 (AI+0x4A8), with 0x487370 method flags at entity+0x74C. After translating authored mode, only translated 2 on exact case-insensitive class camera2 changes to 15; save via 0x40A260(mode,0), restore via 0x40A2A0. An empty name leaves constructor saved-list index -1. No none sentinel check is made for this name.
// UNREALRED VERIFIED [ai-arrival-target-20261029] Early six-byte initial-state prefix positions1 and3 are v58 and v45: v58 (version0 default1) sets entity+0x810 bit0x10000; v45 (version64 default0) sets entity+0x7D0/AI+0x530 bit0x80. The former participates in0x434010 runtime-enabled owner eligibility; the latter restricts0x40BA80 changed target writes to player-associated objects. Preserve separately from prefix2 ready and prefix4 holstered. v58 also drives vehicle headlamp handling; this pass does not claim that vehicle branch implemented.
// UNREALRED VERIFIED [combat-reaction-20261111]: Selected weapon ordering: authored saved-mode restore precedes primary string handling, which precedes secondary string handling. Empty/unresolved overrides retain constructor-selected IDs; case-insensitive none writes the corresponding selected ID to-1, valid resolved override grants/selects that ID. Primary glock aliases12mm handgun. Primary-none ownership clearing has an indexing quirk:4820DD uses outer var_40, not loop var_13C; do not generalize it as a correct category-wide byte clear. Selected-index outcomes are independent of that ownership quirk.
// UNREALRED VERIFIED [combat-reaction-primary-none-20261111]: Primary-none prefix precision:4812CA reads sectioncount into var3C,4812CD initializes outervar40=0,4812D6 increments it before4812E2 counttest. Therefore4820DD uses ZERO-BASED SERIALIZED ENTITY ROW ORDINAL including skipped rows, not UID, created-entity count, or weaponloop index. If nativeprimarycount>0, looprepeatedly zeros ONE byteEntity+42C+ordinal, then selectedprimary=-1. With ordinal0..63 thishits one inventory-presence byte; ordinal64..127 hits the following64-byte array; >=128 reachesAI+20C dynamicarray/adjacentstate. Do not implement a category-wide primarypresenceclear or claim the out-of-layout host effects are represented.
// UNREALRED VERIFIED [combat-reaction-literal-names-20261111]: Authored primary/secondary weapon strings are WHOLE untrimmed RFStrings.5609B0 compares complete buffers to none (and primary glock alias) with _stricmp, then50FB80 compares whole lookup strings. Therefore padded none is NOT a selected/presence clear, padded glock is NOT the alias, and a padded unmatched weapon preserves the constructor selection. Do not trim these serialized strings or route them through normalized UI aliases.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: RFL weapon overrides follow fullnativeconstructor. Valid primary grants-1 then ifAmmoID>=0 writesactiveMax; selectsprimary; rocketlauncher special unconditionallywrites rawreserve[AmmoID]=3. Validsecondary grants-1/selectssecondary without explicit maxfill. None clauses clear presence only, not counters; original serializedordinal primarywrongindex and secondaryrange remain distinct. Preserve allsame-source default/override order, not folded UI ammo pickup totals.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Native source for AI+4CC(Entity+76C/+1900) consumed by40AEB0 is RFL signed int32 v86 read with minimumversion150 and default-1 at earlier read phase, then copied after mode/context restore. It is third int32 after legacy object-entry list (previous reads minversions98 and116). Retain this authored alarm-event identifier separately from waypoint or current combat target; absent version uses proven-1, not0.
// UNREALRED VERIFIED [combat-ai-view-prerequisites-20261111] Reached spawned-entity path overwritesEntity840 at481B13 from serialized full int FOV via shown degree*pi/180/2 conversion with FLOAT angle store then cosine. Earlier class764 copy does not replace this authored overwrite; no0..360 rejection appears in this native conversion.
// UNREALRED VERIFIED [combat-native-view-fov-20261112]: RFL FOV uses SIGNED INT32 var60 viaFILD481AE0, not a float conversion first; same promoted-pi/180/2 arithmetic then FLOAT angle store481AF5 precedes cosine and Entity840 store481B13. Recovered139 version branch initializes source int180 when no authored field is read. Native class764 copied in42CB80 is overwritten by this RFL source scalar; do not clamp a raw source integer or substitute a host perception-profile FOV.
// UNREALRED VERIFIED [combat-original-facing-20261112]: Authored constructor option byte producer:481820 initializes localvar140=0; its only subsequent writers before creation are OR2 at48183B (v130 initial-inactive) and OR4 at481852 (v169).481889 pushes this word as42CB80 argumenta6;42CB80 retains a6&1 as its player-constructor option. Therefore this fresh authored-RFL creator path proves that option0, independent of class mouselook flag4000. Do not extend this receipt to player/source-free/restore creator paths. Existing class764 then authored signed-int840 writer notes remain authoritative.
void __cdecl rf_rfl_entities_section_load(_DWORD *a1)
{
  char *v1; // eax
  char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  double v5; // st7
  char *v6; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  int v12; // eax
  char *v13; // eax
  int canonical_index; // eax
  char *v15; // eax
  char *v16; // eax
  char *v17; // eax
  char *v18; // eax
  char v19; // [esp+0h] [ebp-184h]
  float v20; // [esp+Ch] [ebp-178h]
  _DWORD *v21; // [esp+10h] [ebp-174h]
  int v22; // [esp+14h] [ebp-170h]
  _DWORD *v23; // [esp+18h] [ebp-16Ch]
  int index_by_name; // [esp+1Ch] [ebp-168h]
  int v25; // [esp+20h] [ebp-164h] BYREF
  _DWORD *v26; // [esp+24h] [ebp-160h]
  int v27; // [esp+28h] [ebp-15Ch]
  int v28; // [esp+2Ch] [ebp-158h]
  int v29; // [esp+30h] [ebp-154h]
  int v30[4]; // [esp+34h] [ebp-150h] BYREF
  int v31; // [esp+44h] [ebp-140h]
  int j; // [esp+48h] [ebp-13Ch]
  int runtime; // [esp+4Ch] [ebp-138h]
  int v34; // [esp+50h] [ebp-134h]
  char v35; // [esp+57h] [ebp-12Dh]
  int v36; // [esp+58h] [ebp-12Ch]
  int v37; // [esp+5Ch] [ebp-128h]
  int v38; // [esp+60h] [ebp-124h]
  float v39; // [esp+64h] [ebp-120h]
  int v40; // [esp+68h] [ebp-11Ch]
  int v41[2]; // [esp+6Ch] [ebp-118h] BYREF
  char v42; // [esp+77h] [ebp-10Dh]
  _DWORD v43[2]; // [esp+78h] [ebp-10Ch] BYREF
  float v44[3]; // [esp+80h] [ebp-104h] BYREF
  char v45; // [esp+8Eh] [ebp-F6h]
  char v46; // [esp+8Fh] [ebp-F5h]
  int v47[2]; // [esp+90h] [ebp-F4h] BYREF
  int v48[9]; // [esp+98h] [ebp-ECh] BYREF
  char v49; // [esp+BCh] [ebp-C8h]
  char v50; // [esp+BDh] [ebp-C7h]
  char v51; // [esp+BEh] [ebp-C6h]
  char v52; // [esp+BFh] [ebp-C5h]
  int v53; // [esp+C0h] [ebp-C4h]
  float float_versioned; // [esp+C4h] [ebp-C0h]
  float v55; // [esp+C8h] [ebp-BCh]
  char v56; // [esp+CFh] [ebp-B5h]
  int v57; // [esp+D0h] [ebp-B4h]
  char v58; // [esp+D7h] [ebp-ADh]
  char v59; // [esp+D8h] [ebp-ACh]
  char v60; // [esp+D9h] [ebp-ABh]
  char v61; // [esp+DAh] [ebp-AAh]
  char v62; // [esp+DBh] [ebp-A9h]
  int v63[2]; // [esp+DCh] [ebp-A8h] BYREF
  int v64[2]; // [esp+E4h] [ebp-A0h] BYREF
  int v65; // [esp+ECh] [ebp-98h]
  int v66[2]; // [esp+F0h] [ebp-94h] BYREF
  unsigned __int8 v67; // [esp+FBh] [ebp-89h]
  int v68; // [esp+FCh] [ebp-88h]
  int v69[2]; // [esp+100h] [ebp-84h] BYREF
  char v70; // [esp+10Ah] [ebp-7Ah]
  char v71; // [esp+10Bh] [ebp-79h]
  int v72[2]; // [esp+10Ch] [ebp-78h] BYREF
  int v73[2]; // [esp+114h] [ebp-70h] BYREF
  char v74; // [esp+11Fh] [ebp-65h]
  int v75; // [esp+120h] [ebp-64h]
  int v76; // [esp+124h] [ebp-60h]
  int v77[2]; // [esp+128h] [ebp-5Ch] BYREF
  char v78; // [esp+132h] [ebp-52h]
  char v79; // [esp+133h] [ebp-51h]
  int v80; // [esp+134h] [ebp-50h]
  int v81[2]; // [esp+138h] [ebp-4Ch] BYREF
  char bool_versioned; // [esp+142h] [ebp-42h]
  char v83; // [esp+143h] [ebp-41h]
  int i; // [esp+144h] [ebp-40h]
  int int32_versioned; // [esp+148h] [ebp-3Ch]
  int v86; // [esp+14Ch] [ebp-38h]
  int v87[2]; // [esp+150h] [ebp-34h] BYREF
  int v88[2]; // [esp+158h] [ebp-2Ch] BYREF
  char v89; // [esp+163h] [ebp-21h]
  int v90; // [esp+164h] [ebp-20h]
  char v91; // [esp+16Ah] [ebp-1Ah]
  unsigned __int8 byte_versioned; // [esp+16Bh] [ebp-19h]
  int v93[2]; // [esp+16Ch] [ebp-18h] BYREF
  char v94; // [esp+175h] [ebp-Fh]
  char v95; // [esp+176h] [ebp-Eh]
  char v96; // [esp+177h] [ebp-Dh]
  int v97; // [esp+180h] [ebp-4h]

  rf_string_construct_empty(v47);
  v97 = 0;
  rf_string_construct_empty(v72);
  LOBYTE(v97) = 1;
  rf_string_construct_empty(v66);
  LOBYTE(v97) = 2;
  rf_string_construct_empty(v63);
  LOBYTE(v97) = 3;
  rf_string_construct_empty(v41);
  LOBYTE(v97) = 4;
  rf_string_construct_empty(v64);
  LOBYTE(v97) = 5;
  rf_string_construct_empty(v43);
  LOBYTE(v97) = 6;
  rf_string_construct_empty(v69);
  LOBYTE(v97) = 7;
  rf_string_construct_empty(v77);
  LOBYTE(v97) = 8;
  rf_string_construct_empty(v87);
  LOBYTE(v97) = 9;
  rf_string_construct_empty(v88);
  LOBYTE(v97) = 10;
  rf_string_construct_empty(v73);
  LOBYTE(v97) = 11;
  rf_vector3_default_construct_noop(v44);
  rf_matrix3_construct((char *)v48);
  rf_string_construct_empty(v81);
  LOBYTE(v97) = 12;
  rf_string_construct_empty(v93);
  LOBYTE(v97) = 13;
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    v53 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, v72, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, v44, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned((char *)v48, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a1, v47, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v75 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v90 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    v40 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, v81, 0, nullptr);
    rf_binary_stream_read_string_object_versioned(a1, v93, 0, nullptr);
    bool_versioned = rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v58 = rf_binary_stream_read_bool_versioned(a1, 0, 1);
    v56 = rf_binary_stream_read_bool_versioned(a1, 54, 0);
    v45 = rf_binary_stream_read_bool_versioned(a1, 64, 0);
    v50 = rf_binary_stream_read_bool_versioned(a1, 70, 0);
    v51 = rf_binary_stream_read_bool_versioned(a1, 72, 0);
    v80 = rf_binary_stream_read_int32_versioned(a1, 72, 0);
    v68 = rf_binary_stream_read_int32_versioned(a1, 72, 0);
    v60 = rf_binary_stream_read_bool_versioned(a1, 76, 0);
    if ( rf_vfile_get_slot_version(a1) < 144 )
      v30[3] = rf_binary_stream_read_int32_versioned(a1, 76, 0);
    v94 = rf_binary_stream_read_bool_versioned(a1, 114, 0);
    v46 = rf_binary_stream_read_bool_versioned(a1, 116, 0);
    float_versioned = rf_binary_stream_read_float_versioned(a1, 102, -1.0);
    v55 = rf_binary_stream_read_float_versioned(a1, 158, -1.0);
    v76 = rf_binary_stream_read_int32_versioned(a1, 139, 180);
    rf_binary_stream_read_string_object_versioned(a1, v66, 0, nullptr);
    rf_binary_stream_read_string_object_versioned(a1, v63, 0, nullptr);
    rf_binary_stream_read_string_object_versioned(a1, v41, 0, nullptr);
    rf_binary_stream_read_string_object_versioned(a1, v64, 0, nullptr);
    rf_binary_stream_read_string_object_versioned(a1, v87, 80, (char *)&byte_6387F7);
    rf_binary_stream_read_string_object_versioned(a1, v77, 80, (char *)&byte_638825);
    rf_binary_stream_read_string_object_versioned(a1, v69, 136, (char *)&byte_638826);
    byte_versioned = rf_binary_stream_read_byte_versioned(a1, 64, 0);
    v67 = rf_binary_stream_read_byte_versioned(a1, 64, 0);
    rf_rfl_discard_legacy_object_entries(a1);
    v65 = rf_binary_stream_read_int32_versioned(a1, 98, -1);
    v57 = rf_binary_stream_read_int32_versioned(a1, 116, -1);
    v86 = rf_binary_stream_read_int32_versioned(a1, 150, -1);
    v83 = rf_binary_stream_read_bool_versioned(a1, 127, 0);
    v59 = rf_binary_stream_read_bool_versioned(a1, 130, 0);
    v95 = rf_binary_stream_read_bool_versioned(a1, 130, 0);
    v70 = rf_binary_stream_read_bool_versioned(a1, 130, 0);
    v52 = rf_binary_stream_read_bool_versioned(a1, 130, 0);
    v89 = rf_binary_stream_read_bool_versioned(a1, 130, 0);
    v91 = rf_binary_stream_read_bool_versioned(a1, 158, 1);
    v42 = rf_binary_stream_read_bool_versioned(a1, 158, 0);
    v78 = rf_binary_stream_read_bool_versioned(a1, 159, 0);
    v74 = rf_binary_stream_read_bool_versioned(a1, 161, 0);
    v71 = rf_binary_stream_read_bool_versioned(a1, 162, 0);
    v61 = rf_binary_stream_read_bool_versioned(a1, 162, 0);
    v79 = rf_binary_stream_read_bool_versioned(a1, 164, 0);
    v62 = rf_binary_stream_read_bool_versioned(a1, 168, 0);
    if ( rf_vfile_get_slot_version(a1) >= 131 && rf_vfile_get_slot_version(a1) < 169 )
      v30[2] = (unsigned __int8)rf_binary_stream_read_byte_versioned(a1, 131, 0);
    v49 = rf_binary_stream_read_bool_versioned(a1, 169, 0);
    v96 = rf_binary_stream_read_bool_versioned(a1, 169, 0);
    v35 = 0;
    v39 = 15.0;
    v35 = rf_binary_stream_read_bool_versioned(a1, 148, 0);
    if ( v35 == 1 )
      v39 = rf_binary_stream_read_float_versioned(a1, 148, 15.0);
    rf_binary_stream_read_string_object_versioned(a1, v88, 154, "none");
    rf_binary_stream_read_string_object_versioned(a1, v73, 154, "none");
    if ( rf_vfile_get_slot_version(a1) >= 157 && rf_vfile_get_slot_version(a1) < 169 )
    {
      rf_string_construct_empty(v30);
      LOBYTE(v97) = 14;
      rf_binary_stream_read_string_object_versioned(a1, v30, 157, "no longer used");
      LOBYTE(v97) = 13;
      rf_string_destroy_buffer(v30);
    }
    v1 = (char *)rf_string_object_c_str_or_empty(v72);
    v36 = sub_431680(v1);
    if ( v36 >= 0 )
    {
      v31 = 0;
      if ( v59 )
        v31 |= 2u;
      if ( v96 )
        v31 |= 4u;
      if ( !rf_multiplayer_runtime_mode || !rf_entity_definition_field436_is_one(v36) )
      {
        v19 = v31;
        v2 = (char *)rf_string_object_c_str_or_empty(v47);
        runtime = rf_entity_create_runtime(v36, v2, -1, v44, (float *)v48, v19, -1);
        if ( runtime )
        {
          *(_DWORD *)(runtime + 5228) = -1;
          if ( rf_string_equals_case_insensitive((int)v72, "masako_fighter") )
          {
            v3 = rf_string_object_c_str_or_empty(unk_6FC300);
            if ( !_stricmp(v3, "l20s2.rfl") )
            {
              v29 = sub_431680("masako");
              if ( v29 > -1 )
              {
                v28 = rf_entity_create_runtime(v29, "masako_endgame", -1, v44, (float *)v48, 2, -1);
                if ( v28 )
                {
                  *(_DWORD *)(runtime + 5228) = *(_DWORD *)(v28 + 44);
                  *(_DWORD *)(v28 + 2068) |= 0x10u;
                  *(_BYTE *)(v28 + 1992) = 1;
                  *(float *)(v28 + 1996) = 10.0;
                  *(_DWORD *)(*(_DWORD *)(v28 + 660) + 1832) |= 0x100u;
                }
              }
            }
          }
          if ( rf_string_equals_case_insensitive((int)v72, (char *)off_638934) )
          {
            v4 = rf_string_object_c_str_or_empty(unk_6FC300);
            if ( !_stricmp(v4, "l11s3.rfl") )
              *(_DWORD *)(*(_DWORD *)(runtime + 660) + 1832) |= 0x200u;
          }
          if ( float_versioned != -1.0 )
          {
            *(float *)(runtime + 52) = float_versioned;
            rf_float_clamp_in_place((float *)(runtime + 52), 0.0, *(float *)(*(_DWORD *)(runtime + 660) + 68));
          }
          if ( v55 != -1.0 )
          {
            *(float *)(runtime + 56) = v55;
            rf_float_clamp_in_place((float *)(runtime + 56), 0.0, *(float *)(*(_DWORD *)(runtime + 660) + 72));
          }
          v20 = (double)v76 * 3.141592741012573 / 180.0 / 2.0;
          v5 = rf_cos_float(v20);
          *(float *)(runtime + 2112) = v5;
          *(_BYTE *)(runtime + 40) = v40;
          *(_DWORD *)(runtime + 1308) = v75;
          *(_DWORD *)(runtime + 504) = v90;
          *(_DWORD *)(runtime + 32) = v53;
          if ( (int)rf_string_length_from_cstr((const char **)v81) > 0 )
          {
            v6 = (char *)rf_string_object_c_str_or_empty(v93);
            v27 = sub_487370(v6);
            v7 = (char *)rf_string_object_c_str_or_empty(v81);
            v8 = sub_487150(v7);
            *(_DWORD *)(runtime + 1864) = v8;
            *(_DWORD *)(runtime + 1868) = v27;
          }
          if ( v83 == 1 )
            *(_DWORD *)(runtime + 2064) |= 0x100000u;
          if ( v95 == 1 )
            *(_DWORD *)(runtime + 2064) |= 0x200000u;
          if ( v70 == 1 )
            *(_DWORD *)(runtime + 2064) |= 0x400000u;
          if ( v52 == 1 )
            *(_DWORD *)(runtime + 2064) |= (unsigned int)&unk_800000;
          if ( v89 == 1 )
            *(_DWORD *)(runtime + 2064) |= (unsigned int)&unk_1000000;
          if ( v49 == 1 )
            *(_DWORD *)(runtime + 2064) |= 0x4000000u;
          if ( v91 == 1 )
            *(_DWORD *)(runtime + 2068) |= 1u;
          if ( v42 == 1 )
            *(_DWORD *)(runtime + 2068) |= 2u;
          if ( v78 == 1 )
            *(_DWORD *)(runtime + 2068) |= 0x80000000;
          if ( v74 == 1 )
            *(_DWORD *)(runtime + 2068) |= 4u;
          if ( v71 == 1 )
            *(_DWORD *)(runtime + 2068) |= 8u;
          if ( v61 == 1 )
            *(_DWORD *)(runtime + 2068) |= 0x10u;
          if ( v79 )
            *(_DWORD *)(runtime + 2068) |= 0x80u;
          if ( v62 )
            *(_DWORD *)(runtime + 2068) |= 0x200u;
          if ( v91 == 1 )
            *(_DWORD *)(runtime + 2068) |= 1u;
          if ( v42 == 1 )
            *(_DWORD *)(runtime + 2068) |= 2u;
          if ( v58 == 1 )
            *(_DWORD *)(runtime + 2064) |= 0x10000u;
          if ( rf_object_is_use_vehicle((_DWORD *)runtime) )
          {
            if ( v58 == 1 )
              rf_entity_enable_headlamp_recursive((_DWORD *)runtime);
            else
              rf_entity_disable_headlamp_recursive((_DWORD *)runtime);
          }
          v37 = rf_set_ai_mode_option_translation[byte_versioned];
          v38 = 0;
          if ( v37 == 2 && rf_string_equals_case_insensitive(*(_DWORD *)(runtime + 660), "camera2") )
            v37 = 15;
          sub_40A260(runtime + 672, v37, v38);
          sub_40A2A0((int *)(runtime + 672));
          *(_DWORD *)(runtime + 1896) = v57;
          *(_DWORD *)(runtime + 1900) = v86;
          if ( v50 == 1 )
            rf_ai_initialize_holstered_pending_state(runtime + 672);
          if ( v51 == 1 )
            *(_DWORD *)(runtime + 2000) |= 0x800u;
          if ( v94 == 1 )
            *(_DWORD *)(runtime + 2064) |= 0x40000u;
          if ( v60 == 1 )
            *(_DWORD *)(runtime + 2000) |= 0x1000u;
          *(_DWORD *)(runtime + 1360) = v80;
          *(_DWORD *)(runtime + 1356) = v68;
          if ( v56 == 1 )
          {
            *(_DWORD *)(runtime + 2064) |= 0x10u;
            *(_DWORD *)(runtime + 2000) |= 1u;
            *(_DWORD *)(runtime + 2000) &= ~0x100u;
          }
          if ( v45 == 1 )
            *(_DWORD *)(runtime + 2000) |= 0x80u;
          if ( dword_66255C[v67] != -1 )
            *(_DWORD *)(runtime + 1856) = dword_66255C[v67];
          if ( rf_string_equals_case_insensitive((int)v66, "none") )
          {
            for ( j = 0; j < dword_911C7C; ++j )
              *(_BYTE *)(i + runtime + 1068) = 0;
            *(_DWORD *)(runtime + 676) = -1;
          }
          else
          {
            if ( rf_string_equals_case_insensitive((int)v66, "glock") )
              rf_string_assign_from_cstr(v66, "12mm handgun");
            v9 = (char *)rf_string_object_c_str_or_empty(v66);
            v34 = sub_50FB80(v9);
            if ( v34 != -1 )
            {
              rf_entity_inventory_grant_weapon((int *)(runtime + 672), v34, -1);
              if ( dword_912024[340 * v34] >= 0 )
                *(_DWORD *)(runtime + 4 * dword_912024[340 * v34] + 684) = unk_912260[340 * v34];
              *(_DWORD *)(runtime + 676) = v34;
              if ( v34 == rf_weapon_id_rocket_launcher )
                *(_DWORD *)(runtime + 4 * dword_912024[340 * v34] + 684) = 3;
            }
          }
          if ( rf_string_equals_case_insensitive((int)v63, "none") )
          {
            for ( j = dword_911C7C; j < dword_911C68; ++j )
              *(_BYTE *)(j + runtime + 1068) = 0;
            *(_DWORD *)(runtime + 680) = -1;
          }
          else
          {
            v10 = (char *)rf_string_object_c_str_or_empty(v63);
            v34 = sub_50FB80(v10);
            if ( v34 != -1 )
            {
              rf_entity_inventory_grant_weapon((int *)(runtime + 672), v34, -1);
              *(_DWORD *)(runtime + 680) = v34;
            }
          }
          *(_BYTE *)(runtime + 1992) = v35;
          *(float *)(runtime + 1996) = v39;
          rf_weapon_preload_impact_vclips(*(_DWORD *)(runtime + 676));
          rf_weapon_preload_impact_vclips(*(_DWORD *)(runtime + 680));
          rf_entity_restore_action_tables_and_apply_weapon_overrides(runtime, *(_DWORD *)(runtime + 676));
          if ( rf_string_equals_case_insensitive((int)v41, "none") )
          {
            *(_DWORD *)(runtime + 2092) = -1;
          }
          else
          {
            v11 = (char *)rf_string_object_c_str_or_empty(v41);
            v12 = rf_item_definition_find_by_name(v11);
            *(_DWORD *)(runtime + 2092) = v12;
          }
          if ( rf_string_equals_case_insensitive((int)v64, "none") )
          {
            *(_DWORD *)(runtime + 2100) = -1;
          }
          else
          {
            v13 = (char *)rf_string_object_c_str_or_empty(v64);
            canonical_index = rf_body_state_find_canonical_index(v13);
            *(_DWORD *)(runtime + 2100) = canonical_index;
          }
          if ( rf_rf_string_not_equals_cstring_case_insensitive((int)v77, (char *)&byte_638827) )
          {
            v15 = (char *)rf_string_object_c_str_or_empty(v77);
            rf_entity_apply_named_skin_profile(runtime, v15);
          }
          if ( rf_rf_string_not_equals_cstring_case_insensitive((int)v87, (char *)&byte_638842) )
          {
            *(_DWORD *)(runtime + 2068) |= 2u;
            rf_rgba8_default_construct_noop(&v25);
            rf_object_sample_ground_light_color(&v25, runtime);
            v16 = (char *)rf_string_object_c_str_or_empty(v87);
            v26 = (_DWORD *)rf_corpse_create_from_entity(runtime, v16, v44, (float *)v48, 1, 1);
            if ( v26 )
            {
              v26[182] = v25;
              v26[8] = *(_DWORD *)(runtime + 32);
              *(_DWORD *)(runtime + 32) = -1;
              rf_object_reactivate_from_respawn(v26);
            }
          }
          rf_string_assign_from_object((_DWORD *)(*(_DWORD *)(runtime + 660) + 32), (int)v69);
          *(_DWORD *)(runtime + 1872) = v65;
          if ( rf_rf_string_not_equals_cstring_case_insensitive((int)v88, "none") )
          {
            v17 = (char *)rf_string_object_c_str_or_empty(v88);
            index_by_name = rf_clutter_class_find_index_by_name(v17);
            v23 = rf_clutter_runtime_create(
                    index_by_name,
                    (char *)&byte_638843,
                    -1,
                    (float *)(runtime + 60),
                    (float *)(runtime + 72),
                    0);
            if ( v23 )
              *(_DWORD *)(runtime + 5212) = v23[11];
          }
          if ( rf_rf_string_not_equals_cstring_case_insensitive((int)v73, "none") )
          {
            v18 = (char *)rf_string_object_c_str_or_empty(v73);
            v22 = rf_clutter_class_find_index_by_name(v18);
            v21 = rf_clutter_runtime_create(
                    v22,
                    (char *)&byte_63885E,
                    -1,
                    (float *)(runtime + 60),
                    (float *)(runtime + 72),
                    0);
            if ( v21 )
              *(_DWORD *)(runtime + 5216) = v21[11];
          }
          if ( (*(_DWORD *)(runtime + 124) & 0x4000) != 0 )
            rf_object_mark_hidden_inactive(runtime);
          rf_progress_update_poll_network_and_callback(0, 0);
        }
      }
    }
  }
  LOBYTE(v97) = 12;
  rf_string_destroy_buffer(v93);
  LOBYTE(v97) = 11;
  rf_string_destroy_buffer(v81);
  LOBYTE(v97) = 10;
  rf_string_destroy_buffer(v73);
  LOBYTE(v97) = 9;
  rf_string_destroy_buffer(v88);
  LOBYTE(v97) = 8;
  rf_string_destroy_buffer(v87);
  LOBYTE(v97) = 7;
  rf_string_destroy_buffer(v77);
  LOBYTE(v97) = 6;
  rf_string_destroy_buffer(v69);
  LOBYTE(v97) = 5;
  rf_string_destroy_buffer(v43);
  LOBYTE(v97) = 4;
  rf_string_destroy_buffer(v64);
  LOBYTE(v97) = 3;
  rf_string_destroy_buffer(v41);
  LOBYTE(v97) = 2;
  rf_string_destroy_buffer(v63);
  LOBYTE(v97) = 1;
  rf_string_destroy_buffer(v66);
  LOBYTE(v97) = 0;
  rf_string_destroy_buffer(v72);
  v97 = -1;
  rf_string_destroy_buffer(v47);
}

