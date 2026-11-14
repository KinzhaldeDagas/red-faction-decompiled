// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047E0B0 rf_rfl_level_environment_read
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Cdecl stream. Reads bitmap RFString(min40,fallback rock01.tga), loads bitmap(-1,1) into global6FC338. Reads global GeoMod hardness(min40,default0); ONLY exact0 becomes55, with
// no0..100 clamp. Reads packed color6FC340(min0,default1C8FC4C); unsigned RGB bytes converted /double255 into binary32 temporaries, alpha not passed to lighting. Reads
// bool(min56,default0): EXACT1 creates normalized direction(0.5,-1,0), directional light with scalar1,RGB,flags(0,1,0); other values set renderer global light triplet directly.
// Directional return handle ignored.
// Reads packed4 field6FC344(min135,defaultRGBA40,40,40,255), FLOAT6FC348(min135,default0), FLOAT6FC34C(min135,default0), copies stored binary32 latter to6FC350. No local
// finite/clamp/read-status validation, bitmap failure rollback or release of prior resources. Temporary bitmap string destroyed on normal/unwind paths.
void __cdecl rf_rfl_level_environment_read(_DWORD *a1)
{
  char *v1; // eax
  int v2; // [esp+2Ch] [ebp-3Ch] BYREF
  int v3; // [esp+30h] [ebp-38h] BYREF
  int v4[3]; // [esp+34h] [ebp-34h] BYREF
  int v5; // [esp+40h] [ebp-28h] BYREF
  float v6; // [esp+44h] [ebp-24h]
  float v7; // [esp+48h] [ebp-20h]
  float v8; // [esp+4Ch] [ebp-1Ch]
  int v9[2]; // [esp+50h] [ebp-18h] BYREF
  char bool_versioned; // [esp+5Bh] [ebp-Dh]
  int v11; // [esp+64h] [ebp-4h]

  rf_string_construct_empty(v9);
  v11 = 0;
  rf_binary_stream_read_string_object_versioned(a1, v9, 40, "rock01.tga");
  v1 = (char *)rf_string_object_c_str_or_empty(v9);
  unk_6FC338 = rf_bitmap_load_with_optional_mipmap_generation(v1, (void *)0xFFFFFFFF, 1);
  rf_geomod_global_hardness = rf_binary_stream_read_int32_versioned(a1, 40, 0);
  if ( !rf_geomod_global_hardness )
    rf_geomod_global_hardness = 55;
  unk_6FC340 = *rf_binary_stream_read_packed4bytes_versioned(a1, &v3, 0, &dword_1C8FC4C);
  bool_versioned = rf_binary_stream_read_bool_versioned(a1, 56, 0);
  v6 = (double)unk_6FC340 / 255.0;
  v7 = (double)unk_6FC341 / 255.0;
  v8 = (double)unk_6FC342 / 255.0;
  if ( bool_versioned == 1 )
  {
    rf_vector3_set_components_return_destination((float *)v4, 0.5, -1.0, 0.0);
    rf_vector_normalize_reciprocal_sqrt((float *)v4);
    rf_renderer_directional_light_create((float *)v4, 1.0, v6, v7, v8, 0, 1, 0);
  }
  else
  {
    rf_renderer_set_global_light_triplet_663b1c(v6, v7, v8);
  }
  rf_rgba8_construct_components_return_self(&v5, 40, 40, 40, 255);
  unk_6FC344 = *rf_binary_stream_read_packed4bytes_versioned(a1, &v2, 135, &v5);
  unk_6FC348 = rf_binary_stream_read_float_versioned(a1, 135, 0.0);
  unk_6FC34C = rf_binary_stream_read_float_versioned(a1, 135, 0.0);
  unk_6FC350 = unk_6FC34C;
  v11 = -1;
  rf_string_destroy_buffer(v9);
}

