// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057A9D0 rf_string_construct_boolean_word
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl return-object RFString storage and byte boolean; any nonzero low byte constructs lowercase true, zero constructs lowercase false. Calls RFString cstring constructor and returns output object pointer. No append/assignment to existing owned string and no numeric formatting.
void *__cdecl rf_string_construct_boolean_word(void *out_string, char value)
{
  if ( value )
    rf_string_construct_from_cstr(out_string, "true");
  else
    rf_string_construct_from_cstr(out_string, "false");
  return out_string;
}

