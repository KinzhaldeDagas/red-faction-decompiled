// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054CD60 rf_record80_construct_invalid32
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall no stack args: invokes invalid-DWORD constructor at+32,writingFFFFFFFF only;returns receiver. No other fields initialized. Global initializer62DA20 uses this callback for512 records,stride50h=80,base149CB20. Not a whole80-byte zero/default constructor.
unsigned int *__thiscall rf_record80_construct_invalid32(unsigned int *this)
{
  rf_dword_construct_invalid_minus_one(this + 8);
  return this;
}

