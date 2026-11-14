// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006004E0 rf_jpeg_main_start_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmainct.c:start_pass_main matched): Rawdata172!=0 no-op. Otherwise main.current_iMCU_row8=0,rowgroup_ctr12=0,suspended16=FALSE,pass_mode20=input. OnlyJBUF_PASS_THRU0accepted;othermodefatal4. Setsmain.process_data4=600570. No outputorbufferallocation;voidcallback.
_DWORD *__cdecl rf_jpeg_main_start_pass(_DWORD *a1, int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // [esp+4h] [ebp-4h]

  result = a1;
  v3 = (_DWORD *)a1[83];
  if ( !a1[43] )
  {
    v3[2] = 0;
    v3[3] = 0;
    v3[4] = 0;
    v3[5] = a2;
    if ( a2 )
    {
      *(_DWORD *)(*a1 + 20) = 4;
      return (_DWORD *)(*(int (__cdecl **)(_DWORD *))*a1)(a1);
    }
    else
    {
      v3[1] = rf_jpeg_main_process_data_simple;
      return v3;
    }
  }
  return result;
}

