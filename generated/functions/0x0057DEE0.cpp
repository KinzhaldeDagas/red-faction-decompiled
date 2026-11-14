// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057DEE0 rf_stream_adapter_set_version
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 forwards value to5924C0 on bound virtual stream; memory mode writes version DWORD+80 and returns receiver. Does not consume bytes, reset cursor/error or change mode. File setter updates per-stream context version, not adapter local version.
_DWORD *__thiscall rf_stream_adapter_set_version(_DWORD *this, int a2)
{
  if ( !*this )
    return rf_vfile_set_open_slot_version((_DWORD *)*(this + 1), a2);
  *(this + 20) = a2;
  return this;
}

