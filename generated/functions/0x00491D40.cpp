// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491D40 rf_respawn_score_pointer_compare
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl qsort-style pointers-to-record-pointers. Reads FLOAT64 from each pointed68-byte respawn record. Returns-1 if ordered scoreA<scoreB,+1 if ordered scoreA>scoreB,0 on equality
// OR unordered(NaN). First compare TEST AH,41 then second TEST AH,5/JP implements this; do not assume NaN receives an ordered end position. No pointer guard or score mutation.
int __cdecl rf_respawn_score_pointer_compare(const void *a1, const void *a2)
{
  if ( *(float *)(*(_DWORD *)a2 + 64) <= (double)*(float *)(*(_DWORD *)a1 + 64) )
    return *(float *)(*(_DWORD *)a2 + 64) < (double)*(float *)(*(_DWORD *)a1 + 64);
  else
    return -1;
}

