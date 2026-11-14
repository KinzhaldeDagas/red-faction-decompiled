// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F600 rf_string_construct_from_cstr
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall destination and source C string. Initializes buffer+4=NULL, assigns source with limit-1 through rf_string_assign_cstr_bounded, returns destination. Source NULL yields empty extent0/NULL buffer. Does not release preexisting destination storage before clearing its pointer; construction rather than reassignment.
_DWORD *__thiscall rf_string_construct_from_cstr(_DWORD *this, char *Source)
{
  *(this + 1) = 0;
  rf_string_assign_cstr_bounded((int)this, Source, -1);
  return this;
}

