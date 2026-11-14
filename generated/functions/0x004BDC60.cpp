// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDC60 rf_physics_state_test_enabled_al
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Cdecl physics-state pointer; AL bool reflects sign bit0x80000000 of DWORD state+288. No mutation or other flag test/null guard. Duplicate semantic predicate of4194F0, but caller-facing boolean result is AL rather than the explicit full-EAX BOOL canonicalization in that helper.
bool __cdecl rf_physics_state_test_enabled_al(int a1)
{
  return *(int *)(a1 + 288) < 0;
}

