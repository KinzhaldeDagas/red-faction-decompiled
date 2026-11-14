// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF970 rf_jpeg_marker_emit_dqt
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_dqt matched): Args cinfo,quanttableindex. Missingpointeratquant68+4*index ->error52 NoQuantTable;no independentindexrangecheckhere. Scansall64uint16coefficients,precision1iffany>255,otherwise0. Ifsent_table128==0,emitsDQT FF DB,length131(16-bit)or67(8-bit),tableID+16*precision;emits64coefficientsinzigzag viaoriginaltable0x648B90,highbytefirstfor16-bit;sets sent_table1. Returns precisionregardlessalready-sentstate. All64lookupentriesindependentlymatchedPE/IJGsource;doesnotmodifycoefficients.
int __cdecl rf_jpeg_marker_emit_dqt(_DWORD *a1, int a2)
{
  __int16 v3; // [esp+0h] [ebp-10h]
  int v4; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]
  int j; // [esp+8h] [ebp-8h]
  int v7; // [esp+Ch] [ebp-4h]

  v4 = a1[a2 + 17];
  if ( !v4 )
  {
    *(_DWORD *)(*a1 + 20) = 52;
    *(_DWORD *)(*a1 + 24) = a2;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  v7 = 0;
  for ( i = 0; i < 64; ++i )
  {
    if ( *(unsigned __int16 *)(v4 + 2 * i) > 0xFFu )
      v7 = 1;
  }
  if ( !*(_DWORD *)(v4 + 128) )
  {
    rf_jpeg_marker_emit_marker(a1, 219);
    rf_jpeg_marker_emit_2bytes(a1, v7 != 0 ? 131 : 67);
    rf_jpeg_marker_emit_byte(a1, a2 + 16 * v7);
    for ( j = 0; j < 64; ++j )
    {
      v3 = *(_WORD *)(v4 + 2 * dword_648B90[j]);
      if ( v7 )
        rf_jpeg_marker_emit_byte(a1, SHIBYTE(v3));
      rf_jpeg_marker_emit_byte(a1, v3);
    }
    *(_DWORD *)(v4 + 128) = 1;
  }
  return v7;
}

