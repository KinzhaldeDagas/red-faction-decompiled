// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004368F0 rf_entity_apply_named_skin_profile
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity,Cstring name), fullEAX pass-through from4BD040(modelHandle128,signed MODEL-INFO
// pointer668 DWORD3964,profileBase=modelInfo+3968,name). No own NULL/name/count/model/body-class admission or pointer validation. Delegate scans108-byte profile records in signed
// order, compares RFString names case-insensitively, applies first matching profile, returns its index even if apply delegate fails; no match/count<=0 yields-1. First matching
// calculated record pointerNULL skips application but still returns index. Native wrapper simply forwards four slots and returns, with no ownership transfer, input-string change,
// fallback name, local state store or independent success normalization.
int __cdecl rf_entity_apply_named_skin_profile(int a1, char *String2)
{
  return rf_model_apply_first_matching_skin_profile(
           *(_DWORD *)(a1 + 128),
           *(_DWORD *)(*(_DWORD *)(a1 + 668) + 3964),
           *(_DWORD *)(a1 + 668) + 3968,
           String2);
}

