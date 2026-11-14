// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00620607 ?__crtCompareStringA_stat@@YAHPAUlocaleinfo_struct@@KKPBDH1HH@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal caller-cleaned ABI
// ECX=localeinfo*,EDX=leftchar*,sixstackDWORDs(LCID,flags,SIGNEDleftCount,rightchar*,SIGNEDrightCount,UINTcodepage),intEAX/plainRET; correctedfalsefastcallcleanup/pointerLCID/CP.
// NoNULLguard. Cache2021E14:0 probesCompareStringW(0,0,fixedoneWCHAR,1,same,1),successmode1,error120mode2,otherfailureleaves0/currentANSIfallback;invalidnonzerootherthan1/2->0.
// PositivecountsstrncnttrimtofirstNUL(EXCLUDINGNUL)withinbound;count0/-1passedraw,values<-1return0AFTERprobe. WmodeCP0fromlocaleRoot+4,LCIDpassedunchangedincluding0.
// Ifeithercount0:equalcounts->2;rightcount>1->1;leftcount>1->3.
// OtherunequalcasesGetCPInfo(CP),failure0;leftcount1versus0->2ifCPMaxCharSize>=2andsoleLEFTbyteinlead-range,else3;left0versusright1analogous2/1.
// Unequalnonpositivecountsfallthroughnormalconversion.
// Bothnonzero/general:MultiByteToWideCharqueryflags9foreachside;requirepositiveunits<=7FFFFFF0,allocate2*units+8taggedscratch(each<=1024stack/headerCCCC,elseheap/headerDDDD,data+8).
// Actualconversionflags1,nonzeroonlychecked;CompareStringWusesQUERYunitcounts,notactualreturnedcounts. Noownscratchinitialization. Query/allocation/conversionfailure
// ->0,freeallocatedscratchnormally;successfulrawCompareStringWresultforwarded. ANSImode0/2:LCID0=root+20,CP0=root+4,ansicp==-1->0. MatchingCPdirectCompareStringA(trimmedcounts).
// DifferentCPconvertcp(inputCP,localeACP,bothstrings,&separatecounts,NULL,0);firstNULL->0,secondNULLfreefirst/0;compareconvertedstringsandupdatedcounts,freeboth. No ownerrno
// mapping,invalidcallback,allocation-finallyonexception;cookiecheckednormalreturns. ReturnrawOS1/2/3or0,not-1/0/+1.
int __usercall __crtCompareStringA_stat@<eax>(
        struct localeinfo_struct *a1@<ecx>,
        const char *a2@<edx>,
        LCID Locale,
        DWORD dwCmpFlags,
        int cbMultiByte,
        const char *a6,
        int cchCount2,
        UINT CodePage)
{
  int v10; // edx
  int result; // eax
  BYTE *LeadByte; // eax
  unsigned __int8 v13; // dl
  BYTE *i; // eax
  unsigned __int8 v15; // dl
  int v16; // eax
  int v17; // ebx
  unsigned int v18; // eax
  void *v19; // esp
  WCHAR *v20; // eax
  int v21; // eax
  int v22; // ebx
  unsigned int v23; // eax
  void *v24; // esp
  WCHAR *v25; // edi
  WCHAR *v26; // eax
  CHAR *v27; // edi
  void *v28; // ebx
  UINT v29; // eax
  UINT v30; // esi
  const CHAR *v31; // eax
  int v32; // esi
  _DWORD v34[2]; // [esp+0h] [ebp-38h] BYREF
  int v35; // [esp+8h] [ebp-30h] BYREF
  int cchCount1; // [esp+Ch] [ebp-2Ch]
  int v37; // [esp+10h] [ebp-28h]
  LPCCH lpMultiByteStr; // [esp+14h] [ebp-24h]
  LPWSTR lpWideCharStr; // [esp+18h] [ebp-20h]
  LPCCH lpString2; // [esp+1Ch] [ebp-1Ch]
  struct _cpinfo CPInfo; // [esp+20h] [ebp-18h] BYREF

  lpMultiByteStr = a2;
  lpString2 = a6;
  if ( !unk_2021E14 )
  {
    if ( CompareStringW(0, 0, &String1, 1, &String1, 1) )
    {
      unk_2021E14 = 1;
    }
    else if ( GetLastError() == 120 )
    {
      unk_2021E14 = 2;
    }
  }
  if ( cbMultiByte <= 0 )
  {
    if ( cbMultiByte < -1 )
      return 0;
  }
  else
  {
    cbMultiByte = strncnt(a2, cbMultiByte);
  }
  v10 = cchCount2;
  if ( cchCount2 <= 0 )
  {
    if ( cchCount2 < -1 )
      return 0;
  }
  else
  {
    v10 = strncnt(lpString2, cchCount2);
    cchCount2 = v10;
  }
  if ( unk_2021E14 == 2 || !unk_2021E14 )
  {
    v27 = nullptr;
    v28 = nullptr;
    if ( !Locale )
      Locale = *(_DWORD *)(*(_DWORD *)a1 + 20);
    if ( !CodePage )
      CodePage = *(_DWORD *)(*(_DWORD *)a1 + 4);
    v29 = __ansicp(Locale);
    v30 = v29;
    if ( v29 == -1 )
      return 0;
    if ( v29 != CodePage )
    {
      v28 = __convertcp(CodePage, v29, lpMultiByteStr, &cbMultiByte, nullptr, 0);
      if ( !v28 )
        return 0;
      v31 = (const CHAR *)__convertcp(CodePage, v30, lpString2, &cchCount2, nullptr, 0);
      v27 = (CHAR *)v31;
      if ( !v31 )
      {
        free(v28);
        return 0;
      }
      lpMultiByteStr = (LPCCH)v28;
      lpString2 = v31;
    }
    v32 = CompareStringA(Locale, dwCmpFlags, lpMultiByteStr, cbMultiByte, lpString2, cchCount2);
    if ( v28 )
    {
      free(v28);
      free(v27);
    }
    return v32;
  }
  result = 1;
  if ( unk_2021E14 != 1 )
    return 0;
  v37 = 0;
  if ( !CodePage )
    CodePage = *(_DWORD *)(*(_DWORD *)a1 + 4);
  if ( cbMultiByte && v10 )
  {
LABEL_44:
    v16 = MultiByteToWideChar(CodePage, 9u, a2, cbMultiByte, nullptr, 0);
    v17 = v16;
    cchCount1 = v16;
    if ( !v16 )
      return 0;
    if ( v16 <= 0 || 0xFFFFFFE0 / v16 < 2 )
    {
      lpWideCharStr = nullptr;
LABEL_55:
      if ( lpWideCharStr )
      {
        if ( MultiByteToWideChar(CodePage, 1u, lpMultiByteStr, cbMultiByte, lpWideCharStr, v17) )
        {
          v21 = MultiByteToWideChar(CodePage, 9u, lpString2, cchCount2, nullptr, 0);
          v22 = v21;
          if ( v21 )
          {
            if ( v21 <= 0 || 0xFFFFFFE0 / v21 < 2 )
            {
              v25 = nullptr;
LABEL_67:
              if ( v25 )
              {
                if ( MultiByteToWideChar(CodePage, 1u, lpString2, cchCount2, v25, v22) )
                  v37 = CompareStringW(Locale, dwCmpFlags, lpWideCharStr, cchCount1, v25, v22);
                _freea(v25);
              }
              goto $error_cleanup$27659;
            }
            v23 = 2 * v21 + 8;
            if ( v23 > 0x400 )
            {
              v26 = (WCHAR *)malloc(2 * v22 + 8);
              if ( v26 )
              {
                *(_DWORD *)v26 = 56797;
                v26 += 4;
              }
              v25 = v26;
              goto LABEL_67;
            }
            v24 = alloca(v23);
            if ( v34 )
            {
              v34[0] = 52428;
              v25 = (WCHAR *)&v35;
              goto LABEL_67;
            }
          }
        }
$error_cleanup$27659:
        _freea(lpWideCharStr);
        return v37;
      }
      return 0;
    }
    v18 = 2 * v16 + 8;
    if ( v18 > 0x400 )
    {
      v20 = (WCHAR *)malloc(2 * v17 + 8);
      if ( v20 )
      {
        *(_DWORD *)v20 = 56797;
        goto LABEL_52;
      }
    }
    else
    {
      v19 = alloca(v18);
      v20 = (WCHAR *)v34;
      if ( v34 )
      {
        v34[0] = 52428;
LABEL_52:
        v20 += 4;
      }
    }
    lpWideCharStr = v20;
    goto LABEL_55;
  }
  if ( cbMultiByte == v10 )
    return 2;
  if ( v10 <= 1 )
  {
    if ( cbMultiByte > 1 )
      return 3;
    if ( !GetCPInfo(CodePage, &CPInfo) )
      return 0;
    if ( cbMultiByte > 0 )
    {
      if ( CPInfo.MaxCharSize >= 2 )
      {
        LeadByte = CPInfo.LeadByte;
        if ( CPInfo.LeadByte[0] )
        {
          while ( 1 )
          {
            v13 = LeadByte[1];
            if ( !v13 )
              break;
            if ( (unsigned int)*a2 >= *LeadByte && (unsigned int)*a2 <= v13 )
              return 2;
            LeadByte += 2;
            if ( !*LeadByte )
              return 3;
          }
        }
      }
      return 3;
    }
    if ( cchCount2 > 0 )
    {
      if ( CPInfo.MaxCharSize >= 2 )
      {
        for ( i = CPInfo.LeadByte; *i; i += 2 )
        {
          v15 = i[1];
          if ( !v15 )
            break;
          if ( (unsigned int)*lpString2 >= *i && (unsigned int)*lpString2 <= v15 )
            return 2;
        }
      }
      return 1;
    }
    goto LABEL_44;
  }
  return result;
}

