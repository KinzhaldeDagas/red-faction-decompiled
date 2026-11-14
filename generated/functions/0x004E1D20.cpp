// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1D20 rf_player_set_four_dword_payload200_and_float216
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL; store sixth argument as F32 into+216, then four DWORD arguments into+200,+204,+208,+212 in order. Native EAX ends as third payload DWORD (fourth overall argument). No clamping, byte packing, phase reset or status result; distinct from HUD tint bytes+4304 and alpha+4308. Higher-level payload meaning not assigned.
int __cdecl rf_player_set_four_dword_payload200_and_float216(int a1, int a2, int a3, int a4, int a5, float a6)
{
  *(float *)(a1 + 216) = a6;
  *(_DWORD *)(a1 + 200) = a2;
  *(_DWORD *)(a1 + 204) = a3;
  *(_DWORD *)(a1 + 208) = a4;
  *(_DWORD *)(a1 + 212) = a5;
  return a4;
}

