// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FD9F0 rf_jpeg_stdio_dest
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jdatadst.c:jpeg_stdio_dest matched): Cdecl(cinfo,FILE*). Ifdest24NULL,allocates28-byte destination object frompermanentpool0. Installs init_destination+8=0x5FDA50,empty_output_buffer+12=0x5FDAA0,term_destination+16=0x5FDB10,stores FILE+20. Bufferpointer24 allocatedlaterperimage. Does not open/closeFILE or validate compressionstate;APIvoid.
int __cdecl rf_jpeg_stdio_dest(int a1, int a2)
{
  _DWORD *v3; // [esp+0h] [ebp-4h]

  if ( !*(_DWORD *)(a1 + 24) )
    *(_DWORD *)(a1 + 24) = (**(int (__cdecl ***)(int, _DWORD, int))(a1 + 4))(a1, 0, 28);
  v3 = *(_DWORD **)(a1 + 24);
  v3[2] = rf_jpeg_stdio_init_destination;
  v3[3] = rf_jpeg_stdio_empty_output_buffer;
  v3[4] = rf_jpeg_stdio_term_destination;
  v3[5] = a2;
  return a2;
}

