// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006154FE @_EH4_CallFilterFunc@8
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Actual fastcall registers ECX filter entry,EDX target frame. Save oldEBP/ESI/EDI/EBX,setEBP=EDX;zeroEAX/EBX/EDX/ESI/EDI,invoke ECX with NO explicit stack
// args. Restore savednonvolatile/frame,plainRET; returns filterEAX. Decorated@8 denotes two register DWORDs, not RET8. Old thiscall one-parameter type omitted frame; corrected
// fastcall ABI. No own exception catch/pointer validation.
int __fastcall _EH4_CallFilterFunc(void *filter, void *frame)
{
  return ((int (*)(void))filter)();
}

