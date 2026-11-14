// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2AB0 rf_cd_detect_and_set_root
// UNREALRED VERIFIED [save-validation-20261028]: Scans optical media accepting either RF marker, passes returned index to0x4F2B20. On success formats Using %s for Red Faction CD text locally; returns setter result.
int rf_cd_detect_and_set_root()
{
  char Buffer[260]; // [esp+0h] [ebp-110h] BYREF
  int v2; // [esp+108h] [ebp-8h]
  int optical_drive_by_marker; // [esp+10Ch] [ebp-4h]

  optical_drive_by_marker = rf_cd_find_optical_drive_by_marker(nullptr);
  v2 = rf_cd_set_root_from_drive_index(optical_drive_by_marker);
  if ( v2 )
    sprintf(Buffer, "Using %s for Red Faction CD\n", &unk_88E598);
  return v2;
}

