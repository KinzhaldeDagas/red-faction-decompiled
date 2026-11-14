// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ACE70 rf_multiplayer_powerup_icons_render
// UNREALRED VERIFIED [multiplayer-hud] Lazily loads and draws damage amplifier, invulnerability, and nano HUD icons from local-player flags 0x20000, 0x40000, and 0x80000 at decoded bottom anchors.
int rf_multiplayer_powerup_icons_render()
{
  int result; // eax
  int v1; // [esp+4h] [ebp-4h]

  result = rf_renderer_get_viewport_height();
  v1 = result;
  if ( dword_681E38 )
  {
    if ( (*(_DWORD *)(dword_681E38 + 2068) & 0x20000) != 0 )
    {
      if ( rf_hud_powerup_damage_bitmap == -1 )
        rf_hud_powerup_damage_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                         "hud_pow_damage.tga",
                                         (void *)0xFFFFFFFF,
                                         1);
      rf_render_color_set_rgba8(255, 255, 255, 255);
      rf_bitmap_draw_unscaled_clipped(rf_hud_powerup_damage_bitmap, 324, v1 - 53, unk_187CD38);
    }
    if ( (*(_DWORD *)(dword_681E38 + 2068) & 0x40000) != 0 )
    {
      if ( rf_hud_powerup_invulnerability_bitmap == -1 )
        rf_hud_powerup_invulnerability_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                                  "hud_pow_invuln.tga",
                                                  (void *)0xFFFFFFFF,
                                                  1);
      rf_render_color_set_rgba8(255, 255, 255, 255);
      rf_bitmap_draw_unscaled_clipped(rf_hud_powerup_invulnerability_bitmap, 271, v1 - 53, unk_187CD38);
    }
    result = dword_681E38;
    if ( (*(_DWORD *)(dword_681E38 + 2068) & 0x80000) != 0 )
    {
      if ( rf_hud_powerup_nano_bitmap == -1 )
        rf_hud_powerup_nano_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                       "hud_pow_nano.tga",
                                       (void *)0xFFFFFFFF,
                                       1);
      rf_render_color_set_rgba8(255, 255, 255, 255);
      return rf_bitmap_draw_unscaled_clipped(rf_hud_powerup_nano_bitmap, 384, v1 - 53, unk_187CD38);
    }
  }
  return result;
}

