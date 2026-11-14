// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CA7F0 unknown_libname_11
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Accessor contract in glass-ledger replay: returns raw BYTE at input pointer+0 unchanged; caller tests nonzero after geometry-record lookup. No normalization, pointer-null guard or allocation in body. Keep generic inherited library label; full geometry subtype meaning of byte0 is not assigned here.
char __thiscall unknown_libname_11(void *this)
{
  return *(_BYTE *)this;
}

