// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060BC4A __validdrive
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(rawDrive), normalized bool. Raw0 returns1
// without API. Nonzero constructs four bytes lowBYTE(rawDrive+64),colon,backslash,NUL in own argument slot and calls GetDriveTypeA. Return1 iff API result neither0 nor1. No 1..26
// validation: high bits discarded for letter, so other raw values may alias drives. No own errno/doserrno mapping, locking or allocation.
BOOL __cdecl _validdrive(int RootPathName)
{
  BOOL result; // eax

  result = true;
  if ( RootPathName )
  {
    LOBYTE(RootPathName) = RootPathName + 64;
    strcpy((char *)&RootPathName + 1, ":\\");
    if ( GetDriveTypeA((LPCSTR)&RootPathName) <= 1 )
      return false;
  }
  return result;
}

