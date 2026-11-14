// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00602820 rf_jpeg_forward_DCT_float
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcdctmgr.c:forward_DCT_float matched): Voidcdecl(cinfo,component,inputSampleRows,outputJBLOCKrow,startRow,startCol,numBlocks). Fetcheskernel fdct28 andfloatdivisors32+4*component.quantindex16. Perhorizontal8x8block,loadsunsignedBYTEpixelsfrom8rows/8cols into64-floatstackworkspace,subtracts128tolevelshift;callsfloatingDCTkernelinplace. For64coefficients,temp=float(workspace[i]*divisor[i]);storeslow16bits of((int)(temp+16384.5)-16384),IJGroundingoffsettrick,notexplicitintegerdivisionorsaturation. AdvancesstartCol8/outputblock128byteseach. No pixel/outputbounds,NaN/overflow/zerodivisorguard;masterconfigurationassumed.
int __cdecl rf_jpeg_forward_DCT_float(int a1, int a2, int a3, int a4, int a5, int a6, unsigned int a7)
{
  int result; // eax
  float v8; // [esp+24h] [ebp-124h]
  int k; // [esp+28h] [ebp-120h]
  unsigned __int8 *v10; // [esp+2Ch] [ebp-11Ch]
  int j; // [esp+30h] [ebp-118h]
  float *v12; // [esp+34h] [ebp-114h]
  float *v13; // [esp+34h] [ebp-114h]
  unsigned int i; // [esp+38h] [ebp-110h]
  int v15; // [esp+3Ch] [ebp-10Ch]
  void (__cdecl *v16)(float *); // [esp+40h] [ebp-108h]
  int v17; // [esp+44h] [ebp-104h]
  float v18[64]; // [esp+48h] [ebp-100h] BYREF
  int v19; // [esp+158h] [ebp+10h]

  v15 = *(_DWORD *)(a1 + 356);
  v16 = *(void (__cdecl **)(float *))(v15 + 28);
  v17 = *(_DWORD *)(v15 + 4 * *(_DWORD *)(a2 + 16) + 32);
  result = a3;
  v19 = a3 + 4 * a5;
  for ( i = 0; i < a7; ++i )
  {
    v12 = v18;
    for ( j = 0; j < 8; ++j )
    {
      v10 = (unsigned __int8 *)(a6 + *(_DWORD *)(v19 + 4 * j));
      *v12 = (float)(*v10 - 128);
      v13 = v12 + 1;
      *v13++ = (float)(*++v10 - 128);
      *v13++ = (float)(*++v10 - 128);
      *v13++ = (float)(*++v10 - 128);
      *v13++ = (float)(*++v10 - 128);
      *v13++ = (float)(*++v10 - 128);
      *v13 = (float)(*++v10 - 128);
      v13[1] = (float)(v10[1] - 128);
      v12 = v13 + 2;
    }
    v16(v18);
    for ( k = 0; k < 64; ++k )
    {
      v8 = v18[k] * *(float *)(v17 + 4 * k);
      *(_WORD *)(a4 + (i << 7) + 2 * k) = (int)(v8 + 16384.5) - 0x4000;
    }
    result = a6 + 8;
    a6 += 8;
  }
  return result;
}

