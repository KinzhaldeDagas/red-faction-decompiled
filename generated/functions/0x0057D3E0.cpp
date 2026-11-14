// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D3E0 rf_stream_adapter_bind_vfile
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Sets mode=0, borrowed virtual-stream pointer+4, memory base+8=0,cursor+12=0,length+16=-1 and returns receiver. Does not clear adapter label, version+80 or error+84; file-mode readers delegate to stream state.
_DWORD *__thiscall rf_stream_adapter_bind_vfile(_DWORD *this, int a2)
{
  *this = 0;
  *(this + 1) = a2;
  *(this + 2) = 0;
  *(this + 4) = -1;
  *(this + 3) = 0;
  return this;
}

