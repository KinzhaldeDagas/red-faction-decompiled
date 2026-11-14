// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00492230 rf_multiplayer_full_scoreboard_gate
// UNREALRED VERIFIED [multiplayer-hud] Forwards the caller's active byte to the full multiplayer score screen unless the decoded suppressor byte is set.
void __cdecl rf_multiplayer_full_scoreboard_gate(char a1)
{
  if ( byte_704E83 != 1 )
    rf_multiplayer_full_scoreboard_render(a1);
}

