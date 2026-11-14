// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00601FB0 rf_jpeg_huff_dump_buffer
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:dump_buffer matched): Workingstate.cinfo32->dest24,callempty_output_buffer+12(cinfo). FALSEreturns0withoutreloadingworkingpointer/free;TRUEcopiesdest.next_output_byte0/free_in_buffer4 intoworkingstate0/4,returns1. Doesnotcommitremainingworkingbitstate,predictorsorcallfatalitself;entropyoutputmaysuspendunlikemarkerwriter.
int __cdecl rf_jpeg_huff_dump_buffer(_DWORD *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = *(_DWORD *)(a1[8] + 24);
  if ( !(*(int (__cdecl **)(_DWORD))(v2 + 12))(a1[8]) )
    return 0;
  *a1 = *(_DWORD *)v2;
  a1[1] = *(_DWORD *)(v2 + 4);
  return 1;
}

