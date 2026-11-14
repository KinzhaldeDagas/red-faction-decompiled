// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052CC00 rf_geomod_intersection_record_index_find
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl vertexPointer,signedCount,arrayOfRecordPointers. Signedascending scan tests RECORD DWORD0==vertex; returnFIRST index. Absent ORcount<=0 returns0, indistinguishable fromfoundindex0, NOT-1. No sorting/dedup performed, pointer/recordvalidity guard, scalarcomparison or outputchange.
int __cdecl rf_geomod_intersection_record_index_find(int a1, int a2, int a3)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    if ( **(_DWORD **)(a3 + 4 * i) == a1 )
      return i;
  }
  return 0;
}

