// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609007 ??8type_info@@QBE_NABV0@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall receiver plus one other type_info pointer, RET4. Compare NUL strings at other+9 and self+9 via strcmp (pushed self first, other second), map raw
// strcmp==0 to full BOOL1 otherwise0 using NEG/SBB/INC. Does not compare object identity/vtables/cache pointers or strip extra chars beyond fixed+9; no NULL/length validation. EAX
// Boolean, not lexical ordering.
BOOL __thiscall type_info::operator==(const char *this, int a2)
{
  return strcmp((const char *)(a2 + 9), this + 9) == 0;
}

