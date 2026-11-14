// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060BECC __chdrive
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errno=E then
// invalid_parameter(NULL,NULL,NULL,0,0); any stated subsequent return requires that handler to return. Cdecl(SIGNED drive),0/-1. Require1..26 else dos15/invalid13/-1. Acquire lock7,
// arm EH4 scope65E9B0, build "X:" plus NUL (NO backslash), SetCurrentDirectoryA; true0, false maps GetLastError/-1 evenerror0. Finally unlock7 normal/unwind handler60BF65. No own
// environment =X: update; drive-relative path interpretation delegated to OS.
int __cdecl _chdrive(int Drive)
{
  DWORD LastError; // eax
  int v3; // [esp+10h] [ebp-20h]
  CHAR PathName; // [esp+14h] [ebp-1Ch] BYREF
  char v5[2]; // [esp+15h] [ebp-1Bh] BYREF
  CPPEH_RECORD ms_exc; // [esp+18h] [ebp-18h]

  if ( Drive >= 1 && Drive <= 26 )
  {
    _lock(7);
    ms_exc.registration.TryLevel = 0;
    PathName = Drive + 64;
    strcpy(v5, ":");
    if ( SetCurrentDirectoryA(&PathName) )
    {
      v3 = 0;
    }
    else
    {
      LastError = GetLastError();
      _dosmaperr(LastError);
      v3 = -1;
    }
    ms_exc.registration.TryLevel = -2;
    _unlock(7);
    return v3;
  }
  else
  {
    *__doserrno() = 15;
    *_errno() = 13;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

