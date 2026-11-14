// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F720 rf_string_length_from_cstr
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Returns strlen(buffer+4) when non-NULL, else0. Does not return stored extent DWORD+0; reserve operations can leave that field larger than current C-string length.
unsigned int __thiscall rf_string_length_from_cstr(const char **this)
{
  if ( *(this + 1) )
    return strlen(*(this + 1));
  else
    return 0;
}

