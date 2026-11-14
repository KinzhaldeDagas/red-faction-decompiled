// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549F20 rf_dword_flag_bit0_assign
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall flagsDWORD,byte truth value. If nonzero ORs bit01,otherwise ANDsFFFFFFFE,preserving every other bit. Returns receiver. No class role/allocation/file-mode meaning inferred from nearby inline functions.
unsigned int *__thiscall rf_dword_flag_bit0_assign(unsigned int *this, char a2)
{
  unsigned int v2; // edx

  if ( a2 )
    v2 = *this | 1;
  else
    v2 = *this & 0xFFFFFFFE;
  *this = v2;
  return this;
}

