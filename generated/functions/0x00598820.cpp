// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598820 rf_audio_environment_is_muted_cached
// UNREALRED VERIFIED [audio-properties-20261028]: Returns bool(global0x1BCA2FC!=0). Does not check extension readiness,read property2 or confirm hardware level; mute helper sets this flag even on API failure.
bool rf_audio_environment_is_muted_cached()
{
  return unk_1BCA2FC != 0;
}

