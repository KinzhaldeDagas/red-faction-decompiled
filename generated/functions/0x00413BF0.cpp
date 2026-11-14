// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413BF0 rf_clutter_registry_initialize_and_warm_textures
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Noargs. Sets class count666B60=0,global666B6C=0,clutter list-head andglobal666FA8 to sentinel666D18;does not destroy prior runtime objects/registry contents here. Loads clutter table via413CF0,stores lookup riot_shield index (possibly-1) in666B64. Loads three filenames through pointers6612D0/D4/D8,stores IDs666B68/80/70,and warms all three unconditionally;loads/warms glasshard_A.tga with ID held onlylocal. Stores sound lookup Riot Shield Impact in666B84;registers414520 at-exit cleanup and returns atexit result. No bitmap/sound success checks or rollback;repeated calls can retain prior per-slot optional fields/arrays and register more exit callbacks.
int rf_clutter_registry_initialize_and_warm_textures()
{
  int v1; // [esp+0h] [ebp-4h]

  unk_666B60 = 0;
  unk_666B6C = 0;
  rf_clutter_list_head = (int)&unk_666D18;
  unk_666FA8 = &unk_666D18;
  rf_clutter_registry_load_table();
  unk_666B64 = rf_clutter_class_find_index_by_name("riot_shield");
  dword_666B68 = rf_bitmap_load_with_optional_mipmap_generation(off_6612D0[0], (void *)0xFFFFFFFF, 1);
  dword_666B80 = rf_bitmap_load_with_optional_mipmap_generation(off_6612D4[0], (void *)0xFFFFFFFF, 1);
  dword_666B70 = rf_bitmap_load_with_optional_mipmap_generation(off_6612D8, (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(dword_666B68);
  rf_renderer_bind_texture_for_level_warmup(dword_666B80);
  rf_renderer_bind_texture_for_level_warmup(dword_666B70);
  v1 = rf_bitmap_load_with_optional_mipmap_generation("glasshard_A.tga", (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(v1);
  unk_666B84 = rf_foley_definition_find_name("Riot Shield Impact");
  return atexit(rf_clutter_class_registry_shutdown);
}

