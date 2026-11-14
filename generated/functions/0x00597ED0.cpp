// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00597ED0 rf_file_transfer_copy_slot_name
// UNREALRED VERIFIED [file-transfer-20261028]: Arguments unsigned slot,destination string object. Copies record name+4 through0x55FFA0 when slot<60,active bit1 and nonempty name; otherwise copies empty string literal0x642397. Returns string assignment result. No record mutation or raw pointer lifetime exposure.
_DWORD *__cdecl rf_file_transfer_copy_slot_name(unsigned int a1, _DWORD *a2)
{
  if ( a1 < 0x3C
    && (unk_1BC3CC8[109 * a1] & 1) != 0
    && (char *)&unk_1BC3CCC + 436 * a1 + strlen((const char *)&unk_1BC3CCC + 436 * a1) + 1 != (char *)&unk_1BC3CCC
                                                                                            + 436 * a1
                                                                                            + 1 )
  {
    return rf_string_assign_from_cstr(a2, (char *)&unk_1BC3CCC + 436 * a1);
  }
  else
  {
    return rf_string_assign_from_cstr(a2, (char *)&byte_642397);
  }
}

