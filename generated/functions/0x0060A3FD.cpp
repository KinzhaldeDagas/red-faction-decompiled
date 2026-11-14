// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A3FD ___crtCorExitProcess
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(exitcode). GetModuleHandleW(mscoree.dll)
// WITHOUT loading it; NULL returns0. Presentmodule ->GetProcAddress(CorExitProcess); NULL returns0. Presentexport indirect STDCALL export(original code); if export returns,
// propagateEAX residue/result, not a guaranteed HMODULE. No regular ExitProcess fallback, FreeLibrary, waiting loop or validation in body.
HMODULE __cdecl __crtCorExitProcess(int a1)
{
  HMODULE result; // eax

  result = GetModuleHandleW(&ModuleName);
  if ( result )
  {
    result = (HMODULE)GetProcAddress(result, "CorExitProcess");
    if ( result )
      return ((HMODULE (__stdcall *)(int))result)(a1);
  }
  return result;
}

