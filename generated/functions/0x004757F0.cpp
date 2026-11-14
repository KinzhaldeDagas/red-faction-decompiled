// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004757F0 rf_ambient_sound_destroy_all_wrapper
// UNREALRED VERIFIED [cutscene-ui-20261028]: Delegates directly to rf_ambient_sounds_destroy_all. No additional state writes in wrapper.
void rf_ambient_sound_destroy_all_wrapper()
{
  rf_ambient_sounds_destroy_all();
}

