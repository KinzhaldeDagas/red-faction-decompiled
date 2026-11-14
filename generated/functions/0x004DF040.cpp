// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DF040 rf_player_dispatch_use_if_nonnull
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl player. NULL does nothing; otherwise invokes rf_player_dispatch_use_after_local_special_action(player), including its local-special/remote-network/general dispatch rules. No entity resolution, action-eligibility check, timing or return-status handling here.
void __usercall rf_player_dispatch_use_if_nonnull(double a1@<st0>, _DWORD *a2)
{
  if ( a2 )
    rf_player_dispatch_use_after_local_special_action(a1, a2);
}

