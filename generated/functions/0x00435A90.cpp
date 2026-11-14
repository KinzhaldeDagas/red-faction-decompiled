// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435A90 rf_entity_definition_field94_by_string8
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(Cstring pointer). Signed i=0..<global definition count681E14, re-read every bound test, stride5396
// from683548. Compare RFString at definition+8 to supplied Cstring through55F9B0; first ANYnonzero AL match returns raw DWORD definition+148(0x94), not definition index/address. No
// match returns fullEAX0, indistinguishable from stored0. No argument/record pointer or capacity75 bound, duplicate-name rejection, resource load, allocation or state write. Caller
// event-switch-model uses this as its type0 definition lookup; raw field meaning is not generalized from that caller alone.
int __cdecl rf_entity_definition_field94_by_string8(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_681E14; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)&unk_683550 + 5396 * i, String2) )
      return unk_6835DC[1349 * i];
  }
  return 0;
}

