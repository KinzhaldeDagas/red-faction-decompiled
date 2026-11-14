// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006178FC ___crtInitCritSecAndSpinCount
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(CS pointer,spin count),returns raw
// InitializeCriticalSectionAndSpinCount BOOL on normal APIreturn. Native EH4 scope65EEE0 hasfilter61791D,handler617934: filterreturns1 ONLY for exception code0xC0000017,0 forothers.
// Matched exception resets savedESP,SetLastError(8),result0. Handler has redundant same-code check beforeSetLastError; exceptions otherthanthatcode propagate ratherthanconverting
// toFALSE. No own pointer validation, fallback InitializeCriticalSection API, allocation, retries or errno assignment. Lifted pseudocode omits this exception-filter body.
BOOL __cdecl __crtInitCritSecAndSpinCount(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount)
{
  return InitializeCriticalSectionAndSpinCount(lpCriticalSection, dwSpinCount);
}

