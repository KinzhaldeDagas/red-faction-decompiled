// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600910 rf_jpeg_coef_compress_data
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccoefct.c:compress_data matched): Pass-throughboolean(cinfo,componentSampleArrays),oneiMCUrowperTRUE. StartsatsavedMCUverticaloffset16/column12;perMCUandscancomponent runsfdct356.forward_DCT+4 into10contiguousMCUblocks,usingcomponent_index4,MCU_sample_width64,horizontalMCUwidth52/height56 andrightmostlast_col_width68. Padsright/bottomdummyblocks:ACzero,DCequalpreviousrealblock/rowlastDC. entropy360.encode_mcu+4FALSE savescurrverticaloffset/columnandreturns0;nextattemptre-DCTsthesameMCU. OnwholeiMCUrowsuccess,incrementcoef.iMCUrow8,resetrowcountersvia600890,return1. No fullimagecoefficientstorageorownbyteoutput;assumesvalidsampling/counts.
int __cdecl rf_jpeg_coef_compress_data(_DWORD *a1, int a2)
{
  int v3; // [esp+0h] [ebp-38h]
  unsigned int j; // [esp+4h] [ebp-34h]
  int v5; // [esp+8h] [ebp-30h]
  int ii; // [esp+Ch] [ebp-2Ch]
  int n; // [esp+Ch] [ebp-2Ch]
  _DWORD *v8; // [esp+10h] [ebp-28h]
  int v9; // [esp+14h] [ebp-24h]
  unsigned int v10; // [esp+18h] [ebp-20h]
  int i; // [esp+1Ch] [ebp-1Ch]
  int k; // [esp+24h] [ebp-14h]
  _DWORD *v13; // [esp+28h] [ebp-10h]
  int m; // [esp+2Ch] [ebp-Ch]
  int v15; // [esp+30h] [ebp-8h]
  unsigned int v16; // [esp+34h] [ebp-4h]

  v8 = (_DWORD *)a1[85];
  v10 = a1[65] - 1;
  v16 = a1[59] - 1;
  for ( i = v8[4]; i < v8[5]; ++i )
  {
    for ( j = v8[3]; j <= v10; ++j )
    {
      v15 = 0;
      for ( k = 0; k < a1[60]; ++k )
      {
        v13 = (_DWORD *)a1[k + 61];
        if ( j >= v10 )
          v3 = v13[17];
        else
          v3 = v13[13];
        v5 = v13[16] * j;
        v9 = 8 * i;
        for ( m = 0; m < v13[14]; ++m )
        {
          if ( v8[2] >= v16 && m + i >= v13[18] )
          {
            rf_jpeg_jzero_far((void *)v8[v15 + 6], v13[13] << 7);
            for ( n = 0; n < v13[13]; ++n )
              *(_WORD *)v8[n + 6 + v15] = *(_WORD *)v8[v15 + 5];
          }
          else
          {
            (*(void (__cdecl **)(_DWORD *, _DWORD *, _DWORD, _DWORD, int, int, int))(a1[89] + 4))(
              a1,
              v13,
              *(_DWORD *)(a2 + 4 * v13[1]),
              v8[v15 + 6],
              v9,
              v5,
              v3);
            if ( v3 < v13[13] )
            {
              rf_jpeg_jzero_far((void *)v8[v3 + 6 + v15], (v13[13] - v3) << 7);
              for ( ii = v3; ii < v13[13]; ++ii )
                *(_WORD *)v8[ii + 6 + v15] = *(_WORD *)v8[ii + 5 + v15];
            }
          }
          v15 += v13[13];
          v9 += 8;
        }
      }
      if ( !(*(int (__cdecl **)(_DWORD *, _DWORD *))(a1[90] + 4))(a1, v8 + 6) )
      {
        v8[4] = i;
        v8[3] = j;
        return 0;
      }
    }
    v8[3] = 0;
  }
  ++v8[2];
  rf_jpeg_coef_start_iMCU_row(a1);
  return 1;
}

