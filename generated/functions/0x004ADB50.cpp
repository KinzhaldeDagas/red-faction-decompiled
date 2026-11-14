// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ADB50 rf_multiplayer_load_network_update_rate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout):
// Corrected ABI: int cdecl(void), no incoming ECX argument. Entry PUSH ECX only reserves local4-byte registry output; native never reads incoming ECX. Call
// registry_read_dword_or_default(NULL,'UpdateRate',&local,2600), then read written local regardless helper status. Store662C60 and signed-clamp minimum2600 (different from console
// minimum1000); no upper clamp. If local player nonNULL dereference net1200 unguarded and copy full32 rate to+2492. No packet send or registry write-back of clamp; no
// runtime/authority gate. EAX incidental: registry delegate result without local player, local net pointer otherwise, not rate or uniform success.
int __cdecl rf_multiplayer_load_network_update_rate()
{
  int v0; // ecx
  int result; // eax
  BYTE Data[4]; // [esp+0h] [ebp-4h] BYREF

  *(_DWORD *)Data = v0;
  result = rf_registry_read_dword_or_default(nullptr, "UpdateRate", Data, 2600);
  *(_DWORD *)&dword_662C60 = *(_DWORD *)Data;
  if ( *(int *)Data < 2600 )
    *(_DWORD *)&dword_662C60 = 2600;
  if ( rf_local_fpgun_player )
  {
    result = *(_DWORD *)(rf_local_fpgun_player + 4608);
    *(_DWORD *)(result + 2492) = *(_DWORD *)&dword_662C60;
  }
  return result;
}

