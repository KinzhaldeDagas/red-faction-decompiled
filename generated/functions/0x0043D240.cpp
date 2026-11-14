// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043D240 rf_blood_effect_resources_init
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Register atexit cleanup0x43D350; load3 texture names at0x661534 and2 at0x661540, bloodsplat.vbm animation and named bloodsplat effect; load somenewblood_A.tga into0x6E6230 for surface marks. Initialize5 cached handles0x6E623C to-1 and store0x486B40(gib bounce) result0x6E6250. Does not initialize8-mark free/active rings;0x43D360 is separate.
int rf_blood_effect_resources_init()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-8h] BYREF
  int i; // [esp+4h] [ebp-4h]

  atexit(rf_entity_info_noop_hook);
  for ( i = 0; i < 3; ++i )
    unk_6E6258[i] = rf_bitmap_load_with_optional_mipmap_generation(off_661534[i], (void *)0xFFFFFFFF, 1);
  for ( i = 0; i < 2; ++i )
    unk_6E6234[i] = rf_bitmap_load_with_optional_mipmap_generation(off_661540[i], (void *)0xFFFFFFFF, 1);
  dword_661548 = rf_bitmap_load_and_query_animation_metadata("bloodsplat.vbm", &dword_66154C, &v1, (void *)0xFFFFFFFF);
  unk_6E622C = sub_507610("bloodsplat");
  unk_6E6230 = rf_bitmap_load_with_optional_mipmap_generation("somenewblood_A.tga", (void *)0xFFFFFFFF, 1);
  for ( i = 0; i < 5; ++i )
    unk_6E623C[i] = -1;
  result = rf_material_custom_sound_set_find("gib bounce");
  unk_6E6250 = result;
  return result;
}

