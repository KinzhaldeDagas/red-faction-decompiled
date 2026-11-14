// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004863C0 rf_material_hit_sounds_build
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl noargs. Iterates canonical pairs0<=i<=j<10, vector at0x6FFFB0+120*i+12*j; does not clear existing vectors before append. Starts ONE signed filename/attenuation counter n=1
// per pair. First family 'Name[i]_hit_Name[j]'+decimal(n)+'.wav' uses signed count matrix[j][i]. Loads each resource with distance=F32(n*double5), current FLOAT volume (initial1),
// scale1; appends returned handle even if -1. After each sound increments n, computes next volume=F32(1-(n-1)*double0.3330000042915344); ordered next volume<=0 clamps to binary32
// 0.1, unordered would be preserved by TEST AH,0x41/JP.
// If i!=j, reverse family 'Name[j]_hit_Name[i]' uses count matrix[i][j] and same vector. Volume resets1 but n DOES NOT RESET: reverse first filename suffix/distance continues after
// forward family, and following volume is derived from that continuing n. Diagonal has only first family. Negative counts produce zero iterations; no maximum count or sound-load
// success validation. After all pairs, ONLY if vector[0][0] empty appends fallback handle -1 there; other empty pairs remain empty and selection logic elsewhere handles fallbacks.
// Destroys temporary RFStrings, no sound-resource unload here.
void rf_material_hit_sounds_build()
{
  const char *v0; // eax
  const char *v1; // eax
  float volume; // [esp+4h] [ebp-A8h]
  float volumea; // [esp+4h] [ebp-A8h]
  std::exception *v4; // [esp+14h] [ebp-98h]
  _DWORD *v5; // [esp+1Ch] [ebp-90h]
  _DWORD *v6; // [esp+24h] [ebp-88h]
  float v7; // [esp+2Ch] [ebp-80h]
  std::exception *v8; // [esp+34h] [ebp-78h]
  _DWORD *v9; // [esp+3Ch] [ebp-70h]
  _DWORD *v10; // [esp+44h] [ebp-68h]
  float distance; // [esp+4Ch] [ebp-60h]
  _BYTE v12[8]; // [esp+50h] [ebp-5Ch] BYREF
  _BYTE v13[8]; // [esp+58h] [ebp-54h] BYREF
  _DWORD v14[2]; // [esp+60h] [ebp-4Ch] BYREF
  _BYTE v15[8]; // [esp+68h] [ebp-44h] BYREF
  _BYTE v16[8]; // [esp+70h] [ebp-3Ch] BYREF
  _DWORD v17[2]; // [esp+78h] [ebp-34h] BYREF
  int v18; // [esp+80h] [ebp-2Ch]
  float v19; // [esp+84h] [ebp-28h]
  int j; // [esp+88h] [ebp-24h]
  int k; // [esp+8Ch] [ebp-20h]
  int v22[2]; // [esp+90h] [ebp-1Ch] BYREF
  int v23; // [esp+98h] [ebp-14h]
  int i; // [esp+9Ch] [ebp-10h]
  int v25; // [esp+A8h] [ebp-4h]

  rf_string_construct_empty(v22);
  v25 = 0;
  for ( i = 0; i < 10; ++i )
  {
    for ( j = i; j < 10; ++j )
    {
      v18 = 1;
      rf_string_assign_from_cstr(v22, (char *)rf_material_names[i]);
      rf_string_append_cstr_in_place(v22, (int)"_hit_");
      rf_string_append_cstr_in_place(v22, (int)rf_material_names[j]);
      v19 = 1.0;
      for ( k = 0; k < rf_material_hit_sound_count_matrix[j][i]; ++k )
      {
        volume = v19;
        distance = (double)v18 * 5.0;
        v10 = rf_string_format_int32_decimal(v17, v18);
        LOBYTE(v25) = 1;
        v9 = rf_string_concat_two_objects(v16, v22, (int)v10);
        LOBYTE(v25) = 2;
        v8 = (std::exception *)rf_string_concat_object_cstr(v15, v9, ".wav");
        LOBYTE(v25) = 3;
        v0 = rf_string_object_c_str_or_empty(v8);
        v23 = rf_sound_resource_load(v0, distance, volume, 1.0);
        LOBYTE(v25) = 2;
        rf_string_destroy_buffer(v15);
        LOBYTE(v25) = 1;
        rf_string_destroy_buffer(v16);
        LOBYTE(v25) = 0;
        rf_string_destroy_buffer(v17);
        rf_pointer_array_append_dword(&rf_material_hit_sound_pair_vectors[30 * i + 3 * j], v23);
        v19 = 1.0 - (double)v18++ * 0.3330000042915344;
        if ( v19 <= 0.0 )
          v19 = 0.1;
      }
      if ( i != j )
      {
        rf_string_assign_from_cstr(v22, (char *)rf_material_names[j]);
        rf_string_append_cstr_in_place(v22, (int)"_hit_");
        rf_string_append_cstr_in_place(v22, (int)rf_material_names[i]);
        v19 = 1.0;
        for ( k = 0; k < rf_material_hit_sound_count_matrix[i][j]; ++k )
        {
          volumea = v19;
          v7 = (double)v18 * 5.0;
          v6 = rf_string_format_int32_decimal(v14, v18);
          LOBYTE(v25) = 4;
          v5 = rf_string_concat_two_objects(v13, v22, (int)v6);
          LOBYTE(v25) = 5;
          v4 = (std::exception *)rf_string_concat_object_cstr(v12, v5, ".wav");
          LOBYTE(v25) = 6;
          v1 = rf_string_object_c_str_or_empty(v4);
          v23 = rf_sound_resource_load(v1, v7, volumea, 1.0);
          LOBYTE(v25) = 5;
          rf_string_destroy_buffer(v12);
          LOBYTE(v25) = 4;
          rf_string_destroy_buffer(v13);
          LOBYTE(v25) = 0;
          rf_string_destroy_buffer(v14);
          rf_pointer_array_append_dword(&rf_material_hit_sound_pair_vectors[30 * i + 3 * j], v23);
          v19 = 1.0 - (double)v18++ * 0.3330000042915344;
          if ( v19 <= 0.0 )
            v19 = 0.1;
        }
      }
    }
  }
  if ( !rf_receiver_get_first_dword(rf_material_hit_sound_pair_vectors) )
    rf_pointer_array_append_dword(rf_material_hit_sound_pair_vectors, -1);
  v25 = -1;
  rf_string_destroy_buffer(v22);
}

