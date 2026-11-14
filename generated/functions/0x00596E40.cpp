// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596E40 rf_file_transfer_find_peer_wire_id
// UNREALRED VERIFIED [file-transfer-20261028]: Arguments peer,16-bit wire ID,direction selector. Scans60 records; nonzero selector requires send bit2, zero requires receive bit4, then matches peer+420 and WORD ID+432. Returns record pointer or null. Does not independently require active bit1 or nonempty name.
int *__cdecl rf_file_transfer_find_peer_wire_id(int a1, __int16 a2, int a3)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 60; ++i )
  {
    if ( (!a3 || (unk_1BC3CC8[109 * i] & 2) != 0)
      && (a3 || (unk_1BC3CC8[109 * i] & 4) != 0)
      && unk_1BC3E6C[109 * i] == a1
      && unk_1BC3E78[218 * i] == a2 )
    {
      return &unk_1BC3CC8[109 * i];
    }
  }
  return nullptr;
}

