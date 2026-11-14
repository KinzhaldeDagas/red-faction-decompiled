// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D330 rf_stream_adapter_construct_unbound
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Initializes only mode DWORD+0=-1 and memory-base DWORD+8=0, returning this. Leaves stream pointer+4, cursor+12, length+16, label+20, version+80 and error+84 untouched. Not a fully usable bound reader; nonzero mode follows memory branches.
_DWORD *__thiscall rf_stream_adapter_construct_unbound(_DWORD *this)
{
  *this = -1;
  *(this + 2) = 0;
  return this;
}

