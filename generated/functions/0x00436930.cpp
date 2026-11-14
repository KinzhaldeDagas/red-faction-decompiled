// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00436930 rf_entity_find_body_action_slot_by_name
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity,Cstring name), fullEAX first slot0..44 or-1. NULL name immediately returns-1 BEFORE entity
// admission; empty nonNULL Cstring is allowed.40D280 speech/body-action predicate ANY nonzero required (nonnull entity/model and class DWORD148==2); AL0 returns-1. Fixed signed loop
// i0..<45 checks slot definition index DWORD[entity+2648+16*i]>=0; negative skips, no positive upper bound. Compare RFString at[GAMEPLAY class660 DWORD1888+52*definitionIndex] to
// supplied Cstring via5609B0; ANY nonzero AL returns i immediately. Exhaustion returns-1. Reads slot+4 definition index, NOT slot animation-record DWORD2644 and not action-active
// state; does not require that record be valid/playing. Whole case-insensitive comparison has no trimming/prefix match; empty input may match empty RFString. No own state writes,
// pool-length/model-node check or fallback.
int __cdecl rf_entity_find_body_action_slot_by_name(int a1, char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  if ( !String2 )
    return -1;
  if ( !rf_entity_admits_speech_body_actions(a1) )
    return -1;
  for ( i = 0; i < 45; ++i )
  {
    if ( *(int *)(a1 + 16 * i + 2648) >= 0
      && rf_string_equals_case_insensitive(
           *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1888) + 52 * *(_DWORD *)(a1 + 16 * i + 2648),
           String2) )
    {
      return i;
    }
  }
  return -1;
}

