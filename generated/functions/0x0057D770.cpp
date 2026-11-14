// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D770 rf_stream_adapter_read_int16
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 delegates signed16 reader with version0/default0. Memory mode allows signed cursor+2<=length, reads low16 bits and advances2. Failure error+84=-1,AX=0,no advancement. AX is the meaningful result; upper EAX is not a sign-extension contract.
__int16 __thiscall rf_stream_adapter_read_int16(_DWORD *this)
{
  __int16 v2; // [esp+4h] [ebp-4h]

  if ( !*this )
    return rf_binary_stream_read_int16_versioned((int *)*(this + 1), 0, 0);
  if ( *(this + 3) + 2 <= *(this + 4) )
  {
    v2 = *(_WORD *)(*(this + 2) + *(this + 3));
    *(this + 3) += 2;
    return v2;
  }
  else
  {
    *(this + 21) = -1;
    return 0;
  }
}

