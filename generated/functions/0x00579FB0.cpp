// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579FB0 rf_text_parser_read_delimited_rfstring
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): ECX parser; destination is existing 8-byte RFString, followed by opening and closing delimiter bytes (RET12). Uses260-byte stack buffer with child reader capacity255, therefore successful body maximum254 bytes. Nonnegative result assigns bounded body to destination and returns byte count. Later count>255 diagnostic is unreachable for the verified child contract. No escape processing or delimiter-flag semantics.
int __thiscall rf_text_parser_read_delimited_rfstring(
        void *parser,
        void *destination,
        char opening_delimiter,
        char closing_delimiter)
{
  signed int delimited_cstring; // [esp+4h] [ebp-10Ch]
  char Destination[260]; // [esp+8h] [ebp-108h] BYREF

  delimited_cstring = rf_text_parser_read_delimited_cstring(
                        (int)parser,
                        Destination,
                        255,
                        opening_delimiter,
                        closing_delimiter);
  if ( delimited_cstring >= 0 )
  {
    if ( delimited_cstring > 255 )
      rf_text_parser_fatal_expected_with_context((char **)parser, "string too long!");
    rf_string_assign_cstr_bounded((int)destination, Destination, delimited_cstring);
  }
  return delimited_cstring;
}

