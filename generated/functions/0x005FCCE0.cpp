// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCCE0 rf_jpeg_write_raw_data
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapistd.c:jpeg_write_raw_data matched): Recovered0x5FCCE0..0x5FCE1D,cdecl(cinfo,componentRowPointerArrays,unsignednumlines). Requiresstate102;pastimageheight emitswarning123,-1 andreturns0. Optionalprogress and delayedmaster startup. Requiredrow count=8*max_v_samp_factor232;num_lines below this triggerserror23 BufferSize. Calls coef340.compress_data+4(cinfo,data);FALSE returns0(suspended) withoutnext_scanlineadvance. Successincrementsnext_scanline byrequired iMCU rows,returnsrequiredcount (caninclude bottompadding beyondheight). No local conversion/scaling.
unsigned int __cdecl rf_jpeg_write_raw_data(void *cinfo, unsigned __int8 ***data, unsigned int num_lines)
{
  unsigned int v4; // [esp+0h] [ebp-4h]

  if ( *((_DWORD *)cinfo + 5) != 102 )
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 20;
    *(_DWORD *)(*(_DWORD *)cinfo + 24) = *((_DWORD *)cinfo + 5);
    (**(void (__cdecl ***)(void *))cinfo)(cinfo);
  }
  if ( *((_DWORD *)cinfo + 55) < *((_DWORD *)cinfo + 8) )
  {
    if ( *((_DWORD *)cinfo + 2) )
    {
      *(_DWORD *)(*((_DWORD *)cinfo + 2) + 4) = *((_DWORD *)cinfo + 55);
      *(_DWORD *)(*((_DWORD *)cinfo + 2) + 8) = *((_DWORD *)cinfo + 8);
      (**((void (__cdecl ***)(void *))cinfo + 2))(cinfo);
    }
    if ( *(_DWORD *)(*((_DWORD *)cinfo + 82) + 12) )
      (*(void (__cdecl **)(void *))(*((_DWORD *)cinfo + 82) + 4))(cinfo);
    v4 = 8 * *((_DWORD *)cinfo + 58);
    if ( num_lines < v4 )
    {
      *(_DWORD *)(*(_DWORD *)cinfo + 20) = 23;
      (**(void (__cdecl ***)(void *))cinfo)(cinfo);
    }
    if ( (*(int (__stdcall **)(void *))(*((_DWORD *)cinfo + 85) + 4))(cinfo) )
    {
      *((_DWORD *)cinfo + 55) += v4;
      return v4;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 123;
    (*(void (__stdcall **)(void *))(*(_DWORD *)cinfo + 4))(cinfo);
    return 0;
  }
}

