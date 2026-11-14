// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E62F0 rf_fpgun_load_type_table
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): No stack arguments. Construct owned memory parser on stack, reset type count87C6D8=0. Open fpgun.tbl with context pointer98967F and final0; any nonzero open code enters fatal loop(line1339). Until case-insensitive PREFIX #End is consumed, require signed count<256 else fatal loop(line1344), then pass ADDRESS of parser as one caller-popped DWORD to63F0. Parser close then destructor on normal path; SEH destroys owned parser. No #start marker, duplicate-name check, bitmap failure rollback or own default record clearing. Native EAX is destroyed-parser residue, not useful table pointer/count; startup caller discards it.
void **rf_fpgun_load_type_table()
{
  void *self[69]; // [esp+4h] [ebp-124h] BYREF
  int v2; // [esp+124h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v2 = 0;
  dword_87C6D8 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "fpgun.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\player\\player_fpgun.cpp",
      1339,
      "Unable to open fpgun.tbl");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    if ( dword_87C6D8 >= 256 )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\gamesrc\\player\\player_fpgun.cpp",
        1344,
        "Too many fpgun types in fpgun.tbl!");
    rf_fpgun_parse_type_record(self);
  }
  rf_memory_text_parser_close_buffer(self);
  v2 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

