// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005888B0 rf_v3c_read_character_resource
// UNREALRED VERIFIED [original-shadow-radius-20261027] V3C MSUB dispatch repeatedly passes the same first allocated mesh slot (pointer at owner+76) to 0x5B8980 -> 0x5B82C0, while incrementing count at +80; it does not advance the destination mesh pointer. Owner+144 selects that first slot. Therefore the last source MSUB supplies the geometry sphere subsequently read by 0x566AC0 -> 0x566A70/0x566AA0. Importers retaining separate source-order MSUB records must use the final record for this native sphere owner.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Forces requested path to .v3c, resets base descriptor, opens virtual file and accepts header word0x5246434D only; other tested signatures also reject (strncmp result in fallback is unused). Forwards second header DWORD to5924C0. Reads counts at+72,+104,+112,+128,+120, one local DWORD,+88(aux100),+96(spheres44). Allocates corresponding pools: meshes144+metadata100 with array cookies, vectors12,records52,materials200,vectors12+index DWORDs,aux100,spheres44. Geometry context borrows shared pools. Chunk dispatch:0x5355424D repeatedly loads into FIRST metadata/mesh pointers, increments loaded-mesh count+80 and sets selected-mesh+144 to first mesh; destination pointers do not advance (last submesh overwrites same slot). 0x424F4E45 invokes character
// bone adapter; false result seeks advertised size relative to current position. 0x43535048 reads next44-byte sphere without count bound. 0x57414954 delegates existing helper;0x44554D42 does no local read/seek; unknown tags seek relative by size; zero tag or EOF ends loop. Closes/destructs stream and returns1 even without validating expected chunk counts. Counts/offsets mostly trusted; only some owning-array size calculations have compiler overflow guards. No source code or bytes patched.
// UNREALRED VERIFIED [combat-panic-bounds-20261104]: Combat navigation bounds and sphere use last source MSUB for character tag2. Each MSUB overwrites same first mesh slot; selected reference pointer+144 remains that slot. Both566AC0 sphere and566B70 AABB therefore consume last source record, independent of rendered multi-submesh aggregation.
char __thiscall rf_v3c_read_character_resource(_DWORD *this, int *a2, char *Str)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  char *v7; // [esp+8h] [ebp-310h]
  char *v8; // [esp+Ch] [ebp-30Ch]
  char *v9; // [esp+10h] [ebp-308h]
  char *v10; // [esp+14h] [ebp-304h]
  char *v11; // [esp+18h] [ebp-300h]
  char *v12; // [esp+1Ch] [ebp-2FCh]
  char *v13; // [esp+20h] [ebp-2F8h]
  char v14; // [esp+27h] [ebp-2F1h]
  _BYTE *v15; // [esp+2Ch] [ebp-2ECh]
  char *v16; // [esp+30h] [ebp-2E8h]
  char *v18; // [esp+3Ch] [ebp-2DCh]
  int v19; // [esp+44h] [ebp-2D4h]
  char *v20; // [esp+48h] [ebp-2D0h]
  int v21; // [esp+50h] [ebp-2C8h]
  char *v22; // [esp+58h] [ebp-2C0h]
  int v23; // [esp+60h] [ebp-2B8h]
  char *v24; // [esp+64h] [ebp-2B4h]
  int v25; // [esp+6Ch] [ebp-2ACh]
  char *v26; // [esp+74h] [ebp-2A4h]
  int v27; // [esp+7Ch] [ebp-29Ch]
  char *v28; // [esp+80h] [ebp-298h]
  int v29; // [esp+88h] [ebp-290h]
  char *v30; // [esp+8Ch] [ebp-28Ch]
  int v31; // [esp+94h] [ebp-284h]
  int Offset; // [esp+9Ch] [ebp-27Ch]
  int v33; // [esp+A0h] [ebp-278h]
  char v34[264]; // [esp+A4h] [ebp-274h] BYREF
  int self[70]; // [esp+1ACh] [ebp-16Ch] BYREF
  char v36; // [esp+2CBh] [ebp-4Dh]
  int int32_versioned; // [esp+2CCh] [ebp-4Ch]
  int v38; // [esp+2D0h] [ebp-48h]
  int v39; // [esp+2D4h] [ebp-44h]
  _DWORD v40[11]; // [esp+2D8h] [ebp-40h] BYREF
  char v41; // [esp+307h] [ebp-11h]
  char Str1[4]; // [esp+308h] [ebp-10h] BYREF
  int v43; // [esp+314h] [ebp-4h]

  v38 = 0;
  rf_vfile_construct_unopened(self);
  v43 = 0;
  rf_path_replace_last_dot_suffix_unbounded(v34, Str, ".v3c");
  rf_v3c_asset_base_reset(this);
  if ( rf_vfile_open_with_extension_cache_control_paths(self, v34, 1, byte_98967F) < 0 )
  {
LABEL_2:
    v43 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
  *(_DWORD *)Str1 = rf_binary_stream_read_int32_versioned(self, 0, 0);
  if ( *(_DWORD *)Str1 != 1380336461 )
  {
    if ( *(_DWORD *)Str1 != 1380332356 && *(_DWORD *)Str1 != 1380337240 )
      strncmp(Str1, "V3DF", 4u);
    goto LABEL_2;
  }
  v16 = v34;
  v15 = this;
  do
  {
    v14 = *v16;
    *v15++ = *v16++;
  }
  while ( v14 );
  int32_versioned = rf_binary_stream_read_int32_versioned(self, 0, 0);
  rf_vfile_set_open_slot_version(self, int32_versioned);
  *(this + 18) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 26) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 28) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 32) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 30) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  v39 = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 22) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 24) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  if ( (int)*(this + 18) <= 0 )
  {
    *(this + 19) = 0;
    *(this + 21) = 0;
  }
  else
  {
    v31 = *(this + 18);
    v4 = (144 * (unsigned __int64)(unsigned int)v31) >> 32 != 0 ? -1 : 144 * v31;
    v30 = (char *)operator new(__CFADD__(v4, 4) ? -1 : v4 + 4);
    LOBYTE(v43) = 1;
    if ( v30 )
    {
      *(_DWORD *)v30 = v31;
      `eh vector constructor iterator'(
        v30 + 4,
        0x90u,
        v31,
        (void (__thiscall *)(void *))rf_model_mesh144_construct_null_geometry,
        (void (__thiscall *)(void *))rf_model_mesh144_destroy_lod_table);
      v13 = v30 + 4;
    }
    else
    {
      v13 = nullptr;
    }
    LOBYTE(v43) = 0;
    *(this + 19) = v13;
    v29 = *(this + 18);
    v5 = (100 * (unsigned __int64)(unsigned int)v29) >> 32 != 0 ? -1 : 100 * v29;
    v28 = (char *)operator new(__CFADD__(v5, 4) ? -1 : v5 + 4);
    LOBYTE(v43) = 2;
    if ( v28 )
    {
      *(_DWORD *)v28 = v29;
      `eh vector constructor iterator'(
        v28 + 4,
        0x64u,
        v29,
        (void (__thiscall *)(void *))rf_v3c_mesh_metadata100_construct_defaults,
        rf_v3c_mesh_metadata100_destruct_noop);
      v12 = v28 + 4;
    }
    else
    {
      v12 = nullptr;
    }
    LOBYTE(v43) = 0;
    *(this + 21) = v12;
  }
  if ( (int)*(this + 26) <= 0 )
  {
    *(this + 27) = 0;
  }
  else
  {
    v27 = *(this + 26);
    v26 = (char *)operator new(12 * v27);
    LOBYTE(v43) = 3;
    if ( v26 )
    {
      rf_vector_construct_no_unwind(v26, 0xCu, v27, rf_vector3_default_construct_noop);
      v11 = v26;
    }
    else
    {
      v11 = nullptr;
    }
    LOBYTE(v43) = 0;
    *(this + 27) = v11;
  }
  if ( (int)*(this + 28) <= 0 )
    *(this + 29) = 0;
  else
    *(this + 29) = operator new(52 * *(this + 28));
  if ( (int)*(this + 30) <= 0 )
  {
    *(this + 31) = 0;
  }
  else
  {
    v25 = *(this + 30);
    v6 = (200 * (unsigned __int64)(unsigned int)v25) >> 32 != 0 ? -1 : 200 * v25;
    v24 = (char *)operator new(__CFADD__(v6, 4) ? -1 : v6 + 4);
    LOBYTE(v43) = 4;
    if ( v24 )
    {
      *(_DWORD *)v24 = v25;
      `eh vector constructor iterator'(
        v24 + 4,
        0xC8u,
        v25,
        (void (__thiscall *)(void *))rf_material_initialize,
        rf_material200_destroy_owned_float_arrays);
      v10 = v24 + 4;
    }
    else
    {
      v10 = nullptr;
    }
    LOBYTE(v43) = 0;
    *(this + 31) = v10;
  }
  if ( (int)*(this + 32) <= 0 )
  {
    *(this + 33) = 0;
    *(this + 34) = 0;
  }
  else
  {
    v23 = *(this + 32);
    v22 = (char *)operator new(12 * v23);
    LOBYTE(v43) = 5;
    if ( v22 )
    {
      rf_vector_construct_no_unwind(v22, 0xCu, v23, rf_vector3_default_construct_noop);
      v9 = v22;
    }
    else
    {
      v9 = nullptr;
    }
    LOBYTE(v43) = 0;
    *(this + 33) = v9;
    *(this + 34) = operator new(4 * *(this + 32));
  }
  rf_mesh_read_context_construct_zero_cursors(v40);
  LOBYTE(v43) = 6;
  v40[1] = *(this + 27);
  v40[4] = *(this + 34);
  v40[6] = *(this + 29);
  v40[8] = *(this + 31);
  v40[3] = *(this + 33);
  if ( (int)*(this + 22) <= 0 )
  {
    *(this + 23) = 0;
  }
  else
  {
    v21 = *(this + 22);
    v20 = (char *)operator new(100 * v21);
    LOBYTE(v43) = 7;
    if ( v20 )
    {
      rf_vector_construct_no_unwind(
        v20,
        0x64u,
        v21,
        (void *(__thiscall *)(void *))rf_v3c_aux_transform_record_construct);
      v8 = v20;
    }
    else
    {
      v8 = nullptr;
    }
    LOBYTE(v43) = 6;
    *(this + 23) = v8;
  }
  if ( (int)*(this + 24) <= 0 )
  {
    *(this + 25) = 0;
  }
  else
  {
    v19 = *(this + 24);
    v18 = (char *)operator new(44 * v19);
    LOBYTE(v43) = 8;
    if ( v18 )
    {
      rf_vector_construct_no_unwind(
        v18,
        0x2Cu,
        v19,
        (void *(__thiscall *)(void *))rf_v3c_collision_sphere_record_construct);
      v7 = v18;
    }
    else
    {
      v7 = nullptr;
    }
    LOBYTE(v43) = 6;
    *(this + 25) = v7;
  }
  v41 = 0;
  v36 = 0;
  while ( !v36 && !rf_vfile_is_position_at_or_past_end_signed(self) )
  {
    v33 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    Offset = rf_binary_stream_read_int32_versioned(self, 0, 0);
    if ( v33 > 1146441026 )
    {
      if ( v33 == 1398096461 )
      {
        rf_v3c_mesh_metadata100_read_binary((char *)*(this + 21), self, (int)v40, (char *)*(this + 19));
        ++*(this + 20);
        *(this + 36) = *(this + 19);
      }
      else if ( v33 == 1463896404 )
      {
        rf_v3c_wait_chunk_noop((int)self);
      }
      else
      {
LABEL_72:
        rf_vfile_seek(self, Offset, 1);
      }
    }
    else if ( v33 != 1146441026 )
    {
      if ( v33 )
      {
        if ( v33 == 1112493637 )
        {
          if ( !rf_character_read_bone_chunk_adapter(a2, (int)self) )
            rf_vfile_seek(self, Offset, 1);
        }
        else
        {
          if ( v33 != 1129533512 )
            goto LABEL_72;
          rf_v3c_read_collision_sphere44(*(this + 25) + 44 * v38++, self);
        }
      }
      else
      {
        v36 = 1;
      }
    }
  }
  rf_vfile_close_stdio_or_vpp(self);
  LOBYTE(v43) = 0;
  rf_shared_noop_destructor_4580d0();
  v43 = -1;
  rf_vfile_destruct_close_if_open(self);
  return 1;
}

