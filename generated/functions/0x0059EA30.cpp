// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059EA30 rf_vpackfile_add_entries
// UNREALRED VERIFIED [vpp-streaming] Decodes 64-byte table entries, hashes their 60-byte names, and inserts them. While loading user maps, .tbl comparison names are replaced with DEADBEEF so stock tables cannot be overridden.
// UNREALRED VERIFIED [streaming-contract-20260829] Copies exactly 60 filename bytes from each VPP table entry without appending a terminator, then passes that buffer to C-string checksum and pool-copy consumers.
int __cdecl rf_vpackfile_add_entries(int a1, int a2, int a3, _DWORD *a4)
{
  const char *String1; // [esp+8h] [ebp-50h]
  int v6; // [esp+Ch] [ebp-4Ch]
  int v7; // [esp+Ch] [ebp-4Ch]
  int v8; // [esp+10h] [ebp-48h]
  int i; // [esp+14h] [ebp-44h]
  char Str[60]; // [esp+18h] [ebp-40h] BYREF

  v6 = 0;
  for ( i = 0; i < a3; ++i )
  {
    qmemcpy(Str, (const void *)(v6 + a2), sizeof(Str));
    v7 = v6 + 60;
    v8 = *(_DWORD *)(v7 + a2);
    v6 = v7 + 4;
    *(_DWORD *)(24 * *a4 + *(_DWORD *)(a1 + 168)) = rf_vpackfile_calc_file_name_checksum(Str);
    *(_DWORD *)(*(_DWORD *)(a1 + 168) + 24 * *a4 + 4) = rf_string_pool_copy_c_string(byte_1C8FBC8, Str);
    *(_DWORD *)(*(_DWORD *)(a1 + 168) + 24 * *a4 + 12) = v8;
    *(_DWORD *)(*(_DWORD *)(a1 + 168) + 24 * *a4 + 16) = a1;
    *(_DWORD *)(*(_DWORD *)(a1 + 168) + 24 * *a4 + 20) = 0;
    if ( rf_vpackfile_loading_user_maps )
    {
      String1 = rf_path_find_last_dot_or_empty_literal(Str);
      if ( String1 )
      {
        if ( !_stricmp(String1, ".tbl") )
          *(_DWORD *)(*(_DWORD *)(a1 + 168) + 24 * *a4 + 4) = "DEADBEEF";
      }
    }
    rf_vpackfile_add_to_lookup_table(*(_DWORD *)(a1 + 168) + 24 * *a4);
    ++*a4;
  }
  return 1;
}

