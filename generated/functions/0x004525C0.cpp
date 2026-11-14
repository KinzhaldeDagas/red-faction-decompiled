// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004525C0 rf_control_assign_code_name_from_table256
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(required existing RFString destination,raw32 code), canonical full EAX0/-1. Require SIGNED code>=0 AND code<256. Valid
// range reads mutable C-string pointer table6619A8[code], assigns through55FFA0(destination,source), then returns0 regardless helper result/source content. Invalid negative or>=256
// code assigns exact empty PE literal634CE3 and returns-1; it does not preserve previous destination text. No table-entry NULL guard: nullable source is handled by shared
// string-assignment delegate and yields empty, still result0 for valid numeric code. Existing owning destination is REASSIGNED through delegate rather than copy-constructed; NULL
// destination itself is unguarded. No key polling, code masking/wrapping, encoded modifier interpretation, input dispatch or string-length bound. Saved unsigned code spelling has
// same accepted numeric set; native uses two signed branches.
int __cdecl rf_control_assign_code_name_from_table256(_DWORD *a1, unsigned int a2)
{
  if ( a2 < 0x100 )
  {
    rf_string_assign_from_cstr(a1, (&off_6619A8)[a2]);
    return 0;
  }
  else
  {
    rf_string_assign_from_cstr(a1, (char *)&byte_634CE3);
    return -1;
  }
}

