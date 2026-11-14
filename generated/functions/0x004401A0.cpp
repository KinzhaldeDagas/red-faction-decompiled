// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004401A0 rf_foley_cache_broken_glass_footstep_index
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): No stack arguments. Calls446EE0 with exact CString Broken Glass Footstep, stores returned full EAX into shared DWORD661570 and returns that
// same EAX unchanged. No lookup-result validation, fallback, allocation, parser operation, exception-hook registration or input/output pointer args. Literal gameplay foley
// lookup/global cache write disproves inherited __initp_eh_hooks CRT-library identification; clear FUNC_LIB while preserving native bytes and other flags. Called directly by
// entity-resource initializer423520 after blood-resource initialization.
int rf_foley_cache_broken_glass_footstep_index()
{
  int result; // eax

  result = rf_foley_definition_find_name("Broken Glass Footstep");
  dword_661570 = result;
  return result;
}

