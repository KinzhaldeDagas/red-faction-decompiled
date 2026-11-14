// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475E30 rf_cutscene_camera_find_index_by_id
// UNREALRED VERIFIED [cutscene-ui-20261028]: Scans pointer-array0x6FB258; compares first dword of each pointed camera record with caller ID, returns first array index or-1. No null-element checks.
int __cdecl rf_cutscene_camera_find_index_by_id(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_6FB258); ++i )
  {
    if ( **(_DWORD **)sub_552200(unk_6FB258, i) == a1 )
      return i;
  }
  return -1;
}

