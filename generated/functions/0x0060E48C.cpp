// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E48C __mtinit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs startup, returns1 on completed main-thread
// PTD setup,0 on detected failure. FindKERNEL32 viaGetModuleHandleW thenwaitinghelper. Resolve FlsAlloc/GetValue/SetValue/Free into rawglobals20213B0/B4/B8/BC; if ANY missing replace
// ALL four with crtTlsAlloc,TlsGetValue,TlsSetValue,TlsFree. Allocate separate getter-cache TLS index6650C4 andstore UNENCODED getter pointer usingTlsSetValue. TlsAlloc==-1 ORthis
// TlsSetValueFALSE returns0 DIRECTLY, bypassing mtterm and leaving partial raw-provider/TLS state. Otherwise callinit_pointers thenencode each provider global. mtinitlocks;
// decodeallocator, stdcall alloc(freefls callback),store index6650C0; index!=-1 ->calloc_crt(1,532),decodeprovider
// setter,set(index,PTD),theninitptd(NULLlocale),threadID/+4=-1,return1. Module failure, lock failure, provider-index failure, PTDalloc failure or provider-setterFALSE after encoding
// callmtterm then0. On provider-setterFALSE body has NO explicit free of the newly allocated uninstalled PTD, unlike getptd_noexit. No own exception cleanup or rollback of all
// globals.
int _mtinit()
{
  HMODULE ModuleHandleW; // eax
  HMODULE v1; // edi
  BOOL (__stdcall *FlsFree)(DWORD); // eax
  DWORD v3; // eax
  int (__stdcall *v4)(_DWORD); // eax
  int v5; // eax
  DWORD *v6; // esi
  int (__stdcall *v7)(int, int); // eax
  DWORD CurrentThreadId; // eax
  int v10; // [esp-8h] [ebp-10h]
  int v11; // [esp-4h] [ebp-Ch]

  ModuleHandleW = GetModuleHandleW(L"KERNEL32.DLL");
  if ( !ModuleHandleW )
    ModuleHandleW = _crt_waiting_on_module_handle(L"KERNEL32.DLL");
  v1 = ModuleHandleW;
  if ( ModuleHandleW )
  {
    MEMORY[0x20213B0] = (DWORD (__stdcall *)(PFLS_CALLBACK_FUNCTION))GetProcAddress(ModuleHandleW, "FlsAlloc");
    MEMORY[0x20213B4] = (PVOID (__stdcall *)(DWORD))GetProcAddress(v1, "FlsGetValue");
    MEMORY[0x20213B8] = (BOOL (__stdcall *)(DWORD, PVOID))GetProcAddress(v1, "FlsSetValue");
    FlsFree = (BOOL (__stdcall *)(DWORD))GetProcAddress(v1, "FlsFree");
    dword_20213BC = FlsFree;
    if ( !MEMORY[0x20213B0] || !MEMORY[0x20213B4] || !MEMORY[0x20213B8] || !FlsFree )
    {
      MEMORY[0x20213B4] = TlsGetValue;
      MEMORY[0x20213B0] = (DWORD (__stdcall *)(PFLS_CALLBACK_FUNCTION))__crtTlsAlloc;
      MEMORY[0x20213B8] = TlsSetValue;
      dword_20213BC = TlsFree;
    }
    v3 = TlsAlloc();
    dwTlsIndex = v3;
    if ( v3 == -1 || !TlsSetValue(v3, MEMORY[0x20213B4]) )
      return 0;
    _init_pointers();
    MEMORY[0x20213B0] = (DWORD (__stdcall *)(PFLS_CALLBACK_FUNCTION))_encode_pointer(MEMORY[0x20213B0]);
    MEMORY[0x20213B4] = (PVOID (__stdcall *)(DWORD))_encode_pointer(MEMORY[0x20213B4]);
    MEMORY[0x20213B8] = (BOOL (__stdcall *)(DWORD, PVOID))_encode_pointer(MEMORY[0x20213B8]);
    dword_20213BC = _encode_pointer(dword_20213BC);
    if ( _mtinitlocks() )
    {
      v4 = (int (__stdcall *)(_DWORD))_decode_pointer(MEMORY[0x20213B0]);
      dword_6650C0 = v4(_freefls);
      if ( dword_6650C0 != -1 )
      {
        v5 = _calloc_crt(1u, 532);
        v6 = (DWORD *)v5;
        if ( v5 )
        {
          v11 = v5;
          v10 = dword_6650C0;
          v7 = (int (__stdcall *)(int, int))_decode_pointer(MEMORY[0x20213B8]);
          if ( v7(v10, v11) )
          {
            _initptd(v6, nullptr);
            CurrentThreadId = GetCurrentThreadId();
            v6[1] = -1;
            *v6 = CurrentThreadId;
            return 1;
          }
        }
      }
    }
  }
  _mtterm();
  return 0;
}

