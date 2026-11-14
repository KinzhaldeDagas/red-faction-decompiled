// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041D2B0 rf_corpse_shutdown_hook_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Exact native55 8B EC 5D C3; registered atexit by corpse initialization. No list traversal, resource destruction, count reset or application writes. Preserves incoming EAX; no defined return value.
void __cdecl rf_corpse_shutdown_hook_noop()
{
  ;
}

