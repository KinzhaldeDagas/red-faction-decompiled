// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060611A crt_bad_alloc_scalar_delete
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native thiscall ECX receiver plus one4-byte flag slot, RET4. Preserve receiver in ESI. Install std::bad_alloc vtable then call60F87E base exception message
// destructor. Then test ONLY bit0 of flag slot; set bit admits cdecl operator delete6060E9(receiver), POP ECX reclaims slot. Always return original receiver bits in EAX, including
// after free. Other flag bits ignored; no array cookie, element loop, own NULL/ownership validation or repeated-delete guard. Native member/base work precedes optional scalar
// deallocation; char formal uses same low flag bit in a DWORD stack slot.
_DWORD *__thiscall crt_bad_alloc_scalar_delete(_DWORD *this, char a2)
{
  *this = &std::bad_alloc::`vftable';
  crt_exception_destroy_owned_message(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

