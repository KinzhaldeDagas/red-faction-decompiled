// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005895B0 rf_character_build_aux_bindings_disabled
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Entry unconditionally XORs AL to0 and jumps to epilogue, then RET4. Thus returns false and does not build bindings for normal entry callers. Retained unreachable body checks model count and duplicates auxiliary100/sphere44 binding construction; do NOT treat it as live loading behavior. ECX is saved for that dead body; existing inferred stdcall stack-argument ABI left unchanged. Caller at588025 tests AL and fails its legacy load path.
char __stdcall rf_character_build_aux_bindings_disabled(int a1)
{
  return 0;
}

