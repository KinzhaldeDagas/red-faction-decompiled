// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8970 rf_v3c_mesh_metadata100_destruct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mesh initializers, binary reader stores, caller layouts and signature classification): No-op metadata destructor used by100-byte array cleanup: spills ECX to a stack local, restores stack and returns. No object writes, frees, calls or stack-argument cleanup. Preserves existing library classification.
void __thiscall rf_v3c_mesh_metadata100_destruct_noop(void *this)
{
  ;
}

