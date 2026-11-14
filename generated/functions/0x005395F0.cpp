// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005395F0 rf_flags_test_2025_clear
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall pointer to flags DWORD,returns BOOL((*flags&0x2025)==0). All bits in mask must clear. No other field reads/writes;used by lightmap processing537980. Original owning class/individual bit meanings unproven;do not assign a broader face visibility or allocation predicate.
bool __thiscall rf_flags_test_2025_clear(_DWORD *this)
{
  return (*this & 0x2025) == 0;
}

