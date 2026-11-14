// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FCA40 rf_jpeg_write_m_byte
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcapimin.c:jpeg_write_m_byte matched): Recovered0x5FCA40..0x5FCA5E,cdecl(cinfo,intvalue). Directly calls marker344.write_marker_byte+24(cinfo,value),WITHOUT state/remaining-length check. No data-pointer call or allocation;APIvoid.
void __cdecl rf_jpeg_write_m_byte(void *cinfo, int value)
{
  (*(void (__cdecl **)(void *, int))(*((_DWORD *)cinfo + 86) + 24))(cinfo, value);
}

