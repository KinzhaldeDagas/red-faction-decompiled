// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549EE0 rf_stream_adapter_get_cached_or_vfile_version
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): If adapter firstDWORD nonzero,returns cached version DWORD+80. Else calls vfile slot-version getter5924A0 on pointer+4. No input validation,status query,version update or byte read. Literal branch on whole DWORD,not bit0 alone;not itself the version-at-least comparison.
int __thiscall rf_stream_adapter_get_cached_or_vfile_version(_DWORD *this)
{
  if ( *this )
    return *(this + 20);
  else
    return rf_vfile_get_slot_version((_DWORD *)*(this + 1));
}

