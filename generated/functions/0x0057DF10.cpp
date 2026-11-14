// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057DF10 rf_stream_adapter_read_int32_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 forwards minimum version/default to file int32 reader. Memory version+80 below minimum returns supplied default with no bounds check/consumption. Otherwise signed cursor+4<=length reads DWORD and advances4; failure sets error+84=-1 and returns0. No overflow or negative-position validation.
int __thiscall rf_stream_adapter_read_int32_versioned(_DWORD *this, int a2, int a3)
{
  int v4; // [esp+4h] [ebp-4h]

  if ( !*this )
    return rf_binary_stream_read_int32_versioned((void *)*(this + 1), a2, a3);
  if ( *(this + 20) < a2 )
    return a3;
  if ( *(this + 3) + 4 <= *(this + 4) )
  {
    v4 = *(_DWORD *)(*(this + 2) + *(this + 3));
    *(this + 3) += 4;
    return v4;
  }
  else
  {
    *(this + 21) = -1;
    return 0;
  }
}

