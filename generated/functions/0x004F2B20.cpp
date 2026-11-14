// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2B20 rf_cd_set_root_from_drive_index
// UNREALRED VERIFIED [save-validation-20261028]: Nonnegative index formats lowercase drive root at0x88E598 using index+97, copies it via0x57E330, returns1. Negative index clears only root first byte and returns0; no upper drive-index bound here.
int __cdecl rf_cd_set_root_from_drive_index(int a1)
{
  if ( a1 >= 0 )
  {
    sprintf(&unk_88E598, "%c:\\", a1 + 97);
    rf_vpackfile_set_external_root_path(&unk_88E598);
    return 1;
  }
  else
  {
    unk_88E598 = 0;
    return 0;
  }
}

