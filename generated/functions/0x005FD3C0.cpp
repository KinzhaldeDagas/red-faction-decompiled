// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FD3C0 rf_jpeg_set_colorspace
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:jpeg_set_colorspace matched): Requiresstate100;stores jpeg_color_space60,clears write_JFIF_header204/write_Adobe_marker216. Component stride84:ID0,h/vsampling8/12,quantIndex16,DC20,AC24. UNKNOWN:count=input_components36,requires1..10,IDs0..N-1,1x1sampling,alltables0. GRAY1:JFIF1,count1,ID1,1x1,tables0. RGB2:Adobe1,count3,IDsASCII R/G/B,1x1,tables0. YCbCr3:JFIF1,count3,IDs1/2/3,Y2x2tables0,Cb/Cr1x1tables1. CMYK4:Adobe1,count4,ASCII C/M/Y/K,1x1tables0. YCCK5:Adobe1,count4,IDs1/2/3/4,Y/K2x2tables0,Cb/Cr1x1tables1. Unknownoutputenumerror10. Onlypopulateslistedcomponentfields;assumescomp_info64 allocated(defaults). APIvoid.
_DWORD *__cdecl rf_jpeg_set_colorspace(_DWORD *a1, int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // [esp+4h] [ebp-8h]
  _DWORD *v4; // [esp+4h] [ebp-8h]
  _DWORD *v5; // [esp+4h] [ebp-8h]
  _DWORD *v6; // [esp+4h] [ebp-8h]
  _DWORD *v7; // [esp+4h] [ebp-8h]
  _DWORD *v8; // [esp+4h] [ebp-8h]
  _DWORD *v9; // [esp+4h] [ebp-8h]
  _DWORD *v10; // [esp+4h] [ebp-8h]
  _DWORD *v11; // [esp+4h] [ebp-8h]
  _DWORD *v12; // [esp+4h] [ebp-8h]
  _DWORD *v13; // [esp+4h] [ebp-8h]
  _DWORD *v14; // [esp+4h] [ebp-8h]
  _DWORD *v15; // [esp+4h] [ebp-8h]
  _DWORD *v16; // [esp+4h] [ebp-8h]
  _DWORD *v17; // [esp+4h] [ebp-8h]
  _DWORD *v18; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( a1[5] != 100 )
  {
    *(_DWORD *)(*a1 + 20) = 20;
    *(_DWORD *)(*a1 + 24) = a1[5];
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  a1[15] = a2;
  a1[51] = 0;
  a1[54] = 0;
  switch ( a2 )
  {
    case 0:
      a1[14] = a1[9];
      if ( (int)a1[14] < 1 || (int)a1[14] > 10 )
      {
        *(_DWORD *)(*a1 + 20) = 26;
        *(_DWORD *)(*a1 + 24) = a1[14];
        *(_DWORD *)(*a1 + 28) = 10;
        (*(void (__cdecl **)(_DWORD *))*a1)(a1);
      }
      for ( i = 0; ; ++i )
      {
        result = a1;
        if ( i >= a1[14] )
          break;
        v18 = (_DWORD *)(a1[16] + 84 * i);
        *v18 = i;
        v18[2] = 1;
        v18[3] = 1;
        v18[4] = 0;
        v18[5] = 0;
        v18[6] = 0;
      }
      break;
    case 1:
      a1[51] = 1;
      a1[14] = 1;
      v3 = (_DWORD *)a1[16];
      *v3 = 1;
      v3[2] = 1;
      v3[3] = 1;
      v3[4] = 0;
      v3[5] = 0;
      v3[6] = 0;
      result = v3;
      break;
    case 2:
      a1[54] = 1;
      a1[14] = 3;
      v4 = (_DWORD *)a1[16];
      *v4 = 82;
      v4[2] = 1;
      v4[3] = 1;
      v4[4] = 0;
      v4[5] = 0;
      v4[6] = 0;
      v5 = (_DWORD *)(a1[16] + 84);
      *v5 = 71;
      v5[2] = 1;
      v5[3] = 1;
      v5[4] = 0;
      v5[5] = 0;
      v5[6] = 0;
      v6 = (_DWORD *)(a1[16] + 168);
      *v6 = 66;
      v6[2] = 1;
      v6[3] = 1;
      v6[4] = 0;
      v6[5] = 0;
      v6[6] = 0;
      result = v6;
      break;
    case 3:
      a1[51] = 1;
      a1[14] = 3;
      v7 = (_DWORD *)a1[16];
      *v7 = 1;
      v7[2] = 2;
      v7[3] = 2;
      v7[4] = 0;
      v7[5] = 0;
      v7[6] = 0;
      v8 = (_DWORD *)(a1[16] + 84);
      *v8 = 2;
      v8[2] = 1;
      v8[3] = 1;
      v8[4] = 1;
      v8[5] = 1;
      v8[6] = 1;
      v9 = (_DWORD *)(a1[16] + 168);
      *v9 = 3;
      v9[2] = 1;
      v9[3] = 1;
      v9[4] = 1;
      v9[5] = 1;
      v9[6] = 1;
      result = v9;
      break;
    case 4:
      a1[54] = 1;
      a1[14] = 4;
      v10 = (_DWORD *)a1[16];
      *v10 = 67;
      v10[2] = 1;
      v10[3] = 1;
      v10[4] = 0;
      v10[5] = 0;
      v10[6] = 0;
      v11 = (_DWORD *)(a1[16] + 84);
      *v11 = 77;
      v11[2] = 1;
      v11[3] = 1;
      v11[4] = 0;
      v11[5] = 0;
      v11[6] = 0;
      v12 = (_DWORD *)(a1[16] + 168);
      *v12 = 89;
      v12[2] = 1;
      v12[3] = 1;
      v12[4] = 0;
      v12[5] = 0;
      v12[6] = 0;
      v13 = (_DWORD *)(a1[16] + 252);
      *v13 = 75;
      v13[2] = 1;
      v13[3] = 1;
      v13[4] = 0;
      v13[5] = 0;
      v13[6] = 0;
      result = v13;
      break;
    case 5:
      a1[54] = 1;
      a1[14] = 4;
      v14 = (_DWORD *)a1[16];
      *v14 = 1;
      v14[2] = 2;
      v14[3] = 2;
      v14[4] = 0;
      v14[5] = 0;
      v14[6] = 0;
      v15 = (_DWORD *)(a1[16] + 84);
      *v15 = 2;
      v15[2] = 1;
      v15[3] = 1;
      v15[4] = 1;
      v15[5] = 1;
      v15[6] = 1;
      v16 = (_DWORD *)(a1[16] + 168);
      *v16 = 3;
      v16[2] = 1;
      v16[3] = 1;
      v16[4] = 1;
      v16[5] = 1;
      v16[6] = 1;
      v17 = (_DWORD *)(a1[16] + 252);
      *v17 = 4;
      v17[2] = 2;
      v17[3] = 2;
      v17[4] = 0;
      v17[5] = 0;
      v17[6] = 0;
      result = v17;
      break;
    default:
      *(_DWORD *)(*a1 + 20) = 10;
      result = (_DWORD *)(*(int (__cdecl **)(_DWORD *))*a1)(a1);
      break;
  }
  return result;
}

