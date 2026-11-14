// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560890 rf_string_append_byte_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall destination and byte. Uses object-plus-byte constructor560560, assigns temporary back, destroys it and returns destination. Byte0 adds no visible C-string character; underlying length is recomputed.
_DWORD *__thiscall rf_string_append_byte_in_place(_DWORD *this, char a2)
{
  _DWORD *v3; // [esp+4h] [ebp-20h]
  _DWORD v5[2]; // [esp+10h] [ebp-14h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  v3 = rf_string_concat_object_byte(v5, (int)this, a2);
  v6 = 0;
  rf_string_assign_from_object(this, (int)v3);
  v6 = -1;
  rf_string_destroy_buffer(v5);
  return this;
}

