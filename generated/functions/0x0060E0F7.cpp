// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E0F7 __decode_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl raw pointer; returns transformed pointer or ORIGINAL input. Read TlsGetValue(global dwTlsIndex). If nonNULL and provider index6650C0!=-1, push provider
// index then re-fetch TLS function pointer and CALL it, WITHOUT second NULL check. NonNULL returned provider object selects function at+508; a NULL selected function falls through
// identity return, not platform retry. If provider admission fails or provider returnsNULL: GetModuleHandleW(KERNEL32.DLL), fallback __crt_waiting_on_module_handle ifNULL; absent
// module returns original. Otherwise GetProcAddress(DecodePointer), invoke nonNULL stdcall function(input) and return its result; missing export returns original. No pointer
// dereference, constant-XOR encoding assumption, validation, cache store, FreeLibrary or synchronization in own body. Explicit4-byte caller argument cleanup remains cdecl.
PVOID __cdecl _decode_pointer(void *a1)
{
  int (__stdcall *Value)(int); // eax
  int v2; // eax
  PVOID (__stdcall *DecodePointer)(PVOID); // eax
  HMODULE ModuleHandleW; // eax
  int v6; // [esp-4h] [ebp-8h]

  if ( TlsGetValue(dwTlsIndex)
    && dword_6650C0 != -1
    && (v6 = dword_6650C0, Value = (int (__stdcall *)(int))TlsGetValue(dwTlsIndex), (v2 = Value(v6)) != 0) )
  {
    DecodePointer = *(PVOID (__stdcall **)(PVOID))(v2 + 508);
  }
  else
  {
    ModuleHandleW = GetModuleHandleW(L"KERNEL32.DLL");
    if ( !ModuleHandleW )
    {
      ModuleHandleW = _crt_waiting_on_module_handle(L"KERNEL32.DLL");
      if ( !ModuleHandleW )
        return a1;
    }
    DecodePointer = (PVOID (__stdcall *)(PVOID))GetProcAddress(ModuleHandleW, "DecodePointer");
  }
  if ( DecodePointer )
    return DecodePointer(a1);
  return a1;
}

