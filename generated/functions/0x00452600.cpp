// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452600 rf_control_assign_code_name_from_registry5
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(required existing RFString destination,raw32 code), canonical full EAX0/-1. Native SIGNED inclusive0..4 admits. Read
// pointer entry6EFE80[code], DEREFERENCE its firstDWORD as C-string source, assign via55FFA0(destination,source), then return0 independent of text/assignment result. Registry entry
// pointer is NOT NULL-checked; NULL firstDWORD source is permitted by delegate and assigns empty while returning0. Negative or>=5 code instead assigns exact empty PE literal634CEE
// and returns-1, replacing previous visible destination text through shared assignment rules. No code masking, table-size recheck, record-type test, resource ownership transfer,
// key/button polling or dispatch. Saved unsigned spelling does not change admitted numeric set. Does not collapse two pointer indirections into an inline C-string array.
int __cdecl rf_control_assign_code_name_from_registry5(_DWORD *a1, unsigned int a2)
{
  if ( a2 <= 4 )
  {
    rf_string_assign_from_cstr(a1, *(char **)dword_6EFE80[a2]);
    return 0;
  }
  else
  {
    rf_string_assign_from_cstr(a1, (char *)&byte_634CEE);
    return -1;
  }
}

