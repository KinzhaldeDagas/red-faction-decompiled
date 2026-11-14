// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BDFF0 rf_particle_definition_read_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): NonNULL virtual stream reads name and parent strings via unbounded-capacity NUL reader into256-byte local,then unbounded copies to definition65-byte name fields; parent defaults Scene Root and strips prefix through FIRST hyphen when present. Reads high flag in count+148,version-gated flags+172,low31bit channel count; resolves at most3 channel names by exact name/source-basename pair but does NOT cap stored count. Reads frame offset+200,count+204. Version>=0x40000 reads material index; older versions append200-byte material in caller pools,load texture(s),legacy RGB or crossfade settings and allocate alpha/selfillum arrays from shared counters. Reads
// maxParticles+152,emissionStart+156,lifetimeTicks+160,variation+164,shape+168; pre0x30010 flags read at later position. Width envelope+176/180 uses float from0x30005 else integer convertedfloat,values>1 divided100,both0=>upper1;alpha envelope+184/188 defaults0/1 from0x30006,both0=>upper1. Flag0x100 reads triangle-tail scalar+192; versions<0x3000D seek56 relative bytes. Reserves frameCount52-byte keys from caller pool; each reads position,quaternion,width+28,depth+32,size+36,speed+40 and spread+44 multiplied12,spread made nonnegative,rate+48. Tracks max speed/spread at+212/216. Versions<0x40005 read per-key alpha clamped[0,1] into material array. No destination pool,channel-count,frame/maxParticle count,material index,string length,stream status or offset validation;NULL stream leaves object unchanged.
void __thiscall rf_particle_definition_read_versioned(int this, int *a2, int a3)
{
  char *backslash_basename_pointer; // eax
  int exact_pair; // eax
  double float_versioned; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  char v14; // [esp+13h] [ebp-19Dh]
  _BYTE *v15; // [esp+18h] [ebp-198h]
  char *v16; // [esp+1Ch] [ebp-194h]
  char v17; // [esp+33h] [ebp-17Dh]
  _BYTE *v18; // [esp+38h] [ebp-178h]
  char *v19; // [esp+3Ch] [ebp-174h]
  bool v20; // [esp+40h] [ebp-170h]
  char v21; // [esp+4Bh] [ebp-165h]
  _BYTE *v22; // [esp+50h] [ebp-160h]
  char *v23; // [esp+54h] [ebp-15Ch]
  char v24; // [esp+5Bh] [ebp-155h]
  _BYTE *v25; // [esp+60h] [ebp-150h]
  char *v26; // [esp+64h] [ebp-14Ch]
  char v27; // [esp+7Bh] [ebp-135h]
  _BYTE *v28; // [esp+80h] [ebp-130h]
  char *p_Str; // [esp+84h] [ebp-12Ch]
  float v31; // [esp+8Ch] [ebp-124h]
  float v32; // [esp+8Ch] [ebp-124h]
  float v33; // [esp+8Ch] [ebp-124h]
  char int32_versioned; // [esp+94h] [ebp-11Ch]
  char v35; // [esp+98h] [ebp-118h]
  char v36; // [esp+9Ch] [ebp-114h]
  int v37; // [esp+A0h] [ebp-110h]
  char *first_character; // [esp+A4h] [ebp-10Ch]
  char Str; // [esp+A8h] [ebp-108h] BYREF
  _BYTE v40[255]; // [esp+A9h] [ebp-107h] BYREF
  int i; // [esp+1ACh] [ebp-4h]

  if ( a2 )
  {
    rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
    p_Str = &Str;
    v28 = (_BYTE *)this;
    do
    {
      v27 = *p_Str;
      *v28++ = *p_Str++;
    }
    while ( v27 );
    strcpy((char *)(this + 65), "Scene Root");
    rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
    if ( &v40[strlen(&Str)] != v40 )
    {
      first_character = rf_cstring_find_first_character(&Str, 45);
      if ( first_character )
      {
        v26 = first_character + 1;
        v25 = (_BYTE *)(this + 65);
        do
        {
          v24 = *v26;
          *v25++ = *v26++;
        }
        while ( v24 );
      }
      else
      {
        v23 = &Str;
        v22 = (_BYTE *)(this + 65);
        do
        {
          v21 = *v23;
          *v22++ = *v23++;
        }
        while ( v21 );
      }
    }
    *(_DWORD *)(this + 148) = (rf_binary_stream_read_bool_versioned(a2, 0, 1) << 31)
                            | *(_DWORD *)(this + 148) & 0x7FFFFFFF;
    *(_DWORD *)(this + 172) = rf_binary_stream_read_int32_versioned(a2, 196624, 0);
    *(_DWORD *)(this + 148) = rf_binary_stream_read_int32_versioned(a2, 0, 0) & 0x7FFFFFFF
                            | *(_DWORD *)(this + 148) & 0x80000000;
    for ( i = 0; i < 3; ++i )
    {
      if ( i >= (*(_DWORD *)(this + 148) & 0x7FFFFFFF) )
      {
        *(_DWORD *)(this + 4 * i + 136) = 0;
      }
      else
      {
        rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
        backslash_basename_pointer = rf_vfile_get_backslash_basename_pointer((char *)a2);
        exact_pair = rf_named_source_cache_find_exact_pair(&Str, backslash_basename_pointer);
        *(_DWORD *)(this + 4 * i + 136) = exact_pair;
      }
    }
    *(_DWORD *)(this + 200) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    *(_DWORD *)(this + 204) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    if ( rf_binary_stream_version_at_least(a2, 0x40000) )
    {
      *(_DWORD *)(this + 196) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    }
    else
    {
      *(_DWORD *)(this + 196) = **(_DWORD **)a3;
      v37 = *(_DWORD *)(a3 + 4) + 200 * *(_DWORD *)(this + 196);
      ++**(_DWORD **)a3;
      if ( (*(_DWORD *)(this + 172) & 0x100) != 0 )
      {
        *(_DWORD *)v37 = 2;
        int32_versioned = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        v35 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        v36 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        rf_color4_set_bytes_return_destination((_BYTE *)(v37 + 9), int32_versioned, v35, v36, 255);
        *(_DWORD *)(v37 + 184) = 1;
        *(_DWORD *)(v37 + 188) = *(_DWORD *)(a3 + 20) + 4 * (**(_DWORD **)(a3 + 16))++;
        **(float **)(v37 + 188) = rf_binary_stream_read_float_versioned(a2, 196625, 0.0);
        *(_DWORD *)(v37 + 192) = *(_DWORD *)(this + 204);
        *(_DWORD *)(v37 + 196) = *(_DWORD *)(a3 + 28) + 4 * **(_DWORD **)(a3 + 24);
        **(_DWORD **)(a3 + 24) += *(_DWORD *)(this + 204);
      }
      else
      {
        *(_DWORD *)v37 = rf_binary_stream_read_int32_versioned(a2, 0, 0);
        v20 = rf_binary_stream_read_bool_versioned(a2, 196611, 0) || (*(_DWORD *)(this + 172) & 1) != 0;
        *(_BYTE *)(v37 + 8) = v20;
        rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
        v19 = &Str;
        v18 = (_BYTE *)(v37 + 20);
        do
        {
          v17 = *v19;
          *v18++ = *v19++;
        }
        while ( v17 );
        *(_DWORD *)(v37 + 16) = rf_bitmap_load_with_optional_mipmap_generation(
                                  (char *)(v37 + 20),
                                  (void *)0xFFFFFFFF,
                                  1);
        *(_DWORD *)(v37 + 56) = 0;
        *(float *)(v37 + 60) = rf_binary_stream_read_float_versioned(a2, 196626, 1.0);
        *(_DWORD *)(v37 + 64) = 0;
        if ( *(_DWORD *)v37 == 1 )
        {
          rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
          if ( &v40[strlen(&Str)] == v40 )
          {
            *(_BYTE *)(v37 + 72) = 0;
            *(_DWORD *)(v37 + 68) = -1;
          }
          else
          {
            v16 = &Str;
            v15 = (_BYTE *)(v37 + 72);
            do
            {
              v14 = *v16;
              *v15++ = *v16++;
            }
            while ( v14 );
            *(_DWORD *)(v37 + 68) = rf_bitmap_load_with_optional_mipmap_generation(&Str, (void *)0xFFFFFFFF, 1);
          }
          *(_DWORD *)(v37 + 108) = 0;
          *(float *)(v37 + 112) = rf_binary_stream_read_float_versioned(a2, 196626, 1.0);
          *(_DWORD *)(v37 + 116) = 0;
        }
        else
        {
          *(_BYTE *)(v37 + 72) = 0;
          *(_DWORD *)(v37 + 68) = -1;
          *(_DWORD *)(v37 + 108) = 0;
          *(float *)(v37 + 112) = 1.0;
          *(_DWORD *)(v37 + 116) = 0;
        }
        if ( !rf_binary_stream_version_at_least(a2, 196626) )
        {
          *(_DWORD *)(v37 + 56) = 0;
          *(_DWORD *)(v37 + 108) = 0;
          *(float *)(v37 + 60) = 1.0;
          *(float *)(v37 + 112) = 1.0;
          *(_DWORD *)(v37 + 64) = 0;
          *(_DWORD *)(v37 + 116) = 0;
        }
        if ( *(_DWORD *)v37 == 1 )
        {
          *(_DWORD *)(v37 + 124) = *(_DWORD *)(this + 204);
          *(_DWORD *)(v37 + 128) = *(_DWORD *)(a3 + 12) + 4 * **(_DWORD **)(a3 + 8);
          **(_DWORD **)(a3 + 8) += *(_DWORD *)(v37 + 124);
          for ( i = 0; i < *(_DWORD *)(v37 + 124); ++i )
          {
            float_versioned = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
            *(float *)(*(_DWORD *)(v37 + 128) + 4 * i) = float_versioned;
            v6 = rf_float_maximum_two_values(*(float *)(*(_DWORD *)(v37 + 128) + 4 * i), 0.0);
            *(float *)(*(_DWORD *)(v37 + 128) + 4 * i) = v6;
            v7 = rf_float_minimum_two_values(*(float *)(*(_DWORD *)(v37 + 128) + 4 * i), 1.0);
            *(float *)(*(_DWORD *)(v37 + 128) + 4 * i) = v7;
          }
        }
        *(_DWORD *)(v37 + 184) = 1;
        *(_DWORD *)(v37 + 188) = *(_DWORD *)(a3 + 20) + 4 * (**(_DWORD **)(a3 + 16))++;
        **(float **)(v37 + 188) = rf_binary_stream_read_float_versioned(a2, 196625, 0.0);
        *(_DWORD *)(v37 + 192) = *(_DWORD *)(this + 204);
        *(_DWORD *)(v37 + 196) = *(_DWORD *)(a3 + 28) + 4 * **(_DWORD **)(a3 + 24);
        **(_DWORD **)(a3 + 24) += *(_DWORD *)(this + 204);
      }
    }
    *(_DWORD *)(this + 152) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    *(_DWORD *)(this + 156) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    *(_DWORD *)(this + 160) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    *(float *)(this + 164) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(_DWORD *)(this + 168) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    if ( !rf_binary_stream_version_at_least(a2, 196624) )
      *(_DWORD *)(this + 172) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    if ( rf_binary_stream_version_at_least(a2, 196613) )
    {
      *(float *)(this + 176) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      if ( *(float *)(this + 176) > 1.0 )
        *(float *)(this + 176) = *(float *)(this + 176) / 100.0;
      *(float *)(this + 180) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      if ( *(float *)(this + 180) > 1.0 )
        *(float *)(this + 180) = *(float *)(this + 180) / 100.0;
      if ( *(float *)(this + 176) == 0.0 && *(float *)(this + 180) == 0.0 )
        *(float *)(this + 180) = 1.0;
    }
    else
    {
      *(float *)(this + 176) = (float)rf_binary_stream_read_int32_versioned(a2, 0, 0);
      if ( *(float *)(this + 176) > 1.0 )
        *(float *)(this + 176) = *(float *)(this + 176) / 100.0;
      *(float *)(this + 180) = (float)rf_binary_stream_read_int32_versioned(a2, 0, 0);
      if ( *(float *)(this + 180) > 1.0 )
        *(float *)(this + 180) = *(float *)(this + 180) / 100.0;
      if ( *(float *)(this + 176) == 0.0 && *(float *)(this + 180) == 0.0 )
        *(float *)(this + 180) = 1.0;
    }
    *(float *)(this + 184) = rf_binary_stream_read_float_versioned(a2, 196614, 0.0);
    *(float *)(this + 188) = rf_binary_stream_read_float_versioned(a2, 196614, 1.0);
    if ( *(float *)(this + 184) == 0.0 && *(float *)(this + 188) == 0.0 )
      *(float *)(this + 188) = 1.0;
    if ( (*(_DWORD *)(this + 172) & 0x100) != 0 )
      *(float *)(this + 192) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    if ( !rf_binary_stream_version_at_least(a2, 196621) )
      rf_vfile_seek(a2, 56, 1);
    *(_DWORD *)(this + 208) = *(_DWORD *)(a3 + 36) + 52 * *(_DWORD *)(a3 + 32);
    *(_DWORD *)(a3 + 32) += *(_DWORD *)(this + 204);
    for ( i = 0; i < *(_DWORD *)(this + 204); ++i )
    {
      rf_binary_stream_read_vector3_versioned(a2, (float *)(*(_DWORD *)(this + 208) + 52 * i), 0, unk_1C8FBDC);
      rf_binary_stream_read_float4_versioned(a2, (float *)(*(_DWORD *)(this + 208) + 52 * i + 12), 0, unk_1C8FC3C);
      v8 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 208) + 52 * i + 28) = v8;
      v9 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 208) + 52 * i + 32) = v9;
      v10 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 208) + 52 * i + 36) = v10;
      v11 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 208) + 52 * i + 40) = v11 * 12.0;
      if ( *(float *)(this + 212) < (double)*(float *)(*(_DWORD *)(this + 208) + 52 * i + 40) )
        *(float *)(this + 212) = *(float *)(*(_DWORD *)(this + 208) + 52 * i + 40);
      v12 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 208) + 52 * i + 44) = v12 * 12.0;
      if ( *(float *)(*(_DWORD *)(this + 208) + 52 * i + 44) < 0.0 )
        *(float *)(*(_DWORD *)(this + 208) + 52 * i + 44) = *(float *)(*(_DWORD *)(this + 208) + 52 * i + 44) * -1.0;
      if ( *(float *)(this + 216) < (double)*(float *)(*(_DWORD *)(this + 208) + 52 * i + 44) )
        *(float *)(this + 216) = *(float *)(*(_DWORD *)(this + 208) + 52 * i + 44);
      v13 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 208) + 52 * i + 48) = v13;
      if ( !rf_binary_stream_version_at_least(a2, 262149) )
      {
        v31 = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
        v32 = rf_float_maximum_two_values(v31, 0.0);
        v33 = rf_float_minimum_two_values(v32, 1.0);
        *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 132) + 140) + 200 * *(_DWORD *)(this + 196) + 196) + 4 * i) = v33;
      }
    }
  }
}

