// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057CFA0 rf_vfile_attempt_delete_matching_files_smaller_than_ten_bytes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl pattern and numeric root id. Constructs UNUSED unopened local VFile, builds loose wildcard path into512-byte local and enumerates direct entries. For nondirectories with UNSIGNED32 size<10 (raw JNB rejects>=10), calls57CF20 using bare returned name and same root id; ignores deletion return. Pattern subdirectory prefix is not carried into this bare-name deletion. Closes find handle; destroys unused temporary. EAX returns destructor residue (normally local-object pointer), not deleted count/status; zero-byte files included,10-byte files excluded. No recursion, special-id precheck before unbounded path builder or lookup-table update.
int __cdecl rf_vfile_attempt_delete_matching_files_smaller_than_ten_bytes(const char *a1, char *a2)
{
  struct _finddata64i32_t FindData; // [esp+4h] [ebp-45Ch] BYREF
  intptr_t FindHandle; // [esp+130h] [ebp-330h]
  char FileName[512]; // [esp+134h] [ebp-32Ch] BYREF
  int self[71]; // [esp+334h] [ebp-12Ch] BYREF
  int v7; // [esp+45Ch] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v7 = 0;
  rf_vfile_build_loose_path((int)a2, a1, FileName);
  FindHandle = _findfirst64i32(FileName, &FindData);
  if ( FindHandle != -1 )
  {
    do
    {
      if ( (FindData.attrib & 0x10) == 0 && FindData.size < 0xA )
        rf_vfile_unlink_loose_file_after_reset_attributes(FindData.name, a2);
    }
    while ( !_findnext64i32(FindHandle, &FindData) );
    _findclose(FindHandle);
  }
  v7 = -1;
  return rf_vfile_destruct_close_if_open(self);
}

