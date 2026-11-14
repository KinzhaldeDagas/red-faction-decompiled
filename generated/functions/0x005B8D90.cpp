// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8D90 sub_5B8D90
// UNREALRED VERIFIED [mesh-streaming-20260930] Opens the single supplied resource. Open failure or signature other than 0x52463344 takes cleanup and returns -1; recognized character/effect signatures do not redirect to another loader here. The successful path closes the selected VFile and returns its close result.
int __thiscall sub_5B8D90(int *this, char *Str, int a3, int a4, int a5)
{
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  char *v9; // [esp+8h] [ebp-208h]
  char *v10; // [esp+Ch] [ebp-204h]
  char *v11; // [esp+10h] [ebp-200h]
  char *v12; // [esp+14h] [ebp-1FCh]
  char *v13; // [esp+18h] [ebp-1F8h]
  char *v14; // [esp+1Ch] [ebp-1F4h]
  char *v15; // [esp+20h] [ebp-1F0h]
  char v16; // [esp+27h] [ebp-1E9h]
  int *v17; // [esp+2Ch] [ebp-1E4h]
  char *v18; // [esp+30h] [ebp-1E0h]
  int v20; // [esp+38h] [ebp-1D8h]
  char *v21; // [esp+3Ch] [ebp-1D4h]
  int v22; // [esp+44h] [ebp-1CCh]
  char *v23; // [esp+48h] [ebp-1C8h]
  int v24; // [esp+50h] [ebp-1C0h]
  char *v25; // [esp+54h] [ebp-1BCh]
  int v26; // [esp+5Ch] [ebp-1B4h]
  char *v27; // [esp+60h] [ebp-1B0h]
  int v28; // [esp+68h] [ebp-1A8h]
  char *v29; // [esp+70h] [ebp-1A0h]
  int v30; // [esp+78h] [ebp-198h]
  char *v31; // [esp+7Ch] [ebp-194h]
  int v32; // [esp+84h] [ebp-18Ch]
  char *v33; // [esp+88h] [ebp-188h]
  int v34; // [esp+90h] [ebp-180h]
  int Offset; // [esp+9Ch] [ebp-174h]
  int v36; // [esp+A0h] [ebp-170h]
  int self[70]; // [esp+A4h] [ebp-16Ch] BYREF
  char v38; // [esp+1C3h] [ebp-4Dh]
  int v39; // [esp+1C4h] [ebp-4Ch]
  int v40; // [esp+1C8h] [ebp-48h]
  int v41; // [esp+1CCh] [ebp-44h]
  int int32_versioned; // [esp+1D0h] [ebp-40h]
  _DWORD v43[11]; // [esp+1D4h] [ebp-3Ch] BYREF
  char Str1[4]; // [esp+200h] [ebp-10h] BYREF
  int v45; // [esp+20Ch] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v45 = 0;
  v39 = 0;
  v40 = 0;
  v41 = 0;
  rf_mesh_read_context_construct_zero_cursors(v43);
  LOBYTE(v45) = 1;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, byte_98967F) < 0 )
  {
LABEL_2:
    LOBYTE(v45) = 0;
    rf_shared_noop_destructor_4580d0();
    v45 = -1;
    rf_vfile_destruct_close_if_open(self);
    return -1;
  }
  v18 = Str;
  v17 = this;
  do
  {
    v16 = *v18;
    *(_BYTE *)v17 = *v18++;
    v17 = (int *)((char *)v17 + 1);
  }
  while ( v16 );
  *(_DWORD *)Str1 = rf_binary_stream_read_int32_versioned(self, 0, 0);
  if ( *(_DWORD *)Str1 != 1380332356 )
  {
    if ( *(_DWORD *)Str1 != 1380336461 && *(_DWORD *)Str1 != 1380337240 )
      strncmp(Str1, "V3DF", 4u);
    goto LABEL_2;
  }
  *(this + 35) = 0;
  *(this + 17) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  rf_vfile_set_open_slot_version(self, *(this + 17));
  *(this + 18) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 26) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 28) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 32) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 30) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  int32_versioned = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 22) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  *(this + 24) = rf_binary_stream_read_int32_versioned(self, 0, 0);
  if ( *(this + 18) <= 0 )
  {
    *(this + 19) = 0;
    *(this + 21) = 0;
  }
  else
  {
    v34 = *(this + 18);
    v6 = (144 * (unsigned __int64)(unsigned int)v34) >> 32 != 0 ? -1 : 144 * v34;
    v33 = (char *)operator new(__CFADD__(v6, 4) ? -1 : v6 + 4);
    LOBYTE(v45) = 2;
    if ( v33 )
    {
      *(_DWORD *)v33 = v34;
      `eh vector constructor iterator'(
        v33 + 4,
        0x90u,
        v34,
        (void (__thiscall *)(void *))rf_model_mesh144_construct_null_geometry,
        (void (__thiscall *)(void *))rf_model_mesh144_destroy_lod_table);
      v15 = v33 + 4;
    }
    else
    {
      v15 = nullptr;
    }
    LOBYTE(v45) = 1;
    *(this + 19) = (int)v15;
    v32 = *(this + 18);
    v7 = (100 * (unsigned __int64)(unsigned int)v32) >> 32 != 0 ? -1 : 100 * v32;
    v31 = (char *)operator new(__CFADD__(v7, 4) ? -1 : v7 + 4);
    LOBYTE(v45) = 3;
    if ( v31 )
    {
      *(_DWORD *)v31 = v32;
      `eh vector constructor iterator'(
        v31 + 4,
        0x64u,
        v32,
        (void (__thiscall *)(void *))rf_v3c_mesh_metadata100_construct_defaults,
        rf_v3c_mesh_metadata100_destruct_noop);
      v14 = v31 + 4;
    }
    else
    {
      v14 = nullptr;
    }
    LOBYTE(v45) = 1;
    *(this + 21) = (int)v14;
  }
  if ( *(this + 26) <= 0 )
  {
    *(this + 27) = 0;
  }
  else
  {
    v30 = *(this + 26);
    v29 = (char *)operator new(12 * v30);
    LOBYTE(v45) = 4;
    if ( v29 )
    {
      rf_vector_construct_no_unwind(v29, 0xCu, v30, rf_vector3_default_construct_noop);
      v13 = v29;
    }
    else
    {
      v13 = nullptr;
    }
    LOBYTE(v45) = 1;
    *(this + 27) = (int)v13;
  }
  if ( *(this + 28) <= 0 )
    *(this + 29) = 0;
  else
    *(this + 29) = (int)operator new(52 * *(this + 28));
  if ( *(this + 32) <= 0 )
  {
    *(this + 33) = 0;
  }
  else
  {
    v28 = *(this + 32);
    v27 = (char *)operator new(12 * v28);
    LOBYTE(v45) = 5;
    if ( v27 )
    {
      rf_vector_construct_no_unwind(v27, 0xCu, v28, rf_vector3_default_construct_noop);
      v12 = v27;
    }
    else
    {
      v12 = nullptr;
    }
    LOBYTE(v45) = 1;
    *(this + 33) = (int)v12;
  }
  if ( *(this + 30) <= 0 )
  {
    *(this + 31) = 0;
  }
  else
  {
    v26 = *(this + 30);
    v8 = (200 * (unsigned __int64)(unsigned int)v26) >> 32 != 0 ? -1 : 200 * v26;
    v25 = (char *)operator new(__CFADD__(v8, 4) ? -1 : v8 + 4);
    LOBYTE(v45) = 6;
    if ( v25 )
    {
      *(_DWORD *)v25 = v26;
      `eh vector constructor iterator'(
        v25 + 4,
        0xC8u,
        v26,
        (void (__thiscall *)(void *))rf_material_initialize,
        rf_material200_destroy_owned_float_arrays);
      v11 = v25 + 4;
    }
    else
    {
      v11 = nullptr;
    }
    LOBYTE(v45) = 1;
    *(this + 31) = (int)v11;
  }
  if ( *(this + 22) <= 0 )
  {
    *(this + 23) = 0;
  }
  else
  {
    v24 = *(this + 22);
    v23 = (char *)operator new(100 * v24);
    LOBYTE(v45) = 7;
    if ( v23 )
    {
      rf_vector_construct_no_unwind(
        v23,
        0x64u,
        v24,
        (void *(__thiscall *)(void *))rf_v3c_aux_transform_record_construct);
      v10 = v23;
    }
    else
    {
      v10 = nullptr;
    }
    LOBYTE(v45) = 1;
    *(this + 23) = (int)v10;
  }
  if ( *(this + 24) <= 0 )
  {
    *(this + 25) = 0;
  }
  else
  {
    v22 = *(this + 24);
    v21 = (char *)operator new(44 * v22);
    LOBYTE(v45) = 8;
    if ( v21 )
    {
      rf_vector_construct_no_unwind(
        v21,
        0x2Cu,
        v22,
        (void *(__thiscall *)(void *))rf_v3c_collision_sphere_record_construct);
      v9 = v21;
    }
    else
    {
      v9 = nullptr;
    }
    LOBYTE(v45) = 1;
    *(this + 25) = (int)v9;
  }
  v43[1] = *(this + 27);
  v43[6] = *(this + 29);
  v43[8] = *(this + 31);
  v43[3] = *(this + 33);
  v43[4] = 0;
  v38 = 0;
  while ( !v38 )
  {
    v36 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    Offset = rf_binary_stream_read_int32_versioned(self, 0, 0);
    if ( v36 > 1146441026 )
    {
      if ( v36 != 1398096461 )
        goto LABEL_64;
      rf_v3c_mesh_metadata100_read_binary(
        (char *)(*(this + 21) + 100 * v39),
        self,
        (int)v43,
        (char *)(*(this + 19) + 144 * v39));
      ++v39;
      ++*(this + 20);
    }
    else if ( v36 != 1146441026 )
    {
      if ( v36 )
      {
        if ( v36 == 1129533512 )
          rf_v3c_read_collision_sphere44(*(this + 25) + 44 * v41++, self);
        else
LABEL_64:
          rf_vfile_seek(self, Offset, 1);
      }
      else
      {
        v38 = 1;
      }
    }
  }
  v20 = rf_vfile_close_stdio_or_vpp(self);
  LOBYTE(v45) = 0;
  rf_shared_noop_destructor_4580d0();
  v45 = -1;
  rf_vfile_destruct_close_if_open(self);
  return v20;
}

