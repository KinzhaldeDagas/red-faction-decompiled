// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402B20 rf_ai_seek_ammo_waypoint_list
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): False CRT __fputchar/library identification corrected: one cdecl AI-block pointer is forwarded
// to402950(block,literal ammo), exactly two pushed args/8-byte cleanup. Existing verified delegate searches waypoint-list NAME PREFIXES case-insensitively, not nearby ammo pickups,
// and requests mode4 only on accepted list route. Wrapper has no guard, direct counter mutation or independent success result; EAX inherited incidentally from void delegate. Original
// literal and code bytes verified against PE.
int __cdecl rf_ai_seek_ammo_waypoint_list(int Character)
{
  int result; // eax

  sub_402950((int *)Character, "ammo");
  return result;
}

