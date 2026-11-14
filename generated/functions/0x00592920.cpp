// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592920 rf_vfile_loose_lookup_free_bucket_chains
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl shutdown called by57B840. For all32768 bucket heads1BA1F00, saves old head, clears head, walks links at node+8, frees separately allocated pointer at node+4 then frees node itself. Returns32768. Does not zero auxiliary DWORD1BA1EF8 here, free shared-string pool itself or check for cycles. Distinct from5928D0 initialization which clears heads without frees.
int rf_vfile_loose_lookup_free_bucket_chains()
{
  int result; // eax
  void *v1; // [esp+0h] [ebp-Ch]
  void *Block; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < 0x8000; ++i )
  {
    Block = (void *)dword_1BA1F00[i];
    dword_1BA1F00[i] = 0;
    while ( Block )
    {
      v1 = *((void **)Block + 2);
      free(*((void **)Block + 1));
      free(Block);
      Block = v1;
    }
    result = i + 1;
  }
  return result;
}

