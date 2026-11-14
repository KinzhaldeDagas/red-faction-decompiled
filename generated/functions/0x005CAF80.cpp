// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CAF80 rf_scene_definition_read_vsfx_binary
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): Thiscall output scene definition (308-byte allocation proven by caller5B1E30), filename and VFile context; AL1 success/0 failure. Opens mode1 BEFORE checking filename strlen<64, then copies filename including NUL into receiver0. Reads exact case-sensitive signature VSFX and signed version; version<0x30000 returns0, version0x40000..0x40004 inclusive fatals anim_fx.cpp769 asking re-export, other versions>=0x30000 have no upper bound here. Sets stream version before version-gated header reads. FILE HEADER READ ORDER, destination BYTE offsets:68,132,76,84,100,92,108,116,124,136,144,152,160,[skip4 if version<0x3000A],168,176,184,192,200,208,216,224,232,240,248,256,264,272,280,288,296. Gated defaults:68
// min30008/default0;124 and296 min3000F/default0;136 min40000/default0;144 min40002/default128;152 min40003/default0;160 min40005/default0;208 min3000D/default count76;216 min30009/default count200;224/232/240/248 min30009/default0. Remaining listed reads are unconditional. Minima written in hex. Read helper also returns its supplied default on stream error; header status is NOT checked before allocation, only later at chunk-loop gate/final close. Compatibility overrides: version<40000 sets material count136=1+particle count92+count176; version<40003 sets count152=material count136; version<40005 sets count160=material count136*scalar132 for version>=3000C, else material count136*(scalar132+1), with unchecked32-bit arithmetic. ALLOCATION MAP
// (countOffset:pointerOffset:elementStrideBytes):76:72:292,84:80:180,92:88:220,100:96:172,108:104:224,116:112:148,124:120:144,136:140:200,144:148:4,152:156:4,160:164:4,168:172:144,176:180:4,184:188:44,192:196:4,200:204:40,208:212:4,216:220:40,224:228:20,232:236:40,240:244:20,248:252:40,256:260:36,264:268:28,272:276:52,280:284:48,288:292:28,296:300:8. Signed count<=0 selects NULL without rejecting file. Cookie arrays add4-byte count header for pointers72,80,88,96,104,112,120,140,204,212,228,260,268,276,284 and use compiler multiplication/addition overflow guards; other raw pools use unchecked size products. No common allocation-success gate or pre-release of existing receiver pools. Local read contexts borrow these pools and share material/index cursors through pointers to local counters. CHUNKS: loop until signed-position EOF or nonzero stream status; reads tag DWORD and signed
// payload-size DWORD. Little-endian FourCC dispatch: SFXO and CHNE share292-byte model pool72/cursor, calling5B2960 and5B4B30 respectively; ALGT uses point180 pool80; PART emitter220 pool88; DMMY transform172 pool96; WARP channel224 pool104; CMRA range148 pool112; SELS reference144 pool120; MATL material200 pool140. Each scene-node chunk writes owner pointer+132 before subreader. MMOD allocates140-byte binding, overwrites receiver128, assigns owner+132 and calls binding reader; repeated MMOD can lose previous binding. Known chunks IGNORE advertised payload size, without skipping leftover or checking over-consumption. Unknown tags, including0, seek signed advertised size relative to current cursor; no size/progress validation. No per-type chunk-count bounds, mandatory-chunk test or final declared-vs-loaded count reconciliation; subreader results not tested at dispatch. Four final
// version-query results are discarded. Postprocess always applies5CD9D0 visibility flags, clears receiver304 bit0, then walks DECLARED model count. For each model material ref (count+188,list+192), material byte8 nonzero ORs model flags+276 with1000h then BREAKS material loop; otherwise texture handle material+16>=0 with resolved format4/5/7 ORs2000h and continues. Indices/pointers unchecked. Constructor5B2710 leaves model188/192 untouched, so missing model chunks can expose uninitialized refs in this pass. Final explicit close status0 yields AL1, nonzero yields0; EOF alone does not prove all records read. Normal false-return paths destroy only local no-op contexts and VFile (close-if-open), NOT scene-owned completed allocations; fields/flags/pools can remain partially changed. Caller5B1E30 converts false to fatal; direct reuse requires external ownership handling.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, SFXO/CHNE model wire layout, signed vertex unpacking, vector-return ABI, shared pools and key/geometry conversions): Additional SFXO/CHNE dispatch verification: CHNE5B4B30 sets faceCount180=0 and subtype140=1 but NEVER initializes material-reference count188 or pointer192. Model constructor5B2710 also leaves these fields untouched. Outer postprocess reads them for EVERY declared model slot, so CHNE slots as well as missing-model chunks can expose retained storage values; zero material count is not established by faceCount0. SFXO5B2960 does initialize count188 and pointer192. Both readers trust shared120-byte pool cursors, return void, ignore per-read failure status and lack payload-length bounds. Key counts32 are truncated to unsigned16, geometry sizes use unchecked products, and keyed-transform/vertex-animation flag
// combinations are not validated. This supplements existing full VSFX loader/header contract; no executable bytes changed.
char __thiscall rf_scene_definition_read_vsfx_binary(int *this, char *Str, char *a3)
{
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // [esp+4h] [ebp-530h]
  char *v21; // [esp+Ch] [ebp-528h]
  char *v22; // [esp+10h] [ebp-524h]
  char *v23; // [esp+14h] [ebp-520h]
  char *v24; // [esp+18h] [ebp-51Ch]
  char *v25; // [esp+1Ch] [ebp-518h]
  char *v26; // [esp+20h] [ebp-514h]
  char *v27; // [esp+24h] [ebp-510h]
  char *v28; // [esp+28h] [ebp-50Ch]
  char *v29; // [esp+2Ch] [ebp-508h]
  char *v30; // [esp+30h] [ebp-504h]
  char *v31; // [esp+34h] [ebp-500h]
  char *v32; // [esp+38h] [ebp-4FCh]
  char *v33; // [esp+3Ch] [ebp-4F8h]
  char *v34; // [esp+40h] [ebp-4F4h]
  char *v35; // [esp+44h] [ebp-4F0h]
  char *v36; // [esp+48h] [ebp-4ECh]
  char *v37; // [esp+4Ch] [ebp-4E8h]
  char *v38; // [esp+50h] [ebp-4E4h]
  char *v39; // [esp+54h] [ebp-4E0h]
  char *v40; // [esp+58h] [ebp-4DCh]
  char *v41; // [esp+5Ch] [ebp-4D8h]
  char *v42; // [esp+60h] [ebp-4D4h]
  char v43; // [esp+67h] [ebp-4CDh]
  int *v44; // [esp+6Ch] [ebp-4C8h]
  char *v45; // [esp+70h] [ebp-4C4h]
  void *v47; // [esp+8Ch] [ebp-4A8h]
  char *v48; // [esp+98h] [ebp-49Ch]
  int v49; // [esp+A0h] [ebp-494h]
  char *v50; // [esp+A4h] [ebp-490h]
  int v51; // [esp+ACh] [ebp-488h]
  char *v52; // [esp+B0h] [ebp-484h]
  int v53; // [esp+B8h] [ebp-47Ch]
  char *v54; // [esp+BCh] [ebp-478h]
  int v55; // [esp+C4h] [ebp-470h]
  char *v56; // [esp+C8h] [ebp-46Ch]
  int v57; // [esp+D0h] [ebp-464h]
  char *v58; // [esp+D4h] [ebp-460h]
  int v59; // [esp+DCh] [ebp-458h]
  char *v60; // [esp+E0h] [ebp-454h]
  int v61; // [esp+E8h] [ebp-44Ch]
  char *v62; // [esp+ECh] [ebp-448h]
  int v63; // [esp+F4h] [ebp-440h]
  char *v64; // [esp+F8h] [ebp-43Ch]
  int v65; // [esp+100h] [ebp-434h]
  char *v66; // [esp+104h] [ebp-430h]
  int v67; // [esp+10Ch] [ebp-428h]
  char *v68; // [esp+110h] [ebp-424h]
  int v69; // [esp+118h] [ebp-41Ch]
  char *v70; // [esp+11Ch] [ebp-418h]
  int v71; // [esp+124h] [ebp-410h]
  char *v72; // [esp+12Ch] [ebp-408h]
  int v73; // [esp+134h] [ebp-400h]
  char *v74; // [esp+13Ch] [ebp-3F8h]
  int v75; // [esp+144h] [ebp-3F0h]
  char *v76; // [esp+154h] [ebp-3E0h]
  int v77; // [esp+15Ch] [ebp-3D8h]
  char *v78; // [esp+160h] [ebp-3D4h]
  int v79; // [esp+168h] [ebp-3CCh]
  char *v80; // [esp+16Ch] [ebp-3C8h]
  int v81; // [esp+174h] [ebp-3C0h]
  char *v82; // [esp+178h] [ebp-3BCh]
  int v83; // [esp+180h] [ebp-3B4h]
  char *v84; // [esp+184h] [ebp-3B0h]
  int v85; // [esp+18Ch] [ebp-3A8h]
  char *v86; // [esp+190h] [ebp-3A4h]
  int v87; // [esp+198h] [ebp-39Ch]
  char *v88; // [esp+19Ch] [ebp-398h]
  int v89; // [esp+1A4h] [ebp-390h]
  char *v90; // [esp+1A8h] [ebp-38Ch]
  int v91; // [esp+1B0h] [ebp-384h]
  signed int v92; // [esp+1BCh] [ebp-378h]
  int j; // [esp+1C0h] [ebp-374h]
  _DWORD *v94; // [esp+1C4h] [ebp-370h]
  int i; // [esp+1C8h] [ebp-36Ch]
  int Offset; // [esp+1D0h] [ebp-364h]
  int v97; // [esp+1D4h] [ebp-360h]
  char Buffer[260]; // [esp+1D8h] [ebp-35Ch] BYREF
  char Str1[4]; // [esp+2DCh] [ebp-258h] BYREF
  int v100; // [esp+2E0h] [ebp-254h]
  int v101; // [esp+2E4h] [ebp-250h] BYREF
  _DWORD v102[2]; // [esp+2E8h] [ebp-24Ch] BYREF
  _DWORD v103[6]; // [esp+2F0h] [ebp-244h] BYREF
  int self[70]; // [esp+308h] [ebp-22Ch] BYREF
  int v105; // [esp+424h] [ebp-110h]
  int v106; // [esp+428h] [ebp-10Ch]
  int v107; // [esp+42Ch] [ebp-108h]
  int int32_versioned; // [esp+430h] [ebp-104h]
  int v109; // [esp+434h] [ebp-100h]
  _DWORD v110[6]; // [esp+438h] [ebp-FCh] BYREF
  int v111; // [esp+450h] [ebp-E4h] BYREF
  int v112[2]; // [esp+454h] [ebp-E0h] BYREF
  int v113; // [esp+45Ch] [ebp-D8h]
  unsigned int context[30]; // [esp+460h] [ebp-D4h] BYREF
  _DWORD v115[10]; // [esp+4D8h] [ebp-5Ch] BYREF
  int v116; // [esp+500h] [ebp-34h]
  int v117; // [esp+504h] [ebp-30h] BYREF
  _DWORD v118[2]; // [esp+508h] [ebp-2Ch] BYREF
  _DWORD v119[2]; // [esp+510h] [ebp-24h] BYREF
  int v120; // [esp+518h] [ebp-1Ch] BYREF
  _DWORD v121[2]; // [esp+51Ch] [ebp-18h] BYREF
  int v122; // [esp+524h] [ebp-10h]
  int v123; // [esp+530h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v123 = 0;
  v109 = 0;
  v116 = 0;
  v105 = 0;
  v100 = 0;
  v107 = 0;
  v113 = 0;
  v106 = 0;
  v120 = 0;
  v117 = 0;
  v111 = 0;
  v101 = 0;
  rf_scene_model_read_context120_construct_zero(context);
  LOBYTE(v123) = 1;
  rf_two_dword_construct_zero_413790(v119);
  LOBYTE(v123) = 2;
  rf_two_dword_construct_zero_413790(v121);
  LOBYTE(v123) = 3;
  rf_scene_pool_counters_construct_zero(v115);
  LOBYTE(v123) = 4;
  rf_two_dword_construct_zero_413790(v118);
  LOBYTE(v123) = 5;
  rf_two_dword_construct_zero_413790(v102);
  LOBYTE(v123) = 6;
  rf_scene_two_dword_cursor_construct_zero(v112);
  LOBYTE(v123) = 7;
  rf_scene_material_pool_cursors_construct_empty(v110);
  LOBYTE(v123) = 8;
  rf_scene_material_index_context24_construct_zero(v103);
  LOBYTE(v123) = 9;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, a3) < 0 || strlen(Str) >= 0x40 )
  {
    LOBYTE(v123) = 8;
    rf_scene_material_index_context_destruct_noop();
    LOBYTE(v123) = 7;
    rf_scene_material_cursor_context_destruct_noop();
    LOBYTE(v123) = 6;
    rf_scene_reference_cursor_destruct_noop();
    LOBYTE(v123) = 5;
    rf_shared_noop_destructor_4580d0();
    LOBYTE(v123) = 4;
    rf_shared_noop_destructor_4580d0();
    LOBYTE(v123) = 3;
    rf_scene_pool_element_destroy_noop();
    LOBYTE(v123) = 2;
    rf_shared_noop_destructor_4580d0();
    LOBYTE(v123) = 1;
    rf_shared_noop_destructor_4580d0();
    LOBYTE(v123) = 0;
    rf_shared_noop_destructor_4580d0();
    v123 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
  v45 = Str;
  v44 = this;
  do
  {
    v43 = *v45;
    *(_BYTE *)v44 = *v45++;
    v44 = (int *)((char *)v44 + 1);
  }
  while ( v43 );
  rf_vfile_read_buffered_bytes_versioned(self, Str1, 4u, 0, 0);
  if ( strncmp(Str1, "VSFX", 4u) )
    goto LABEL_221;
  int32_versioned = rf_binary_stream_read_int32_versioned(self, 0, 0);
  if ( int32_versioned < 196608 )
    goto LABEL_221;
  if ( int32_versioned >= 0x40000 && int32_versioned <= 262148 )
  {
    sprintf(Buffer, "Incompatible .vfx version. Please re-export \"%s\".\n", Str);
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\geom\\anim_fx.cpp", 769, Buffer);
  }
  rf_vfile_set_open_slot_version(self, int32_versioned);
  *(this + 17) = rf_binary_stream_read_int32_versioned(self, 196616, 0);
  *(this + 33) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 19) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 21) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 25) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 23) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 27) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 29) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 31) = rf_binary_stream_read_int32_versioned(self, 196623, 0);
  *(this + 34) = rf_binary_stream_read_int32_versioned(self, 0x40000, 0);
  *(this + 36) = rf_binary_stream_read_int32_versioned(self, 262146, 128);
  *(this + 38) = rf_binary_stream_read_int32_versioned(self, 262147, 0);
  *(this + 40) = rf_binary_stream_read_int32_versioned(self, 262149, 0);
  if ( !rf_binary_stream_version_at_least(self, 196618) )
    rf_vfile_seek(self, 4, 1);
  *(this + 42) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 44) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 46) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 48) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 50) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 52) = rf_binary_stream_read_int32_versioned(self, 196621, *(this + 19));
  *(this + 54) = rf_binary_stream_read_int32_versioned(self, 196617, *(this + 50));
  *(this + 56) = rf_binary_stream_read_int32_versioned(self, 196617, 0);
  *(this + 58) = rf_binary_stream_read_int32_versioned(self, 196617, 0);
  *(this + 60) = rf_binary_stream_read_int32_versioned(self, 196617, 0);
  *(this + 62) = rf_binary_stream_read_int32_versioned(self, 196617, 0);
  *(this + 64) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 66) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 68) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 70) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 72) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 74) = rf_binary_stream_read_int32_versioned(self, 196623, 0);
  if ( !rf_binary_stream_version_at_least(self, 0x40000) )
  {
    *(this + 34) = 0;
    *(this + 34) += *(this + 23);
    ++*(this + 34);
    *(this + 34) += *(this + 44);
  }
  if ( !rf_binary_stream_version_at_least(self, 262147) )
    *(this + 38) = *(this + 34);
  if ( !rf_binary_stream_version_at_least(self, 262149) )
  {
    if ( rf_binary_stream_version_at_least(self, 196620) )
      v4 = *(this + 33) * *(this + 34);
    else
      v4 = *(this + 34) * (*(this + 33) + 1);
    *(this + 40) = v4;
  }
  if ( *(this + 19) <= 0 )
  {
    *(this + 18) = 0;
  }
  else
  {
    v91 = *(this + 19);
    v5 = (292 * (unsigned __int64)(unsigned int)v91) >> 32 != 0 ? -1 : 292 * v91;
    v90 = (char *)operator new(__CFADD__(v5, 4) ? -1 : v5 + 4);
    LOBYTE(v123) = 10;
    if ( v90 )
    {
      *(_DWORD *)v90 = v91;
      `eh vector constructor iterator'(
        v90 + 4,
        0x124u,
        v91,
        (void (__thiscall *)(void *))rf_scene_model_definition292_construct_defaults,
        (void (__thiscall *)(void *))rf_scene_model_definition292_destroy_arrays);
      v42 = v90 + 4;
    }
    else
    {
      v42 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 18) = (int)v42;
  }
  if ( *(this + 21) <= 0 )
  {
    *(this + 20) = 0;
  }
  else
  {
    v89 = *(this + 21);
    v6 = (180 * (unsigned __int64)(unsigned int)v89) >> 32 != 0 ? -1 : 180 * v89;
    v88 = (char *)operator new(__CFADD__(v6, 4) ? -1 : v6 + 4);
    LOBYTE(v123) = 11;
    if ( v88 )
    {
      *(_DWORD *)v88 = v89;
      `eh vector constructor iterator'(
        v88 + 4,
        0xB4u,
        v89,
        (void (__thiscall *)(void *))rf_scene_point_definition_construct,
        rf_scene_point_definition180_destroy_noop);
      v41 = v88 + 4;
    }
    else
    {
      v41 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 20) = (int)v41;
  }
  if ( *(this + 23) <= 0 )
  {
    *(this + 22) = 0;
  }
  else
  {
    v87 = *(this + 23);
    v7 = (220 * (unsigned __int64)(unsigned int)v87) >> 32 != 0 ? -1 : 220 * v87;
    v86 = (char *)operator new(__CFADD__(v7, 4) ? -1 : v7 + 4);
    LOBYTE(v123) = 12;
    if ( v86 )
    {
      *(_DWORD *)v86 = v87;
      `eh vector constructor iterator'(
        v86 + 4,
        0xDCu,
        v87,
        (void (__thiscall *)(void *))rf_particle_definition_construct,
        rf_particle_definition_destroy_noop);
      v40 = v86 + 4;
    }
    else
    {
      v40 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 22) = (int)v40;
  }
  if ( *(this + 25) <= 0 )
  {
    *(this + 24) = 0;
  }
  else
  {
    v85 = *(this + 25);
    v8 = (172 * (unsigned __int64)(unsigned int)v85) >> 32 != 0 ? -1 : 172 * v85;
    v84 = (char *)operator new(__CFADD__(v8, 4) ? -1 : v8 + 4);
    LOBYTE(v123) = 13;
    if ( v84 )
    {
      *(_DWORD *)v84 = v85;
      `eh vector constructor iterator'(
        v84 + 4,
        0xACu,
        v85,
        (void (__thiscall *)(void *))rf_scene_transform_track_definition_construct,
        rf_scene_transform_track_definition_destruct_noop);
      v39 = v84 + 4;
    }
    else
    {
      v39 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 24) = (int)v39;
  }
  if ( *(this + 27) <= 0 )
  {
    *(this + 26) = 0;
  }
  else
  {
    v83 = *(this + 27);
    v9 = (224 * (unsigned __int64)(unsigned int)v83) >> 32 != 0 ? -1 : 224 * v83;
    v82 = (char *)operator new(__CFADD__(v9, 4) ? -1 : v9 + 4);
    LOBYTE(v123) = 14;
    if ( v82 )
    {
      *(_DWORD *)v82 = v83;
      `eh vector constructor iterator'(
        v82 + 4,
        0xE0u,
        v83,
        (void (__thiscall *)(void *))rf_scene_frame_channel_construct,
        (void (__thiscall *)(void *))rf_scene_frame_channel_unlink_cache);
      v38 = v82 + 4;
    }
    else
    {
      v38 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 26) = (int)v38;
  }
  if ( *(this + 29) <= 0 )
  {
    *(this + 28) = 0;
  }
  else
  {
    v81 = *(this + 29);
    v10 = (148 * (unsigned __int64)(unsigned int)v81) >> 32 != 0 ? -1 : 148 * v81;
    v80 = (char *)operator new(__CFADD__(v10, 4) ? -1 : v10 + 4);
    LOBYTE(v123) = 15;
    if ( v80 )
    {
      *(_DWORD *)v80 = v81;
      `eh vector constructor iterator'(
        v80 + 4,
        0x94u,
        v81,
        (void (__thiscall *)(void *))rf_scene_transform_range_definition_construct,
        rf_scene_transform_range_definition_destruct_noop);
      v37 = v80 + 4;
    }
    else
    {
      v37 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 28) = (int)v37;
  }
  if ( *(this + 31) <= 0 )
  {
    *(this + 30) = 0;
  }
  else
  {
    v79 = *(this + 31);
    v11 = (144 * (unsigned __int64)(unsigned int)v79) >> 32 != 0 ? -1 : 144 * v79;
    v78 = (char *)operator new(__CFADD__(v11, 4) ? -1 : v11 + 4);
    LOBYTE(v123) = 16;
    if ( v78 )
    {
      *(_DWORD *)v78 = v79;
      `eh vector constructor iterator'(
        v78 + 4,
        0x90u,
        v79,
        (void (__thiscall *)(void *))rf_scene_named_reference_list_construct,
        rf_scene_named_reference_list_destruct_noop);
      v36 = v78 + 4;
    }
    else
    {
      v36 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 30) = (int)v36;
  }
  if ( *(this + 34) <= 0 )
  {
    *(this + 35) = 0;
  }
  else
  {
    v77 = *(this + 34);
    v12 = (200 * (unsigned __int64)(unsigned int)v77) >> 32 != 0 ? -1 : 200 * v77;
    v76 = (char *)operator new(__CFADD__(v12, 4) ? -1 : v12 + 4);
    LOBYTE(v123) = 17;
    if ( v76 )
    {
      *(_DWORD *)v76 = v77;
      `eh vector constructor iterator'(
        v76 + 4,
        0xC8u,
        v77,
        (void (__thiscall *)(void *))rf_material_initialize,
        rf_material200_destroy_owned_float_arrays);
      v35 = v76 + 4;
    }
    else
    {
      v35 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 35) = (int)v35;
  }
  if ( *(this + 36) <= 0 )
    *(this + 37) = 0;
  else
    *(this + 37) = (int)operator new(4 * *(this + 36));
  if ( *(this + 38) <= 0 )
    *(this + 39) = 0;
  else
    *(this + 39) = (int)operator new(4 * *(this + 38));
  if ( *(this + 40) <= 0 )
    *(this + 41) = 0;
  else
    *(this + 41) = (int)operator new(4 * *(this + 40));
  if ( *(this + 42) <= 0 )
  {
    *(this + 43) = 0;
  }
  else
  {
    v75 = *(this + 42);
    v74 = (char *)operator new(144 * v75);
    LOBYTE(v123) = 18;
    if ( v74 )
    {
      rf_vector_construct_no_unwind(
        v74,
        0x90u,
        v75,
        (void *(__thiscall *)(void *))rf_scene_record144_construct_vectors_noop);
      v34 = v74;
    }
    else
    {
      v34 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 43) = (int)v34;
  }
  if ( *(this + 44) <= 0 )
    *(this + 45) = 0;
  else
    *(this + 45) = (int)operator new(4 * *(this + 44));
  if ( *(this + 46) <= 0 )
  {
    *(this + 47) = 0;
  }
  else
  {
    v73 = *(this + 46);
    v72 = (char *)operator new(44 * v73);
    LOBYTE(v123) = 19;
    if ( v72 )
    {
      rf_vector_construct_no_unwind(v72, 0x2Cu, v73, rf_scene_record44_construct_vector_noop);
      v33 = v72;
    }
    else
    {
      v33 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 47) = (int)v33;
  }
  if ( *(this + 48) <= 0 )
    *(this + 49) = 0;
  else
    *(this + 49) = (int)operator new(4 * *(this + 48));
  if ( *(this + 50) <= 0 )
  {
    *(this + 51) = 0;
  }
  else
  {
    v71 = *(this + 50);
    v13 = (40 * (unsigned __int64)(unsigned int)v71) >> 32 != 0 ? -1 : 40 * v71;
    v70 = (char *)operator new(__CFADD__(v13, 4) ? -1 : v13 + 4);
    LOBYTE(v123) = 20;
    if ( v70 )
    {
      *(_DWORD *)v70 = v71;
      `eh vector constructor iterator'(
        v70 + 4,
        0x28u,
        v71,
        (void (__thiscall *)(void *))rf_scene_record40_construct_preserving_high_flag,
        (void (__thiscall *)(void *))rf_scene_record40_clear_low31_bits);
      v32 = v70 + 4;
    }
    else
    {
      v32 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 51) = (int)v32;
  }
  if ( *(this + 52) <= 0 )
  {
    *(this + 53) = 0;
  }
  else
  {
    v69 = *(this + 52);
    v14 = (unsigned __int64)(unsigned int)v69 >> 30 != 0 ? -1 : 4 * v69;
    v68 = (char *)operator new(__CFADD__(v14, 4) ? -1 : v14 + 4);
    LOBYTE(v123) = 21;
    if ( v68 )
    {
      *(_DWORD *)v68 = v69;
      `eh vector constructor iterator'(
        v68 + 4,
        4u,
        v69,
        (void (__thiscall *)(void *))rf_record_zero_dword0_construct_5B2390,
        rf_saved_receiver_noop_5B23B0);
      v31 = v68 + 4;
    }
    else
    {
      v31 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 53) = (int)v31;
  }
  if ( *(this + 54) <= 0 )
  {
    *(this + 55) = 0;
  }
  else
  {
    v67 = *(this + 54);
    v66 = (char *)operator new(40 * v67);
    LOBYTE(v123) = 22;
    if ( v66 )
    {
      rf_vector_construct_no_unwind(
        v66,
        0x28u,
        v67,
        (void *(__thiscall *)(void *))rf_scene_pose_vector_record40_construct);
      v30 = v66;
    }
    else
    {
      v30 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 55) = (int)v30;
  }
  if ( *(this + 56) <= 0 )
  {
    *(this + 57) = 0;
  }
  else
  {
    v65 = *(this + 56);
    v15 = (20 * (unsigned __int64)(unsigned int)v65) >> 32 != 0 ? -1 : 20 * v65;
    v64 = (char *)operator new(__CFADD__(v15, 4) ? -1 : v15 + 4);
    LOBYTE(v123) = 23;
    if ( v64 )
    {
      *(_DWORD *)v64 = v65;
      `eh vector constructor iterator'(
        v64 + 4,
        0x14u,
        v65,
        (void (__thiscall *)(void *))rf_scene_key_tracks_construct_empty,
        rf_saved_receiver_noop_5F6F30);
      v29 = v64 + 4;
    }
    else
    {
      v29 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 57) = (int)v29;
  }
  if ( *(this + 58) <= 0 )
  {
    *(this + 59) = 0;
  }
  else
  {
    v63 = *(this + 58);
    v62 = (char *)operator new(40 * v63);
    LOBYTE(v123) = 24;
    if ( v62 )
    {
      rf_vector_construct_no_unwind(
        v62,
        0x28u,
        v63,
        (void *(__thiscall *)(void *))rf_scene_vector_key40_construct_from_global_affine);
      v28 = v62;
    }
    else
    {
      v28 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 59) = (int)v28;
  }
  if ( *(this + 60) <= 0 )
  {
    *(this + 61) = 0;
  }
  else
  {
    v61 = *(this + 60);
    v60 = (char *)operator new(20 * v61);
    LOBYTE(v123) = 25;
    if ( v60 )
    {
      rf_vector_construct_no_unwind(v60, 0x14u, v61, (void *(__thiscall *)(void *))rf_scene_rotation_key20_construct);
      v27 = v60;
    }
    else
    {
      v27 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 61) = (int)v27;
  }
  if ( *(this + 62) <= 0 )
  {
    *(this + 63) = 0;
  }
  else
  {
    v59 = *(this + 62);
    v58 = (char *)operator new(40 * v59);
    LOBYTE(v123) = 26;
    if ( v58 )
    {
      rf_vector_construct_no_unwind(v58, 0x28u, v59, (void *(__thiscall *)(void *))rf_scene_vector_key40_construct);
      v26 = v58;
    }
    else
    {
      v26 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 63) = (int)v26;
  }
  if ( *(this + 64) <= 0 )
  {
    *(this + 65) = 0;
  }
  else
  {
    v57 = *(this + 64);
    v16 = (36 * (unsigned __int64)(unsigned int)v57) >> 32 != 0 ? -1 : 36 * v57;
    v56 = (char *)operator new(__CFADD__(v16, 4) ? -1 : v16 + 4);
    LOBYTE(v123) = 27;
    if ( v56 )
    {
      *(_DWORD *)v56 = v57;
      `eh vector constructor iterator'(
        v56 + 4,
        0x24u,
        v57,
        rf_scene_record36_construct_flag1,
        rf_saved_receiver_noop_5955F0);
      v25 = v56 + 4;
    }
    else
    {
      v25 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 65) = (int)v25;
  }
  if ( *(this + 66) <= 0 )
  {
    *(this + 67) = 0;
  }
  else
  {
    v55 = *(this + 66);
    v17 = (28 * (unsigned __int64)(unsigned int)v55) >> 32 != 0 ? -1 : 28 * v55;
    v54 = (char *)operator new(__CFADD__(v17, 4) ? -1 : v17 + 4);
    LOBYTE(v123) = 28;
    if ( v54 )
    {
      *(_DWORD *)v54 = v55;
      `eh vector constructor iterator'(
        v54 + 4,
        0x1Cu,
        v55,
        (void (__thiscall *)(void *))rf_scene_transform_frame28_construct_quaternion_only,
        rf_saved_receiver_noop_5FAD70);
      v24 = v54 + 4;
    }
    else
    {
      v24 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 67) = (int)v24;
  }
  if ( *(this + 68) <= 0 )
  {
    *(this + 69) = 0;
  }
  else
  {
    v53 = *(this + 68);
    v18 = (52 * (unsigned __int64)(unsigned int)v53) >> 32 != 0 ? -1 : 52 * v53;
    v52 = (char *)operator new(__CFADD__(v18, 4) ? -1 : v18 + 4);
    LOBYTE(v123) = 29;
    if ( v52 )
    {
      *(_DWORD *)v52 = v53;
      `eh vector constructor iterator'(
        v52 + 4,
        0x34u,
        v53,
        (void (__thiscall *)(void *))rf_particle_key52_construct,
        rf_particle_key52_destroy_noop);
      v23 = v52 + 4;
    }
    else
    {
      v23 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 69) = (int)v23;
  }
  if ( *(this + 70) <= 0 )
  {
    *(this + 71) = 0;
  }
  else
  {
    v51 = *(this + 70);
    v19 = (48 * (unsigned __int64)(unsigned int)v51) >> 32 != 0 ? -1 : 48 * v51;
    v50 = (char *)operator new(__CFADD__(v19, 4) ? -1 : v19 + 4);
    LOBYTE(v123) = 30;
    if ( v50 )
    {
      *(_DWORD *)v50 = v51;
      `eh vector constructor iterator'(
        v50 + 4,
        0x30u,
        v51,
        (void (__thiscall *)(void *))rf_scene_frame48_construct_quaternion_only,
        rf_saved_receiver_noop_5F8750);
      v22 = v50 + 4;
    }
    else
    {
      v22 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 71) = (int)v22;
  }
  if ( *(this + 72) <= 0 )
  {
    *(this + 73) = 0;
  }
  else
  {
    v49 = *(this + 72);
    v48 = (char *)operator new(28 * v49);
    LOBYTE(v123) = 31;
    if ( v48 )
    {
      rf_vector_construct_no_unwind(v48, 0x1Cu, v49, (void *(__thiscall *)(void *))rf_scene_pose_key28_construct);
      v21 = v48;
    }
    else
    {
      v21 = nullptr;
    }
    LOBYTE(v123) = 9;
    *(this + 73) = (int)v21;
  }
  if ( *(this + 74) <= 0 )
    *(this + 75) = 0;
  else
    *(this + 75) = (int)operator new(8 * *(this + 74));
  context[1] = *(this + 43);
  context[2] = (unsigned int)&v120;
  context[3] = *(this + 35);
  context[4] = (unsigned int)&v117;
  context[5] = *(this + 37);
  context[6] = (unsigned int)&v111;
  context[7] = *(this + 39);
  context[8] = (unsigned int)&v101;
  context[9] = *(this + 41);
  context[11] = *(this + 45);
  context[13] = *(this + 47);
  context[15] = *(this + 49);
  context[17] = *(this + 51);
  context[19] = *(this + 53);
  context[21] = *(this + 55);
  context[23] = *(this + 57);
  context[25] = *(this + 59);
  context[27] = *(this + 61);
  context[29] = *(this + 63);
  v119[1] = *(this + 65);
  v121[1] = *(this + 67);
  v115[0] = &v120;
  v115[1] = *(this + 35);
  v115[2] = &v117;
  v115[3] = *(this + 37);
  v115[4] = &v111;
  v115[5] = *(this + 39);
  v115[6] = &v101;
  v115[7] = *(this + 41);
  v115[9] = *(this + 69);
  v118[1] = *(this + 71);
  v102[1] = *(this + 73);
  v112[1] = *(this + 75);
  v110[0] = &v120;
  v110[1] = *(this + 35);
  v110[2] = &v117;
  v110[3] = *(this + 37);
  v110[4] = &v111;
  v110[5] = *(this + 39);
  v103[0] = &v117;
  v103[1] = *(this + 37);
  v103[2] = &v111;
  v103[3] = *(this + 39);
  v103[4] = &v101;
  v103[5] = *(this + 41);
  v122 = 0;
  while ( !rf_vfile_is_position_at_or_past_end_signed(self) && !rf_vfile_get_open_slot_status(self) )
  {
    v97 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    Offset = rf_binary_stream_read_int32_versioned(self, 0, 0);
    if ( v97 > 1347567959 )
    {
      if ( v97 > 1414676816 )
      {
        if ( v97 == 1498238276 )
        {
          *(_DWORD *)(*(this + 24) + 172 * v100 + 132) = this;
          rf_scene_transform_track_definition_read_binary(*(this + 24) + 172 * v100++, (int)self, v121);
        }
        else
        {
LABEL_206:
          rf_vfile_seek(self, Offset, 1);
        }
      }
      else
      {
        switch ( v97 )
        {
          case 1414676816:
            *(_DWORD *)(*(this + 22) + 220 * v105 + 132) = this;
            rf_particle_definition_read_versioned(*(this + 22) + 220 * v105++, self, (int)v115);
            break;
          case 1397507411:
            *(_DWORD *)(*(this + 30) + 144 * v106 + 132) = this;
            rf_scene_named_reference_list_read_binary(*(this + 30) + 144 * v106++, self, v112, this);
            break;
          case 1413958721:
            *(_DWORD *)(*(this + 20) + 180 * v116 + 132) = this;
            rf_scene_point_definition_read_binary(*(this + 20) + 180 * v116++, self, v119);
            break;
          default:
            goto LABEL_206;
        }
      }
    }
    else if ( v97 == 1347567959 )
    {
      *(_DWORD *)(*(this + 26) + 224 * v107 + 132) = this;
      rf_scene_frame_channel_read_binary(*(this + 26) + 224 * v107++, (char *)self, v118);
    }
    else if ( v97 > 1162758211 )
    {
      if ( v97 == 1280590157 )
      {
        rf_material_deserialize((char *)(*(this + 35) + 200 * v120++), self, (int)v103);
      }
      else
      {
        if ( v97 != 1331185235 )
          goto LABEL_206;
        *(_DWORD *)(*(this + 18) + 292 * v109 + 132) = this;
        rf_scene_model_definition_read_sfxo_binary((char *)(*(this + 18) + 292 * v109++), self, context);
      }
    }
    else
    {
      switch ( v97 )
      {
        case 1162758211:
          *(_DWORD *)(*(this + 18) + 292 * v109 + 132) = this;
          rf_scene_model_definition_read_chne_binary((char *)(*(this + 18) + 292 * v109++), self, context);
          ++v122;
          break;
        case 1095912771:
          *(_DWORD *)(*(this + 28) + 148 * v113 + 132) = this;
          rf_scene_transform_range_read_binary(*(this + 28) + 148 * v113++, self, v102);
          break;
        case 1146047821:
          v47 = operator new(0x8Cu);
          LOBYTE(v123) = 32;
          if ( v47 )
            v20 = rf_scene_material_binding_construct((int)v47);
          else
            v20 = 0;
          LOBYTE(v123) = 9;
          *(this + 32) = v20;
          *(_DWORD *)(*(this + 32) + 132) = this;
          rf_scene_material_binding_read_index_or_legacy((_DWORD *)*(this + 32), (int)self, (int)v110);
          break;
        default:
          goto LABEL_206;
      }
    }
  }
  rf_binary_stream_version_at_least(self, 0x40000);
  rf_binary_stream_version_at_least(self, 262146);
  rf_binary_stream_version_at_least(self, 262149);
  rf_binary_stream_version_at_least(self, 196621);
  rf_scene_definition_initialize_visibility_control_flags(this);
  *(this + 76) &= ~1u;
  for ( i = 0; i < *(this + 19); ++i )
  {
    v94 = (_DWORD *)(*(this + 18) + 292 * i);
    for ( j = 0; j < v94[47]; ++j )
    {
      if ( *(_BYTE *)(*(this + 35) + 200 * *(_DWORD *)(v94[48] + 4 * j) + 8) )
      {
        v94[69] |= 0x1000u;
        break;
      }
      v92 = *(_DWORD *)(*(this + 35) + 200 * *(_DWORD *)(v94[48] + 4 * j) + 16);
      if ( v92 >= 0 && rf_bitmap_resolved_format_is_4_5_7(v92) )
        v94[69] |= 0x2000u;
    }
  }
  if ( !rf_vfile_close_stdio_or_vpp(self) )
  {
    LOBYTE(v123) = 8;
    rf_scene_material_index_context_destruct_noop();
    LOBYTE(v123) = 7;
    rf_scene_material_cursor_context_destruct_noop();
    LOBYTE(v123) = 6;
    rf_scene_reference_cursor_destruct_noop();
    LOBYTE(v123) = 5;
    rf_shared_noop_destructor_4580d0();
    LOBYTE(v123) = 4;
    rf_shared_noop_destructor_4580d0();
    LOBYTE(v123) = 3;
    rf_scene_pool_element_destroy_noop();
    LOBYTE(v123) = 2;
    rf_shared_noop_destructor_4580d0();
    LOBYTE(v123) = 1;
    rf_shared_noop_destructor_4580d0();
    LOBYTE(v123) = 0;
    rf_shared_noop_destructor_4580d0();
    v123 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 1;
  }
LABEL_221:
  LOBYTE(v123) = 8;
  rf_scene_material_index_context_destruct_noop();
  LOBYTE(v123) = 7;
  rf_scene_material_cursor_context_destruct_noop();
  LOBYTE(v123) = 6;
  rf_scene_reference_cursor_destruct_noop();
  LOBYTE(v123) = 5;
  rf_shared_noop_destructor_4580d0();
  LOBYTE(v123) = 4;
  rf_shared_noop_destructor_4580d0();
  LOBYTE(v123) = 3;
  rf_scene_pool_element_destroy_noop();
  LOBYTE(v123) = 2;
  rf_shared_noop_destructor_4580d0();
  LOBYTE(v123) = 1;
  rf_shared_noop_destructor_4580d0();
  LOBYTE(v123) = 0;
  rf_shared_noop_destructor_4580d0();
  v123 = -1;
  rf_vfile_destruct_close_if_open(self);
  return 0;
}

