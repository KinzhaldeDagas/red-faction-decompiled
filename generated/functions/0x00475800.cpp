// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475800 rf_ambient_sound_level_reset
// UNREALRED VERIFIED [ambient-audio]: Runs ambient level cleanup and restores the persistent-list sentinel and tail to an empty state.
int rf_ambient_sound_level_reset()
{
  rf_ambient_sound_destroy_all_wrapper();
  rf_ambient_sound_list_head = &rf_ambient_sound_list_head;
  rf_ambient_sound_list_tail = &rf_ambient_sound_list_head;
  return 0;
}

