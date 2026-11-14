// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D8B0 rf_stream_adapter_read_char8
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 delegates char8 reader with version0/default0. Memory mode reads one byte and advances when signed cursor+1<=length; failure sets error+84=-1 and returns0 inAL, no advancement. No sign-extension contract for upper EAX.
char __thiscall rf_stream_adapter_read_char8(_DWORD *this)
{
  if ( !*this )
    return rf_binary_stream_read_char8_versioned((int *)*(this + 1), 0, 0);
  if ( *(this + 3) + 1 <= *(this + 4) )
  {
    return *(_BYTE *)(*(this + 2) + (*(this + 3))++);
  }
  else
  {
    *(this + 21) = -1;
    return 0;
  }
}

