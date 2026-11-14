// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00404F90 sub_404F90
// UNREALRED VERIFIED [combat-panic-20261104]: Numeric17 update calls40ECE0 route update then405030 speech, then persistent expiry testAI+254. Expired armed branch40B6D0true calls40B2D0; else samples[30,40] and passes returned float at405006 into40AC80 with currentstoredtarget. In standalone both ordinary recovery paths have mode17 guards, so expiry alone is NOT restoration to idle/combat. Other target-type/MP branches remain distinct.
// UNREALRED VERIFIED [combat-reaction-20261111]: Expired AI+254 calls40B6D0 on every elapsed tick, without rearming. True calls40B2D0. False samples float[30,40], stores binary32 at405006, THEN reads CURRENT stored target AI+2C0 and calls40AC80. Route update and405030 speech precede this phase; unrepresented host speech/route providers must not invent a native expiry gate.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] Panic expiry unarmed branch calls5677D0(30,40) BEFORE loading current target and40AC80 reaction. Use shared rand15→stored binary32 unit mapping with final binary32 range result; an absent host RNG cannot become fabricated duration or a completed false decision.
char __cdecl sub_404F90(int *Character)
{
  char result; // al
  float v2; // [esp+4h] [ebp-4h]

  rf_ai_route_update((int)(Character + 186));
  sub_405030(Character);
  result = rf_replicator_has_elapsed(Character + 149);
  if ( result == 1 )
  {
    if ( sub_40B6D0(Character) == 1 )
    {
      return sub_40B2D0(Character);
    }
    else
    {
      v2 = rf_random_float_range(30.0, 40.0);
      return sub_40AC80(Character, Character[176], v2);
    }
  }
  return result;
}

