// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E4A90 rf_player_reset_vehicle_camera_and_chaingun_spin
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Assumes player nonNULL; store F32+0 to angle4296 then speed4300, DWORD0 to camera mode4292. Return player pointer EAX. No clearing of global camera nodes, model handles or shared animation latch.
int __cdecl rf_player_reset_vehicle_camera_and_chaingun_spin(int a1)
{
  *(float *)(a1 + 4296) = 0.0;
  *(float *)(a1 + 4300) = 0.0;
  *(_DWORD *)(a1 + 4292) = 0;
  return a1;
}

