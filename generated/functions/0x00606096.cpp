// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606096 __onexit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(_onexit_t callback), same callback/NULL result
// as __onexit_nolock. lockexit acquires CRT lock8; call nolock helper and preserve its return. EH4 scope65E6D0 finally6060CC invokes unlockexit on normal completion and unwind. No
// own callback validation, invocation, allocation logic, or error translation.
_onexit_t __cdecl _onexit(_onexit_t Func)
{
  int (__cdecl *v2)(); // [esp+10h] [ebp-1Ch]

  _lockexit();
  v2 = _onexit_nolock(Func);
  _unlockexit();
  return v2;
}

