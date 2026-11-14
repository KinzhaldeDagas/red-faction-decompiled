// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A493 __cinit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(int fpmathArg), int initialization status. If
// function-pointer slot648D38 nonNULL AND IsNonwritableInCurrentImage(address OF SLOT648D38), invoke current pointer with argument. The test validates slot location, not callback
// target. Always initp_misc_cfltcvt_tab (encodes ten current DWORDs665060..84, no once guard). __initterm_e over [630F30,630F4C) executes C initializers, returns first nonzero
// unchanged. Success registers atexit(crt_run_empty_callback_span657DDC), ignoring registration failure; then __initterm over [6303E8,630F2C),721 pointer slots, using
// EAX-first/stack-last ABI. Finally if slot2022F98 nonNULL AND nonwritable-slot check succeeds, call current callback(0,2,0), with callee cleanup12. Return0. No own lock, once guard,
// catch, rollback, or validation of function-pointer destinations. Original PE C initializer slots: 0,606065,60CDE4,60F574,60F945,612F3D,61799E.
int __cdecl _cinit(int a1)
{
  int result; // eax

  if ( _fpmath && _IsNonwritableInCurrentImage((int)&off_648D38) )
    _fpmath(a1);
  _initp_misc_cfltcvt_tab();
  result = _initterm_e((_PIFV *)&dword_630F30, (_PIFV *)&Last);
  if ( !result )
  {
    atexit(crt_run_empty_callback_span_00657ddc);
    _initterm(&unk_6303E8, (void *)&First);
    if ( unk_2022F98 )
    {
      if ( _IsNonwritableInCurrentImage((int)&unk_2022F98) )
        unk_2022F98(0, 2, 0);
    }
    return 0;
  }
  return result;
}

