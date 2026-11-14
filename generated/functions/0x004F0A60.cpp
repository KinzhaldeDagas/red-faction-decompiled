// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0A60 rf_register_retail_loose_search_roots
// UNREALRED VERIFIED [loose-root-registration] Registers RF retail direct roots in order: base, data/movies, data, savegame, user_maps/multi, then user_maps/single, each with its own decoded extension mask.
int rf_register_retail_loose_search_roots()
{
  int result; // eax

  dword_88E3F4 = rf_vfile_register_loose_search_root((char *)&unk_63D3BE, ".vpp .plr .txt .map .bty .btz .ver", 1);
  unk_88E3F8 = rf_vfile_register_loose_search_root("data\\movies", "*.bik", 1);
  unk_88E400 = rf_vfile_register_loose_search_root("data", "*.cfg", 1);
  unk_88E41C = rf_vfile_register_loose_search_root("savegame", "*.svl", 0);
  unk_88E440 = rf_vfile_register_loose_search_root("user_maps\\multi", "*.vpp", 0);
  result = rf_vfile_register_loose_search_root("user_maps\\single", "*.vpp", 0);
  unk_88E43C = result;
  return result;
}

