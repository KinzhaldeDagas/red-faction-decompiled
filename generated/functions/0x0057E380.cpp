// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E380 rf_aggregate8034_construct_three_dword_tail
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Thiscall constructor calls three-DWORD zero constructor57E3A0 at receiver+32820(0x8034),returns receiver. Thus only12 bytes at8034..803F are zeroed;all earlier fields untouched. Original aggregate class and full size unproven;do not infer complete object zeroing or std::vector layout from old library name.
char *__thiscall rf_aggregate8034_construct_three_dword_tail(char *this)
{
  rf_three_dword_zero_construct((_DWORD *)this + 8205);
  return this;
}

