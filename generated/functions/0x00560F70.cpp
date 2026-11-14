// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560F70 rf_string_byte_pointer_or_zero_sentinel
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): If signed index>=0 and index<stored extent+0, returns buffer+4 plus index without a separate buffer-NULL check. Otherwise writes zero to shared byte17F1114 and returns its address. Returns a writable pointer; invalid accesses share mutable sentinel storage. Uses stored extent rather than recomputed strlen.
char *__thiscall rf_string_byte_pointer_or_zero_sentinel(int *this, int a2)
{
  if ( a2 >= 0 && a2 < *this )
    return (char *)(a2 + *(this + 1));
  byte_17F1114[0] = 0;
  return byte_17F1114;
}

