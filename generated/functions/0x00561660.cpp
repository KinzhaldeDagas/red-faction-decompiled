// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561660 rf_string_format_uint32_hex_with_prefix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): cdecl(output RFString,int32bits). sprintf local44byte buffer with"0x%x", constructs temporary RFString then copy-constructs output and destroys temp. Lowercase hex, no fixed-width padding, value formatted as unsigned32bit bits. Returns output; no supplied format string.
_DWORD *__cdecl rf_string_format_uint32_hex_with_prefix(_DWORD *a1, int a2)
{
  char *v3[2]; // [esp+8h] [ebp-44h] BYREF
  char Buffer[44]; // [esp+10h] [ebp-3Ch] BYREF
  int v5; // [esp+48h] [ebp-4h]

  sprintf(Buffer, "0x%x", a2);
  rf_string_construct_from_cstr(v3, Buffer);
  v5 = 1;
  rf_string_copy_construct_from_object(a1, v3);
  LOBYTE(v5) = 0;
  rf_string_destroy_buffer(v3);
  return a1;
}

