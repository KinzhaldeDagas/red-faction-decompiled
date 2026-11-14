// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCAF0 rf_jpeg_start_compress
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapistd.c:jpeg_start_compress matched): Requiresstate100 elseerror20. If write_all_tables nonzero,clears sent_table flags via suppress_tables(cinfo,0). Resets err callback+16,initializesdest24+8,initializes compression master0x600100,master328.prepare_for_pass+0,next_scanline220=0;state20=102 if raw_data_in172 nonzero,else101. Does not consume image rows or necessarily emitall frame/scan headers until pass_startup. APIvoid.
int __cdecl rf_jpeg_start_compress(_DWORD *a1, int a2)
{
  int result; // eax

  if ( a1[5] != 100 )
  {
    *(_DWORD *)(*a1 + 20) = 20;
    *(_DWORD *)(*a1 + 24) = a1[5];
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( a2 )
    rf_jpeg_suppress_tables((int)a1, 0);
  (*(void (__cdecl **)(_DWORD *))(*a1 + 16))(a1);
  (*(void (__cdecl **)(_DWORD *))(a1[6] + 8))(a1);
  rf_jpeg_jinit_compress_master((int)a1);
  (*(void (__cdecl **)(_DWORD *))a1[82])(a1);
  a1[55] = 0;
  result = (a1[43] != 0) + 101;
  a1[5] = result;
  return result;
}

