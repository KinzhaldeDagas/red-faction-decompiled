// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E780 rf_vpackfile_init
// UNREALRED VERIFIED [vpp-streaming] Initializes the VPP lookup table and mounts retail packs in fixed order: audio, maps_en, campaign/multiplayer levels, maps1..4, meshes, motions, music, tables, then ui.
int rf_vpackfile_init()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  rf_vpackfile_count = 0;
  rf_vpackfile_entry_count = 0;
  for ( i = 0; i < 20713; ++i )
  {
    rf_vpackfile_lookup_table[2 * i] = -1;
    unk_1C67474[2 * i] = 0;
  }
  rf_string_pool_allocate_owned(byte_1C8FBC8, 0x40000u);
  rf_vpackfile_add("audio.vpp", nullptr);
  rf_vpackfile_add("maps_en.vpp", nullptr);
  rf_vpackfile_add("levels1.vpp", nullptr);
  rf_vpackfile_add("levels2.vpp", nullptr);
  rf_vpackfile_add("levels3.vpp", nullptr);
  rf_vpackfile_add("levelsm.vpp", nullptr);
  rf_vpackfile_add("levelseb.vpp", nullptr);
  rf_vpackfile_add("levelsbg.vpp", nullptr);
  rf_vpackfile_add("maps1.vpp", nullptr);
  rf_vpackfile_add("maps2.vpp", nullptr);
  rf_vpackfile_add("maps3.vpp", nullptr);
  rf_vpackfile_add("maps4.vpp", nullptr);
  rf_vpackfile_add("meshes.vpp", nullptr);
  rf_vpackfile_add("motions.vpp", nullptr);
  rf_vpackfile_add("music.vpp", nullptr);
  rf_vpackfile_add("tables.vpp", nullptr);
  result = rf_vpackfile_add("ui.vpp", nullptr);
  rf_vpackfile_initialized = 1;
  return result;
}

