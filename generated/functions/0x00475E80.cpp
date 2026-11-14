// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475E80 rf_cutscene_record_find_by_id
// UNREALRED VERIFIED [cutscene-ui-20261028]: Scans pointer-array0x6FB264; compares first dword of each record with caller identifier, returns first matching pointer or0. Does not compare names or start playback.
int __cdecl rf_cutscene_record_find_by_id(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_6FB264); ++i )
  {
    if ( **(_DWORD **)sub_552200(unk_6FB264, i) == a1 )
      return *(_DWORD *)sub_552200(unk_6FB264, i);
  }
  return 0;
}

