// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057DFC0 rf_stream_adapter_read_uint32_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 forwards minimum version/default to unsigned32 file reader. Memory implementation is same rawDWORD read as int32: older version returns default unchanged, accepted bounds allow exact end and advance4, failure sets error+84=-1/returns0. No signed-value conversion is performed.
unsigned int __thiscall rf_stream_adapter_read_uint32_versioned(void *this, int a2, unsigned int a3)
{
  unsigned int v4; // [esp+4h] [ebp-4h]

  if ( !*(_DWORD *)this )
    return rf_binary_stream_read_uint32_versioned(*((int **)this + 1), a2, a3);
  if ( *((_DWORD *)this + 20) < a2 )
    return a3;
  if ( *((_DWORD *)this + 3) + 4 <= *((_DWORD *)this + 4) )
  {
    v4 = *(_DWORD *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
    *((_DWORD *)this + 3) += 4;
    return v4;
  }
  else
  {
    *((_DWORD *)this + 21) = -1;
    return 0;
  }
}

