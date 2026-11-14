// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560810 rf_string_append_cstr_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall destination and nullable C string. Concatenates through560260 into temporary, assigns it back via object assignment, destroys temporary and returns destination. NULL input preserves text through temporary copy. Does not impose a maximum length.
char **__thiscall rf_string_append_cstr_in_place(char **this, const char *a2)
{
  _DWORD *v3; // [esp+4h] [ebp-20h]
  _DWORD v5[2]; // [esp+10h] [ebp-14h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  v3 = rf_string_concat_object_cstr(v5, this, a2);
  v6 = 0;
  rf_string_assign_from_object(this, (int)v3);
  v6 = -1;
  rf_string_destroy_buffer(v5);
  return this;
}

