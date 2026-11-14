// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF460 rf_jpeg_marker_write_marker_header
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:write_marker_header matched): Cdecl(cinfo,intmarker,unsignedpayloadLength). payloadLength>65533 fatalerror11 BadLength;elseemit FF+marker lowbyte,then big-endian16(length+2). Doesnotemitpayload,validatemarkerkindortrackremaininglength. Marker outputcannot suspend;application-levelstatevalidationhandledbypublicwrapper5FC9C0/5FC900. VoidAPI.
int __cdecl rf_jpeg_marker_write_marker_header(_DWORD *a1, char a2, unsigned int a3)
{
  if ( a3 > 0xFFFD )
  {
    *(_DWORD *)(*a1 + 20) = 11;
    (*(void (__cdecl **)(_DWORD *))*a1)(a1);
  }
  rf_jpeg_marker_emit_marker((int)a1, a2);
  return rf_jpeg_marker_emit_2bytes(a1, a3 + 2);
}

