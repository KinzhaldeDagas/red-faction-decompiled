// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057DD40 rf_stream_adapter_get_label
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 returns delegated backslash-basename pointer from virtual stream. Any nonzero mode returns adapter+20 label address. No ownership transfer, allocation, NULL validation or guarantee unbound constructor initialized label.
char *__thiscall rf_stream_adapter_get_label(_DWORD *this)
{
  if ( *this )
    return (char *)(this + 5);
  else
    return rf_vfile_get_backslash_basename_pointer((char *)*(this + 1));
}

