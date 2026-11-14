// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D810 rf_stream_adapter_read_uint16
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 delegates unsigned16 reader with version0/default0. Memory mode reads little-endian16 bits and advances2 when signed cursor+2<=length; failure sets error+84=-1 and returns0 inAX. Same bit-level memory implementation as signed16 reader; callers zero-extend AX for lengths.
unsigned __int16 __thiscall rf_stream_adapter_read_uint16(void *this)
{
  unsigned __int16 v2; // [esp+4h] [ebp-4h]

  if ( !*(_DWORD *)this )
    return rf_binary_stream_read_uint16_versioned(*((int **)this + 1), 0, 0);
  if ( *((_DWORD *)this + 3) + 2 <= *((_DWORD *)this + 4) )
  {
    v2 = *(_WORD *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
    *((_DWORD *)this + 3) += 2;
    return v2;
  }
  else
  {
    *((_DWORD *)this + 21) = -1;
    return 0;
  }
}

