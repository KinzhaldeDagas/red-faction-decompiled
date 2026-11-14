// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2B80 rf_cd_clear_root_and_add_music_archive
// UNREALRED VERIFIED [save-validation-20261028]: Clears CD root through0x4F2B20(-1), then returns rf_vpackfile_add(music.vpp,null).
int rf_cd_clear_root_and_add_music_archive()
{
  rf_cd_set_root_from_drive_index(-1);
  return rf_vpackfile_add("music.vpp", nullptr);
}

