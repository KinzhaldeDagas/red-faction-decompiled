// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437DF0 rf_entity_decrement_counter1424_and_reset_if_negative
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity,raw reset DWORD), canonical AL0/1. NULL returns0 without writes. Otherwise load counter
// entity5156, subtract1 with32-bit wrap, STORE decremented value before SIGNED comparison. If new value>=0 return0 while retaining it; only new SIGNED value<0 stores raw reset
// argument into5156 and returns1. Thus initial1 becomes0/false, initial0 triggers reset/true, INT_MIN wrapsINT_MAX/false. Reset may itself be negative; no clamp or unit/frame/time
// interpretation. Does not test437DC0, which accepts zero before this decrement path resets it.
char __cdecl rf_entity_decrement_counter1424_and_reset_if_negative(int a1, int a2)
{
  if ( !a1 )
    return 0;
  if ( (int)--*(_DWORD *)(a1 + 5156) >= 0 )
    return 0;
  *(_DWORD *)(a1 + 5156) = a2;
  return 1;
}

