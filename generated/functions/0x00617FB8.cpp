// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617FB8 __set_exp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Leaf x87 double exponent-field rewrite, ST0 return,
// cdecl double plus full 32-bit exponent argument. Copies input through FLD/FSTP then sets top WORD to (oldTop &0x800F) OR low16((exponent+1022)<<4), with 32-bit wrapping addition.
// No 0x7FF0 mask on shifted exponent: out-of-range biased exponent can force sign bit; this is not general arithmetic scaling/range validation. Overlapping DWORD read at input+6
// includes argument bytes but AND 0x800F discards those bytes. Native instructions write only EAX/ECX plus frame/stack; EDX is preserved and __decomp relies on it across CALL.
// Explicit __spoils<eax,ecx> records that contract. No special-value classification, errno or environment preservation; live x87 loads/stores may quiet/trap signaling NaNs.
double __cdecl __spoils<eax,ecx> _set_exp(double a1, int a2)
{
  double v3; // [esp+0h] [ebp-8h]

  v3 = a1;
  HIWORD(v3) = HIWORD(a1) & 0x800F | (16 * (a2 + 1022));
  return v3;
}

