// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B2A0 rf_vfile_construct_loose_directory_rfstring
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl output RFString return storage and search-root identifier. Constructs temporary from data-root cstring189CD90. Nonzero id concatenates registered root pointer at1897490+12*id with NO extra separator. Id0 calls inclusive substring0..strlen(root)-2, removing final root byte under normal trailing-backslash invariant; no empty-root guard and substring helper does not validate negative count. Constructs output, destroys temporary, returns output pointer. No identifier validation or special9999999 handling.
_DWORD *__cdecl rf_vfile_construct_loose_directory_rfstring(_DWORD *a1, int a2)
{
  unsigned int v3; // eax
  char *v4[2]; // [esp+8h] [ebp-14h] BYREF
  int v5; // [esp+18h] [ebp-4h]

  rf_string_construct_from_cstr(v4, &unk_189CD90);
  v5 = 1;
  if ( a2 )
  {
    rf_string_concat_object_cstr(a1, v4, (const char *)dword_1897490[3 * a2]);
  }
  else
  {
    v3 = rf_string_length_from_cstr((const char **)v4);
    rf_string_substring_inclusive(v4, a1, 0, v3 - 2);
  }
  LOBYTE(v5) = 0;
  rf_string_destroy_buffer(v4);
  return a1;
}

