// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061E560 __tsopen_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31);
// handle0,flagsBYTE4,lookaheadBYTE5,CSinitDWORD8,CS12,encodingBYTE36,extraLookahead37/38,positionLow/High40/44,conversionDWORD48,pendingConsoleBYTE52/pendingDWORD56. Kind is SIGNED
// low7 encoding bits, normally0 ANSI,1 UTF8-backed UTF16,2 UTF16LE; flags80 controls text separately. Invalid(E) below means errno E plus invalid_parameter(NULL,NULL,NULL,0,0);
// stated return follows only if handler returns. InternalmixedABI: EAXint*outfd;FIVEstackslots(acquiredFlagPointer,filename,oflag,share,pmode),callerreclaims20.
// Returnerrno-style0orcurrenterrno. NoownNULLvalidationofoutfd/acquiredflag/name. SECURITY_ATTRIBUTES len12,descriptorNULL,inherit=(oflag80clear);descriptorflag10setfornoinherit.
// Getdefaultmode2021E18throughcheckedhelper,nonzero invokesWatson(5zeros). TEXTflag80unlessoflag8000 OR(no74000bitsANDdefaultmode8000). Accesslow2:0->80000000,1->40000000
// exceptappend8+any70000Unicodebits upgradesC0000000;2->C0000000;3->dos0,*outfd-1,invalid22/return22.
// Share16/32/48/64->0/1/2/3;128->1ONLYifinitialaccessreadonly80000000,else0;otherinvalidsame22. Creation(oflag&700) mapping0/400->3,100->4,200/600->5,300->2,500/700->1.
// Attributes80default;create100 AND(pmode &~umask2021350 &0x80)==0 ->attribute1. oflag40 addsattribute04000000,access00010000,share4;oflag1000
// addsattribute100;20adds08000000,else10adds10000000. alloc_osfhnd returnsRESERVEDLOCKEDfd; failuredos0,*fd-1,errno24/currenterrno. Success*acquiredFlag=1 BEFORECreateFileA.
// CreatefailurecanretryONLYwhenaccessmaskC0000000 andoflagbit1,removingREADbit80000000,sameotherargs.
// Finalcreatefailureclearrecordopen1,dosmaperr(GetLastError),returncurrenterrno,keepfd/lockforcallerfinally. GetFileType0
// clearsopen,mapsLastError,CloseHandle;LastError0forceserrno13;typeEXACT2addsdevice40,EXACT3pipe8 (notlowbytecomparehere).
// set_osfhnd(fd,H)statusIGNORED;writeflags=open1|text/noinherit/type;clearencodinglow7,preservehighbit. Forregular!(flags48),TEXT,andoflag2(readwrite):seek-1END; exact-1
// toleratedONLYdoserrno131;elseclose/returnerrno. Atlastbytecallread_nolock(...,1) withBuffer0; ONLYret0 ANDBufferCtrlZ invokeschsize_nolock(fd,lastoffset),comparesONLYresult==-1
// despitehelperreturningerrnoVALUE. Thenalwaysseek0SET; failureclose/returncurrenterrno. UnicodeconfigurationonlywhenTEXT: ifno74000explicitbits use(default&74000) or4000.
// Recognizedkind:4000->0;20000/24000->2;40000/44000->1;10000/14000->2 ONLYif(oflag&301)==301,elseinitial0. Unsupportedcombinationsnotexplicitlyrejected. IfUnicode70000bits
// andnotdevice40, BOMwork: readonlyalwaysreadBOM;RWcreation1/2/5writeBOM,3/4seekEND,zero->write,nonzero(including-1)->seek0SET/checkthenread.
// Writeonlysamecreationrulesbutnonempty3/4onlyrewinds/checks,doesNOTreadBOM. WriteBOMkind1=IMMEDIATE00BFBBEF bytesEFBBBF,length3;kind2=0000FEFF
// bytesFFFE,length2;usePUBLIC_writewhiledone<length,only-1checked,noexplicitzero-progressguard. Detectionread_nolock3 whileencodingstill0;ret-1close/error;ret3+DWORD00BFBBEF
// ->kind1/leavepositionafter3;ret2/3 lowWORDFFFE ->close,errno22/return22 NOinvalidhandler;lowWORDFEFF ->seek2SET,kind2;else seek0SET. Finalencodinglow7=kind,highbitCOPYoflagbit16
// (WTEXT10000),notANYUnicodebit. Regularnondevice/nonpipe plusappend8 setsdescriptor20. IfinitialdesiredaccessstillRWandoflagbit1,CloseHandleold (BOOLignored)
// thenCreateFileA(writeonly,OPEN_EXISTING3,...). SuccessDIRECTLYreplacerecordhandle,noSetStdHandle refresh. Failuredosmaperr,clearopen1,THENfree_osfhnd:
// stableclosedCRTrecordforceshelpererrno9/dos0 andretainsoldhandlevalue (OSCloseHandle successwasnotchecked),overwritingoriginalreopenerror.
// Noownunlock/SEH;calleracquiredflaggovernsrelease. Errorclose/partialtruncation/BOMwritesnotrolledback.
int __usercall _tsopen_nolock@<eax>(int *a1@<eax>, _DWORD *a2, LPCSTR lpFileName, int a4, int a5, char a6)
{
  unsigned int v7; // eax
  int v8; // eax
  _BYTE *v9; // eax
  DWORD LastError; // eax
  DWORD FileType; // eax
  _BYTE *v13; // eax
  DWORD v14; // esi
  char v15; // cl
  _BYTE *v16; // eax
  int v17; // eax
  DWORD v18; // eax
  DWORD v19; // eax
  signed int v20; // edi
  __int64 v21; // rax
  unsigned int nolock; // eax
  __int64 v23; // rax
  DWORD v24; // eax
  int v25; // eax
  _BYTE *v26; // eax
  _BYTE *v27; // eax
  _BYTE *v28; // eax
  DWORD v29; // edi
  HANDLE v30; // eax
  DWORD v31; // eax
  _BYTE *v32; // eax
  int v33; // [esp-Ch] [ebp-48h]
  DWORD v34; // [esp-8h] [ebp-44h]
  struct _SECURITY_ATTRIBUTES SecurityAttributes; // [esp+Ch] [ebp-30h] BYREF
  int v36; // [esp+1Ch] [ebp-20h] BYREF
  HANDLE hFile; // [esp+20h] [ebp-1Ch]
  signed int Buf; // [esp+24h] [ebp-18h] BYREF
  DWORD dwCreationDisposition; // [esp+28h] [ebp-14h]
  DWORD dwShareMode; // [esp+2Ch] [ebp-10h]
  DWORD dwFlagsAndAttributes; // [esp+30h] [ebp-Ch]
  DWORD dwDesiredAccess; // [esp+34h] [ebp-8h]
  CHAR Buffer; // [esp+38h] [ebp-4h] BYREF
  char v44; // [esp+39h] [ebp-3h]
  char v45; // [esp+3Ah] [ebp-2h]
  char v46; // [esp+3Bh] [ebp-1h]

  v36 = 0;
  v45 = 0;
  SecurityAttributes.nLength = 12;
  SecurityAttributes.lpSecurityDescriptor = nullptr;
  if ( (a4 & 0x80u) == 0 )
  {
    SecurityAttributes.bInheritHandle = 1;
    v46 = 0;
  }
  else
  {
    SecurityAttributes.bInheritHandle = 0;
    v46 = 16;
  }
  if ( crt_get_dword_02021e18_checked(&v36) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  if ( (a4 & 0x8000) == 0 && ((a4 & 0x74000) != 0 || v36 != 0x8000) )
    v46 |= 0x80u;
  if ( (a4 & 3) != 0 )
  {
    if ( (a4 & 3) != 1 )
    {
      if ( (a4 & 3) != 2 )
      {
LABEL_13:
        *__doserrno() = 0;
        *a1 = -1;
        *_errno() = 22;
        _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
        return 22;
      }
      goto LABEL_14;
    }
    if ( (a4 & 8) != 0 && (a4 & 0x70000) != 0 )
    {
LABEL_14:
      dwDesiredAccess = -1073741824;
      goto LABEL_19;
    }
    dwDesiredAccess = 0x40000000;
  }
  else
  {
    dwDesiredAccess = 0x80000000;
  }
LABEL_19:
  switch ( a5 )
  {
    case 16:
      dwShareMode = 0;
      break;
    case 32:
      dwShareMode = 1;
      break;
    case 48:
      dwShareMode = 2;
      break;
    case 64:
      dwShareMode = 3;
      break;
    case 128:
      dwShareMode = dwDesiredAccess == 0x80000000;
      break;
    default:
      goto LABEL_13;
  }
  v7 = a4 & 0x700;
  if ( v7 > 0x400 )
  {
    if ( v7 != 1280 )
    {
      if ( v7 == 1536 )
        goto LABEL_51;
      if ( v7 != 1792 )
        goto LABEL_13;
    }
    dwCreationDisposition = 1;
    goto LABEL_42;
  }
  if ( (a4 & 0x700) == 0x400 || (a4 & 0x700) == 0 )
  {
    dwCreationDisposition = 3;
    goto LABEL_42;
  }
  if ( v7 == 256 )
  {
    dwCreationDisposition = 4;
    goto LABEL_42;
  }
  if ( v7 == 512 )
  {
LABEL_51:
    dwCreationDisposition = 5;
    goto LABEL_42;
  }
  if ( v7 != 768 )
    goto LABEL_13;
  dwCreationDisposition = 2;
LABEL_42:
  dwFlagsAndAttributes = 128;
  if ( (a4 & 0x100) != 0 && (a6 & ~unk_2021350 & 0x80u) == 0 )
    dwFlagsAndAttributes = 1;
  if ( (a4 & 0x40) != 0 )
  {
    dwFlagsAndAttributes |= 0x4000000u;
    dwDesiredAccess |= 0x10000u;
    dwShareMode |= 4u;
  }
  if ( (a4 & 0x1000) != 0 )
    dwFlagsAndAttributes |= 0x100u;
  if ( (a4 & 0x20) != 0 )
  {
    dwFlagsAndAttributes |= 0x8000000u;
  }
  else if ( (a4 & 0x10) != 0 )
  {
    dwFlagsAndAttributes |= 0x10000000u;
  }
  v8 = _alloc_osfhnd();
  *a1 = v8;
  if ( v8 == -1 )
  {
    *__doserrno() = 0;
    *a1 = -1;
    *_errno() = 24;
    return *_errno();
  }
  v34 = dwFlagsAndAttributes;
  *a2 = 1;
  hFile = CreateFileA(
            lpFileName,
            dwDesiredAccess,
            dwShareMode,
            &SecurityAttributes,
            dwCreationDisposition,
            v34,
            nullptr);
  if ( hFile == (HANDLE)-1 )
  {
    if ( (dwDesiredAccess & 0xC0000000) != 0xC0000000
      || (a4 & 1) == 0
      || (dwDesiredAccess &= ~0x80000000,
          hFile = CreateFileA(
                    lpFileName,
                    dwDesiredAccess,
                    dwShareMode,
                    &SecurityAttributes,
                    dwCreationDisposition,
                    dwFlagsAndAttributes,
                    nullptr),
          hFile == (HANDLE)-1) )
    {
      v9 = (_BYTE *)(unk_2021E40[*a1 >> 5] + ((*a1 & 0x1F) << 6) + 4);
      *v9 &= ~1u;
      LastError = GetLastError();
      _dosmaperr(LastError);
      return *_errno();
    }
  }
  FileType = GetFileType(hFile);
  switch ( FileType )
  {
    case 0u:
      v13 = (_BYTE *)(unk_2021E40[*a1 >> 5] + ((*a1 & 0x1F) << 6) + 4);
      *v13 &= ~1u;
      v14 = GetLastError();
      _dosmaperr(v14);
      CloseHandle(hFile);
      if ( !v14 )
        *_errno() = 13;
      return *_errno();
    case 2u:
      v46 |= 0x40u;
      break;
    case 3u:
      v46 |= 8u;
      break;
  }
  _set_osfhnd(*a1, hFile);
  v15 = v46 | 1;
  *(_BYTE *)(unk_2021E40[*a1 >> 5] + ((*a1 & 0x1F) << 6) + 4) = v46 | 1;
  v16 = (_BYTE *)(unk_2021E40[*a1 >> 5] + ((*a1 & 0x1F) << 6) + 36);
  *v16 &= 0x80u;
  v44 = v15 & 0x48;
  v46 = v15;
  if ( (v15 & 0x48) == 0 )
  {
    if ( v15 >= 0 )
      goto LABEL_131;
    if ( (a4 & 2) != 0 )
    {
      Buf = _lseek_nolock(*a1, -1, 2u);
      if ( Buf == -1 )
      {
        if ( *__doserrno() != 131 )
        {
LABEL_74:
          _close_nolock(*a1);
          return *_errno();
        }
      }
      else
      {
        v33 = *a1;
        Buffer = 0;
        if ( !_read_nolock(v33, &Buffer, 1u) && Buffer == 26 && _chsize_nolock(*a1, Buf) == -1
          || _lseek_nolock(*a1, 0, 0) == -1 )
        {
          goto LABEL_74;
        }
      }
    }
  }
  if ( v46 >= 0 )
    goto LABEL_131;
  if ( (a4 & 0x74000) == 0 )
  {
    if ( (v36 & 0x74000) != 0 )
      a4 |= v36 & 0x74000;
    else
      a4 |= 0x4000u;
  }
  v17 = a4 & 0x74000;
  if ( (a4 & 0x74000) == 0x4000 )
  {
    v45 = 0;
    goto LABEL_95;
  }
  switch ( v17 )
  {
    case 65536:
    case 81920:
      if ( (a4 & 0x301) != 0x301 )
        break;
LABEL_93:
      v45 = 2;
      break;
    case 131072:
    case 147456:
      goto LABEL_93;
    case 262144:
    case 278528:
      v45 = 1;
      break;
  }
LABEL_95:
  if ( (a4 & 0x70000) == 0 )
    goto LABEL_131;
  Buf = 0;
  if ( (v46 & 0x40) != 0 )
    goto LABEL_131;
  v18 = dwDesiredAccess & 0xC0000000;
  if ( (dwDesiredAccess & 0xC0000000) == 0x40000000 )
  {
    v19 = dwCreationDisposition;
    if ( !dwCreationDisposition )
      goto LABEL_131;
    if ( dwCreationDisposition > 2 )
    {
      if ( dwCreationDisposition > 4 )
      {
LABEL_103:
        if ( v19 != 5 )
          goto LABEL_131;
        goto LABEL_104;
      }
      if ( _lseeki64_nolock(*a1, 0, 0, 2u) )
      {
        v23 = _lseeki64_nolock(*a1, 0, 0, 0);
        v24 = HIDWORD(v23) & v23;
        goto LABEL_119;
      }
    }
    goto LABEL_104;
  }
  if ( v18 == 0x80000000 )
    goto LABEL_109;
  if ( v18 != -1073741824 )
    goto LABEL_131;
  v19 = dwCreationDisposition;
  if ( !dwCreationDisposition )
    goto LABEL_131;
  if ( dwCreationDisposition <= 2 )
    goto LABEL_104;
  if ( dwCreationDisposition > 4 )
    goto LABEL_103;
  if ( !_lseeki64_nolock(*a1, 0, 0, 2u) )
  {
LABEL_104:
    v20 = 0;
    if ( v45 == 1 )
    {
      Buf = (signed int)&unk_BFBBEF;
      dwCreationDisposition = 3;
LABEL_129:
      while ( 1 )
      {
        v25 = _write(*a1, (char *)&Buf + v20, dwCreationDisposition - v20);
        if ( v25 == -1 )
          goto LABEL_74;
        v20 += v25;
        if ( (int)dwCreationDisposition <= v20 )
          goto LABEL_131;
      }
    }
    if ( v45 == 2 )
    {
      Buf = 65279;
      dwCreationDisposition = 2;
      goto LABEL_129;
    }
    goto LABEL_131;
  }
  v21 = _lseeki64_nolock(*a1, 0, 0, 0);
  if ( (HIDWORD(v21) & (unsigned int)v21) == 0xFFFFFFFF )
    goto LABEL_74;
LABEL_109:
  nolock = _read_nolock(*a1, (CHAR *)&Buf, 3u);
  if ( nolock == -1 )
    goto LABEL_74;
  if ( nolock != 2 )
  {
    if ( nolock != 3 )
    {
LABEL_127:
      v24 = _lseek_nolock(*a1, 0, 0);
LABEL_119:
      if ( v24 == -1 )
        goto LABEL_74;
      goto LABEL_131;
    }
    if ( (_UNKNOWN *)Buf == &unk_BFBBEF )
    {
      v45 = 1;
      goto LABEL_131;
    }
  }
  if ( (unsigned __int16)Buf == 65534 )
  {
    _close_nolock(*a1);
    *_errno() = 22;
    return 22;
  }
  if ( (unsigned __int16)Buf != 65279 )
    goto LABEL_127;
  if ( _lseek_nolock(*a1, 2, 0) == -1 )
    goto LABEL_74;
  v45 = 2;
LABEL_131:
  v26 = (_BYTE *)(unk_2021E40[*a1 >> 5] + ((*a1 & 0x1F) << 6) + 36);
  *v26 ^= (v45 ^ *v26) & 0x7F;
  v27 = (_BYTE *)(unk_2021E40[*a1 >> 5] + ((*a1 & 0x1F) << 6) + 36);
  *v27 = *v27 & 0x7F | (BYTE2(a4) << 7);
  if ( !v44 && (a4 & 8) != 0 )
  {
    v28 = (_BYTE *)(unk_2021E40[*a1 >> 5] + ((*a1 & 0x1F) << 6) + 4);
    *v28 |= 0x20u;
  }
  v29 = dwDesiredAccess;
  if ( (dwDesiredAccess & 0xC0000000) == 0xC0000000 && (a4 & 1) != 0 )
  {
    CloseHandle(hFile);
    v30 = CreateFileA(lpFileName, v29 & 0x7FFFFFFF, dwShareMode, &SecurityAttributes, 3u, dwFlagsAndAttributes, nullptr);
    if ( v30 == (HANDLE)-1 )
    {
      v31 = GetLastError();
      _dosmaperr(v31);
      v32 = (_BYTE *)(unk_2021E40[*a1 >> 5] + ((*a1 & 0x1F) << 6) + 4);
      *v32 &= ~1u;
      _free_osfhnd(*a1);
      return *_errno();
    }
    *(_DWORD *)(((*a1 & 0x1F) << 6) + unk_2021E40[*a1 >> 5]) = v30;
  }
  return 0;
}

