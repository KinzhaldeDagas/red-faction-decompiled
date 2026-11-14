// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614528 __read_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31);
// handle0,flagsBYTE4,lookaheadBYTE5,CSinitDWORD8,CS12,encodingBYTE36,extraLookahead37/38,positionLow/High40/44,conversionDWORD48,pendingConsoleBYTE52/pendingDWORD56. Kind is SIGNED
// low7 encoding bits, normally0 ANSI,1 UTF8-backed UTF16,2 UTF16LE; flags80 controls text separately. Invalid(E) below means errno E plus invalid_parameter(NULL,NULL,NULL,0,0);
// stated return follows only if handler returns. Cdecl(fd,buffer,unsigned count),raw count/0/-1 inEAX,noownlock. Fd-2 clearsdoserrno,errno9/-1 withoutinvalidhandler.
// Othernegative/outofrange/notopen clearsdoserrno,invalid(9)/-1. Count>INT_MAX clearsdoserrno,invalid(22)/-1 BEFORE zero/EOF shortcuts. Count0 ORdescriptorEOFflag2 ->0
// beforebuffer/kind checks. OtherNULLbuffer oroddcount withkind1/2 ->doserrno0,invalid(22)/-1. Kind2 uses callerbuffer/even count; othernon1 kinds use callerbuffer directly. Kind1
// allocates max(4,count/2),failureerrno12/doserrno8/-1; saves lseeki64_nolock(fd,0,CUR) rawresult toR40/44 even-1. For flags48, consume cachedR5 unlessLFsentinel10; nonzero kind
// maythenconsumeR37,kind1 alsoR38, respecting remainingrawrequest andresettingeachconsumedslotto10. AlwaysReadFile(remainingrawrequest),even0. FALSE,negative actualcount
// oractual>request ->GetLastError:5 errno9/dos5/-1;109 return0 evenifcacheprefixalreadyconsumed;othersdosmaperr/-1. No cache/progress rollback onOSfailure. Successaddsactualcount;
// iftext80clear,returnraw workingcount. Consequently kind1 withtext80clear reads intoTEMPthenfrees it without copyingtocallerbuffer; kind admission/allocation is not gated
// bytextflag. Textbyte path(kind!=2): setflag4 iff OSactualnonzero ANDFIRSTworkingbyteLF,elseclear; scaninplace,CRLF->LF,ordinaryNULretained. CtrlZ: device40 copiesoneCtrlZthenSTOP;
// otherrecords setEOF2 andSTOP/discardremainingrawbuffer. TrailingCR peeks1byte: failedpeekwithnonzeroLastError OR0bytes keepsCR,noerrmapping. Pipe/device48 pluspeekLF emitsLF; nonLF
// emitsCR,cachesbyteR5. Seekable: ifnooutputyet ANDpeekLF emitLF; otherwiseseek-1CUR IGNOREresult; peeknonLF emitsCR,peekLF omitsCR/outputthisiteration andleavesLFforthenextread.
// UTF16kind2 performs analogousWORDCR/LF/CtrlZ handling,peek2/cacheR5/R37 withR38=10,seek-2CUR. Onlyrequestedcountparitychecked: oddACTUALread or1-bytepeekcanstillbeusedasWORD. Kind1
// text withnonemptytranslatedbytes: inspectlastbyte; ASCIIcomplete,elsewalkbackthroughzero665B30 entries,up-to4 counter tests. Nativechecks pointer>=base BEFOREdecrement,so
// malformedall-continuation inputcanreadbase-1. TableC0..DF=1,E0..EF=2,F0..F7=3,others0; nolead ->errno42/-1. Complete iff table[lead]+1==scannedcount;
// otherwisepushincompletetailbackwithignoredseek(-count,CUR),orcacheleadandup-to2bytesforflags48; excludeitfromconversion.
// MultiByteToWideChar(65001,0,working,completeBytes,caller,count/2),noNULappend;0 ->dosmaperr(GetLastError)/-1;nonzero return2*UTF16units,setR48=(units!=completeBytes). Zero
// translatedbytes bypassconversion/retainR48. Cleanup freesworkingpointer ONLYif !=callerbuffer; all errors/shortresults preserveearlierIO/headerprogress. No
// exception-finallyallocationcleanup or fullUTF8scalar validation.
unsigned int __cdecl _read_nolock(int FileHandle, CHAR *lpBuffer, DWORD nNumberOfBytesToRead)
{
  DWORD v3; // edx
  unsigned int result; // eax
  int v5; // esi
  int v6; // eax
  char v7; // cl
  CHAR *v8; // eax
  __int64 v9; // rax
  int v10; // ecx
  int v11; // ecx
  CHAR v12; // cl
  int v13; // ecx
  CHAR v14; // cl
  int v15; // ecx
  bool v16; // zf
  CHAR v17; // cl
  int v18; // ecx
  int v19; // eax
  char *v20; // eax
  CHAR *v21; // ebx
  CHAR v22; // al
  _BYTE *v23; // eax
  _BYTE *v24; // ebx
  int v25; // ecx
  int v26; // eax
  char v27; // dl
  int v28; // ecx
  _BYTE *v29; // ebx
  int v30; // ebx
  DWORD LastError; // eax
  int v32; // edx
  BOOL v33; // ecx
  CHAR *v34; // ebx
  __int16 v35; // cx
  _BYTE *v36; // esi
  __int16 v37; // [esp-Ch] [ebp-2Ch]
  DWORD v38; // [esp+4h] [ebp-1Ch]
  DWORD NumberOfBytesRead; // [esp+8h] [ebp-18h] BYREF
  unsigned int v40; // [esp+Ch] [ebp-14h]
  unsigned int v41; // [esp+10h] [ebp-10h]
  LPCCH lpMultiByteStr; // [esp+14h] [ebp-Ch]
  __int16 v43; // [esp+18h] [ebp-8h] BYREF
  char v44; // [esp+1Eh] [ebp-2h]
  char Buffer; // [esp+1Fh] [ebp-1h] BYREF
  LPCCH nNumberOfBytesToReada; // [esp+30h] [ebp+10h]
  LPCCH nNumberOfBytesToReadb; // [esp+30h] [ebp+10h]

  v3 = nNumberOfBytesToRead;
  v40 = -2;
  v38 = nNumberOfBytesToRead;
  if ( FileHandle == -2 )
  {
    *__doserrno() = 0;
    *_errno() = 9;
    return -1;
  }
  if ( FileHandle < 0 || FileHandle >= MEMORY[0x2021E20] )
  {
    *__doserrno() = 0;
    *_errno() = 9;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  v5 = (FileHandle & 0x1F) << 6;
  v6 = v5 + unk_2021E40[FileHandle >> 5];
  v7 = *(_BYTE *)(v6 + 4);
  if ( (v7 & 1) == 0 )
  {
    *__doserrno() = 0;
    *_errno() = 9;
LABEL_19:
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  if ( nNumberOfBytesToRead > 0x7FFFFFFF )
    goto LABEL_18;
  v41 = 0;
  if ( !nNumberOfBytesToRead || (v7 & 2) != 0 )
    return 0;
  if ( !lpBuffer )
    goto LABEL_18;
  v44 = (char)(2 * *(_BYTE *)(v6 + 36)) >> 1;
  if ( v44 != 1 )
  {
    if ( v44 != 2 )
    {
LABEL_16:
      v8 = lpBuffer;
      lpMultiByteStr = lpBuffer;
      goto LABEL_26;
    }
    if ( (nNumberOfBytesToRead & 1) == 0 )
    {
      nNumberOfBytesToRead &= ~1u;
      goto LABEL_16;
    }
LABEL_18:
    *__doserrno() = 0;
    *_errno() = 22;
    goto LABEL_19;
  }
  if ( (nNumberOfBytesToRead & 1) != 0 )
    goto LABEL_18;
  nNumberOfBytesToRead = 4;
  if ( v3 >> 1 >= 4 )
    nNumberOfBytesToRead = v3 >> 1;
  lpMultiByteStr = (LPCCH)_malloc_crt(nNumberOfBytesToRead);
  if ( !lpMultiByteStr )
  {
    *_errno() = 12;
    *__doserrno() = 8;
    return -1;
  }
  v9 = _lseeki64_nolock(FileHandle, 0, 0, 1u);
  v10 = unk_2021E40[FileHandle >> 5];
  *(_DWORD *)(v5 + v10 + 40) = v9;
  v8 = (CHAR *)lpMultiByteStr;
  *(_DWORD *)(v5 + v10 + 44) = HIDWORD(v9);
LABEL_26:
  v11 = v5 + unk_2021E40[FileHandle >> 5];
  if ( (*(_BYTE *)(v11 + 4) & 0x48) != 0 )
  {
    v12 = *(_BYTE *)(v11 + 5);
    if ( v12 != 10 )
    {
      if ( nNumberOfBytesToRead )
      {
        *v8 = v12;
        v13 = unk_2021E40[FileHandle >> 5];
        ++v8;
        --nNumberOfBytesToRead;
        v41 = 1;
        *(_BYTE *)(v5 + v13 + 5) = 10;
        if ( v44 )
        {
          v14 = *(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 37);
          if ( v14 != 10 )
          {
            if ( nNumberOfBytesToRead )
            {
              *v8 = v14;
              v15 = unk_2021E40[FileHandle >> 5];
              ++v8;
              --nNumberOfBytesToRead;
              v16 = v44 == 1;
              v41 = 2;
              *(_BYTE *)(v5 + v15 + 37) = 10;
              if ( v16 )
              {
                v17 = *(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 38);
                if ( v17 != 10 )
                {
                  if ( nNumberOfBytesToRead )
                  {
                    *v8 = v17;
                    v18 = unk_2021E40[FileHandle >> 5];
                    ++v8;
                    --nNumberOfBytesToRead;
                    v41 = 3;
                    *(_BYTE *)(v5 + v18 + 38) = 10;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if ( !ReadFile(*(HANDLE *)(v5 + unk_2021E40[FileHandle >> 5]), v8, nNumberOfBytesToRead, &NumberOfBytesRead, nullptr)
    || (NumberOfBytesRead & 0x80000000) != 0
    || NumberOfBytesRead > nNumberOfBytesToRead )
  {
    LastError = GetLastError();
    if ( LastError == 5 )
    {
      *_errno() = 9;
      *__doserrno() = 5;
      goto LABEL_93;
    }
    if ( LastError == 109 )
    {
      v40 = 0;
      goto $error_return$28993;
    }
    goto LABEL_92;
  }
  v19 = unk_2021E40[FileHandle >> 5];
  v41 += NumberOfBytesRead;
  v20 = (char *)(v5 + v19 + 4);
  if ( *v20 < 0 )
  {
    if ( v44 != 2 )
    {
      if ( NumberOfBytesRead && *lpMultiByteStr == 10 )
        *v20 |= 4u;
      else
        *v20 &= ~4u;
      v21 = (CHAR *)lpMultiByteStr;
      nNumberOfBytesToReada = lpMultiByteStr;
      v41 += (unsigned int)lpMultiByteStr;
      if ( (unsigned int)lpMultiByteStr < v41 )
      {
        do
        {
          v22 = *nNumberOfBytesToReada;
          if ( *nNumberOfBytesToReada == 26 )
          {
            v23 = (_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 4);
            if ( (*v23 & 0x40) != 0 )
              *v21++ = *nNumberOfBytesToReada;
            else
              *v23 |= 2u;
            break;
          }
          if ( v22 == 13 )
          {
            if ( (unsigned int)nNumberOfBytesToReada < v41 - 1 )
            {
              if ( nNumberOfBytesToReada[1] == 10 )
              {
                nNumberOfBytesToReada += 2;
                goto LABEL_52;
              }
              ++nNumberOfBytesToReada;
LABEL_63:
              *v21 = 13;
LABEL_64:
              ++v21;
              continue;
            }
            ++nNumberOfBytesToReada;
            if ( !ReadFile(*(HANDLE *)(v5 + unk_2021E40[FileHandle >> 5]), &Buffer, 1u, &NumberOfBytesRead, nullptr)
              && GetLastError()
              || !NumberOfBytesRead )
            {
              goto LABEL_63;
            }
            if ( (*(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 4) & 0x48) != 0 )
            {
              if ( Buffer != 10 )
              {
                *v21 = 13;
                *(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 5) = Buffer;
                goto LABEL_64;
              }
LABEL_52:
              *v21 = 10;
              goto LABEL_64;
            }
            if ( v21 == lpMultiByteStr && Buffer == 10 )
              goto LABEL_52;
            _lseeki64_nolock(FileHandle, -1, -1, 1u);
            if ( Buffer != 10 )
              goto LABEL_63;
          }
          else
          {
            *v21++ = v22;
            ++nNumberOfBytesToReada;
          }
        }
        while ( (unsigned int)nNumberOfBytesToReada < v41 );
      }
      v41 = v21 - lpMultiByteStr;
      if ( v44 != 1 || v21 == lpMultiByteStr )
        goto $error_return$28993;
      v24 = v21 - 1;
      LOBYTE(v25) = *v24;
      if ( (char)*v24 < 0 )
      {
        v26 = 1;
        v25 = (unsigned __int8)v25;
        while ( !byte_665B30[v25] && v26 <= 4 && v24 >= lpMultiByteStr )
        {
          v25 = (unsigned __int8)*--v24;
          ++v26;
        }
        v27 = *v24;
        if ( !byte_665B30[(unsigned __int8)*v24] )
        {
          *_errno() = 42;
LABEL_93:
          v40 = -1;
          goto $error_return$28993;
        }
        if ( byte_665B30[(unsigned __int8)*v24] + 1 == v26 )
        {
          v24 += v26;
        }
        else
        {
          v28 = v5 + unk_2021E40[FileHandle >> 5];
          if ( (*(_BYTE *)(v28 + 4) & 0x48) != 0 )
          {
            v29 = v24 + 1;
            *(_BYTE *)(v28 + 5) = v27;
            if ( v26 >= 2 )
              *(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 37) = *v29++;
            if ( v26 == 3 )
              *(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 38) = *v29++;
            v24 = &v29[-v26];
          }
          else
          {
            _lseeki64_nolock(FileHandle, -v26, -v26 >> 31, 1u);
          }
        }
      }
      else
      {
        ++v24;
      }
      v30 = v24 - lpMultiByteStr;
      v41 = MultiByteToWideChar(0xFDE9u, 0, lpMultiByteStr, v30, (LPWSTR)lpBuffer, v38 >> 1);
      if ( v41 )
      {
        v32 = unk_2021E40[FileHandle >> 5];
        v33 = v41 != v30;
        v41 *= 2;
        *(_DWORD *)(v5 + v32 + 48) = v33;
        goto $error_return$28993;
      }
      LastError = GetLastError();
LABEL_92:
      _dosmaperr(LastError);
      goto LABEL_93;
    }
    if ( NumberOfBytesRead && *(_WORD *)lpMultiByteStr == 10 )
      *v20 |= 4u;
    else
      *v20 &= ~4u;
    v34 = (CHAR *)lpMultiByteStr;
    nNumberOfBytesToReadb = lpMultiByteStr;
    v41 += (unsigned int)lpMultiByteStr;
    if ( (unsigned int)lpMultiByteStr >= v41 )
    {
LABEL_129:
      v41 = v34 - lpMultiByteStr;
      goto $error_return$28993;
    }
    while ( 1 )
    {
      v35 = *(_WORD *)nNumberOfBytesToReadb;
      if ( *(_WORD *)nNumberOfBytesToReadb == 26 )
      {
        v36 = (_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 4);
        if ( (*v36 & 0x40) != 0 )
        {
          *(_WORD *)v34 = *(_WORD *)nNumberOfBytesToReadb;
          v34 += 2;
        }
        else
        {
          *v36 |= 2u;
        }
        goto LABEL_129;
      }
      if ( v35 == 13 )
      {
        if ( (unsigned int)nNumberOfBytesToReadb < v41 - 2 )
        {
          if ( *((_WORD *)nNumberOfBytesToReadb + 1) == 10 )
          {
            nNumberOfBytesToReadb += 4;
            goto LABEL_110;
          }
          nNumberOfBytesToReadb += 2;
LABEL_121:
          v37 = 13;
LABEL_122:
          *(_WORD *)v34 = v37;
          goto LABEL_123;
        }
        nNumberOfBytesToReadb += 2;
        if ( !ReadFile(*(HANDLE *)(v5 + unk_2021E40[FileHandle >> 5]), &v43, 2u, &NumberOfBytesRead, nullptr)
          && GetLastError()
          || !NumberOfBytesRead )
        {
          goto LABEL_121;
        }
        if ( (*(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 4) & 0x48) != 0 )
        {
          if ( v43 != 10 )
          {
            *(_WORD *)v34 = 13;
            *(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 5) = v43;
            *(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 37) = HIBYTE(v43);
            *(_BYTE *)(v5 + unk_2021E40[FileHandle >> 5] + 38) = 10;
LABEL_123:
            v34 += 2;
            goto LABEL_124;
          }
LABEL_110:
          v37 = 10;
          goto LABEL_122;
        }
        if ( v34 == lpMultiByteStr && v43 == 10 )
          goto LABEL_110;
        _lseeki64_nolock(FileHandle, -2, -1, 1u);
        if ( v43 != 10 )
          goto LABEL_121;
      }
      else
      {
        *(_WORD *)v34 = v35;
        v34 += 2;
        nNumberOfBytesToReadb += 2;
      }
LABEL_124:
      if ( (unsigned int)nNumberOfBytesToReadb >= v41 )
        goto LABEL_129;
    }
  }
$error_return$28993:
  if ( lpMultiByteStr != lpBuffer )
    free((void *)lpMultiByteStr);
  result = v40;
  if ( v40 == -2 )
    return v41;
  return result;
}

