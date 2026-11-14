// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005888A0 rf_v3c_wait_chunk_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Called by resource chunk dispatch for numeric tag0x57414954. Saves ECX to stack and returns with RET4; neither accesses supplied stack argument nor consumes/skips stream bytes. No object/global writes. Prior generic library label was a false semantic lead; do not describe this branch as parsing WAIT payload.
void __stdcall rf_v3c_wait_chunk_noop(int a1)
{
  ;
}

