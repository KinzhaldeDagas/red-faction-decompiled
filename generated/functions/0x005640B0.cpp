// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005640B0 rf_v3m_cache_get_with_default_limit
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Normalizes third word-1 to9999999 then calls5B7F80(filename,cacheByte,limit). Returns shared V3M cache asset directly, not pooled model handle. Cache loader canonicalizes .v3m and does its own parse/cache ownership; no wrapper allocation or instance.
char *__cdecl rf_v3m_cache_get_with_default_limit(char *Str, unsigned __int8 a2, char *a3)
{
  if ( a3 == (char *)-1 )
    a3 = byte_98967F;
  return sub_5B7F80(Str, a2, (int)a3);
}

