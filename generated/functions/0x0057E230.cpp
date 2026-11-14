// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E230 rf_stream_adapter_read_bool_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 forwards minimum/default to file bool reader. Memory older version returns supplied default byte without normalizing it. Accepted version calls bulk read of1 into an UNINITIALIZED local and ignores byte-count result, then returns whether that local is nonzero. Thus memory exact-end rejection or other read failure can produce an indeterminate boolean while setting error+84; it does not reliably return false/default. No cursor advance on failed underlying read.
char __thiscall rf_stream_adapter_read_bool_versioned(int **this, int a2, char a3)
{
  char v4; // [esp+7h] [ebp-5h] BYREF
  size_t Size; // [esp+8h] [ebp-4h]

  if ( !*this )
    return rf_binary_stream_read_bool_versioned(*(this + 1), a2, a3);
  if ( (int)*(this + 20) < a2 )
    return a3;
  Size = 1;
  rf_stream_adapter_read_bytes(this, &v4, 1u);
  return v4 != 0;
}

