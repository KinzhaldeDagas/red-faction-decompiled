// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B08F0 rf_multiplayer_compare_stats_word0_descending
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl qsort comparator of pointers-to-player-pointers. Dereference each Player.statsDWORD44 then SIGNED WORD at offset0 (not scoreboard scoreWORD2).
// Return-1 when left greater,+1 when smaller,0 equal; no subtraction overflow, secondary key, stable tie policy or NULL guards. Used by4B0950 auto-balance ordering.
int __cdecl rf_multiplayer_compare_stats_word0_descending(const void *a1, const void *a2)
{
  if ( **(__int16 **)(*(_DWORD *)a1 + 44) <= **(__int16 **)(*(_DWORD *)a2 + 44) )
    return **(__int16 **)(*(_DWORD *)a1 + 44) < **(__int16 **)(*(_DWORD *)a2 + 44);
  else
    return -1;
}

