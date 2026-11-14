// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E172 ___set_flsgetvalue
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): No arguments; returns a GETTER FUNCTION POINTER, not
// thread data. TlsGetValue(TLS index6650C4); nonNULL cached value returned unchanged. NULL result decodes provider global20213B4, saves pointer, calls TlsSetValue(index,pointer),
// ignores BOOL, returns decoded pointer even if caching failed. No distinction between empty TLS value and TlsGetValue failure, no callable-pointer validation, allocation or
// LastError preservation. Cache holds unencoded getter; other-thread cache misses decode live encoded global.
void *__set_flsgetvalue()
{
  void *Value; // esi

  Value = TlsGetValue(dwTlsIndex);
  if ( !Value )
  {
    Value = _decode_pointer(MEMORY[0x20213B4]);
    TlsSetValue(dwTlsIndex, Value);
  }
  return Value;
}

