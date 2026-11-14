// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FC9C0 rf_jpeg_write_m_header
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_write_m_header matched): Recovered0x5FC9C0..0x5FCA33. Requiresnext_scanline220==0,state101/102/103;elseerror20. Forwards(cinfo,marker,length) to marker344 callback+20. Starts piecemeal application marker;does not emit payload or track remaining bytes itself. APIvoid.
void __cdecl rf_jpeg_write_m_header(void *cinfo, int marker, unsigned int length)
{
  if ( *((_DWORD *)cinfo + 55)
    || *((_DWORD *)cinfo + 5) != 101 && *((_DWORD *)cinfo + 5) != 102 && *((_DWORD *)cinfo + 5) != 103 )
  {
    *(_DWORD *)(*(_DWORD *)cinfo + 20) = 20;
    *(_DWORD *)(*(_DWORD *)cinfo + 24) = *((_DWORD *)cinfo + 5);
    (**(void (__cdecl ***)(void *))cinfo)(cinfo);
  }
  (*(void (__cdecl **)(void *, int, unsigned int))(*((_DWORD *)cinfo + 86) + 20))(cinfo, marker, length);
}

