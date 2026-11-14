// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061159E __get_errno_from_oserr
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw OSerror DWORD), returns errno VALUE
// without storing errno/doserrno. Ordered FIRST-match scan of45 pairs at665110,stride8; return secondDWORD unchanged. Duplicate key6 maps9 atfirstentry and22 later, so latter
// unreachable. If noexactmatch, unsigned(error-19)<=17 =>13; elseunsigned(error-188)<=14 =>8; everyother bitpattern=>22. No LastError query, pointer allocation or handler. Exact
// ordered pairs:
// 1:22,2:2,3:2,4:24,5:13,6:9,7:12,8:12,9:12,10:7,11:8,12:22,13:22,15:2,16:13,17:18,18:2,33:13,53:2,65:13,67:2,80:17,82:13,83:13,87:22,89:11,108:13,109:32,112:28,114:9,6:22,128:10,129:10,130:9,131:22,132:13,145:41,158:13,161:2,164:11,167:13,183:17,206:2,215:11,1816:12.
int __cdecl _get_errno_from_oserr(int a1)
{
  unsigned int i; // ecx

  for ( i = 0; i < 0x2D; ++i )
  {
    if ( a1 == dword_665110[2 * i] )
      return dword_665114[2 * i];
  }
  if ( (unsigned int)(a1 - 19) > 0x11 )
    return (unsigned int)(a1 - 188) > 0xE ? 22 : 8;
  else
    return 13;
}

