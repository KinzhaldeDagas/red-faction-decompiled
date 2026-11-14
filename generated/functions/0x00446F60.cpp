// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446F60 rf_foley_get_sound_by_index
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(signed FoleySetIndex,signed soundIndex), fullEAX selected DWORD or-1. Require0<=setIndex<SIGNED global6EDC30;
// then0<=soundIndex<DWORD[6E6E54+44*setIndex] with signed comparisons. Failure either level returns fullFFFFFFFF. Success loads table pointer DWORD[6E6E58+44*setIndex] and returns
// DWORD[table+4*soundIndex] verbatim, including any stored-1/0. No RNG, fallback-to-first, sound playback, pointer/table validation, allocation or mutation. Caller variant0 selects
// first stored sound rather than random Foley entry.
int __cdecl rf_foley_get_sound_by_index(int a1, int a2)
{
  if ( a1 < 0 || a1 >= unk_6EDC30 )
    return -1;
  if ( a2 >= 0 && a2 < unk_6E6E54[11 * a1] )
    return *(_DWORD *)(dword_6E6E58[11 * a1] + 4 * a2);
  return -1;
}

