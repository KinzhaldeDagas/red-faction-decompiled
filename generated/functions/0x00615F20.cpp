// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00615F20 ?__crtLCMapStringA_stat@@YAHPAUlocaleinfo_struct@@KKPBDHPADHHH@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal ECX=localeinfo
// pointer(firstfieldlocaleRoot),EAX
// intresult,EIGHTcaller-cleanedstackslots(LCID,mapFlags,constchar*source,SIGNEDbyteCount,char*destination,SIGNEDdestCapacity,UINTcodepage,finalFlag);
// correctedfalsecdecl/missingECX/pointer-likecounts. NoNULL/countvalidation. Cache2021C70:0
// probesLCMapStringW(0,100h,fixedoneWCHAR,1,NULL,0),successmode1,error120mode2,otherfailureleaves0andusesANSIthiscall;invalidnonzerootherthan1/2returns0.
// PositivebyteCountshortensatfirstNULwithinboundandINCLUDESeventualNUL;nonpositivepassedraw. Wmode:codepage0fromlocaleRoot+4,LCIDpassedUNCHANGEDincluding0.
// MultiByteToWideCharqueryflags1|(finalFlag!=0?8:0);0returns0beforeoutputwrite.
// Requirequeryn>0andn<=0x7FFFFFF0,allocate2*n+8:totalsize<=1024usesstackprobe/headerCCCC,largerheapmalloc/headerDDDD;data=base+8.
// Actualconversionusesflags1ONLY;0->freeainput/return0. LCMapStringWsizequerysetsreturnCount. Query0->freeainput/0.
// Sortkeyflag400h:ifcapacity!=0andrequired<=SIGNEDcapacitycallLCMapStringWdirectlytodestination,IGNOREactualreturn;otherwiseNOwrite;returnrequiredEVENinsufficientcapacity/APIwritefailure.
// Otherflags:allocatemappedUTF16scratchsameguard/threshold;allocationfailureORactualLCMapStringWfailurecanreturnPOSITIVErequiredcountWITHOUTwritingdestination.
// SuccessfulmappingcallsWideCharToMultiByte(codepage,0,mapped,QUERYrequiredcount,destination,capacity,NULL,NULL),orNULL/0sizequerywhencapacity0;returnitsactualresult.
// Freeabothscratchesnormally. ANSImode0/2:LCID0fromlocaleRoot+20,CP0fromroot+4,ansicp(LCID)==-1->0. MatchingCPdirectLCMapStringAandrawreturn.
// DifferentCPconvertcp(inputCP,localeACP,source,&length,NULL,0),NULL->0;LCMapStringAsizequery,requirepositivecount<=0xFFFFFFE0,allocatecount+8stack/heapasabove,memsettemporarymappedbytes0,actualLCMapStringA;0->0.
// Convertmappedbytesbackvia convertcp(localeACP,inputCP,temp,&count,destination,capacity);nonnull->count,NULL->0.
// freeamappedtemporary,freeconvertedsource,freeconvertedoutputONLYifnonnulland!=destination. Noownerrno translation,defaultsubstitutioncheckorrollback.
// Cookiecheckednormalreturns;noexception-finallyscratchcleanup. Earlyquery/allocationfailurescanleavecalleroutputUNINITIALIZED/unchanged;setSBUpLowignoresreturnstatus.
int __usercall __crtLCMapStringA_stat@<eax>(
        struct localeinfo_struct *a1@<ecx>,
        LCID Locale,
        DWORD dwMapFlags,
        const char *lpMultiByteStr,
        int cbMultiByte,
        char *lpDestStr,
        int cchDest,
        UINT CodePage,
        int a9)
{
  int v10; // ecx
  const char *v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // edi
  unsigned int v15; // eax
  void *v16; // esp
  WCHAR *v17; // eax
  int v18; // eax
  int v19; // ecx
  unsigned int v20; // eax
  void *v21; // esp
  WCHAR *v22; // esi
  WCHAR *v23; // eax
  int v24; // eax
  UINT v26; // eax
  WCHAR *v27; // eax
  int v28; // eax
  int v29; // esi
  size_t v30; // eax
  void *v31; // esp
  int *v32; // edi
  int *v33; // eax
  _DWORD v34[2]; // [esp+0h] [ebp-20h] BYREF
  int v35; // [esp+8h] [ebp-18h] BYREF
  UINT v36; // [esp+Ch] [ebp-14h]
  void *Block; // [esp+10h] [ebp-10h]
  LPWSTR lpWideCharStr; // [esp+14h] [ebp-Ch]
  int cchWideChar; // [esp+18h] [ebp-8h] BYREF

  if ( !unk_2021C70 )
  {
    if ( LCMapStringW(0, 0x100u, &String1, 1, nullptr, 0) )
    {
      unk_2021C70 = 1;
    }
    else if ( GetLastError() == 120 )
    {
      unk_2021C70 = 2;
    }
  }
  if ( cbMultiByte > 0 )
  {
    v10 = cbMultiByte;
    v11 = lpMultiByteStr;
    while ( 1 )
    {
      --v10;
      if ( !*v11 )
        break;
      ++v11;
      if ( !v10 )
      {
        v10 = -1;
        break;
      }
    }
    v12 = cbMultiByte - v10 - 1;
    if ( v12 < cbMultiByte )
      v12 = cbMultiByte - v10;
    cbMultiByte = v12;
  }
  if ( unk_2021C70 != 2 && unk_2021C70 )
  {
    if ( unk_2021C70 == 1 )
    {
      cchWideChar = 0;
      if ( !CodePage )
        CodePage = *(_DWORD *)(*(_DWORD *)a1 + 4);
      v13 = MultiByteToWideChar(CodePage, 8 * (a9 != 0) + 1, lpMultiByteStr, cbMultiByte, nullptr, 0);
      v14 = v13;
      if ( v13 )
      {
        if ( v13 <= 0 || 0xFFFFFFE0 / v13 < 2 )
        {
          lpWideCharStr = nullptr;
LABEL_30:
          if ( lpWideCharStr )
          {
            if ( MultiByteToWideChar(CodePage, 1u, lpMultiByteStr, cbMultiByte, lpWideCharStr, v14) )
            {
              v18 = LCMapStringW(Locale, dwMapFlags, lpWideCharStr, v14, nullptr, 0);
              v19 = v18;
              cchWideChar = v18;
              if ( v18 )
              {
                if ( (dwMapFlags & 0x400) != 0 )
                {
                  if ( cchDest )
                  {
                    if ( v18 <= cchDest )
                      LCMapStringW(Locale, dwMapFlags, lpWideCharStr, v14, (LPWSTR)lpDestStr, cchDest);
                  }
                  goto LABEL_53;
                }
                if ( v18 <= 0 || 0xFFFFFFE0 / v18 < 2 )
                {
                  v22 = nullptr;
LABEL_46:
                  if ( v22 )
                  {
                    if ( LCMapStringW(Locale, dwMapFlags, lpWideCharStr, v14, v22, cchWideChar) )
                    {
                      if ( cchDest )
                        v24 = WideCharToMultiByte(CodePage, 0, v22, cchWideChar, lpDestStr, cchDest, nullptr, nullptr);
                      else
                        v24 = WideCharToMultiByte(CodePage, 0, v22, cchWideChar, nullptr, 0, nullptr, nullptr);
                      cchWideChar = v24;
                    }
                    _freea(v22);
                  }
                  goto LABEL_53;
                }
                v20 = 2 * v18 + 8;
                if ( v20 > 0x400 )
                {
                  v23 = (WCHAR *)malloc(2 * v19 + 8);
                  if ( v23 )
                  {
                    *(_DWORD *)v23 = 56797;
                    v23 += 4;
                  }
                  v22 = v23;
                  goto LABEL_46;
                }
                v21 = alloca(v20);
                if ( v34 )
                {
                  v34[0] = 52428;
                  v22 = (WCHAR *)&v35;
                  goto LABEL_46;
                }
              }
            }
LABEL_53:
            _freea(lpWideCharStr);
            return cchWideChar;
          }
          return 0;
        }
        v15 = 2 * v13 + 8;
        if ( v15 > 0x400 )
        {
          v17 = (WCHAR *)malloc(2 * v14 + 8);
          if ( v17 )
          {
            *(_DWORD *)v17 = 56797;
            goto LABEL_27;
          }
        }
        else
        {
          v16 = alloca(v15);
          v17 = (WCHAR *)v34;
          if ( v34 )
          {
            v34[0] = 52428;
LABEL_27:
            v17 += 4;
          }
        }
        lpWideCharStr = v17;
        goto LABEL_30;
      }
    }
    return 0;
  }
  lpWideCharStr = nullptr;
  Block = nullptr;
  if ( !Locale )
    Locale = *(_DWORD *)(*(_DWORD *)a1 + 20);
  if ( !CodePage )
    CodePage = *(_DWORD *)(*(_DWORD *)a1 + 4);
  v26 = __ansicp(Locale);
  v36 = v26;
  if ( v26 == -1 )
    return 0;
  if ( v26 == CodePage )
  {
    v29 = LCMapStringA(Locale, dwMapFlags, lpMultiByteStr, cbMultiByte, lpDestStr, cchDest);
    goto LABEL_78;
  }
  v27 = (WCHAR *)__convertcp(CodePage, v26, lpMultiByteStr, &cbMultiByte, nullptr, 0);
  lpWideCharStr = v27;
  if ( !v27 )
    return 0;
  v28 = LCMapStringA(Locale, dwMapFlags, (LPCSTR)v27, cbMultiByte, nullptr, 0);
  cchWideChar = v28;
  if ( v28 )
  {
    if ( v28 <= 0 )
    {
      v32 = nullptr;
    }
    else
    {
      v30 = v28 + 8;
      if ( v30 > 0x400 )
      {
        v33 = (int *)malloc(v30);
        if ( v33 )
        {
          *v33 = 56797;
          v33 += 2;
        }
        v32 = v33;
      }
      else
      {
        v31 = alloca(v30);
        if ( !v34 )
          goto LABEL_63;
        v34[0] = 52428;
        v32 = &v35;
      }
    }
    if ( v32 )
    {
      memset(v32, 0, cchWideChar);
      cchWideChar = LCMapStringA(Locale, dwMapFlags, (LPCSTR)lpWideCharStr, cbMultiByte, (LPSTR)v32, cchWideChar);
      if ( cchWideChar )
      {
        Block = __convertcp(v36, CodePage, (const CHAR *)v32, &cchWideChar, lpDestStr, cchDest);
        v29 = Block != nullptr ? cchWideChar : 0;
      }
      else
      {
        v29 = 0;
      }
      _freea(v32);
      goto LABEL_78;
    }
  }
LABEL_63:
  v29 = 0;
LABEL_78:
  if ( lpWideCharStr )
    free(lpWideCharStr);
  if ( Block && lpDestStr != Block )
    free(Block);
  return v29;
}

