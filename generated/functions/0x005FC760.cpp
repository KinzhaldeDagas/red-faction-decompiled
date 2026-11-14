// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FC760 rf_jpeg_finish_compress
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_finish_compress matched): Accepts states101scanning/102raw:requiresnext_scanline220>=image_height32 elseerror67,then master328.finish_pass+8. State103write-coefficients skips first finish;otherstate error20. Until master.is_last_pass+16,prepare_pass+0,loop total_iMCU_rows236 with progress callback8 updated pass counter/limit,coef340.compress_data+4(cinfo,NULL);FALSE yields error24 CantSuspend;finish_pass eachpass. Marker344.write_file_trailer+12,dest24.term_destination+16,then jpeg_abort resets/freeimagepool. Does not destroy permanent pool/close FILE;APIvoid.
int __cdecl rf_jpeg_finish_compress(_DWORD *a1)
{
  unsigned int i; // [esp+0h] [ebp-4h]

  if ( a1[5] != 101 && a1[5] != 102 )
  {
    if ( a1[5] != 103 )
    {
      *(_DWORD *)(*a1 + 20) = 20;
      *(_DWORD *)(*a1 + 24) = a1[5];
      (*(void (__cdecl **)(_DWORD *))*a1)(a1);
    }
    goto LABEL_8;
  }
  if ( a1[55] < a1[8] )
  {
    *(_DWORD *)(*a1 + 20) = 67;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  while ( 1 )
  {
    (*(void (__cdecl **)(_DWORD *))(a1[82] + 8))(a1);
LABEL_8:
    if ( *(_DWORD *)(a1[82] + 16) )
      break;
    (*(void (__cdecl **)(_DWORD *))a1[82])(a1);
    for ( i = 0; i < a1[59]; ++i )
    {
      if ( a1[2] )
      {
        *(_DWORD *)(a1[2] + 4) = i;
        *(_DWORD *)(a1[2] + 8) = a1[59];
        (*(void (__cdecl **)(_DWORD *))a1[2])(a1);
      }
      if ( !(*(int (__cdecl **)(_DWORD *, _DWORD))(a1[85] + 4))(a1, 0) )
      {
        *(_DWORD *)(*a1 + 20) = 24;
        (*(void (__cdecl **)(_DWORD *))*a1)(a1);
      }
    }
  }
  (*(void (__cdecl **)(_DWORD *))(a1[86] + 12))(a1);
  (*(void (__cdecl **)(_DWORD *))(a1[6] + 16))(a1);
  return rf_jpeg_abort(a1);
}

