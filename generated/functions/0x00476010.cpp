// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476010 rf_cutscene_level_reset
// UNREALRED VERIFIED [cutscene-ui-20261028]: Ends active cutscene through0x476BF0, destroys both camera/cutscene registries through0x475EE0, clears globals0x6FB24C,0x6FB248,0x6FB250. Returns backing-release helper value; no boolean status contract.
void **rf_cutscene_level_reset()
{
  void **result; // eax

  rf_cutscene_end_restore_player_state();
  result = rf_cutscene_registries_destroy_all();
  unk_6FB24C = 0;
  unk_6FB248 = 0;
  unk_6FB250 = 0;
  return result;
}

