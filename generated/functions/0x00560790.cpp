// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560790 rf_string_append_object_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall destination and source RF object. Concatenates into a temporary through5600E0, assigns result to destination via object assignment and destroys temporary. Returns destination. Temporary construction allows ordinary exact-self append before reassignment; underlying sum/extent checks are unchanged.
int *__thiscall rf_string_append_object_in_place(int *this, int a2)
{
  _DWORD *v3; // [esp+4h] [ebp-20h]
  _DWORD v5[2]; // [esp+10h] [ebp-14h] BYREF
  int v6; // [esp+20h] [ebp-4h]

  v3 = rf_string_concat_two_objects(v5, this, a2);
  v6 = 0;
  rf_string_assign_from_object(this, (int)v3);
  v6 = -1;
  rf_string_destroy_buffer(v5);
  return this;
}

