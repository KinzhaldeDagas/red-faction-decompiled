// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472F80 rf_item_definition_clear_names_at_exit
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Across all96 fixed80-byte definitions assigns constant strings0x638096/0x638097 to class-name(+0) and model-name(+8) RF strings via0x55FFA0. Does not reset count, callbacks, numeric fields or item instance list in this body.
void __cdecl rf_item_definition_clear_names_at_exit()
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 96; ++i )
  {
    rf_string_assign_from_cstr((_DWORD *)&unk_6F9130 + 20 * i, (char *)&byte_638096);
    rf_string_assign_from_cstr((_DWORD *)&unk_6F9130 + 20 * i + 2, (char *)&byte_638097);
  }
}

