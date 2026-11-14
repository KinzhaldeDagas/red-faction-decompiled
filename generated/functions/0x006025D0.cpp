// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006025D0 rf_jpeg_jinit_forward_dct
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcdctmgr.c:jinit_forward_dct matched): Allocates48-byteFDCTmanagerimagepool1,cinfo.fdct356=it,start_pass0=602690. ONLYdct_method192==2(JDCT_FLOAT)accepted:forward_DCTcallback4=602820,floatkernel28=605620. Othermethods0ISLOW/1IFASTfatal48 NotCompiled;thisiscompile-timefeatureselection,notautomaticfallback. Clears4integerdivisorptrs12..27and4floatdivisorptrs32..47. DoesnotprecomputedivisorsorrunDCT;voidAPI. RFJPEGwriter5DFA40explicitlysetsJDCT_FLOATafterdefaultsmethod0.
void __cdecl rf_jpeg_jinit_forward_dct(void *cinfo)
{
  int (__cdecl **v1)(int); // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v1 = (int (__cdecl **)(int))(**((int (__cdecl ***)(void *, int, int))cinfo + 1))(cinfo, 1, 48);
  *((_DWORD *)cinfo + 89) = v1;
  *v1 = rf_jpeg_fdct_start_pass;
  if ( *((_DWORD *)cinfo + 48) == 2 )
  {
    v1[1] = (int (__cdecl *)(int))rf_jpeg_forward_DCT_float;
    v1[7] = (int (__cdecl *)(int))rf_jpeg_fdct_float;
  }
  else
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 48;
    (**(void (__cdecl ***)(void *))cinfo)(cinfo);
  }
  for ( i = 0; i < 4; ++i )
  {
    v1[i + 3] = nullptr;
    v1[i + 8] = nullptr;
  }
}

