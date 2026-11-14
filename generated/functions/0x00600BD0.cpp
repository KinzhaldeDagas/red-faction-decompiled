// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600BD0 rf_jpeg_coef_compress_first_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccoefct.c:compress_first_pass matched): Boolean(cinfo,inputcomponentplanes),full-bufferfirstpass. ForeachALLimagecomponents(accessnotjustscancomponents),accesswritablevirtualblockstripatstart=coef.iMCUrow8*v_samp,maxrows=v_samp. ForwardDCTentirewidth_in_blocks,fillrightpaddingtohsamplingmultiplewithzeroAC/previousDC. OnfinaliMCUrow,padmissingbottomrows,zeroACandcopyDCfromlastrealrowlastblockofeachMCUgroup. AllDCT/quantizedcoefficientsstoredvirtualarraysbeforecallingcompress_output600E80forcurrent scan. ReturnitsTRUE/FALSE,suspensionstateownedbyoutputfunction. Doesnotadvanceindexindependentlyorclearwholeimage.
int __cdecl rf_jpeg_coef_compress_first_pass(_DWORD *cinfo, unsigned __int8 ***unused_input)
{
  int v3; // [esp+0h] [ebp-40h]
  int j; // [esp+4h] [ebp-3Ch]
  int n; // [esp+4h] [ebp-3Ch]
  int v6; // [esp+8h] [ebp-38h]
  unsigned int m; // [esp+Ch] [ebp-34h]
  int v8; // [esp+10h] [ebp-30h]
  unsigned int v9; // [esp+14h] [ebp-2Ch]
  unsigned int v10; // [esp+14h] [ebp-2Ch]
  __int16 v11; // [esp+18h] [ebp-28h]
  __int16 v12; // [esp+18h] [ebp-28h]
  int i; // [esp+1Ch] [ebp-24h]
  int k; // [esp+1Ch] [ebp-24h]
  char *v15; // [esp+20h] [ebp-20h]
  char *v16; // [esp+20h] [ebp-20h]
  char *v17; // [esp+20h] [ebp-20h]
  int v18; // [esp+24h] [ebp-1Ch]
  _DWORD *v19; // [esp+28h] [ebp-18h]
  int v20; // [esp+30h] [ebp-10h]
  unsigned int v21; // [esp+34h] [ebp-Ch]
  unsigned int v22; // [esp+38h] [ebp-8h]
  int v23; // [esp+3Ch] [ebp-4h]

  v6 = cinfo[85];
  v21 = cinfo[59] - 1;
  v18 = 0;
  v19 = (_DWORD *)cinfo[16];
  while ( v18 < cinfo[14] )
  {
    v3 = (*(int (__cdecl **)(_DWORD *, _DWORD, int, _DWORD, int))(cinfo[1] + 32))(
           cinfo,
           *(_DWORD *)(v6 + 4 * v18 + 64),
           v19[3] * *(_DWORD *)(v6 + 8),
           v19[3],
           1);
    if ( *(_DWORD *)(v6 + 8) >= v21 )
    {
      v8 = v19[8] % v19[3];
      if ( !v8 )
        v8 = v19[3];
    }
    else
    {
      v8 = v19[3];
    }
    v9 = v19[7];
    v22 = v19[2];
    v23 = v9 % v22;
    if ( (int)(v9 % v22) > 0 )
      v23 = v22 - v23;
    for ( i = 0; i < v8; ++i )
    {
      v15 = *(char **)(v3 + 4 * i);
      (*(void (__cdecl **)(_DWORD *, _DWORD *, unsigned __int8 **, char *, int, _DWORD, unsigned int))(cinfo[89] + 4))(
        cinfo,
        v19,
        unused_input[v18],
        v15,
        8 * i,
        0,
        v9);
      if ( v23 > 0 )
      {
        v16 = &v15[128 * v9];
        rf_jpeg_jzero_far(v16, v23 << 7);
        v11 = *((_WORD *)v16 - 64);
        for ( j = 0; j < v23; ++j )
          *(_WORD *)&v16[128 * j] = v11;
      }
    }
    if ( *(_DWORD *)(v6 + 8) == v21 )
    {
      v10 = v23 + v9;
      for ( k = v8; k < v19[3]; ++k )
      {
        v17 = *(char **)(v3 + 4 * k);
        v20 = *(_DWORD *)(v3 + 4 * k - 4);
        rf_jpeg_jzero_far(v17, v10 << 7);
        for ( m = 0; m < v10 / v22; ++m )
        {
          v12 = *(_WORD *)(v20 + ((v22 - 1) << 7));
          for ( n = 0; n < (int)v22; ++n )
            *(_WORD *)&v17[128 * n] = v12;
          v17 += 128 * v22;
          v20 += v22 << 7;
        }
      }
    }
    ++v18;
    v19 += 21;
  }
  return rf_jpeg_coef_compress_output(cinfo, unused_input);
}

