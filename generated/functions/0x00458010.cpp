// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458010 rf_receiver_plus4_address_458010
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall ECX receiver,no stack arguments. Save receiver only to local stack, return EAX=receiver+4 using wrapping32-bit ADD. Does NOT dereference receiver or
// load DWORD[receiver+4]: result is an interior address, not member value or allocated copy. NULL receiver produces pointer bits4; FFFFFFFC wraps0. No NULL/type/alignment guard,
// allocation, ownership change, object/global write or normalization. Used by multiple RF UI pointer-processing callers, but generic offset-address native operation alone does not
// uniquely prove implementation origin; library flag preserved.
char *__thiscall rf_receiver_plus4_address_458010(char *this)
{
  return this + 4;
}

