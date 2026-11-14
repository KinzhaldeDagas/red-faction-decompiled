// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6770 rf_byte_zero_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Thiscall(receiver), no stack arguments. Writes ONLY receiver BYTE0=0 and returns receiver in EAX. No whole-object zeroing, allocation or assumed record size. Many static
// initialization thunks share this trivial byte-prefix constructor; no stronger network-object identity inferred.
_BYTE *__thiscall rf_byte_zero_construct(_BYTE *this)
{
  *this = 0;
  return this;
}

