// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D440 rf_entity_class_flags724_has_mask4000000
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): One cdecl entity pointer. Null returns canonicalAL0. Otherwise dereferences class pointer entity+660, reads
// class DWORD+1828 and returnsAL1 iff mask0x04000000 set. No class-pointer guard, object-type dispatch, runtime-state mutation or broader authored-flag label inferred. UpperEAX bits
// are incidental.
bool __cdecl rf_entity_class_flags724_has_mask4000000(int a1)
{
  return a1 && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x4000000) != 0;
}

