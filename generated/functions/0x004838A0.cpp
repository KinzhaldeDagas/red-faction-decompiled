// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004838A0 rf_rfl_clear_parser_scratch
// UNREALRED VERIFIED [level-lifecycle-20261028]: Assigns constant0x638872 to global RF scratch string0x6FCCC0 and releases backing storage for array0x6FCCC8. Does not individually free any pointed elements in this function.
void **rf_rfl_clear_parser_scratch()
{
  rf_string_assign_from_cstr(unk_6FCCC0, (char *)byte_638872);
  return rf_pointer_array_release_storage((void **)unk_6FCCC8);
}

