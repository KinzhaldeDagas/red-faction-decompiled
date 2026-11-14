// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FD000 rf_jpeg_set_defaults
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:jpeg_set_defaults matched): Requiresstate100. Allocates missing840-byte component array(10*84) frompermanentpool0. data_precision52=8,set_quality75baselineTRUE,standard Huffman tables. For16arith slots,L=0,U=1,K=5. Clears scan count164/script pointer168,raw_data172,arith_coding176,optimize180(8-bit),CCIR601184,smoothing188,DCTmethod192=0,restart interval196/rows200=0;JFIFmajor/minor208/209=1,densityunit210=0,X/Ydensity212/214=1. Calls default_colorspace frominput enum40,which sets component/sampling/JFIF/Adobe fields. Does not initialize image dimensions,input_components,in_color_space or client gamma;APIvoid.
int __cdecl rf_jpeg_set_defaults(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( *(_DWORD *)(a1 + 20) != 100 )
  {
    *(_DWORD *)(*(_DWORD *)a1 + 20) = 20;
    *(_DWORD *)(*(_DWORD *)a1 + 24) = *(_DWORD *)(a1 + 20);
    (**(void (__cdecl ***)(int))a1)(a1);
  }
  if ( !*(_DWORD *)(a1 + 64) )
    *(_DWORD *)(a1 + 64) = (**(int (__cdecl ***)(int, _DWORD, int))(a1 + 4))(a1, 0, 840);
  *(_DWORD *)(a1 + 52) = 8;
  rf_jpeg_set_quality((_DWORD *)a1, 75, 1);
  rf_jpeg_std_huff_tables(a1);
  for ( i = 0; i < 16; ++i )
  {
    *(_BYTE *)(i + a1 + 116) = 0;
    *(_BYTE *)(i + a1 + 132) = 1;
    *(_BYTE *)(i + a1 + 148) = 5;
  }
  *(_DWORD *)(a1 + 168) = 0;
  *(_DWORD *)(a1 + 164) = 0;
  *(_DWORD *)(a1 + 172) = 0;
  *(_DWORD *)(a1 + 176) = 0;
  *(_DWORD *)(a1 + 180) = 0;
  if ( *(int *)(a1 + 52) > 8 )
    *(_DWORD *)(a1 + 180) = 1;
  *(_DWORD *)(a1 + 184) = 0;
  *(_DWORD *)(a1 + 188) = 0;
  *(_DWORD *)(a1 + 192) = 0;
  *(_DWORD *)(a1 + 196) = 0;
  *(_DWORD *)(a1 + 200) = 0;
  *(_BYTE *)(a1 + 208) = 1;
  *(_BYTE *)(a1 + 209) = 1;
  *(_BYTE *)(a1 + 210) = 0;
  *(_WORD *)(a1 + 212) = 1;
  *(_WORD *)(a1 + 214) = 1;
  return rf_jpeg_default_colorspace((_DWORD *)a1);
}

