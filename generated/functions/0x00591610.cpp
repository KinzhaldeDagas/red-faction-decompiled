// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591610 rf_audio_clear_property_extension_mode
// UNREALRED VERIFIED [dsound-playback-20261028]: Sets globalbyte0x193BBE2=0. Does not clear extension-ready0x1BCA304,release shared property interface or reset extension parameters.
void rf_audio_clear_property_extension_mode()
{
  unk_193BBE2 = 0;
}

