// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617E75 ___security_init_cookie
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs security-cookie setup. Readcookie664BD8; if
// !=0xBB40E64E ANDhigh16 nonzero, leavecookieunchanged andrefreshcomplement664BDC=~cookie only. Else XOR FILETIME low/high,processID,threadID,GetTickCount,QPC low/high into32-bit
// candidate. FILETIME localzeroed beforeAPI; QPC localNOTinitialized andAPI BOOLignored. Candidate==default ->default+1 (0xBB40E64F); otherwiseifhigh16==0,ORcandidate
// withcandidate<<16. Storecookie/complement. Zero candidate remainsZERO; no separate nonzero/fixed0x4711 correction, stack-address entropy, crypto RNG or own errorhandling. Do not
// substitute a newer CRT cookie recipe for these exact native operands.
void __cdecl __security_init_cookie()
{
  DWORD v0; // esi
  DWORD v1; // esi
  DWORD v2; // esi
  DWORD v3; // esi
  DWORD v4; // esi
  LARGE_INTEGER PerformanceCount; // [esp+8h] [ebp-10h] BYREF
  struct _FILETIME SystemTimeAsFileTime; // [esp+10h] [ebp-8h] BYREF

  SystemTimeAsFileTime.dwLowDateTime = 0;
  SystemTimeAsFileTime.dwHighDateTime = 0;
  if ( dword_664BD8 == -1153374642 || (dword_664BD8 & 0xFFFF0000) == 0 )
  {
    GetSystemTimeAsFileTime(&SystemTimeAsFileTime);
    v0 = SystemTimeAsFileTime.dwLowDateTime ^ SystemTimeAsFileTime.dwHighDateTime;
    v1 = GetCurrentProcessId() ^ v0;
    v2 = GetCurrentThreadId() ^ v1;
    v3 = GetTickCount() ^ v2;
    QueryPerformanceCounter(&PerformanceCount);
    v4 = PerformanceCount.LowPart ^ PerformanceCount.HighPart ^ v3;
    if ( v4 == -1153374642 )
    {
      v4 = -1153374641;
    }
    else if ( (v4 & 0xFFFF0000) == 0 )
    {
      v4 |= v4 << 16;
    }
    dword_664BD8 = v4;
    dword_664BDC = ~v4;
  }
  else
  {
    dword_664BDC = ~dword_664BD8;
  }
}

