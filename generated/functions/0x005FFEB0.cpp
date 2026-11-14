// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FFEB0 rf_jpeg_marker_emit_sos
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_sos matched): EmitsSOS FF DA,length=2*comps_in_scan240+6,componentcountBYTE. Foreachcur_comp_info244+,emitscomponentID andDC/ACselectors. ProgressiveACscanforcesDCselector0;progressiveDCscanforcesAC0,andDCrefinementAh320!=0 withHuffman(nonarith)forcesDC0. Sequentialusesconfiguredselectors. ThenSs312,Se316,packed(Ah320<<4)+Al324. No ownscanparametervalidation,payloademissionorstatechange.
int __cdecl rf_jpeg_marker_emit_sos(int a1)
{
  int v2; // [esp+0h] [ebp-10h]
  int v3; // [esp+4h] [ebp-Ch]
  _DWORD *v4; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  rf_jpeg_marker_emit_marker((_DWORD *)a1, 218);
  rf_jpeg_marker_emit_2bytes((_DWORD *)a1, 2 * *(_DWORD *)(a1 + 240) + 6);
  rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_DWORD *)(a1 + 240));
  for ( i = 0; i < *(_DWORD *)(a1 + 240); ++i )
  {
    v4 = *(_DWORD **)(a1 + 4 * i + 244);
    rf_jpeg_marker_emit_byte((_DWORD *)a1, *v4);
    v2 = v4[5];
    v3 = v4[6];
    if ( *(_DWORD *)(a1 + 224) )
    {
      if ( *(_DWORD *)(a1 + 312) )
      {
        LOBYTE(v2) = 0;
      }
      else
      {
        LOBYTE(v3) = 0;
        if ( *(_DWORD *)(a1 + 320) )
        {
          if ( !*(_DWORD *)(a1 + 176) )
            LOBYTE(v2) = 0;
        }
      }
    }
    rf_jpeg_marker_emit_byte((_DWORD *)a1, v3 + 16 * v2);
  }
  rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_DWORD *)(a1 + 312));
  rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_DWORD *)(a1 + 316));
  return rf_jpeg_marker_emit_byte((_DWORD *)a1, *(_BYTE *)(a1 + 324) + 16 * *(_BYTE *)(a1 + 320));
}

