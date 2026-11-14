// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FC510 rf_jpeg_CreateCompress
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_CreateCompress matched): Cdecl(cinfo,version,structsize). Clears mem4 BEFORE validation;requiresversion62,size372,else errorcodes12/21 via err.error_exit with expected/actual parameters. Saves err0/client_data12,zeroes372bytes,restores them;is_decompressor16=0,jinit_memory_mgr,progress8/dest24/comp_info64=NULL,4quant pointers68 and4DC/AC pointers84/100=NULL,script_space364=NULL,input_gamma double44=1,global_state20=100. No parameters/colorspace defaults beyond this;application must set err beforecall. API returnvoid;EAX incidental cinfo.
char *__cdecl rf_jpeg_CreateCompress(char *a1, int a2, int a3)
{
  int v4; // [esp+0h] [ebp-Ch]
  int v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]
  int j; // [esp+8h] [ebp-4h]

  *((_DWORD *)a1 + 1) = 0;
  if ( a2 != 62 )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 12;
    *(_DWORD *)(*(_DWORD *)a1 + 24) = 62;
    *(_DWORD *)(*(_DWORD *)a1 + 28) = a2;
    (**(void (__cdecl ***)(char *))a1)(a1);
  }
  if ( a3 != 372 )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 21;
    *(_DWORD *)(*(_DWORD *)a1 + 24) = 372;
    *(_DWORD *)(*(_DWORD *)a1 + 28) = a3;
    (**(void (__cdecl ***)(char *))a1)(a1);
  }
  v5 = *(_DWORD *)a1;
  v4 = *((_DWORD *)a1 + 3);
  memset(a1, 0, 0x174u);
  *(_DWORD *)a1 = v5;
  *((_DWORD *)a1 + 3) = v4;
  *((_DWORD *)a1 + 4) = 0;
  rf_jpeg_jinit_memory_mgr(a1);
  *((_DWORD *)a1 + 2) = 0;
  *((_DWORD *)a1 + 6) = 0;
  *((_DWORD *)a1 + 16) = 0;
  for ( i = 0; i < 4; ++i )
    *(_DWORD *)&a1[4 * i + 68] = 0;
  for ( j = 0; j < 4; ++j )
  {
    *(_DWORD *)&a1[4 * j + 84] = 0;
    *(_DWORD *)&a1[4 * j + 100] = 0;
  }
  *((_DWORD *)a1 + 91) = 0;
  *(double *)(a1 + 44) = 1.0;
  *((_DWORD *)a1 + 5) = 100;
  return a1;
}

