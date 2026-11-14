// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004756C0 rf_ambient_sound_system_construct
// UNREALRED VERIFIED [ambient-audio]: Initializes the persistent ambient intrusive-list sentinel, tail, record count, and level-owned bookkeeping, then registers shutdown cleanup.
int rf_ambient_sound_system_construct()
{
  rf_ambient_sound_list_head = &rf_ambient_sound_list_head;
  rf_ambient_sound_list_tail = &rf_ambient_sound_list_head;
  rf_ambient_sound_record_count = 0;
  unk_6FB200 = 0;
  unk_6FB204 = -1;
  return atexit(rf_ambient_sounds_destroy_all);
}

