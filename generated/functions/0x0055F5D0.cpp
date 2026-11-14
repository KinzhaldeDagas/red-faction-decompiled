// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F5D0 rf_string_construct_empty
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Sets buffer pointer+4=NULL and assigns the static empty C string through55F3F0 with limit-1, resulting in extent0 and NULL buffer. Thiscall, no stack arguments. Does not allocate.
void __thiscall rf_string_construct_empty(_DWORD *this)
{
  *(this + 1) = 0;
  rf_string_assign_cstr_bounded((int)this, (char *)&byte_640808, -1);
}

