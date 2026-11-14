// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00618734 __except1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Unary FP exception adapter; ordinary
// cdecl(flags,operation,double arg,double defaultResult,unsigned savedCW),28 caller stack bytes, ST0 double return. Incoming EBP is saved/restored, NOT semantic argument.
// Custom16-byte aligned frame uses EBX=entryESP-4 as original argument anchor and copies original return PC into synthetic frame. handle_exc(flags,&byValueResult,savedCW) may update
// result. If zero, clear only bit0 of scratchDWORD at scratchBase+0x40 (other bits not initialized here), then
// raise_exc(scratchBase,&byValueCW,flags,operation,&byValueArg,&byValueResult),24 caller-popped bytes. errcode(lowBYTE flags) controls errno/math dispatch. Mode0x666060 nonzero or
// code0 -> errnoFromMatherr(code), ctrlfp(savedCW,0xFFFF), return possibly updated result via FLD. Otherwise umatherr(code,operation,arg,+0.0,result,savedCW) returns ST0. Verify
// frame cookie on returning paths then restore aligned frame/entry ESP. Cookie match preserves ST0. No own SEH/finally, guaranteed CW restore if a delegate throws, or SSE-state
// restore.
double __cdecl _except1(unsigned int a1, int a2, double a3, double a4, unsigned int a5)
{
  int v5; // ebp
  int v6; // eax
  double result; // st7
  _DWORD v8[16]; // [esp+1Ch] [ebp-8Ch] BYREF
  int v9; // [esp+5Ch] [ebp-4Ch]
  unsigned int v10; // [esp+98h] [ebp-10h]
  _DWORD v11[3]; // [esp+9Ch] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+A8h] [ebp+0h]

  v11[0] = v5;
  v11[1] = retaddr;
  v10 = (unsigned int)v11 ^ dword_664BD8;
  if ( !_handle_exc(a1, &a4, a5) )
  {
    v9 &= ~1u;
    _raise_exc(v8, &a5, a1, a2, &a3, &a4);
  }
  v6 = _errcode(a1);
  if ( dword_666060 || !v6 )
  {
    _set_errno_from_matherr(v6);
    _ctrlfp(a5, 0xFFFFu);
    result = a4;
  }
  else
  {
    result = _umatherr(v6, a2, a3, 0.0, a4, a5);
  }
  crt_check_security_cookie_ecx((unsigned int)v11 ^ v10);
  return result;
}

