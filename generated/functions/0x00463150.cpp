// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00463150 rf_browser_save_cache_and_favorites
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Open favlist6F5090 wb;for every favorite100 entry,find live endpoint and if found export current108 row INTO favorite entry,then fwrite100 regardless hit;close. If
// favorite fopen failed,no refresh of in-memory favorite metadata occurs. Independently open svrlist6F51B8 wb;export each live row to100-byte local and fwrite;close. Ignore
// writes/close errors. Serialized flags only low2;favorites persist through separate file membership. No atomic replace,rollback,count/storage/selection validation or LAN guard in
// body (caller supplies policy). Existing FILE* return is incidental fopen/fclose residue,not consistent success status.
FILE *rf_browser_save_cache_and_favorites()
{
  FILE *result; // eax
  _BYTE Buffer[108]; // [esp+0h] [ebp-80h] BYREF
  int j; // [esp+70h] [ebp-10h]
  int v3; // [esp+74h] [ebp-Ch] BYREF
  FILE *Stream; // [esp+78h] [ebp-8h]
  int i; // [esp+7Ch] [ebp-4h]

  Stream = fopen(unk_6F5090, "wb");
  if ( Stream )
  {
    for ( i = 0; i < dword_6F52EC; ++i )
    {
      if ( rf_browser_find_endpoint_or_insertion_index(
             *(_DWORD *)(unk_6F52E8 + 100 * i),
             *(_DWORD *)(unk_6F52E8 + 100 * i + 4),
             &v3) )
      {
        rf_browser_export_row_to_cache100(v3, unk_6F52E8 + 100 * i);
      }
      fwrite((const void *)(unk_6F52E8 + 100 * i), 0x64u, 1u, Stream);
    }
    fclose(Stream);
  }
  result = fopen(unk_6F51B8, "wb");
  Stream = result;
  if ( result )
  {
    for ( j = 0; j < dword_6F51A8; ++j )
    {
      rf_browser_export_row_to_cache100(j, (int)Buffer);
      fwrite(Buffer, 0x64u, 1u, Stream);
    }
    return (FILE *)fclose(Stream);
  }
  return result;
}

