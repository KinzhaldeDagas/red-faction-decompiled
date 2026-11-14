// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560FB0 rf_string_format_int32_decimal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Cdecl output object and signed int32. sprintf with "%d" into fixed stack character buffer, constructs temporary RF string, copy-constructs output, destroys temporary and returns output. No stream/file output or locale-independent replacement formatting.
_DWORD *__cdecl rf_string_format_int32_decimal(_DWORD *a1, int a2)
{
  char *v3[2]; // [esp+8h] [ebp-44h] BYREF
  char Buffer[44]; // [esp+10h] [ebp-3Ch] BYREF
  int v5; // [esp+48h] [ebp-4h]

  sprintf(Buffer, "%d", a2);
  rf_string_construct_from_cstr(v3, Buffer);
  v5 = 1;
  rf_string_copy_construct_from_object(a1, v3);
  LOBYTE(v5) = 0;
  rf_string_destroy_buffer(v3);
  return a1;
}

