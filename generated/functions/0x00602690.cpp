// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602690 rf_jpeg_fdct_start_pass
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcdctmgr.c:start_pass_fdctmgr matched): Forallcomponents,quanttableindex16must<4andcinfo.quant68+4*i nonNULL elsefatal52. Requiremethod192==2elsefatal48. Allocatemissing64-floatdivisortable(256bytesimagepool)atfdct32+4*quantIndex;forallrow/col0..7 storesfloat reciprocal1/(quantWord*aanFactor[row]*aanFactor[col]*8). Factors8doubles0x648CD0 independentlymatchedPE:1,1.387039845,1.306562965,1.175875602,1,.785694958,.5411961,.275899379. Recomputesevenexistingtables;no quantWord0orfinitecheckhere,assumesvalidsetup. Doesnotmutatequantcoefficientsorlevelshiftinput.
int __cdecl rf_jpeg_fdct_start_pass(int a1)
{
  int result; // eax
  int v2; // [esp+8h] [ebp-24h]
  int j; // [esp+Ch] [ebp-20h]
  int k; // [esp+10h] [ebp-1Ch]
  int v5; // [esp+14h] [ebp-18h]
  int v6; // [esp+18h] [ebp-14h]
  unsigned int v7; // [esp+1Ch] [ebp-10h]
  int i; // [esp+20h] [ebp-Ch]
  int v9; // [esp+24h] [ebp-8h]
  int v10; // [esp+28h] [ebp-4h]

  v5 = *(_DWORD *)(a1 + 356);
  v6 = 0;
  for ( i = *(_DWORD *)(a1 + 64); ; i += 84 )
  {
    result = a1;
    if ( v6 >= *(_DWORD *)(a1 + 56) )
      break;
    v7 = *(_DWORD *)(i + 16);
    if ( v7 >= 4 || !*(_DWORD *)(a1 + 4 * v7 + 68) )
    {
      *(_DWORD *)(*(_DWORD *)a1 + 20) = 52;
      *(_DWORD *)(*(_DWORD *)a1 + 24) = v7;
      (**(void (__cdecl ***)(int))a1)(a1);
    }
    v9 = *(_DWORD *)(a1 + 4 * v7 + 68);
    if ( *(_DWORD *)(a1 + 192) == 2 )
    {
      if ( !*(_DWORD *)(v5 + 4 * v7 + 32) )
        *(_DWORD *)(v5 + 4 * v7 + 32) = (**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 256);
      v2 = *(_DWORD *)(v5 + 4 * v7 + 32);
      v10 = 0;
      for ( j = 0; j < 8; ++j )
      {
        for ( k = 0; k < 8; ++k )
        {
          *(float *)(v2 + 4 * v10) = 1.0
                                   / ((double)*(unsigned __int16 *)(v9 + 2 * v10)
                                    * dbl_648CD0[j]
                                    * dbl_648CD0[k]
                                    * 8.0);
          ++v10;
        }
      }
    }
    else
    {
      *(_DWORD *)(*(_DWORD *)a1 + 20) = 48;
      (**(void (__cdecl ***)(int))a1)(a1);
    }
    ++v6;
  }
  return result;
}

