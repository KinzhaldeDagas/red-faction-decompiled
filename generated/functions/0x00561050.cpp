// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561050 rf_string_format_uint32_hex_prefixed
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Cdecl output object and32-bit value. sprintf with "0x%x" into fixed stack buffer, so lower-case hexadecimal with prefix and no forced padding. Constructs/copies/destroys RF temporary and returns output. Negative signed caller bits print their unsigned32-bit hexadecimal representation.
_DWORD *__cdecl rf_string_format_uint32_hex_prefixed(_DWORD *a1, int a2)
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

