// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A3A4 __crt_waiting_on_module_handle
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(moduleName wide pointer), returns
// GetModuleHandleW result orNULL. No immediate lookup: delay1000, Sleep(delay),GetModuleHandleW(name),delay+=1000; stop if nextdelay>60000 ORmodule nonNULL, otherwise repeat. Thus
// delays1000..60000 inclusive, max60 polls and nominal1,830,000ms total sleep (30.5minutes) when all fail, not a60-second cumulative timeout. No LoadLibrary, free, pointer validation
// or own error mapping.
HMODULE __cdecl _crt_waiting_on_module_handle(LPCWSTR lpModuleName)
{
  DWORD v1; // edi
  HMODULE result; // eax

  v1 = 1000;
  do
  {
    Sleep(v1);
    result = GetModuleHandleW(lpModuleName);
    v1 += 1000;
  }
  while ( v1 <= 0xEA60 && !result );
  return result;
}

