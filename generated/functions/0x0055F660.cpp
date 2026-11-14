// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F660 rf_string_copy_construct_from_object
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Thiscall destination object, source object pointer. Sets destination buffer+4=NULL, then assigns source.buffer through bounded-C-string assign helper with limit-1. Recomputes strlen and discards source reserve extent. Does not first release existing destination storage; intended for construction. No self-copy guard (source aliasing destination observes the just-cleared pointer).
void __thiscall rf_string_copy_construct_from_object(_DWORD *this, char **a2)
{
  *(this + 1) = 0;
  rf_string_assign_cstr_bounded((int)this, a2[1], -1);
}

