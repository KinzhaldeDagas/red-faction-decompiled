// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B82C0 rf_model_mesh144_read_geometry_materials
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mesh initializers, binary reader stores, caller layouts and signature classification): ECX mesh144; stack stream and shared mesh-read context, RET8. Reads two24-byte name fields at0/65, loads geometry/LOD pointer140 via rf_model_geometry_read_lod_table and returns-1 if NULL. Reads signed material count132; positive count takes material base136=context32+200*context28, else formats unused diagnostic and sets136NULL. Adds count to context28 even if negative. For each material: reads32-byte primary texture name, empty name triggers fatal mesh.cpp448; sets material DWORD0=0, copies name to+20, loads texture handle+16; sets curve count184=1 and allocates4-byte key pointer188, reads illumination key then floats132,136,140. Reads32-byte secondary name at144 and loads handle180 or uses-1 when empty. Reads flags: resolved
// primary format4/5/7 ORs runtime flags+4 with8; authored bit2 sets BYTE8=1 and ORs8, otherwise BYTE8=0; authored bit1 ORs0x10; always ORs1. Existing flags+4 are not reset here. Returns0 without a final I/O-status gate or rollback. Counts/pool cursors/name lengths and allocations are not validated locally. Preserves earlier field-meaning notes in repeatable comment; this contract records stores and control flow.
int __thiscall rf_model_mesh144_read_geometry_materials(char *this, int *a2, int a3)
{
  char *backslash_basename_pointer; // eax
  int v5; // eax
  double float_versioned; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  int v10; // eax
  char v11; // [esp+17h] [ebp-15Dh]
  _BYTE *v12; // [esp+1Ch] [ebp-158h]
  char *v13; // [esp+20h] [ebp-154h]
  int v15; // [esp+3Ch] [ebp-138h] BYREF
  int int32_versioned; // [esp+5Ch] [ebp-118h]
  char v17[12]; // [esp+60h] [ebp-114h] BYREF
  char Buffer[256]; // [esp+6Ch] [ebp-108h] BYREF
  int i; // [esp+170h] [ebp-4h]

  rf_vector3_default_construct_noop(v17);
  rf_vfile_read_buffered_bytes_versioned(a2, this, 0x18u, 0, 0);
  rf_vfile_read_buffered_bytes_versioned(a2, this + 65, 0x18u, 0, 0);
  *((_DWORD *)this + 35) = rf_model_geometry_read_lod_table((int)a2);
  if ( !*((_DWORD *)this + 35) )
    return -1;
  *((_DWORD *)this + 33) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
  if ( *((int *)this + 33) <= 0 )
  {
    backslash_basename_pointer = rf_vfile_get_backslash_basename_pointer((char *)a2);
    sprintf(Buffer, "Mesh \"%s\" in \"%s\" has no material.\n", this, backslash_basename_pointer);
    *((_DWORD *)this + 34) = 0;
  }
  else
  {
    *((_DWORD *)this + 34) = *(_DWORD *)(a3 + 32) + 200 * *(_DWORD *)(a3 + 28);
  }
  *(_DWORD *)(a3 + 28) += *((_DWORD *)this + 33);
  for ( i = 0; i < *((_DWORD *)this + 33); ++i )
  {
    rf_vfile_read_buffered_bytes_versioned(a2, (char *)&v15, 0x20u, 0, 0);
    if ( (char *)&v15 + strlen((const char *)&v15) + 1 == (char *)&v15 + 1 )
    {
      sprintf(Buffer, "Material has no texture.  Mesh is %s\n", this);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\geom\\mesh.cpp", 448, Buffer);
    }
    *(_DWORD *)(200 * i + *((_DWORD *)this + 34)) = 0;
    v13 = (char *)&v15;
    v12 = (_BYTE *)(*((_DWORD *)this + 34) + 200 * i + 20);
    do
    {
      v11 = *v13;
      *v12++ = *v13++;
    }
    while ( v11 );
    v5 = rf_bitmap_load_with_optional_mipmap_generation((char *)&v15, (void *)0xFFFFFFFF, 1);
    *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 16) = v5;
    *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 184) = 1;
    *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 188) = operator new(4u);
    float_versioned = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    **(float **)(*((_DWORD *)this + 34) + 200 * i + 188) = float_versioned;
    v7 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(float *)(*((_DWORD *)this + 34) + 200 * i + 132) = v7;
    v8 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(float *)(*((_DWORD *)this + 34) + 200 * i + 136) = v8;
    v9 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(float *)(*((_DWORD *)this + 34) + 200 * i + 140) = v9;
    rf_vfile_read_buffered_bytes_versioned(a2, (char *)(*((_DWORD *)this + 34) + 200 * i + 144), 0x20u, 0, 0);
    if ( *((_DWORD *)this + 34) + 200 * i + 144 + strlen((const char *)(*((_DWORD *)this + 34) + 200 * i + 144)) + 1 == *((_DWORD *)this + 34) + 200 * i + 145 )
    {
      *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 180) = -1;
    }
    else
    {
      v10 = rf_bitmap_load_with_optional_mipmap_generation(
              (char *)(*((_DWORD *)this + 34) + 200 * i + 144),
              (void *)0xFFFFFFFF,
              1);
      *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 180) = v10;
    }
    int32_versioned = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    if ( rf_bitmap_resolved_format_is_4_5_7(*(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 16)) )
      *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 4) |= 8u;
    if ( (int32_versioned & 2) != 0 )
    {
      *(_BYTE *)(*((_DWORD *)this + 34) + 200 * i + 8) = 1;
      *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 4) |= 8u;
    }
    else
    {
      *(_BYTE *)(*((_DWORD *)this + 34) + 200 * i + 8) = 0;
    }
    if ( (int32_versioned & 1) != 0 )
      *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 4) |= 0x10u;
    *(_DWORD *)(*((_DWORD *)this + 34) + 200 * i + 4) |= 1u;
  }
  return 0;
}

