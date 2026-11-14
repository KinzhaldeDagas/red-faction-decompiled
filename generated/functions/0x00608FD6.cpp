// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608FD6 crt_type_info_destroy_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): ECX type_info receiver, no stack args/plain RET. Push SAME receiver as one cdecl stack argument, overwrite DWORD0 with type_info vtable, call615D6E
// _Type_info_dtor, POP ECX reclaims argument. No own containing delete, NULL test, returned receiver guarantee or extra member cleanup. Runtime RTTI-name/cache teardown remains
// delegated to615D6E; native explicit push means that helper receives stack pointer argument even though wrapper is member ABI.
void __thiscall crt_type_info_destroy_members(struct type_info *this)
{
  *(_DWORD *)this = &type_info::`vftable';
  type_info::_Type_info_dtor(this);
}

