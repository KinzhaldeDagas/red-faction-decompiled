// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004766B0 rf_cutscene_ui_event_callback
// UNREALRED VERIFIED [cutscene-playback-20261028]: Forwards only low8 bits of event argument to0x442030 and returns its result. No direct skip/end-cutscene behavior in this wrapper.
char __cdecl rf_cutscene_ui_event_callback(char a1)
{
  return rf_gameplay_ui_pause_event_callback(a1);
}

