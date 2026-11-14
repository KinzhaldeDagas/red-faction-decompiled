// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539740 rf_dual_array28_construct_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Initializes DWORD-array headers at receiver+4 and+16,each count/capacity/backing0 via549FB0(initialCapacity0). Prefix DWORD0 untouched;no allocation or full28-byte zeroing. Exact original aggregate class unproven.
void __thiscall rf_dual_array28_construct_members(char *this)
{
  rf_dword_array_construct_capacity(this + 4, 0);
  rf_dword_array_construct_capacity(this + 16, 0);
}

