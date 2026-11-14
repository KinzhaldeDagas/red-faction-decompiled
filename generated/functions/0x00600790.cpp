// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600790 rf_jpeg_coef_start_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccoefct.c:start_pass_coef matched): Setscoef.iMCU_row_num8=0,start_iMCU_row600890(resetsMCUposition). Passmode0 PASS_THRU requireswhole_image[0]64NULL,setscompress_data4=600910. Mode3 SAVE_AND_PASSrequireswholeimage,sets600BD0firstpass;mode2 CRANK_DESTrequireswholeimage,sets600E80output-only. Missing/wrongbuffermodeorotherenum fatal4. No allocation,entropyoutputorinputconsumption;voidcallback.
_DWORD *__cdecl rf_jpeg_coef_start_pass(_DWORD *a1, int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // [esp+4h] [ebp-4h]

  v3 = (_DWORD *)a1[85];
  v3[2] = 0;
  result = rf_jpeg_coef_start_iMCU_row(a1);
  if ( a2 )
  {
    if ( a2 == 2 )
    {
      result = v3;
      if ( !v3[16] )
      {
        *(_DWORD *)(*a1 + 20) = 4;
        result = (_DWORD *)(*(int (__cdecl **)(_DWORD *))*a1)(a1);
      }
      v3[1] = rf_jpeg_coef_compress_output;
    }
    else if ( a2 == 3 )
    {
      if ( !v3[16] )
      {
        *(_DWORD *)(*a1 + 20) = 4;
        result = (_DWORD *)(*(int (__cdecl **)(_DWORD *))*a1)(a1);
      }
      v3[1] = rf_jpeg_coef_compress_first_pass;
    }
    else
    {
      *(_DWORD *)(*a1 + 20) = 4;
      return (_DWORD *)(*(int (__cdecl **)(_DWORD *))*a1)(a1);
    }
  }
  else
  {
    if ( v3[16] )
    {
      *(_DWORD *)(*a1 + 20) = 4;
      (*(void (__cdecl **)(_DWORD *))*a1)(a1);
    }
    v3[1] = rf_jpeg_coef_compress_data;
    return v3;
  }
  return result;
}

