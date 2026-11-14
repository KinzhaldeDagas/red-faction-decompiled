// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DC8E __ms_p5_mp_test_fdiv
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs int. Original GetModuleHandleA("KERNEL32"),if
// nonNULL GetProcAddress(handle,"IsProcessorFeaturePresent"). NonNULL function pointer: push raw featureID0,indirect CALL expecting stdcall RET4,return RAW helper EAX (not normalized
// locally). Missing module or symbol ->TAIL JMP ms_p5_test_fdiv with original returnPC,whose arithmetic diagnostic supplies canonical0/1. Resolve fresh each invocation,no pointer
// caching,FreeLibrary,CPU pinning/per-processor loop,own SEH or FPU control normalization. Function name does not imply iteration over processors; API capability policy belongs to
// delegate.
int _ms_p5_mp_test_fdiv()
{
  HMODULE ModuleHandleA; // eax
  BOOL (__stdcall *IsProcessorFeaturePresent)(DWORD); // eax

  ModuleHandleA = GetModuleHandleA("KERNEL32");
  if ( ModuleHandleA
    && (IsProcessorFeaturePresent = (BOOL (__stdcall *)(DWORD))GetProcAddress(
                                                                 ModuleHandleA,
                                                                 "IsProcessorFeaturePresent")) != nullptr )
  {
    return IsProcessorFeaturePresent(0);
  }
  else
  {
    return _ms_p5_test_fdiv();
  }
}

