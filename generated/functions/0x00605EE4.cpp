// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605EE4 crt_check_security_cookie_ecx
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native ECX security-cookie value, not an object receiver. CMP ECX,DWORD664BD8; equality executes REP RET without changing EAX or stack arguments. Mismatch
// tail-JMP60F3BC report-gsfailure, without pushing arguments or building own frame; no normal mismatch return promised. Original callers61CEC1/61CF69 supply savedCookie XOR EBP and
// preserve their status EAX on equal path. No receiver dereference, cookie repair or Boolean result. Corrected ABI is void fastcall one unsigned DWORD in ECX; native bytes unchanged.
void __fastcall crt_check_security_cookie_ecx(unsigned int a1)
{
  if ( a1 != dword_664BD8 )
    __report_gsfailure();
}

