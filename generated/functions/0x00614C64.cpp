// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614C64 __ioinit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31);
// handle0,flagsBYTE4,lookaheadBYTE5,CSinitDWORD8,CS12,encodingBYTE36,extraLookahead37/38,positionLow/High40/44,conversionDWORD48,pendingConsoleBYTE52/pendingDWORD56. Kind is SIGNED
// low7 encoding bits, normally0 ANSI,1 UTF8-backed UTF16,2 UTF16LE; flags80 controls text separately. Noargs descriptor initialization,0/-1. EH4 scope65EDE0 arms
// ONLYaroundGetStartupInfoA; filter614EA1 returns1 forANYexception,handler614EA5 restoresESP andreturns-1. AfterGetStartupInfo disablescope;
// laterallocation/CSexceptionsnotcaughtbythattry. calloc_crt(32,64); firstfailure-1 beforeoverwritingtable/limit. Successinstallblock0 andlimit32;
// eachrecordflags0,handle-1,lookahead5/37/38=10,CSinit0,encoding0,pending52/56=0,otherbytesfromcalloc. IfcbReserved2!=0 ANDlpReserved2nonnull: readRAWsignedcount atblob0 withNO
// byte-length validation; flags=blob+4,handlearray=blob+4+ORIGINALcount (offsetcomputedBEFOREclamp). Signedcount>=2048 clamped2048; negativecountsnotrejectedbutloops skip.
// Addcalloc32x64blocks untilLIVElimit>=count; laterallocationfailurecapsprocessingcounttoexistinglimit andcontinues,notfatal.
// Eachnewrecordsameinitialization,encodinglow7cleared/preservebit7 (callocinitial0). Inheritfirstcountrecords ifhandle !=-1/-2 ANDflagsopen1 AND(pipe8 ORGetFileType(handle)nonzero);
// zeroHANDLEwithpipe8canpasswithoutOSquery. Copyrawhandle/flags,initCSspin4000; FALSEreturns-1 withpartialtables/handlesretained,no rollback; successCSinit++. Forfd0..2:
// existinghandleotherthan-1/-2 simplyORtext80. Missingstandardsetsflags81,GetStdHandle(-10/-11/-12),requirehandle!=0/-1
// andGetFileTypenonzero;storehandle,classifyLOWBYTEtype2->device40,3->pipe8,initCS/incrementorreturn-1. InvalidstandardgetsflagsC1,handle-2,NOCSinitialization.
// FullsuccessSetHandleCount(limit),IGNOREresult,return0. No close/freeofpreviousglobals, fullstartupblob validation, encodinginheritance, orcleanupofearlierinstalledrecords
// onlaterfailure.
int _ioinit()
{
  char *v0; // eax
  unsigned int i; // ecx
  int v2; // edi
  LPBYTE v3; // ebx
  char *v4; // eax
  _DWORD *v5; // ecx
  unsigned int j; // edx
  int v7; // esi
  int m; // ebx
  int v9; // esi
  DWORD v10; // eax
  HANDLE StdHandle; // eax
  HANDLE v12; // edi
  DWORD FileType; // eax
  struct _STARTUPINFOA StartupInfo; // [esp+10h] [ebp-64h] BYREF
  int k; // [esp+54h] [ebp-20h]
  HANDLE *v17; // [esp+58h] [ebp-1Ch]
  CPPEH_RECORD ms_exc; // [esp+5Ch] [ebp-18h]

  ms_exc.registration.TryLevel = 0;
  GetStartupInfoA(&StartupInfo);
  ms_exc.registration.TryLevel = -2;
  v0 = (char *)_calloc_crt(0x20u, 0x40u);
  if ( !v0 )
    return -1;
  unk_2021E40[0] = (int)v0;
  MEMORY[0x2021E20] = 32;
  for ( i = (unsigned int)(v0 + 2048); (unsigned int)v0 < i; i = unk_2021E40[0] + 2048 )
  {
    v0[4] = 0;
    *(_DWORD *)v0 = -1;
    v0[5] = 10;
    *((_DWORD *)v0 + 2) = 0;
    v0[36] = 0;
    v0[37] = 10;
    v0[38] = 10;
    *((_DWORD *)v0 + 14) = 0;
    v0[52] = 0;
    v0 += 64;
  }
  if ( StartupInfo.cbReserved2 && StartupInfo.lpReserved2 )
  {
    v2 = *(_DWORD *)StartupInfo.lpReserved2;
    v3 = StartupInfo.lpReserved2 + 4;
    v17 = (HANDLE *)&StartupInfo.lpReserved2[*(_DWORD *)StartupInfo.lpReserved2 + 4];
    if ( v2 >= 2048 )
      v2 = 2048;
    k = 1;
    while ( (int)MEMORY[0x2021E20] < v2 )
    {
      v4 = (char *)_calloc_crt(0x20u, 0x40u);
      if ( !v4 )
      {
        v2 = MEMORY[0x2021E20];
        break;
      }
      v5 = (_DWORD *)(4 * k + 33693248);
      unk_2021E40[k] = (int)v4;
      MEMORY[0x2021E20] += 32;
      for ( j = (unsigned int)(v4 + 2048); (unsigned int)v4 < j; j = *v5 + 2048 )
      {
        v4[4] = 0;
        *(_DWORD *)v4 = -1;
        v4[5] = 10;
        *((_DWORD *)v4 + 2) = 0;
        v4[36] &= 0x80u;
        v4[37] = 10;
        v4[38] = 10;
        *((_DWORD *)v4 + 14) = 0;
        v4[52] = 0;
        v4 += 64;
      }
      ++k;
    }
    for ( k = 0; k < v2; ++v17 )
    {
      if ( *v17 != (HANDLE)-1 && *v17 != (HANDLE)-2 && (*v3 & 1) != 0 && ((*v3 & 8) != 0 || GetFileType(*v17)) )
      {
        v7 = unk_2021E40[k >> 5] + ((k & 0x1F) << 6);
        *(_DWORD *)v7 = *v17;
        *(_BYTE *)(v7 + 4) = *v3;
        if ( !__crtInitCritSecAndSpinCount((LPCRITICAL_SECTION)(v7 + 12), 0xFA0u) )
          return -1;
        ++*(_DWORD *)(v7 + 8);
      }
      ++k;
      ++v3;
    }
  }
  for ( m = 0; m < 3; ++m )
  {
    v9 = unk_2021E40[0] + (m << 6);
    if ( *(_DWORD *)v9 == -1 || *(_DWORD *)v9 == -2 )
    {
      *(_BYTE *)(v9 + 4) = -127;
      if ( m )
        v10 = -(m != 1) - 11;
      else
        v10 = -10;
      StdHandle = GetStdHandle(v10);
      v12 = StdHandle;
      if ( StdHandle != (HANDLE)-1 && StdHandle && (FileType = GetFileType(StdHandle)) != 0 )
      {
        *(_DWORD *)v9 = v12;
        if ( (unsigned __int8)FileType == 2 )
        {
          *(_BYTE *)(v9 + 4) |= 0x40u;
        }
        else if ( (unsigned __int8)FileType == 3 )
        {
          *(_BYTE *)(v9 + 4) |= 8u;
        }
        if ( !__crtInitCritSecAndSpinCount((LPCRITICAL_SECTION)(v9 + 12), 0xFA0u) )
          return -1;
        ++*(_DWORD *)(v9 + 8);
      }
      else
      {
        *(_BYTE *)(v9 + 4) |= 0x40u;
        *(_DWORD *)v9 = -2;
      }
    }
    else
    {
      *(_BYTE *)(v9 + 4) |= 0x80u;
    }
  }
  SetHandleCount(MEMORY[0x2021E20]);
  return 0;
}

