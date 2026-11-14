// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452680 rf_control_find_first_action_name_case_insensitive
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(required binding-context,nullable name C-string). Start signed index0; while index<current SIGNED DWORD[context+3596],
// re-reading count every condition, compare RFString object at context+24+28*index with name through5609B0. ANY nonzero AL returns that FIRST index immediately, ascending order;
// otherwise continue. Count<=0 or exhausted live range returns explicit fullEAX-1. No fixed128/other upper bound, context/count/pointer validation, whitespace trim, prefix match,
// numeric ID mapping, array snapshot or mutation. Shared comparison is exact case-insensitive and null/empty aware: stored extent0 record matches incoming NULL or empty string, so
// NULL name is not universally rejected; stale RFString extent/buffer behavior follows delegate. Record addressing uses wrapped32 multiplication/addition. Does not inspect binding
// codes or validate that matched index has usable display names.
int __cdecl rf_control_find_first_action_name_case_insensitive(int a1, char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < *(_DWORD *)(a1 + 3596); ++i )
  {
    if ( rf_string_equals_case_insensitive(a1 + 28 * i + 24, String2) )
      return i;
  }
  return -1;
}

