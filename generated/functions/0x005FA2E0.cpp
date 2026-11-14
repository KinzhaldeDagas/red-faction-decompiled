// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA2E0 rf_bluebeard_metadata_find_first_free_slot
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Scans indices0..4095 for first record whose flags172&0x10000000==0. On found sets global BYTE0x1F6D24B=0,returns pointer to180-byte record. Does NOT mark slot active,clear its contents or advance iteration cursor. Full pool returnsNULL without flag change. Caller metadata loader initializes record.
char *rf_bluebeard_metadata_find_first_free_slot()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 4096; ++i )
  {
    if ( (unk_1F6D3DC[45 * i] & 0x10000000) == 0 )
    {
      unk_1F6D24B = 0;
      return (char *)&unk_1F6D330 + 180 * i;
    }
  }
  return nullptr;
}

