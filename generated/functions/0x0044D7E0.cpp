// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044D7E0 rf_hud_status_bitmaps_initialize
// UNREALRED VERIFIED [ingame-hud-layers] Loads eleven health and envirosuit frames plus on-foot/vehicle directional damage, corpse, jeep, driller, and common vehicle-frame HUD bitmaps.
int rf_hud_status_bitmaps_initialize()
{
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 11; ++i )
    unk_6EFD5C[i] = rf_hud_load_frame_zero_bitmap(&aHealth0Tga[16 * i]);
  for ( j = 0; j < 11; ++j )
    unk_6EFD30[j] = rf_hud_load_frame_zero_bitmap(&aEnviro0Tga[16 * j]);
  rf_hud_damage_indicator_on_foot_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                             "damage_indicator.tga",
                                             (void *)0xFFFFFFFF,
                                             1);
  rf_hud_damage_indicator_on_foot_vertical_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                                      "damage_indicator_v.tga",
                                                      (void *)0xFFFFFFFF,
                                                      1);
  rf_hud_damage_indicator_vehicle_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                             "vdamage_indicator.tga",
                                             (void *)0xFFFFFFFF,
                                             1);
  rf_hud_damage_indicator_vehicle_vertical_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                                      "vdamage_indicator_v.tga",
                                                      (void *)0xFFFFFFFF,
                                                      1);
  dword_661878 = rf_bitmap_load_with_optional_mipmap_generation("body_indicator.tga", (void *)0xFFFFFFFF, 1);
  dword_66187C = rf_bitmap_load_with_optional_mipmap_generation("health_jeep.tga", (void *)0xFFFFFFFF, 1);
  dword_661880 = rf_bitmap_load_with_optional_mipmap_generation("health_driller.tga", (void *)0xFFFFFFFF, 1);
  dword_661884 = rf_bitmap_load_with_optional_mipmap_generation("health_vehicleframe.tga", (void *)0xFFFFFFFF, 1);
  return atexit(rf_hud_status_bitmaps_atexit_noop);
}

