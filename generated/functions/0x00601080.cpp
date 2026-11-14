// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00601080 rf_jpeg_make_c_derived_tbl
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jchuff.c:jpeg_make_c_derived_tbl matched): Cdecl(cinfo,isDC,unsignedtableIndex,derivedTablePointerSlot),voidAPI. Requiresindex<4andselectedDC84+/AC100+tableexists(error50). Allocatesmissing1280-bytederivedtableimagepool1. BuildsHuffmansizesequencefrombits1..16 withtotal<=256(error8),generatescanonicalcodesandrejectsoversubscription/all-onesexhaustion(code>=1<<size). Clears256-byteehufsiatderived1024;foreachemittedsymbolvalidatesDCsymbol<=15orAC<=255,andnorepeatedsymbol,thenwrites32-bitcodeat4*symbol,lengthBYTEat1024+symbol. Unusedcodewordsremainuninitializedbutsize0marksabsent. Emptybitssequenceisnotrejectedhere. No tableemission,cinfo-statecheckorinputcapacityguard;source/callerdataflowverifieddespiteoldfunction-pointer-heavyinferredtype.
void __cdecl rf_jpeg_make_c_derived_tbl(void *cinfo, int is_dc, unsigned int table_index, void **derived_table)
{
  int v5; // [esp+0h] [ebp-544h]
  int i; // [esp+4h] [ebp-540h]
  int v7; // [esp+8h] [ebp-53Ch]
  char *v8; // [esp+Ch] [ebp-538h]
  int v9; // [esp+10h] [ebp-534h]
  _BYTE v10[1308]; // [esp+14h] [ebp-530h]
  int v11; // [esp+530h] [ebp-14h]
  int v12; // [esp+534h] [ebp-10h]
  int v13; // [esp+538h] [ebp-Ch]
  int v14; // [esp+53Ch] [ebp-8h]
  int j; // [esp+540h] [ebp-4h]

  if ( table_index >= 4 )
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 50;
    *(_DWORD *)(*(_DWORD *)cinfo + 24) = table_index;
    (**(void (__cdecl ***)(void *))cinfo)(cinfo);
  }
  if ( is_dc )
    v5 = *((_DWORD *)cinfo + table_index + 21);
  else
    v5 = *((_DWORD *)cinfo + table_index + 25);
  v11 = v5;
  if ( !v5 )
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 50;
    *(_DWORD *)(*(_DWORD *)cinfo + 24) = table_index;
    (**(void (__cdecl ***)(void *))cinfo)(cinfo);
  }
  if ( !*derived_table )
    *derived_table = (void *)(**((int (__cdecl ***)(void *, int, int))cinfo + 1))(cinfo, 1, 1280);
  v8 = (char *)*derived_table;
  j = 0;
  for ( i = 1; i <= 16; ++i )
  {
    v14 = *(unsigned __int8 *)(i + v11);
    if ( v14 + j > 256 )
    {
      *(_DWORD *)(*(_DWORD *)cinfo + 20) = 8;
      (**(void (__cdecl ***)(void *))cinfo)(cinfo);
    }
    while ( v14-- )
      v10[j++] = i;
  }
  v10[j] = 0;
  v9 = j;
  v12 = 0;
  v7 = v10[0];
  j = 0;
  while ( v10[j] )
  {
    while ( (char)v10[j] == v7 )
      *(_DWORD *)&v10[4 * j++ + 272] = v12++;
    if ( v12 >= 1 << v7 )
    {
      *(_DWORD *)(*(_DWORD *)cinfo + 20) = 8;
      (**(void (__cdecl ***)(void *))cinfo)(cinfo);
    }
    v12 *= 2;
    ++v7;
  }
  memset(v8 + 1024, 0, 0x100u);
  v13 = is_dc != 0 ? 15 : 255;
  for ( j = 0; j < v9; ++j )
  {
    v14 = *(unsigned __int8 *)(j + v11 + 17);
    if ( v14 > v13 || v8[v14 + 1024] )
    {
      *(_DWORD *)(*(_DWORD *)cinfo + 20) = 8;
      (**(void (__cdecl ***)(void *))cinfo)(cinfo);
    }
    *(_DWORD *)&v8[4 * v14] = *(_DWORD *)&v10[4 * j + 272];
    v8[v14 + 1024] = v10[j];
  }
}

