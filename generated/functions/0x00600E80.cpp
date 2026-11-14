// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600E80 rf_jpeg_coef_compress_output
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jccoefct.c:compress_output matched): Booleancdecl(cinfo,unusedInputPlanes). CallbackhasTWOarguments,secondignored (oldinferredone-argprototypecorrected). Forcurrentscancomponents(max4),accessreadonlyvirtualarraystripusingcomponent_index4,coef.iMCUrow8*v_samp andv_samprows. Walksavedverticaloffset16/MCUcolumn12,gatherblockpointersintoMCU_buffer24 incomponent/row/columnorderusingMCU_width52/height56,encode_mcu callbackentropy+4. FALSEsavescurrentoffset/column,returns0withoutadvancingiMCUrow. Successadvancesrow8,resetsrowstate600890,returns1. No DCT/requantization,inputreadingorcopyingcoefficientdata;outputsfromstoredarrays.
int __cdecl rf_jpeg_coef_compress_output(void *cinfo, unsigned __int8 ***unused_input)
{
  int v2; // eax
  unsigned int k; // [esp+0h] [ebp-38h]
  _DWORD v5[4]; // [esp+4h] [ebp-34h]
  int n; // [esp+14h] [ebp-24h]
  _DWORD *v7; // [esp+18h] [ebp-20h]
  int j; // [esp+1Ch] [ebp-1Ch]
  int i; // [esp+20h] [ebp-18h]
  int v10; // [esp+24h] [ebp-14h]
  _DWORD *v11; // [esp+28h] [ebp-10h]
  int m; // [esp+2Ch] [ebp-Ch]
  int v13; // [esp+30h] [ebp-8h]
  int v14; // [esp+34h] [ebp-4h]

  v7 = *((_DWORD **)cinfo + 85);
  for ( i = 0; i < *((_DWORD *)cinfo + 60); ++i )
  {
    v11 = *((_DWORD **)cinfo + i + 61);
    v2 = (*(int (__cdecl **)(void *, _DWORD, int, _DWORD, _DWORD))(*((_DWORD *)cinfo + 1) + 32))(
           cinfo,
           v7[v11[1] + 16],
           v11[3] * v7[2],
           v11[3],
           0);
    v5[i] = v2;
  }
  for ( j = v7[4]; j < v7[5]; ++j )
  {
    for ( k = v7[3]; k < *((_DWORD *)cinfo + 65); ++k )
    {
      v13 = 0;
      for ( i = 0; i < *((_DWORD *)cinfo + 60); ++i )
      {
        v11 = *((_DWORD **)cinfo + i + 61);
        v10 = v11[13] * k;
        for ( m = 0; m < v11[14]; ++m )
        {
          v14 = *(_DWORD *)(v5[i] + 4 * (j + m)) + (v10 << 7);
          for ( n = 0; n < v11[13]; ++n )
          {
            v7[v13++ + 6] = v14;
            v14 += 128;
          }
        }
      }
      if ( !(*(int (__cdecl **)(void *, _DWORD *))(*((_DWORD *)cinfo + 90) + 4))(cinfo, v7 + 6) )
      {
        v7[4] = j;
        v7[3] = k;
        return 0;
      }
    }
    v7[3] = 0;
  }
  ++v7[2];
  rf_jpeg_coef_start_iMCU_row(cinfo);
  return 1;
}

