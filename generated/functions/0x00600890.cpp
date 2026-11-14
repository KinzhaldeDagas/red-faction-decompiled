// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600890 rf_jpeg_coef_start_iMCU_row
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccoefct.c:start_iMCU_row matched): Determinescoef.MCU_rows_per_iMCU_row20:interleavedscan(comps_in_scan240>1)=1;singlecomponentscan usescomponent.v_samp_factor12 fornonfinaliMCUrow,component.last_row_height72 onfinalrow. Setscoef.mcu_ctr12=0,MCU_vert_offset16=0. DoesnotincrementiMCUindex8orwritecoefficients;assumescurrentcomponentpresent.
_DWORD *__cdecl rf_jpeg_coef_start_iMCU_row(_DWORD *a1)
{
  _DWORD *v2; // [esp+0h] [ebp-4h]

  v2 = (_DWORD *)a1[85];
  if ( (int)a1[60] <= 1 )
  {
    if ( v2[2] >= (unsigned int)(a1[59] - 1) )
      v2[5] = *(_DWORD *)(a1[61] + 72);
    else
      v2[5] = *(_DWORD *)(a1[61] + 12);
  }
  else
  {
    v2[5] = 1;
  }
  v2[3] = 0;
  v2[4] = 0;
  return v2;
}

