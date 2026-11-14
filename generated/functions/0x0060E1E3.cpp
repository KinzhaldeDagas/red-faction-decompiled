// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E1E3 __initptd
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(PTD, optional locinfo), initializes selected
// fields of existing storage, no allocation or NULL check. GetModuleHandleW(KERNEL32.DLL), ifNULL call waiting helper; when module nonNULL lookup EncodePointer/DecodePointer and
// store raw results atPTD+504/+508, includingNULL. If module remainsNULL those fields are untouched. SetPTD+92=64E860 exception-action table,+20=1,+112=1,bytes+200/+331=ASCII
// C,+104=static665468 mbinfo. Lock13/armSEH, InterlockedIncrement(mbinfo refcount), finallyunlock13. Separately lock12/armSEH, set+108 to supplied locinfo or LIVE pointer665A70,
// addlocaleref, finallyunlock12. Both scopes enclose-2; no nested13/12 lock and no whole-PTD zeroing, failure rollback or semantic return value. Corrected prototype is void with two
// pointer arguments; both direct callers discard EAX before GetCurrentThreadId. Caller normally supplied532-byte calloc storage.
void __cdecl _initptd(void *ptd, void *locinfo)
{
  HMODULE ModuleHandleW; // eax
  HMODULE hModule; // [esp+10h] [ebp-1Ch]
  int savedregs; // [esp+2Ch] [ebp+0h]

  ModuleHandleW = GetModuleHandleW(L"KERNEL32.DLL");
  if ( !ModuleHandleW )
    ModuleHandleW = _crt_waiting_on_module_handle(L"KERNEL32.DLL");
  hModule = ModuleHandleW;
  *((_DWORD *)ptd + 23) = &unk_64E860;
  *((_DWORD *)ptd + 5) = 1;
  if ( ModuleHandleW )
  {
    *((_DWORD *)ptd + 126) = GetProcAddress(ModuleHandleW, "EncodePointer");
    *((_DWORD *)ptd + 127) = GetProcAddress(hModule, "DecodePointer");
  }
  *((_DWORD *)ptd + 28) = 1;
  *((_BYTE *)ptd + 200) = 67;
  *((_BYTE *)ptd + 331) = 67;
  *((_DWORD *)ptd + 26) = &unk_665468;
  _lock(13);
  InterlockedIncrement(*((volatile LONG **)ptd + 26));
  _unlock(13);
  _lock(12);
  *((_DWORD *)ptd + 27) = locinfo;
  if ( !locinfo )
    *((_DWORD *)ptd + 27) = off_665A70;
  __addlocaleref(*((volatile LONG **)ptd + 27));
  savedregs = 6349484;
  _unlock(12);
}

