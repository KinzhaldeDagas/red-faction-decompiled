// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCE20 rf_jpeg_add_quant_table
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:jpeg_add_quant_table matched): Requiresstate100 andunsignedtableIndex<4 elseerrors20/31. Allocates missing132-byte quant table frompermanentpool0 via0x5FF360. For64coefficients computes signedint(scale*basicTable[i]+50)/100,clamps1..32767,then<=255 ifforce_baseline nonzero;storesuint16coeffs,sent_table128=0. No overflow check onscale product or basicTable pointer;voidAPI,incidental returntable slotaddress.
_DWORD *__cdecl rf_jpeg_add_quant_table(_DWORD *a1, unsigned int a2, int a3, int a4, int a5)
{
  int *v6; // [esp+0h] [ebp-Ch]
  int v7; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( a1[5] != 100 )
  {
    *(_DWORD *)(*a1 + 20) = 20;
    *(_DWORD *)(*a1 + 24) = a1[5];
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  if ( a2 >= 4 )
  {
    *(_DWORD *)(*a1 + 20) = 31;
    *(_DWORD *)(*a1 + 24) = a2;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  v6 = &a1[a2 + 17];
  if ( !*v6 )
    *v6 = rf_jpeg_alloc_quant_table((int)a1);
  for ( i = 0; i < 64; ++i )
  {
    v7 = (a4 * *(_DWORD *)(a3 + 4 * i) + 50) / 100;
    if ( v7 <= 0 )
      v7 = 1;
    if ( v7 > 0x7FFF )
      v7 = 0x7FFF;
    if ( a5 )
    {
      if ( v7 > 255 )
        LOWORD(v7) = 255;
    }
    *(_WORD *)(*v6 + 2 * i) = v7;
  }
  *(_DWORD *)(*v6 + 128) = 0;
  return &a1[a2 + 17];
}

