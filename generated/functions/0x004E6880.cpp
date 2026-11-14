// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6880 rf_fpgun_assets_initialize
// UNREALRED VERIFIED [fpgun-vmesh-decode]: Loads $1st Person Mesh into definition +0x48 and independently loads $Spark VFX into +0x500.
char rf_fpgun_assets_initialize()
{
  char *v0; // eax
  int v3m_mode1; // eax
  char *v2; // eax
  const char *instance; // eax
  char *v4; // eax
  int v6; // [esp+Ch] [ebp-14h] BYREF
  const char **v7; // [esp+10h] [ebp-10h]
  int v8; // [esp+14h] [ebp-Ch] BYREF
  int i; // [esp+18h] [ebp-8h]
  char load_context_byte; // [esp+1Fh] [ebp-1h]

  load_context_byte = rf_bitmap_get_load_context_byte();
  rf_bitmap_set_load_context_byte(0);
  rf_fpgun_load_interlace_screen_bitmap();
  dword_662FB4 = rf_bitmap_load_with_optional_mipmap_generation("ass2_scope_circle.tga", (void *)0xFFFFFFFF, 1);
  dword_662FB8 = rf_bitmap_load_with_optional_mipmap_generation("scope_zoom_corner256_red.tga", (void *)0xFFFFFFFF, 1);
  dword_662FBC = rf_bitmap_load_with_optional_mipmap_generation("scope_numbers.vbm", (void *)0xFFFFFFFF, 1);
  dword_662FC0 = rf_bitmap_load_with_optional_mipmap_generation("scope_light.vbm", (void *)0xFFFFFFFF, 1);
  dword_662FC4 = rf_bitmap_load_with_optional_mipmap_generation("ass2_scope_numbers.tga", (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(dword_662FB4);
  rf_renderer_bind_texture_for_level_warmup(dword_662FB8);
  rf_renderer_bind_texture_for_level_warmup(dword_662FBC);
  rf_renderer_bind_texture_for_level_warmup(dword_662FC0);
  rf_renderer_bind_texture_for_level_warmup(dword_662FC4);
  dword_662FEC = rf_bitmap_load_with_optional_mipmap_generation("fusion_rocket_armed.tga", (void *)0xFFFFFFFF, 1);
  dword_662FF0 = rf_bitmap_load_with_optional_mipmap_generation("fusion_rocket_safe.tga", (void *)0xFFFFFFFF, 1);
  dword_662FE0 = rf_bitmap_load_with_optional_mipmap_generation("boom01.vbm", (void *)0xFFFFFFFF, 1);
  unk_87C6D0 = rf_bitmap_animation_metadata_query(dword_662FE0, &flt_87C6D4);
  rf_renderer_bind_texture_for_level_warmup(dword_662FEC);
  rf_renderer_bind_texture_for_level_warmup(dword_662FF0);
  rf_renderer_bind_texture_for_level_warmup(dword_662FE0);
  dword_662FC8 = rf_bitmap_load_and_query_animation_metadata("assault_digits.vbm", &v8, &v6, (void *)0xFFFFFFFF);
  rf_renderer_bind_texture_for_level_warmup(dword_662FC8);
  dword_662FD8 = rf_bitmap_load_with_optional_mipmap_generation("railrifleGlowAlpha.tga", (void *)0xFFFFFFFF, 1);
  dword_662FDC = rf_bitmap_load_with_optional_mipmap_generation("smokedark.tga", (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(dword_662FD8);
  rf_renderer_bind_texture_for_level_warmup(dword_662FDC);
  rf_vector3_set_components_thiscall(flt_87C704, 0.0, 0.0099999998, 0.0);
  unk_87C710 = 0.1;
  unk_87C714 = 0.0099999998;
  unk_87C718 = 0.0;
  unk_87C71C = -0.2;
  unk_87C720 = 0.5;
  unk_87C724 = dword_662FDC;
  unk_87C728 = 1;
  rf_color4_set_bytes_return_destination(byte_87C72C, 255, 255, 255, 128);
  rf_color4_set_bytes_return_destination(byte_87C730, 255, 255, 255, 0);
  unk_87C734 = 100672014;
  unk_87C738 = 0;
  dword_662E30 = rf_bitmap_load_with_optional_mipmap_generation("riotshield1.tga", (void *)0xFFFFFFFF, 1);
  dword_662E34 = rf_bitmap_load_with_optional_mipmap_generation("RiotShieldHit.tga", (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(dword_662E30);
  rf_renderer_bind_texture_for_level_warmup(dword_662E34);
  for ( i = 0; i < 64; ++i )
  {
    v7 = (const char **)((char *)&rf_weapon_records + 1360 * i);
    if ( rf_string_length_from_cstr(v7 + 314) && !v7[316] )
    {
      v0 = (char *)rf_string_object_c_str_or_empty(v7 + 314);
      v3m_mode1 = rf_model_handle_load_v3m_mode1(v0, 1, (void *)0xFFFFFFFF);
      v7[316] = (const char *)v3m_mode1;
    }
    if ( rf_string_length_from_cstr(v7 + 318) )
    {
      if ( !v7[320] )
      {
        v2 = (char *)rf_string_object_c_str_or_empty(v7 + 318);
        instance = (const char *)rf_vfx_load_instance(v2, (int)byte_98967F);
        v7[320] = instance;
      }
    }
  }
  unk_87C6F4 = rf_model_handle_load_v3m_mode1("flmthrow_pilot.v3d", 1, (void *)0xFFFFFFFF);
  v4 = (char *)rf_string_object_c_str_or_empty((char *)&unk_912010 + 1360 * dword_911C78);
  unk_87C6F0 = rf_model_handle_load_v3m_mode1(v4, 1, (void *)0xFFFFFFFF);
  return rf_bitmap_set_load_context_byte(load_context_byte);
}

