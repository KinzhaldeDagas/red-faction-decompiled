// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476000 rf_cutscene_atexit_cleanup
// UNREALRED VERIFIED [cutscene-ui-20261028]: Delegates to rf_cutscene_registries_destroy_all. Does not independently end active playback.
void __cdecl rf_cutscene_atexit_cleanup()
{
  rf_cutscene_registries_destroy_all();
}

