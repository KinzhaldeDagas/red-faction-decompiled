// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050D2E0 sub_50D2E0
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Weapon-registry startup initializes 64 records: world handle+0x30=0, grip node+0x38=-1 and other cached fields. It then parses the weapon table and selects active configuration. Registers 50ADC0 at exit. Canonical global weapon IDs are resolved from registry strings.
int sub_50D2E0()
{
  float *v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 64; ++i )
  {
    v1 = (float *)((char *)&rf_weapon_records + 1360 * i);
    v1[83] = 0.0;
    v1[14] = NAN;
    v1[12] = 0.0;
    v1[13] = NAN;
    v1[153] = 0.0;
  }
  dword_911C68 = 0;
  rf_weapon_table_initialize();
  rf_weapon_recompute_lifetime_velocity_product();
  rf_rail_trail_load_alpha_bitmap();
  rf_weapon_derive_flags2_threshold_bits();
  rf_weapon_id_rocket_launcher = sub_50FB80("Rocket Launcher");
  dword_911C78 = sub_50FB80("remote charge");
  unk_911C88 = sub_50FB80("remote charge detonator");
  unk_911CB4 = sub_50FB80("Sniper Rifle");
  dword_911CBC = sub_50FB80("12mm handgun");
  dword_911CC4 = sub_50FB80("machine pistol");
  unk_911C98 = sub_50FB80("machine pistol special");
  rf_weapon_index_grenade = sub_50FB80("grenade");
  dword_911C80 = sub_50FB80("riot shield");
  rf_weapon_id_riot_stick = sub_50FB80("Riot Stick");
  rf_weapon_id_flamethrower = sub_50FB80("flamethrower");
  rf_weapon_id_shotgun = sub_50FB80("Shotgun");
  dword_911CE0 = sub_50FB80("rail_gun");
  unk_911CCC = sub_50FB80("Assault Rifle");
  unk_911CC8 = sub_50FB80("heavy_machine_gun");
  rf_weapon_id_shoulder_cannon = sub_50FB80("shoulder_cannon");
  unk_911CD4 = sub_50FB80("scope_assault_rifle");
  unk_911C6C = sub_50FB80("Undercover 12mm handgun");
  unk_911C9C = sub_50FB80("APC Minigun");
  rf_weapon_id_apc_rocket = sub_50FB80("APC Rocket");
  unk_911CB8 = sub_50FB80("Fighter Minigun");
  rf_weapon_id_fighter_rocket = sub_50FB80("Fighter Rocket");
  unk_911C90 = sub_50FB80("Jeep Gun");
  unk_911CD0 = sub_50FB80("Drill");
  unk_911CDC = sub_50FB80("Torpedo");
  rf_weapon_id_heap = sub_50FB80("HEAP");
  unk_911C8C = sub_50FB80("Vauss");
  unk_911CB0 = sub_50FB80("Sea Creature Attack");
  dword_911C74 = rf_bitmap_load_with_optional_mipmap_generation("bubble01_A.tga", (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(dword_911C74);
  dword_911F74 = (int)&unk_911CE8;
  unk_911F78 = &unk_911CE8;
  return atexit(sub_50ADC0);
}

