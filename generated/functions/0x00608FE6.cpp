// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608FE6 crt_type_info_scalar_delete
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native thiscall ECX receiver plus one4-byte flag slot, RET4. Preserve receiver in ESI. Call00608FD6 member/base destructor once on original receiver. Then
// test ONLY bit0 of flag slot; set bit admits cdecl operator delete6060E9(receiver), POP ECX reclaims slot. Always return original receiver bits in EAX, including after free. Other
// flag bits ignored; no array cookie, element loop, own NULL/ownership validation or repeated-delete guard. Native member/base work precedes optional scalar deallocation; char formal
// uses same low flag bit in a DWORD stack slot.
struct type_info *__thiscall crt_type_info_scalar_delete(struct type_info *this, char a2)
{
  crt_type_info_destroy_members(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

