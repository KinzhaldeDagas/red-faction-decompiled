// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D630 rf_stream_adapter_read_int32
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 delegates int32 reader with version0/default0. Memory mode allows signed cursor+4<=length, reads little-endian DWORD and advances4; otherwise sets error+84=-1, returns0 and leaves cursor. No error reset after success or overflow/negative-cursor validation.
int __thiscall rf_stream_adapter_read_int32(void **this)
{
  int v2; // [esp+4h] [ebp-4h]

  if ( !*this )
    return rf_binary_stream_read_int32_versioned(*(this + 1), 0, 0);
  if ( (int)*(this + 3) + 4 <= (int)*(this + 4) )
  {
    v2 = *(_DWORD *)((char *)*(this + 3) + (_DWORD)*(this + 2));
    *(this + 3) = (char *)*(this + 3) + 4;
    return v2;
  }
  else
  {
    *(this + 21) = (void *)-1;
    return 0;
  }
}

