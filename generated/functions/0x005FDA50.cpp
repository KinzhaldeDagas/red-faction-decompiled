// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDA50 rf_jpeg_stdio_init_destination
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jdatadst.c:init_destination matched): Destinationcallback:allocates4096-byte bufferfromimagepool1,storesdest.buffer24,dest.next_output_byte0=buffer,free_in_buffer4=4096. Existing permanent destination object reused;buffer lifetime ends jpeg_abort/imagepool free. No fwritehere;APIvoid.
_DWORD *__cdecl rf_jpeg_stdio_init_destination(int a1)
{
  _DWORD *v2; // [esp+0h] [ebp-4h]

  v2 = *(_DWORD **)(a1 + 24);
  v2[6] = (**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 4096);
  *v2 = v2[6];
  v2[1] = 4096;
  return v2;
}

