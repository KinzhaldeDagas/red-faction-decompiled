// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D280 rf_entity_admits_speech_body_actions
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] Speech-animation admission predicate: non-null entity, nonzero entity+0x80 model pointer, and dword[entity+0x294 descriptor pointer +0x94]==2. The inner descriptor is not independently null-checked. This controls speech body-action timer initialization in 0x4376C0, not positional voice admission; do not label descriptor numeric value2 as a character class without further evidence.
// UNREALRED VERIFIED [combat-native-followup-20261104]: Body-action eligibility checks nonnull body, nonnull model handle at body+128 and EntityInfo dword+148 equal2. Does not test humanoid/sentient bits. A host bone/animation heuristic is not evidence of this class/model-kind gate; verify producer mapping before admitting ignition.
bool __cdecl rf_entity_admits_speech_body_actions(int a1)
{
  return a1 && *(_DWORD *)(a1 + 128) && *(_DWORD *)(*(_DWORD *)(a1 + 660) + 148) == 2;
}

