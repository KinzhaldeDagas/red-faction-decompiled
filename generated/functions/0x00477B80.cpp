// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477B80 rf_level_reset_auxiliary_name_string
// UNREALRED VERIFIED [level-lifecycle-20261028]: Assigns constant string0x63857D to RF string0x6FC3AC via0x55FFA0. Does not clear logical level-name0x6FC31C or dword0x6FC3A8 in this body; exact role of this secondary name remains unproven.
_DWORD *rf_level_reset_auxiliary_name_string()
{
  return rf_string_assign_from_cstr(unk_6FC3AC, (char *)byte_63857D);
}

