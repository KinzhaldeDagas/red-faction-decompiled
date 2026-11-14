// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004125E0 rf_ai_destroy_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Thiscall ECX embedded AI block, no stack args/plainRET. First destroys dual-pose members through412660(this+744), then
// pointer-array backing storage at this+524. Does not free this block, reset timers/route state, detach target or delete pointed-to objects itself. MSVC SEH state0->-1 with unwind
// map657EA8 and attached622320 tail ensures remaining+524 array cleanup when first member destruction unwinds. No explicit result; no NULL guards.
void __thiscall rf_ai_destroy_members(void **this)
{
  rf_ai_route_pose_members_destroy(this + 186);
  rf_pointer_array_destroy_backing_storage(this + 131);
}

