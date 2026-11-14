// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004612B0 rf_endpoint_array100_find_or_insertion_index
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl(rawIPv4DWORD,rawPortWORD,outIndex*),bool AL. Same native binary-search contract on SEPARATE100-byte global array6F52E8/count6F52EC:IPv4DWORD0 unsigned
// ascending,portWORD4 zero-extended before signed comparisons. Probe writesmid tooutIndex;hitAL1 at any exact pair;miss storeslower/AL0;empty count ->index0. No byte order
// conversion,duplicate-first guarantee,capacity/base/output-pointer validation or insertion. Not the108-byte browser record/display-index array.
char __cdecl rf_endpoint_array100_find_or_insertion_index(unsigned int a1, unsigned __int16 a2, int *a3)
{
  int i; // [esp+0h] [ebp-8h]
  int v5; // [esp+4h] [ebp-4h]

  v5 = 0;
  for ( i = unk_6F52EC - 1; ; i = *a3 - 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        while ( 1 )
        {
          if ( i < v5 )
          {
            *a3 = v5;
            return 0;
          }
          *a3 = v5 + (i - v5) / 2;
          if ( a1 <= *(_DWORD *)(unk_6F52E8 + 100 * *a3) )
            break;
          v5 = *a3 + 1;
        }
        if ( a1 >= *(_DWORD *)(unk_6F52E8 + 100 * *a3) )
          break;
        i = *a3 - 1;
      }
      if ( a2 <= (int)*(unsigned __int16 *)(unk_6F52E8 + 100 * *a3 + 4) )
        break;
      v5 = *a3 + 1;
    }
    if ( a2 >= (int)*(unsigned __int16 *)(unk_6F52E8 + 100 * *a3 + 4) )
      break;
  }
  return 1;
}

