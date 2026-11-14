// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E4A40 rf_player_cycle_vehicle_camera_and_play_sound
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Assumes player nonNULL. Increment DWORD camera mode4292 with32-bit wrap, then SIGNED remainder4 via sign-corrected mask; valid0..3 cycles0->1->2->3->0. Corrupt negative/overflow values are not normalized as unsigned modulo. Store mode, play shared camera-change event87C6B0 with0,F320,F321 and return gamesound helper EAX. No vehicle/node eligibility check.
int __cdecl rf_player_cycle_vehicle_camera_and_play_sound(int a1)
{
  *(_DWORD *)(a1 + 4292) = (*(_DWORD *)(a1 + 4292) + 1) % 4;
  return rf_gamesound_play_event(unk_87C6B0, 0, 0.0, 1.0);
}

