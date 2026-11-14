// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00451640 rf_binding_context_find_RFString_name
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(required context,required RFString object pointer), fullEAX first matching index or-1. Signed
// index0 while index<context DWORD3596, re-read live count every iteration. Compare RFString at context+24+28*index with SECOND RFString OBJECT via560910, not a Cstring comparison;
// ANY nonzero AL returns that index. Nonpositive count skips all records; no128-capacity, context/object/buffer/duplicate or count-validity guard. First match wins; native RFString
// empty/extent/case-insensitive semantics remain delegated. No key/axis code conversion, allocation or context mutation.
int __cdecl rf_binding_context_find_RFString_name(int a1, int a2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < *(_DWORD *)(a1 + 3596); ++i )
  {
    if ( rf_string_object_equals_case_insensitive(a1 + 28 * i + 24, a2) )
      return i;
  }
  return -1;
}

