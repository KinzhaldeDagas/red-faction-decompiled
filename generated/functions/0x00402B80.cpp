// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402B80 rf_ai_seek_weapon_waypoint_list
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): False CRT __fputchar_2/library identification corrected: one cdecl AI block forwarded to402950(block,literal
// weapon), two pushed args/8-byte cleanup. Existing verified delegate searches case-insensitive waypoint-list name PREFIXES and installs route/mode4 only on success; wrapper does not
// enumerate weapon pickups, grant weapons or remove inventory. No own guard or defined success return; EAX incidental.
int __cdecl rf_ai_seek_weapon_waypoint_list(int Character)
{
  int result; // eax

  sub_402950((int *)Character, "weapon");
  return result;
}

