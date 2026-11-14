// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C700 rf_vfile_attempt_delete_writable_root_files
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl root id. Builds root + wildcard * into256-byte local, constructs unopened temporary VFile, enumerates direct entries with findfirst/findnext. Skips entries whose attrib has readonly1 OR directory16; for each other entry resolves bare returned filename, calls5935E0 unlink with NULL new name, and increments attempted count regardless of either result. Resolver may choose another registered source or a VPP member; this is not guaranteed to delete the enumerated physical file. Closes find handle, destroys temporary and returns attempted count. No recursion, attribute clearing or success count; find failure returns0. Unbounded path builder inherited.
int __cdecl rf_vfile_attempt_delete_writable_root_files(int a1)
{
  int v2; // [esp+4h] [ebp-35Ch]
  intptr_t FindHandle; // [esp+8h] [ebp-358h]
  int self[70]; // [esp+Ch] [ebp-354h] BYREF
  char FileName[256]; // [esp+124h] [ebp-23Ch] BYREF
  struct _finddata64i32_t FindData; // [esp+224h] [ebp-13Ch] BYREF
  int v7; // [esp+350h] [ebp-10h]
  int v8; // [esp+35Ch] [ebp-4h]

  v7 = 0;
  rf_vfile_build_loose_path(a1, "*", FileName);
  rf_vfile_construct_unopened(self);
  v8 = 0;
  FindHandle = _findfirst64i32(FileName, &FindData);
  if ( FindHandle != -1 )
  {
    do
    {
      if ( (FindData.attrib & 0x11) == 0 )
      {
        rf_vfile_resolve_open_source((int)self, FindData.name, a1);
        rf_vfile_unlink_resolved_loose_source((int)self, nullptr, (int)byte_98967F);
        ++v7;
      }
    }
    while ( !_findnext64i32(FindHandle, &FindData) );
    _findclose(FindHandle);
  }
  v2 = v7;
  v8 = -1;
  rf_vfile_destruct_close_if_open(self);
  return v2;
}

