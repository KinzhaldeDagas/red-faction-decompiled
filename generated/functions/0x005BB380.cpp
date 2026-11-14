// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB380 rf_rfa_get_start_tick
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Lazily obtains raw buffer and returns header DWORD+16 unchanged as integer authored start tick. No header/version/length or NULL validation.
int __thiscall rf_rfa_get_start_tick(void *this)
{
  return *((_DWORD *)rf_rfa_get_or_load_raw_buffer(this) + 4);
}

