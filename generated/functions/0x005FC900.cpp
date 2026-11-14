// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FC900 rf_jpeg_write_marker
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_write_marker matched): Recovered0x5FC900..0x5FC9B1,cdecl(cinfo,marker,BYTEdata,lengthunsigned). Requiresnext_scanline220==0 andstate101/102/103 elseerror20. Calls marker344.write_marker_header+20(cinfo,marker,length),caches marker.write_marker_byte+24 inLOCAL[ebp-4],then emits length unsigned bytes. No arbitrary call through image data:Hex-Rays may misinfer this cached indirect callback/stack cleanup;assembly0x5FC99C calls local function pointer,notdataptr. Header callback owns marker validation/length rules;no content copy retained. APIvoid.
void __cdecl rf_jpeg_write_marker(void *cinfo, int marker, const unsigned __int8 *data, unsigned int length)
{
  if ( *((_DWORD *)cinfo + 55)
    || *((_DWORD *)cinfo + 5) != 101 && *((_DWORD *)cinfo + 5) != 102 && *((_DWORD *)cinfo + 5) != 103 )
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 20;
    *(_DWORD *)(*(_DWORD *)cinfo + 24) = *((_DWORD *)cinfo + 5);
    (**(void (__cdecl ***)(void *))cinfo)(cinfo);
  }
  (*(void (__stdcall **)(void *))(*((_DWORD *)cinfo + 86) + 20))(cinfo);
  while ( length-- )
  {
    ((void (__cdecl *)(void *, _DWORD))*data)(cinfo, *data);
    ++data;
  }
}

