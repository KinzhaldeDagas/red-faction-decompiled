// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FE080 rf_jpeg_alloc_small
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemmgr.c:alloc_small matched): Cdecl(cinfo,poolID,unsignedbytes). Rejects initialbytes>999999988 viaout_of_memory(case1),roundsrequest UP to multiple8,requiresunsignedpoolID<2 elseerror14. Manager84bytes atcinfo4;smallpoolheads52/56. Header12bytes{next0,used4,left8};walks firstchunk withleft>=roundedrequest,rememberingprevious. Ifnone,allocatesrequest+header+slop:initial slop pool0=1600,pool1=16000,subsequent0/5000 (verifiedtables0x648B70/78),capsnominalchunk1000000000. mallocfailurehalvesslop;below50 fatalOOMcase2. Appendschunk tosmalllist,updatesmanager totalbytes76,bumpsused/reducesleft,returns header+12+oldused. Does NOT zero usermemory;rounding size does not guarantee returnedaddress8alignment becauseheader12.32-bit size arithmetic,no generaloverflow protection.
int __cdecl rf_jpeg_alloc_small(_DWORD *cinfo, unsigned int a2, unsigned int a3)
{
  int v4; // [esp+0h] [ebp-1Ch]
  int v5; // [esp+4h] [ebp-18h]
  unsigned int v6; // [esp+8h] [ebp-14h]
  _DWORD *v7; // [esp+Ch] [ebp-10h]
  int v8; // [esp+10h] [ebp-Ch]
  _DWORD *i; // [esp+14h] [ebp-8h]

  v4 = cinfo[1];
  if ( a3 > 0x3B9AC9F4 )
    rf_jpeg_out_of_memory((int)cinfo, 1);
  if ( a3 % 8 )
    a3 += 8 - a3 % 8;
  if ( a2 >= 2 )
  {
    *(_DWORD *)(*cinfo + 20) = 14;
    *(_DWORD *)(*cinfo + 24) = a2;
    (*(void (__cdecl **)(_DWORD *))*cinfo)(cinfo);
  }
  v7 = nullptr;
  for ( i = *(_DWORD **)(v4 + 4 * a2 + 52); i && i[2] < a3; i = (_DWORD *)*i )
    v7 = i;
  if ( !i )
  {
    v5 = a3 + 12;
    if ( v7 )
      v6 = dword_648B78[a2];
    else
      v6 = dword_648B70[a2];
    if ( v6 > 1000000000 - v5 )
      v6 = 1000000000 - v5;
    while ( 1 )
    {
      i = rf_jpeg_get_small(cinfo, v6 + v5);
      if ( i )
        break;
      v6 >>= 1;
      if ( v6 < 0x32 )
        rf_jpeg_out_of_memory((int)cinfo, 2);
    }
    *(_DWORD *)(v4 + 76) += v6 + v5;
    *i = 0;
    i[1] = 0;
    i[2] = v6 + a3;
    if ( v7 )
      *v7 = i;
    else
      *(_DWORD *)(v4 + 4 * a2 + 52) = i;
  }
  v8 = (int)i + i[1] + 12;
  i[1] += a3;
  i[2] -= a3;
  return v8;
}

