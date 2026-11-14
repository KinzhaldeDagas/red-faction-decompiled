// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402EB0 rf_ai_maybe_seek_weapon_waypoints
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One AI block. Only any-nonzero runtime or splitscreen enters. Consumes rand() BEFORE flags check; signed
// result>=8191 returns. Then flags+1328 mask0x800000 suppresses. Calls4013E0(block), which can repair negative selected weapon. Result-2 immediately delegates402B80(block) to
// weapon-prefixed waypoint search. Result>=0 consumes second rand(), signed-divides by(result+2), and remainder0 delegates same wrapper; negative other than-2 does nothing. Known
// lookup slots0..7 select divisors2..9; no own alternative index clamp or result normalization. EAX path-dependent random/quotient/mask/delegate value, not success. No own
// dead/inactive or authority-byte gate.
int __cdecl rf_ai_maybe_seek_weapon_waypoints(int *Character)
{
  int result; // eax
  int v2; // eax
  int v3; // et2
  int v4; // [esp+0h] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
  {
    result = rand();
    if ( result < 0x1FFF )
    {
      result = (unsigned int)&unk_800000 & Character[332];
      if ( !result )
      {
        result = rf_ai_current_weapon_priority_slot(Character);
        v4 = result;
        if ( result == -2 )
          return rf_ai_seek_weapon_waypoint_list((int)Character);
        if ( result >= 0 )
        {
          v2 = rand();
          v3 = v2 % (v4 + 2);
          result = v2 / (v4 + 2);
          if ( !v3 )
            return rf_ai_seek_weapon_waypoint_list((int)Character);
        }
      }
    }
  }
  return result;
}

