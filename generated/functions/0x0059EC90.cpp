// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059EC90 rf_vpackfile_init_file_list
// UNREALRED VERIFIED [vpp-streaming] Reserves this archive's entries from the fixed global pool and enforces the retail 13,500-entry limit.
BOOL __cdecl rf_vpackfile_init_file_list(int a1)
{
  if ( rf_vpackfile_entry_count + *(_DWORD *)(a1 + 164) > 13500 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\vfile\\file_packfile.cpp",
      487,
      "Out of packfile space!\n");
  *(_DWORD *)(a1 + 168) = (char *)&rf_vpackfile_entries + 24 * rf_vpackfile_entry_count;
  rf_vpackfile_entry_count += *(_DWORD *)(a1 + 164);
  return *(_DWORD *)(a1 + 168) != 0;
}

