// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004194F0 rf_physics_state_is_enabled
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl physics-state pointer. Reads DWORD P+288, masks0x80000000 and canonicalizes to full EAX BOOL0/1 with NEG/SBB/NEG. No mutation or other flag tests. Callers pass common object+136; common flags+124 are a different owner. No null guard.
BOOL __cdecl rf_physics_state_is_enabled(int a1)
{
  return *(int *)(a1 + 288) < 0;
}

