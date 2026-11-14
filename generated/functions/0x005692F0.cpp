// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005692F0 rf_sound_resource_registered_count_get
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl no arguments. Returns signed DWORD sound resource count1DAE7C8 directly throughEAX. No filtering by readiness,record population or active voice count; no mutation.
int __cdecl rf_sound_resource_registered_count_get()
{
  return rf_sound_resource_count;
}

