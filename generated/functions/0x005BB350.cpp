// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB350 rf_rfa_has_morph_vertices
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Lazily obtains raw buffer then returns signed DWORD at header+28>0. Does not validate version, key count, indices or payload presence; failed lazy load is not checked before dereference.
bool __thiscall rf_rfa_has_morph_vertices(void *this)
{
  return *((_DWORD *)rf_rfa_get_or_load_raw_buffer(this) + 7) > 0;
}

