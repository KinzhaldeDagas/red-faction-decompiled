// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB3A0 rf_rfa_get_end_tick
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Lazily obtains raw buffer and returns header DWORD+20 unchanged as integer authored end tick. No header/version/length or NULL validation; ordering against start is not checked.
int __thiscall rf_rfa_get_end_tick(void *this)
{
  return *((_DWORD *)rf_rfa_get_or_load_raw_buffer(this) + 5);
}

