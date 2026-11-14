// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00621F06 ___initconout
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Noargs. XOR EAX0,push seven CreateFileA slots ordered(CONOUT$,0x40000000,3,NULL,3,0,NULL). Call import,store returned rawHANDLE to hConsoleOutput
// andreturnSAME EAX. No INVALID_HANDLE_VALUE check,CloseHandle of previousglobal,once/lock or stdout redirection; repeatedcalls may replace stored handle without release.
// Literalbytes independentlyPE-matched.
HANDLE __initconout()
{
  HANDLE result; // eax

  result = CreateFileA("CONOUT$", 0x40000000u, 3u, nullptr, 3u, 0, nullptr);
  hConsoleOutput = result;
  return result;
}

