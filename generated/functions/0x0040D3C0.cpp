// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D3C0 rf_entity_class_use_is4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): One cdecl entity pointer. Null yields canonicalAL0; otherwise class pointer DWORD entity+660 is
// dereferenced without its own null guard, compares class DWORD+436==EXACT4 and returns canonicalAL1/0. Does not dispatch by common object type or prove this input is entity-backed,
// so not a general shared-use classifier for arbitrary common object types. No state writes/deadline/ownership tests; upperEAX bits not independently canonicalized.
bool __cdecl rf_entity_class_use_is4(int a1)
{
  return a1 && *(_DWORD *)(*(_DWORD *)(a1 + 660) + 436) == 4;
}

