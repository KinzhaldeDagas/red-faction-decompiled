// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00601830 rf_jpeg_huff_start_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:start_pass_huff matched): Arg gather_statistics. TRUEselectsencode_mcu602200/finish6024A0;FALSEselectsencode601A40/finish602130. Foreachscancomponent,readsDC20/AC24tableindices. Gatherrequiresindices<4(error50),allocatesmissing257*4bytecountarraysfromimagepool,zeroesall257entriesforeachreferencedtable. Outputmodecallsrf_jpeg_make_c_derived_tbl forDC/AC,allocating/validatingderivedlookups. Clearsper-scanlastDCpredictors20+4*i,put_buffer12=0,put_bits16=0,restartstogo36=cinfo.restart_interval196,nextrestartnum40=0. No directbyteoutput;sourcepasscontrolsstate.
_DWORD *__cdecl rf_jpeg_huff_start_pass(_DWORD *cinfo, int a2)
{
  unsigned int table_index; // [esp+0h] [ebp-14h]
  int i; // [esp+4h] [ebp-10h]
  int v5; // [esp+8h] [ebp-Ch]
  _DWORD *v6; // [esp+Ch] [ebp-8h]
  unsigned int v7; // [esp+10h] [ebp-4h]

  v6 = (_DWORD *)cinfo[90];
  if ( a2 )
  {
    v6[1] = rf_jpeg_huff_encode_mcu_gather;
    v6[2] = rf_jpeg_huff_finish_pass_gather;
  }
  else
  {
    v6[1] = rf_jpeg_huff_encode_mcu;
    v6[2] = rf_jpeg_huff_finish_pass;
  }
  for ( i = 0; i < cinfo[60]; ++i )
  {
    v5 = cinfo[i + 61];
    table_index = *(_DWORD *)(v5 + 20);
    v7 = *(_DWORD *)(v5 + 24);
    if ( a2 )
    {
      if ( table_index >= 4 )
      {
        *(_DWORD *)(*cinfo + 20) = 50;
        *(_DWORD *)(*cinfo + 24) = table_index;
        (*(void (__cdecl **)(_DWORD *))*cinfo)(cinfo);
      }
      if ( v7 >= 4 )
      {
        *(_DWORD *)(*cinfo + 20) = 50;
        *(_DWORD *)(*cinfo + 24) = v7;
        (*(void (__cdecl **)(_DWORD *))*cinfo)(cinfo);
      }
      if ( !v6[table_index + 19] )
        v6[table_index + 19] = (*(int (__cdecl **)(_DWORD *, int, int))cinfo[1])(cinfo, 1, 1028);
      memset((void *)v6[table_index + 19], 0, 0x404u);
      if ( !v6[v7 + 23] )
        v6[v7 + 23] = (*(int (__cdecl **)(_DWORD *, int, int))cinfo[1])(cinfo, 1, 1028);
      memset((void *)v6[v7 + 23], 0, 0x404u);
    }
    else
    {
      rf_jpeg_make_c_derived_tbl(cinfo, 1, table_index, (void **)&v6[table_index + 11]);
      rf_jpeg_make_c_derived_tbl(cinfo, 0, v7, (void **)&v6[v7 + 15]);
    }
    v6[i + 5] = 0;
  }
  v6[3] = 0;
  v6[4] = 0;
  v6[9] = cinfo[49];
  v6[10] = 0;
  return cinfo;
}

