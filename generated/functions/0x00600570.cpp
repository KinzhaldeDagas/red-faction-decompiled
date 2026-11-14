// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600570 rf_jpeg_main_process_data_simple
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmainct.c:process_data_simple_main matched): Cdecl(cinfo,inputRows,inRowCounterPointer,inRowsAvailable),voidcallback. Whilemain.current_iMCU_row8<total_iMCU_rows236,ifrowgroup_ctr12<8 callprep336.pre_process_data+4 tofill8rowgroupsinto10componentstripbuffersmain24+. Ifnot8ready,returnawaitinginput. Elsecoef340.compress_data+4(cinfo,buffers):FALSEsuspends;firstsuspensiondecrements*inRowCounterONCEandsets suspended16=1,soappdoesnotbelieveallinputconsumedbeforeoutputfinishes. Onsuccessfulresume,restorecounteronce,clearsuspend,resetrowgroup0,advanceiMCUrow. No ownDCT,FILEwritesorinputcopybeyondprepcallback.
_DWORD *__cdecl rf_jpeg_main_process_data_simple(_DWORD *a1, int a2, _DWORD *a3, int a4)
{
  _DWORD *result; // eax
  _DWORD *i; // [esp+0h] [ebp-4h]

  for ( i = (_DWORD *)a1[83]; ; ++i[2] )
  {
    result = a1;
    if ( i[2] >= a1[59] )
      break;
    if ( i[3] < 8u )
      (*(void (__cdecl **)(_DWORD *, int, _DWORD *, int, _DWORD *, _DWORD *, int))(a1[84] + 4))(
        a1,
        a2,
        a3,
        a4,
        i + 6,
        i + 3,
        8);
    result = i;
    if ( i[3] != 8 )
      break;
    if ( !(*(int (__cdecl **)(_DWORD *, _DWORD *))(a1[85] + 4))(a1, i + 6) )
    {
      result = i;
      if ( !i[4] )
      {
        result = a3;
        --*a3;
        i[4] = 1;
      }
      return result;
    }
    if ( i[4] )
    {
      ++*a3;
      i[4] = 0;
    }
    i[3] = 0;
  }
  return result;
}

