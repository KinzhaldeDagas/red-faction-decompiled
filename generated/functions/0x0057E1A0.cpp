// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E1A0 rf_stream_adapter_read_byte_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 forwards minimum version/default byte to file reader. Memory older version returns supplied AL default unchanged; otherwise cursor+1<=length reads/advances1, failure sets error+84=-1 and returnsAL0. No unsigned upper-register guarantee.
char __thiscall rf_stream_adapter_read_byte_versioned(_DWORD *this, int a2, char a3)
{
  if ( !*this )
    return rf_binary_stream_read_byte_versioned((void *)*(this + 1), a2, a3);
  if ( *(this + 20) < a2 )
    return a3;
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

