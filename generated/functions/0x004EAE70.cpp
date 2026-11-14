// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EAE70 rf_player_query_alt_zoom_factor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Unequal global local-fpgun pointer returns x87+0. Equal pointer resolves own entity20 with no independent playerNULL guard. If BOTH flag bytes3988/3989 arezero, reset zoom; independently dead predicate AL EXACT1 (including missing entity) resets again. Return F32 player3992 promoted through ST0 unchanged otherwise. Reset writes factor0, not1, and does not stop global zoom sound. Noncanonical nonzero flag bytes avoid no-flags reset; this query has side effects and no upper/lower clamp.
double __cdecl rf_player_query_alt_zoom_factor(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( a1 != rf_local_fpgun_player )
    return 0.0;
  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !*(_BYTE *)(a1 + 3988) && !*(_BYTE *)(a1 + 3989) )
    rf_player_reset_alt_zoom_state(a1);
  if ( rf_entity_is_dead(v2) )
    rf_player_reset_alt_zoom_state(a1);
  return *(float *)(a1 + 3992);
}

