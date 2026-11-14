// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004611B0 rf_browser_find_endpoint_or_insertion_index
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl(rawIPv4DWORD,rawPortWORD,outIndex*),bool AL. Binary search sorted108-byte records6F52CC/count6F51A8 by UNSIGNED DWORD at84 ascending,then both
// portWORD88 MOVZX to32 and signed comparisons (equivalent unsigned16 ordering). No byte swap,endpoint-padding compare or display-order lookup. Signed
// lower0/upper=count-1;mid=lower+(upper-lower)/2;write outIndex at EVERY probe. Exact pair ->AL1,any duplicate match (not first-equal guarantee). Miss ->outIndex=lower insertion
// position,AL0;empty/negative count yields0 without array read. No output-pointer/positive-count/base/capacity guard;assumes records already endpoint-sorted. Does not insert/mutate
// records.
char __cdecl rf_browser_find_endpoint_or_insertion_index(unsigned int a1, unsigned __int16 a2, int *a3)
{
  int i; // [esp+0h] [ebp-8h]
  int v5; // [esp+4h] [ebp-4h]

  v5 = 0;
  for ( i = unk_6F51A8 - 1; ; i = *a3 - 1 )
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
          if ( a1 <= *((_DWORD *)dword_6F52CC + 27 * *a3 + 21) )
            break;
          v5 = *a3 + 1;
        }
        if ( a1 >= *((_DWORD *)dword_6F52CC + 27 * *a3 + 21) )
          break;
        i = *a3 - 1;
      }
      if ( a2 <= (int)*((unsigned __int16 *)dword_6F52CC + 54 * *a3 + 44) )
        break;
      v5 = *a3 + 1;
    }
    if ( a2 >= (int)*((unsigned __int16 *)dword_6F52CC + 54 * *a3 + 44) )
      break;
  }
  return 1;
}

