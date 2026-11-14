// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050D820 rf_weapon_count_empty_iteration
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): Native empty signed-count loop: local index0, compares against global911C68, increments until index>=count. No per-record access, calls, global writes, cleanup or resource release. EAX is incidental last increment for positive count, uninitialized when loop skipped. Do not invent a weapon shutdown action from adjacency.
int rf_weapon_count_empty_iteration()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_911C68; ++i )
    result = i + 1;
  return result;
}

