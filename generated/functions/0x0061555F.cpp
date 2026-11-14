// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061555F __write_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31);
// handle0,flagsBYTE4,lookaheadBYTE5,CSinitDWORD8,CS12,encodingBYTE36,extraLookahead37/38,positionLow/High40/44,conversionDWORD48,pendingConsoleBYTE52/pendingDWORD56. Kind is SIGNED
// low7 encoding bits, normally0 ANSI,1 UTF8-backed UTF16,2 UTF16LE; flags80 controls text separately. Invalid(E) below means errno E plus invalid_parameter(NULL,NULL,NULL,0,0);
// stated return follows only if handler returns. Cdecl(fd,source,unsigned count),noownfd/range/openvalidation orlock. Stackprobe0x1AE4 andsecuritycookie. Count0 ->0
// beforepointer/fd;NULLsource ->dos0/invalid(22)/-1. Kind1/2 requireEVENcount evenwhenTEXT80clear,else sameinvalid22. No INT_MAXlimit. Appendflag20 callsseekENDandIGNORESresult.
// Console-specialgate:isatty(fd)nonzero,text80,GetConsoleMode(handle)TRUE,and(PTDlocinfoLCIDnonzero ORkindnonzero). ConsoleANSI kind0 useslocaleisleadbyte/mbtowc andGetConsoleCP
// (notGetConsoleOutputCP),thenWideCharToMultiByte(CP,0,oneWCHAR,out5). PendingR56 usescachedleadR52+newbyte,clearsR56BEFOREconversion; trailingunpairedlead
// cachesR52/setsR56=1,credits1bytewithoutOSwrite. Consumeone/twosourcebytes,WriteFileconvertedbytes; afterAPItrue creditFULLsourcecharacterbeforecheckingSHORTencodedwrite. InputLF
// iswrittenFIRST,thenextraCR; extraCRcreditedonlyonsuccess. Consolekind1/2 readsUTF16WORDs,putwch_nolock(word) comparedbyAXtooriginalword;
// successcredits2,LFthenputwch(CR),creditsoneextraoutputunit/count. HelperusesGLOBALconsolehandle,notpassedfd; UFFFFinputequalsWEOFfailurevalue underthiscomparison.
// Unsupportednonzerokindotherthan1/2 doesnotadvancesourceinconsoleloop. Fallback: binaryTEXTclear singleWriteFile(source,count),rawactualcredited,noactual<=requestsanitycheck.
// Textkind0 stagesbytesandPREPENDS CRbeforeeachLF; flushstagingwhenoutputcount>=0x13FF. Textkind2 similarlystagesUTF16WORDs,extraCR2bytes,threshold0x13FE. These branchescountALL
// GENERATED extraCRs beforeWriteFile,evenifshortwrite; returnphysicalcredited-extraCRcount canunderflow/underreport,notclampedtoinputboundary. TextANYothernonzerokind
// buildsUTF16withCRbeforeLF up-to0x6A8stagedbytes,WideCharToMultiByte(65001,0,...,outCapacity3413). RetryWriteFileuntilencodedchunkcomplete,BOOLtrue/0byteshasNOprogressguard. Credit
// originalinputbytesONLYafterwholeencodedchunkcompleted; partialcurrentchunkOSwritescanremainuncredited. NoextraCRsubtractioninthisUTF8branch. Native scratcharraysoverlap;
// lifted1704-byteBuffer doesnotboundthe~5120-bytestagingwindow. Commonexit: ifcreditednonzero returncredited-extraCount modulo32 andignorelatersavederror. Zero-credit:
// errorDWORDnonzero5 ->errno9/dos5;othernonzero->dosmaperr;zeroerroranddevice40ANDfirstsourcebyteCtrlZ ->0;elseerrno28/dos0/-1. ErrorDWORDALIASES WideCharStr;
// consolembtowc/WideCharToMultiBytefailurecanreachcommonexit withoutGetLastErrorcaptureorinitializingwholeDWORD,so doNOTnormalizeconsoleconversionfailuretoacleanerror0policy.
// DirectOSfailureusuallycapturesGetLastError. No progressrollback, ownHeapallocation or exception-finallywork; cookiecheckedonallnormalreturns.
int __cdecl _write_nolock(int FileHandle, const void *a2, DWORD nNumberOfBytesToWrite)
{
  int *v4; // esi
  int v5; // edi
  int v6; // eax
  char v7; // bl
  DWORD *v8; // eax
  UINT ConsoleCP; // eax
  const char *v10; // ebx
  CHAR v11; // cl
  int *v12; // esi
  int v13; // eax
  int v14; // eax
  DWORD v15; // eax
  signed int v16; // esi
  int v17; // eax
  int v18; // esi
  int v19; // ecx
  char v20; // dl
  int v21; // eax
  DWORD v22; // ecx
  CHAR *v23; // eax
  CHAR *v24; // edx
  CHAR v25; // dl
  signed int v26; // ebx
  DWORD v27; // ecx
  CHAR *v28; // eax
  WCHAR *v29; // edx
  WCHAR v30; // dx
  signed int v31; // ebx
  DWORD v32; // ecx
  WCHAR *v33; // eax
  WCHAR v34; // dx
  int v35; // esi
  int v36; // ebx
  void *v37; // [esp-10h] [ebp-1AF8h]
  DWORD Mode; // [esp+4h] [ebp-1AE4h] BYREF
  BOOL v39; // [esp+8h] [ebp-1AE0h]
  char v40; // [esp+Fh] [ebp-1AD9h]
  int *v41; // [esp+10h] [ebp-1AD8h]
  DWORD v42; // [esp+14h] [ebp-1AD4h] BYREF
  int v43; // [esp+18h] [ebp-1AD0h]
  LPCVOID lpBuffer; // [esp+1Ch] [ebp-1ACCh]
  DWORD v45; // [esp+20h] [ebp-1AC8h]
  DWORD NumberOfBytesWritten; // [esp+24h] [ebp-1AC4h] BYREF
  WCHAR WideCharStr[2]; // [esp+28h] [ebp-1AC0h] BYREF
  WCHAR *v48; // [esp+2Ch] [ebp-1ABCh]
  CHAR Buffer[1704]; // [esp+30h] [ebp-1AB8h] BYREF
  CHAR v50[3416]; // [esp+6D8h] [ebp-1410h] BYREF
  WCHAR v51[854]; // [esp+1430h] [ebp-6B8h] BYREF
  CHAR MultiByteStr[8]; // [esp+1ADCh] [ebp-Ch] BYREF

  lpBuffer = a2;
  v45 = 0;
  v43 = 0;
  if ( !nNumberOfBytesToWrite )
    return 0;
  if ( !a2 )
  {
    *__doserrno() = 0;
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  v4 = (int *)(4 * (FileHandle >> 5) + 33693248);
  v5 = (FileHandle & 0x1F) << 6;
  v6 = v5 + unk_2021E40[FileHandle >> 5];
  v7 = (char)(2 * *(_BYTE *)(v6 + 36)) >> 1;
  v41 = v4;
  v40 = v7;
  if ( (v7 == 2 || v7 == 1) && (nNumberOfBytesToWrite & 1) != 0 )
  {
    *__doserrno() = 0;
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  if ( (*(_BYTE *)(v6 + 4) & 0x20) != 0 )
    _lseeki64_nolock(FileHandle, 0, 0, 2u);
  if ( _isatty(FileHandle) )
  {
    if ( *(char *)(v5 + unk_2021E40[FileHandle >> 5] + 4) < 0 )
    {
      v8 = _getptd();
      v37 = *(void **)(v5 + unk_2021E40[FileHandle >> 5]);
      v39 = *(_DWORD *)(v8[27] + 20) == 0;
      if ( GetConsoleMode(v37, &Mode) )
      {
        if ( !v39 || v7 )
        {
          ConsoleCP = GetConsoleCP();
          v10 = (const char *)lpBuffer;
          Mode = ConsoleCP;
          NumberOfBytesWritten = 0;
          v48 = nullptr;
          while ( 1 )
          {
            if ( v40 )
            {
              if ( v40 == 1 || v40 == 2 )
              {
                v18 = *(unsigned __int16 *)v10;
                v10 += 2;
                ++v48;
                *(_DWORD *)WideCharStr = v18;
                v39 = (_WORD)v18 == 10;
              }
              if ( v40 == 1 || v40 == 2 )
              {
                if ( _putwch_nolock(WideCharStr[0]) != WideCharStr[0] )
                  goto LABEL_85;
                v45 += 2;
                if ( v39 )
                {
                  wcscpy(WideCharStr, L"\r");
                  if ( _putwch_nolock(0xDu) != WideCharStr[0] )
                    goto LABEL_85;
                  ++v45;
                  ++v43;
                }
              }
              goto LABEL_42;
            }
            v11 = *v10;
            v12 = v41;
            v39 = *v10 == 10;
            v13 = v5 + *v41;
            if ( *(_DWORD *)(v13 + 56) )
            {
              MultiByteStr[0] = *(_BYTE *)(v13 + 52);
              MultiByteStr[1] = v11;
              *(_DWORD *)(v13 + 56) = 0;
              v14 = mbtowc(WideCharStr, MultiByteStr, 2u);
            }
            else
            {
              if ( isleadbyte(v11) )
              {
                if ( nNumberOfBytesToWrite + (_BYTE *)lpBuffer - v10 <= 1 )
                {
                  v19 = *v12;
                  v20 = *v10;
                  ++v45;
                  *(_BYTE *)(v5 + v19 + 52) = v20;
                  *(_DWORD *)(v5 + *v12 + 56) = 1;
                  goto LABEL_86;
                }
                if ( mbtowc(WideCharStr, v10, 2u) == -1 )
                  goto LABEL_86;
                ++v10;
                v48 = (WCHAR *)((char *)v48 + 1);
                goto LABEL_26;
              }
              v14 = mbtowc(WideCharStr, v10, 1u);
            }
            if ( v14 == -1 )
              goto LABEL_86;
LABEL_26:
            ++v10;
            v48 = (WCHAR *)((char *)v48 + 1);
            v15 = WideCharToMultiByte(Mode, 0, WideCharStr, 1, MultiByteStr, 5, nullptr, nullptr);
            v16 = v15;
            if ( !v15 )
              goto LABEL_86;
            if ( !WriteFile(*(HANDLE *)(v5 + *v41), MultiByteStr, v15, &NumberOfBytesWritten, nullptr) )
              goto LABEL_85;
            v45 = (DWORD)v48 + v43;
            if ( (int)NumberOfBytesWritten < v16 )
              goto LABEL_86;
            if ( v39 )
            {
              v17 = *v41;
              MultiByteStr[0] = 13;
              if ( !WriteFile(*(HANDLE *)(v5 + v17), MultiByteStr, 1u, &NumberOfBytesWritten, nullptr) )
                goto LABEL_85;
              if ( (int)NumberOfBytesWritten < 1 )
                goto LABEL_86;
              ++v43;
              ++v45;
            }
LABEL_42:
            if ( (unsigned int)v48 >= nNumberOfBytesToWrite )
              goto LABEL_86;
          }
        }
      }
    }
  }
  v21 = v5 + unk_2021E40[FileHandle >> 5];
  if ( *(char *)(v21 + 4) >= 0 )
  {
    if ( WriteFile(*(HANDLE *)v21, lpBuffer, nNumberOfBytesToWrite, &v42, nullptr) )
    {
      *(_DWORD *)WideCharStr = 0;
      v45 = v42;
      goto LABEL_86;
    }
  }
  else
  {
    *(_DWORD *)WideCharStr = 0;
    if ( v7 )
    {
      v48 = (WCHAR *)lpBuffer;
      if ( v7 == 2 )
      {
        while ( 1 )
        {
          NumberOfBytesWritten = 0;
          v27 = (char *)v48 - (_BYTE *)lpBuffer;
          v28 = Buffer;
          do
          {
            if ( v27 >= nNumberOfBytesToWrite )
              break;
            v29 = v48++;
            v30 = *v29;
            v27 += 2;
            if ( v30 == 10 )
            {
              v43 += 2;
              *(_WORD *)v28 = 13;
              v28 += 2;
              NumberOfBytesWritten += 2;
            }
            NumberOfBytesWritten += 2;
            *(_WORD *)v28 = v30;
            v28 += 2;
          }
          while ( NumberOfBytesWritten < 0x13FE );
          v31 = v28 - Buffer;
          if ( !WriteFile(*(HANDLE *)(v5 + *v4), Buffer, v28 - Buffer, &v42, nullptr) )
            break;
          v45 += v42;
          if ( (int)v42 < v31 || (char *)v48 - (_BYTE *)lpBuffer >= nNumberOfBytesToWrite )
            goto LABEL_86;
          v4 = v41;
        }
      }
      else
      {
        while ( 1 )
        {
          NumberOfBytesWritten = 0;
          v32 = (char *)v48 - (_BYTE *)lpBuffer;
          v33 = v51;
          do
          {
            if ( v32 >= nNumberOfBytesToWrite )
              break;
            v34 = *v48++;
            v32 += 2;
            if ( v34 == 10 )
            {
              *v33++ = 13;
              NumberOfBytesWritten += 2;
            }
            NumberOfBytesWritten += 2;
            *v33++ = v34;
          }
          while ( NumberOfBytesWritten < 0x6A8 );
          v35 = 0;
          v36 = WideCharToMultiByte(0xFDE9u, 0, v51, v33 - v51, v50, 3413, nullptr, nullptr);
          if ( !v36 )
            break;
          while ( WriteFile(*(HANDLE *)(v5 + *v41), &v50[v35], v36 - v35, &v42, nullptr) )
          {
            v35 += v42;
            if ( v36 <= v35 )
              goto LABEL_80;
          }
          *(_DWORD *)WideCharStr = GetLastError();
LABEL_80:
          if ( v36 <= v35 )
          {
            v45 = (char *)v48 - (_BYTE *)lpBuffer;
            if ( (char *)v48 - (_BYTE *)lpBuffer < nNumberOfBytesToWrite )
              continue;
          }
          goto LABEL_86;
        }
      }
    }
    else
    {
      NumberOfBytesWritten = (DWORD)lpBuffer;
      while ( 1 )
      {
        v48 = nullptr;
        v22 = NumberOfBytesWritten - (_DWORD)lpBuffer;
        v23 = Buffer;
        do
        {
          if ( v22 >= nNumberOfBytesToWrite )
            break;
          v24 = (CHAR *)NumberOfBytesWritten++;
          v25 = *v24;
          ++v22;
          if ( v25 == 10 )
          {
            ++v43;
            *v23++ = 13;
            v48 = (WCHAR *)((char *)v48 + 1);
          }
          *v23++ = v25;
          v48 = (WCHAR *)((char *)v48 + 1);
        }
        while ( (unsigned int)v48 < 0x13FF );
        v26 = v23 - Buffer;
        if ( !WriteFile(*(HANDLE *)(v5 + *v4), Buffer, v23 - Buffer, &v42, nullptr) )
          break;
        v45 += v42;
        if ( (int)v42 < v26 || NumberOfBytesWritten - (unsigned int)lpBuffer >= nNumberOfBytesToWrite )
          goto LABEL_86;
        v4 = v41;
      }
    }
  }
LABEL_85:
  *(_DWORD *)WideCharStr = GetLastError();
LABEL_86:
  if ( !v45 )
  {
    if ( *(_DWORD *)WideCharStr )
    {
      if ( *(_DWORD *)WideCharStr == 5 )
      {
        *_errno() = 9;
        *__doserrno() = 5;
      }
      else
      {
        _dosmaperr(*(unsigned int *)WideCharStr);
      }
    }
    else
    {
      if ( (*(_BYTE *)(v5 + *v41 + 4) & 0x40) != 0 && *(_BYTE *)lpBuffer == 26 )
        return 0;
      *_errno() = 28;
      *__doserrno() = 0;
    }
    return -1;
  }
  return v45 - v43;
}

