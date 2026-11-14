// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C8F0 rf_fixed_block48_copy
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall destination,source. Copies exactly0x30(48) bytes with inline block copy. No allocation,null/overlap guard,numeric conversion or extra homogeneous component initialization. Used as version-fallback copy for0x59FC30; that reader present path additionally writes at byte+48.
void __thiscall rf_fixed_block48_copy(void *this, const void *a2)
{
  qmemcpy(this, a2, 0x30u);
}

