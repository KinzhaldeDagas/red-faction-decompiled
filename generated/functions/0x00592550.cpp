// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592550 rf_vfile_find_registered_loose_file
// UNREALRED VERIFIED [vfile-loose-precedence] Lowercases the requested name, searches the registered direct loose-file table, and returns its search-root identifier when found.
char __cdecl rf_vfile_find_registered_loose_file(char *a1, _DWORD *a2)
{
  _DWORD *exact_name_node; // [esp+0h] [ebp-10Ch]
  char v4[260]; // [esp+4h] [ebp-108h] BYREF

  rf_vfile_lowercase_lookup_name(v4, a1);
  exact_name_node = (_DWORD *)rf_vfile_loose_lookup_find_exact_name_node(v4);
  if ( !exact_name_node )
    return 0;
  *a2 = *exact_name_node;
  return 1;
}

