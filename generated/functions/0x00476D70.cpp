// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476D70 rf_cutscene_aux_record_find_by_id
// UNREALRED VERIFIED [cutscene-playback-20261028]: Scans signed count0x6FB248 of16-byte records at0x6FB270; matches first dword against caller ID and returns first record pointer, else0. Meaning of remaining12 bytes not established here. No bounds cap or record mutation.
int *__cdecl rf_cutscene_aux_record_find_by_id(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_6FB248; ++i )
  {
    if ( unk_6FB270[4 * i] == a1 )
      return &unk_6FB270[4 * i];
  }
  return nullptr;
}

