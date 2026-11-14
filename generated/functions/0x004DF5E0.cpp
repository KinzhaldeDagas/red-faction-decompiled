// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DF5E0 rf_player_request_suicide_or_apply_fixed_damage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl player; NULL does nothing. Multiplayer byte EXACT1 invokes no-argument local suicide helper49ACC0, so supplied nonlocal record is not passed into that branch. Other mode values call damage_dispatch(player entity handle20,float1000,-1,-1,-1,0,-1,0), discard x87 return with FSTP ST, pop32. No own entity/alive/player-ownership/authority validation or guarantee1000 damage kills. No uniform return value.
void __cdecl rf_player_request_suicide_or_apply_fixed_damage(int a1)
{
  if ( a1 )
  {
    if ( rf_multiplayer_runtime_mode == 1 )
      sub_49ACC0();
    else
      rf_damage_dispatch(*(_DWORD *)(a1 + 20), 1000.0, -1, -1, -1, 0, -1, 0);
  }
}

