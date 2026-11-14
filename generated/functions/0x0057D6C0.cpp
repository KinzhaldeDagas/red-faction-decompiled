// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D6C0 rf_stream_adapter_read_float_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 forwards minimum version and default float to file reader. Memory mode returns supplied default without consuming if version+80<minimum; otherwise permits signed cursor+4<=length, reads float and advances4. Failure sets error+84=-1 and returns0.0. Aligned/unaligned paths preserve the same source bits before x87 load; no byte swap or finite-value validation.
double __thiscall rf_stream_adapter_read_float_versioned(_DWORD *this, int a2, float a3)
{
  float v4; // [esp+8h] [ebp-4h]

  if ( !*this )
    return rf_binary_stream_read_float_versioned((int *)*(this + 1), a2, a3);
  if ( *(this + 20) < a2 )
    return a3;
  if ( *(this + 3) + 4 <= *(this + 4) )
  {
    v4 = *(float *)(*(this + 2) + *(this + 3));
    *(this + 3) += 4;
    return v4;
  }
  else
  {
    *(this + 21) = -1;
    return 0.0;
  }
}

