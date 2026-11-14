// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061F134 __putwch_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(wchar character),onlyAXsemantic wint_t/WEOF
// result. UsesGLOBALhConsoleOutput,notdescriptorargument. Ifglobal6660C0!=0,initialhandle-2 callsinitconout;handle-1 ->WEOF0xFFFF.
// TryWriteConsoleW(globalhandle,&stackCharacter,1,&written,NULL);BOOLsuccess setsglobalstate1 andreturnsoriginalcharacterWITHOUTrequiringwritten1. Failure: ONLYstate2
// ANDGetLastError120 setsstate0 andfallsbackANSI;otherfailureWEOF. State0branchesstraighttofallbackwithoutinitconout.
// FallbackGetConsoleOutputCP;WideCharToMultiByte(CP,0,&character,1,out,5,NULL,NULL),thenifcachedhandle!=-1 WriteConsoleA(globalhandle,out,conversionCount,&written,NULL).
// ConversionCount0 notchecked,handle0/-2notrejectedhere,BOOLTRUEreturnscharacter regardlesswritten;FALSEWEOF. Noownerrno, locking, fdtranslation or zero-write retry.
// Securitycookieepilogue; successfulAXloaddoesnotclearupperEAX. write_nolock comparesAXtoinput,soUFFFFcannotdistinguishsameWEOFsentinel.
wint_t __cdecl _putwch_nolock(wchar_t Character)
{
  UINT ConsoleOutputCP; // eax
  DWORD v3; // eax
  DWORD NumberOfCharsWritten; // [esp+4h] [ebp-10h] BYREF
  CHAR MultiByteStr[8]; // [esp+8h] [ebp-Ch] BYREF

  if ( !dword_6660C0 )
    goto LABEL_10;
  if ( hConsoleOutput == (HANDLE)-2 )
    __initconout();
  if ( hConsoleOutput == (HANDLE)-1 )
    return -1;
  if ( !WriteConsoleW(hConsoleOutput, &Character, 1u, &NumberOfCharsWritten, nullptr) )
  {
    if ( dword_6660C0 != 2 || GetLastError() != 120 )
      return -1;
    dword_6660C0 = 0;
LABEL_10:
    ConsoleOutputCP = GetConsoleOutputCP();
    v3 = WideCharToMultiByte(ConsoleOutputCP, 0, &Character, 1, MultiByteStr, 5, nullptr, nullptr);
    if ( hConsoleOutput != (HANDLE)-1 && WriteConsoleA(hConsoleOutput, MultiByteStr, v3, &NumberOfCharsWritten, nullptr) )
      return Character;
    return -1;
  }
  dword_6660C0 = 1;
  return Character;
}

