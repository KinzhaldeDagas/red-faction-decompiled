// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DC620 rf_player_render_fpgun_or_carried_corpse
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player. Missing resolved entity returns0; only fpgun-presentation predicate EXACT1 proceeds. Calls fpgun renderer; ANY nonzero render result skips all fallback. Zero result arms random timestamp60 via4EBD20, then if entity carried-body handle1884!=-1 calls carried-corpse preparation/render helper. AL is whichever gate/helper last produced EAX, not uniform visibility/success status. No cockpit render in this function or own pointer/model guard.
char __cdecl rf_player_render_fpgun_or_carried_corpse(int a1)
{
  int v1; // eax
  int v3; // [esp+4h] [ebp-4h]

  v1 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v3 = v1;
  if ( v1 )
  {
    LOBYTE(v1) = rf_player_should_use_fpgun_presentation(a1);
    if ( (unsigned __int8)v1 == 1 )
    {
      LOBYTE(v1) = rf_player_render_fpgun(a1);
      if ( !(_BYTE)v1 )
      {
        LOBYTE(v1) = sub_4EBD20(a1);
        if ( *(_DWORD *)(v3 + 1884) != -1 )
          LOBYTE(v1) = (unsigned __int8)rf_player_prepare_and_render_carried_corpse(a1);
      }
    }
  }
  return v1;
}

