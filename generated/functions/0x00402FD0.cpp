// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402FD0 rf_ai_maybe_seek_any_waypoint_list
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): Cdecl(AI block,LOWBYTE force). Requires any-nonzero runtime/splitscreen and AI flags+1328 mask0x800000 clear.
// ALWAYS consumes rand() even force byte nonzero. Force any nonzero OR signed random<511 delegates402B60(block), whose empty prefix admits all named waypoint lists. Other paths leave
// state unchanged except random consumption. No own owner/health/inactive validation or explicit success return; EAX is incidental random/mask/delegate value.
int __cdecl rf_ai_maybe_seek_any_waypoint_list(int Character, char a2)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
  {
    result = (unsigned int)&unk_800000 & *(_DWORD *)(Character + 1328);
    if ( !result )
    {
      result = rand();
      if ( a2 || result < 511 )
        return rf_ai_seek_any_waypoint_list(Character);
    }
  }
  return result;
}

