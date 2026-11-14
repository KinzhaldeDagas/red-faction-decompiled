// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043BFA0 rf_entity_class_flag2000000_positive_scalar56
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl entity, NULL-safe canonical AL0/1. NonNULL requires class660 DWORD1828 mask02000000 nonzero, object
// FLOAT56 ORDERED strictly greater than original PE DOUBLE0, and entity DWORD2068 mask20 clear, in that short-circuit order. Equality, either signed zero, negative and NaN fail the
// floating gate. Does not inspect movement/action/weapon/player state or mutate anything; class pointer is unchecked after entityNULL check.
bool __cdecl rf_entity_class_flag2000000_positive_scalar56(int a1)
{
  if ( !a1 )
    return 0;
  return ((unsigned int)&unk_2000000 & *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828)) != 0
      && *(float *)(a1 + 56) > 0.0
      && (*(_DWORD *)(a1 + 2068) & 0x20) == 0;
}

