// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCBB0 rf_jpeg_write_scanlines
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapistd.c:jpeg_write_scanlines matched): Cdecl(cinfo,rowPointerArray,unsigned num_lines),returns rows consumed. Requiresstate101. Ifnext_scanline220>=image_height32 emits warning123(level-1) but continues with remaining0. Optionalprogress callback receivescurrent/limit;calls master.pass_startup+4 when call_pass_startup+12 true. Clamps requestedrows to remaining image height,local rowcount0,main332.process_data+4(cinfo,scanlines,&rowcount,numlines),incrementsnext_scanline byactualcount,returnscount. Suspension allowed throughpartial/zero consumption. No caller-buffer length checks beyond rowcount.
int __cdecl rf_jpeg_write_scanlines(_DWORD *a1, int a2, unsigned int a3)
{
  int v4; // [esp+0h] [ebp-8h] BYREF
  unsigned int v5; // [esp+4h] [ebp-4h]

  if ( a1[5] != 101 )
  {
    *(_DWORD *)(*a1 + 20) = 20;
    *(_DWORD *)(*a1 + 24) = a1[5];
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( a1[55] >= a1[8] )
  {
    *(_DWORD *)(*a1 + 20) = 123;
    (*(void (__cdecl **)(_DWORD *, int))(*a1 + 4))(a1, -1);
  }
  if ( a1[2] )
  {
    *(_DWORD *)(a1[2] + 4) = a1[55];
    *(_DWORD *)(a1[2] + 8) = a1[8];
    (*(void (__cdecl **)(_DWORD *))a1[2])(a1);
  }
  if ( *(_DWORD *)(a1[82] + 12) )
    (*(void (__cdecl **)(_DWORD *))(a1[82] + 4))(a1);
  v5 = a1[8] - a1[55];
  if ( a3 > v5 )
    a3 = v5;
  v4 = 0;
  (*(void (__cdecl **)(_DWORD *, int, int *, unsigned int))(a1[83] + 4))(a1, a2, &v4, a3);
  a1[55] += v4;
  return v4;
}

