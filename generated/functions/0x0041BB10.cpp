// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041BB10 rf_glare_runtime_flags692_has_mask2
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl glare pointer; AL bool true iff pointer nonnull and DWORD+692 mask2 set. Null returns false. No mutation or other flag checks. This mask is installed from attached-factory fourth argument and suppresses the class800 motion modulation in volumetric rendering.
bool __cdecl rf_glare_runtime_flags692_has_mask2(int a1)
{
  return a1 && (*(_DWORD *)(a1 + 692) & 2) != 0;
}

