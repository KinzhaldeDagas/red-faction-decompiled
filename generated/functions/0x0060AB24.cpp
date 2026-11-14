// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060AB24 ___tmainCRTStartup
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs CRT entry returns WinMain/exception status
// only on returning managed or startup-exception paths. EH4 scope65E968 has two independent entries: filter60AC89 returns1, handler60AC8D returns255, covering ONLY GetStartupInfoA
// call; initial STARTUPINFOA stack object is not initialized/zeroed and cb not set. Determine managed flag from fixed image400000 MZ, PE signature via e_lfanew, PE32 magic10B,
// NumberOfRvaAndSizes>14 and nonzero CLR-directory RVA at PE+E8; no bounds validation/module lookup. heap_init(1) false -> fast_error_exit28; mtinit false -> fast_error_exit16; run
// verified empty span657DD4. These precede second try. Second entry filter60AC4F/handler60AC63 covers ioinit through returning cleanup: ioinit<0 -> amsg_exit27; publish
// GetCommandLineA2022F84 and environment20213A0; setargv<0 ->8; setenvp<0 ->9; cinit(1) nonzero -> amsg_exit(that status). WinMain stdcall(400000,NULL,wincmdln(),show), where show is
// zeroextended wShowWindow iff STARTF_USESHOWWINDOW1 else10. Nonmanaged normal result -> FULL exit60A644; managed -> _cexit60A670 then return result. Second filter stores exception
// code, calls XcptFilter(code,EXCEPTION_POINTERS*), returns its disposition. Handler result=exception code; nonmanaged -> QUICK _exit60A65A, managed -> _c_exit60A67F then return. No
// own rollback of partial initialization; cleanup exceptions are subject to installed scope only where native try level remains armed.
int __tmainCRTStartup()
{
  int v0; // eax
  CHAR *v1; // eax
  int wShowWindow; // ecx
  int v3; // eax
  struct _STARTUPINFOA StartupInfo; // [esp+10h] [ebp-68h] BYREF
  int v6; // [esp+58h] [ebp-20h]
  BOOL v7; // [esp+5Ch] [ebp-1Ch]
  CPPEH_RECORD ms_exc; // [esp+60h] [ebp-18h]

  ms_exc.registration.TryLevel = 0;
  GetStartupInfoA(&StartupInfo);
  ms_exc.registration.TryLevel = -2;
  v7 = MEMORY[0x400000] == 23117
    && *(_DWORD *)(MEMORY[0x40003C] + 0x400000) == 17744
    && *(_WORD *)(MEMORY[0x40003C] + 4194328) == 267
    && *(_DWORD *)(MEMORY[0x40003C] + 4194420) > 0xEu
    && *(_DWORD *)(MEMORY[0x40003C] + 4194536) != 0;
  if ( !_heap_init(1) )
    fast_error_exit(28);
  if ( !_mtinit() )
    fast_error_exit(16);
  crt_run_empty_callback_span_00657dd4();
  ms_exc.registration.TryLevel = 1;
  if ( _ioinit() < 0 )
    _amsg_exit(27);
  dword_2022F84 = GetCommandLineA();
  unk_20213A0 = __crtGetEnvironmentStringsA();
  if ( _setargv() < 0 )
    _amsg_exit(8);
  if ( _setenvp() < 0 )
    _amsg_exit(9);
  v0 = _cinit(1);
  if ( v0 )
    _amsg_exit(v0);
  v1 = (CHAR *)_wincmdln();
  if ( (StartupInfo.dwFlags & 1) != 0 )
    wShowWindow = StartupInfo.wShowWindow;
  else
    wShowWindow = 10;
  v3 = WinMain((HINSTANCE)0x400000, nullptr, v1, wShowWindow);
  v6 = v3;
  if ( !v7 )
    exit(v3);
  _cexit();
  return v6;
}

