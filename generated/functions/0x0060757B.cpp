// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060757B ?_store_winword@@YAHPAUlocaleinfo_struct@@HPBUtm@@PAPADPAIPAU__lc_time_data@@@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Time-data pointer is NOT struct tm (prototypes
// repaired to opaque DWORD*). Native byte layout: char* weekday arrays at0/1C (7 each, selected by%a/%A), month arrays38/68 (12 each,%b/%B), AM/PM pointers98/9C, mode0/1/other
// pattern pointersA0/A4/A8, API LCID DWORDAC, DWORD B0==1 selects manual path. Cdecl(localeInfo*,int mode,const tm*,outputPointerSlot*,remainingCounter*,timeData*), return0/1. Select
// mode0 patternA0,mode1 patternA4,EVERY OTHER mode patternA8. Unless timeData.B0==1, try Windows API: select GetTimeFormatA ONLY mode==2, otherwise GetDateFormatA (even other modes
// using time pattern). Build PARTIAL SYSTEMTIME from LOW16 tm fields: year+1900,month+1,day,hour,minute,second,ms0; wDayOfWeek left UNINITIALIZED, no memset/full tm-range validation.
// Query selected API(LCID,flags0,&date,pattern,NULL,0). Raw result0 ->manual fallback. Otherwise N+8 modulo32, SIGNED compare>1024 selects malloc; else alloca_probe_16. Header
// DWORD0CCCC stack or0DDDD heap, second header DWORD uninitialized, payload=base+8. Allocation NULL ->manual fallback; no own addition-overflow guard/new-handler policy. Second
// API(LCID reloaded,0,&date,capturedPattern,payload,N); copy positive(return-1) bytes, stopping if output remaining0, excluding assumed terminator. NO fallback or failure test when
// second return0/1: copy nothing, freea(payload), return1. Truncation likewise return1 with counter0; enclosing formatter detects it. freea frees header only for0DDDD; stack data
// discarded by frame restore. No GetLastError/own errno translation, validation of second count against allocation N, or try/finally if API/helper throws. Security cookie checked on
// ALL normal Boolean returns. Manual path scans selected NUL pattern while remaining!=0 (exhaustion returns1). Count full run of identical bytes before dispatch. Recognized tokens:
// d/dd ->d with alternate1/0; ddd->a; dddd->A. M/MM ->m alternate1/0; MMM->b; MMMM->B. H/HH->H alternate1/0; h/hh->I; m/mm->M; s/ss->S. yy->y,yyyy->Y. Mapped tokens call expandtime,
// consume WHOLE run on success, return0 on its failure. Unsupported run length copies only ONE literal byte, then rescans remaining run, so suffix can become a recognized token. A/a
// branch ALWAYS delegates p. Only when ASCII case-insensitive comparison of the ENTIRE remaining NUL string equals 'am/pm' or 'a/p' does it skip5/3 bytes; otherwise consumes only
// initial identical A/a run. This is full-string comparison, not prefix matching. Manual t ANY run chooses AM/PM using SIGNED tm_hour>11 with NO0..23 validation. Single t copies
// first character (two bytes if lead byte and room>1); it copies even an empty AM/PM string's NUL as counted payload. Other t lengths copy full selected NUL string. Quotes: skip
// ENTIRE consecutive quote run without emitting literal quotes; even run resumes parsing, odd run copies literal bytes until next quote/NUL/exhaustion and skips one closing quote.
// Unclosed quote reachingNUL is accepted. Ordinary literals, quoted literals, t strings: isleadbyte_l receives sign-extended byte (delegate reduces to low8); if lead AND remaining>1
// require following source byte nonNUL, copy both; missing trail ->0 without own errno. With remaining1, copy just lead byte then return success/exhaustion. No common NUL append,
// output rollback, whole-character capacity reservation or general locale snapshot in this helper.
int __cdecl _store_winword(
        struct localeinfo_struct *Locale,
        int a2,
        const struct tm *a3,
        char **a4,
        unsigned int *a5,
        _DWORD *a6)
{
  char *v6; // edi
  int (__stdcall *v7)(LCID, DWORD, const SYSTEMTIME *, LPCSTR, LPSTR, int); // ecx
  WORD tm_min; // dx
  int v9; // eax
  int v10; // eax
  void *v11; // esp
  _DWORD *v12; // eax
  char *v13; // ebx
  int i; // eax
  char *v15; // edx
  int v16; // eax
  CHAR v18; // al
  int v19; // edx
  char *v20; // ecx
  char v21; // al
  char *v22; // edi
  CHAR v23; // al
  char *v24; // edi
  LCID v25; // [esp-18h] [ebp-44h]
  _DWORD v26[3]; // [esp+0h] [ebp-2Ch] BYREF
  SYSTEMTIME Date; // [esp+Ch] [ebp-20h] BYREF
  int v28; // [esp+1Ch] [ebp-10h]
  char *v29; // [esp+20h] [ebp-Ch]
  void *Memory; // [esp+24h] [ebp-8h]

  if ( a2 )
  {
    if ( a2 == 1 )
      v6 = (char *)a6[41];
    else
      v6 = (char *)a6[42];
  }
  else
  {
    v6 = (char *)a6[40];
  }
  if ( a6[44] == 1 )
    goto LABEL_22;
  v7 = GetDateFormatA;
  if ( a2 == 2 )
    v7 = GetTimeFormatA;
  Date.wYear = LOWORD(a3->tm_year) + 1900;
  Date.wMonth = LOWORD(a3->tm_mon) + 1;
  Date.wDay = a3->tm_mday;
  Date.wHour = a3->tm_hour;
  tm_min = a3->tm_min;
  Date.wSecond = a3->tm_sec;
  Date.wMilliseconds = 0;
  v25 = a6[43];
  v29 = (char *)v7;
  Date.wMinute = tm_min;
  v9 = v7(v25, 0, &Date, v6, nullptr, 0);
  v28 = v9;
  if ( !v9 )
    goto LABEL_22;
  v10 = v9 + 8;
  if ( v10 > 1024 )
  {
    v12 = malloc(v10);
    if ( !v12 )
      goto LABEL_16;
    *v12 = 56797;
  }
  else
  {
    v11 = alloca(v10);
    v12 = v26;
    if ( !v26 )
      goto LABEL_16;
    v26[0] = 52428;
  }
  v12 += 2;
LABEL_16:
  Memory = v12;
  if ( v12 )
  {
    v13 = (char *)v12;
    for ( i = ((int (__stdcall *)(_DWORD, _DWORD, SYSTEMTIME *, char *, _DWORD *, int))v29)(
                a6[43],
                0,
                &Date,
                v6,
                v12,
                v28)
            - 1; i > 0; i = v16 - 1 )
    {
      if ( !*a5 )
        break;
      v15 = *a4;
      v28 = i;
      *v15 = *v13;
      ++*a4;
      v16 = v28;
      ++v13;
      --*a5;
    }
    _freea(Memory);
    return 1;
  }
LABEL_22:
  v18 = *v6;
  while ( *v6 )
  {
    if ( !*a5 )
      return 1;
    v19 = 0;
    Memory = nullptr;
    v20 = v6;
    do
    {
      ++v20;
      ++v19;
    }
    while ( *v20 == v18 );
    v29 = v20;
    if ( v18 > 100 )
    {
      switch ( v18 )
      {
        case 'h':
          if ( v19 == 1 )
          {
            Memory = (void *)1;
LABEL_119:
            v21 = 73;
LABEL_120:
            if ( !_expandtime(v21, a3, a4, Locale, a5, a6, (unsigned int)Memory) )
              return 0;
LABEL_121:
            v6 = v29;
            goto LABEL_38;
          }
          if ( v19 == 2 )
            goto LABEL_119;
          break;
        case 'm':
          if ( v19 == 1 )
          {
            Memory = (void *)1;
LABEL_114:
            v21 = 77;
            goto LABEL_120;
          }
          if ( v19 == 2 )
            goto LABEL_114;
          break;
        case 's':
          if ( v19 == 1 )
          {
            Memory = (void *)1;
LABEL_109:
            v21 = 83;
            goto LABEL_120;
          }
          if ( v19 == 2 )
            goto LABEL_109;
          break;
        case 't':
          if ( a3->tm_hour > 11 )
            v24 = (char *)a6[39];
          else
            v24 = (char *)a6[38];
          if ( v19 == 1 && *a5 )
          {
            if ( _isleadbyte_l(*v24, (_locale_t)Locale) && *a5 > 1 )
            {
              if ( !v24[1] )
                return 0;
              *(*a4)++ = *v24;
              --*a5;
              ++v24;
            }
            *(*a4)++ = *v24;
            --*a5;
          }
          else
          {
            while ( *v24 && *a5 )
            {
              if ( _isleadbyte_l(*v24, (_locale_t)Locale) && *a5 > 1 )
              {
                if ( !v24[1] )
                  return 0;
                *(*a4)++ = *v24;
                --*a5;
                ++v24;
              }
              *(*a4)++ = *v24++;
              --*a5;
            }
          }
          goto LABEL_121;
        case 'y':
          if ( v19 == 2 )
          {
            v21 = 121;
            goto LABEL_120;
          }
          if ( v19 == 4 )
          {
            v21 = 89;
            goto LABEL_120;
          }
          break;
      }
    }
    else
    {
      switch ( v18 )
      {
        case 'd':
          switch ( v19 )
          {
            case 1:
              Memory = (void *)1;
LABEL_77:
              v21 = 100;
              goto LABEL_120;
            case 2:
              goto LABEL_77;
            case 3:
              v21 = 97;
              goto LABEL_120;
            case 4:
              v21 = 65;
              goto LABEL_120;
          }
          break;
        case '\'':
          v6 += v19;
          if ( (v19 & 1) != 0 )
          {
            v23 = *v6;
            if ( !*v6 )
              return 1;
            while ( *a5 )
            {
              if ( v23 == 39 )
              {
                ++v6;
                goto LABEL_38;
              }
              if ( _isleadbyte_l(v23, (_locale_t)Locale) && *a5 > 1 )
              {
                if ( !v6[1] )
                  return 0;
                *(*a4)++ = *v6;
                --*a5;
                ++v6;
              }
              *(*a4)++ = *v6++;
              --*a5;
              v23 = *v6;
              if ( !*v6 )
                goto LABEL_38;
            }
          }
          goto LABEL_38;
        case 'A':
          goto LABEL_53;
        case 'H':
          if ( v19 == 1 )
          {
            Memory = (void *)1;
LABEL_52:
            v21 = 72;
            goto LABEL_120;
          }
          if ( v19 == 2 )
            goto LABEL_52;
          break;
        case 'M':
          switch ( v19 )
          {
            case 1:
              Memory = (void *)1;
LABEL_47:
              v21 = 109;
              goto LABEL_120;
            case 2:
              goto LABEL_47;
            case 3:
              v21 = 98;
              goto LABEL_120;
            case 4:
              v21 = 66;
              goto LABEL_120;
          }
          break;
        case 'a':
LABEL_53:
          if ( !__ascii_stricmp((unsigned __int8 *)v6, "am/pm") )
          {
            v22 = v6 + 5;
            goto LABEL_57;
          }
          if ( !__ascii_stricmp((unsigned __int8 *)v6, (unsigned __int8 *)&off_648F2C) )
          {
            v22 = v6 + 3;
LABEL_57:
            v29 = v22;
          }
          v21 = 112;
          goto LABEL_120;
      }
    }
    if ( _isleadbyte_l(v18, (_locale_t)Locale) && *a5 > 1 )
    {
      if ( !v6[1] )
        return 0;
      *(*a4)++ = *v6;
      --*a5;
      ++v6;
    }
    *(*a4)++ = *v6++;
    --*a5;
LABEL_38:
    v18 = *v6;
  }
  return 1;
}

