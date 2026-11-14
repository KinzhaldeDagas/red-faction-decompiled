// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00594770 rf_system_query_legacy_cpu_info
// UNREALRED VERIFIED [system-progress-20261028]: Arguments required outputs family,MMX,3DNow,Katmai/SSE,TSC; optional description buffer and MHz output. Clears outputs; toggles EFLAGS ID bit to test CPUID (does not restore original EFLAGS). Uses leaf1 family bits8..11 without extended family/model decoding. Family<5 becomes4 and optional description Not Pentium Compatible. TSC uses leaf1 EDX bit4; Katmai uses bit25 only for family>5. MMX bit23 is tested but then output is unconditionally overwritten with1 from constant local var_C=1. AMD extended leaves are queried only for AuthenticAMD and max extended leaf>=0x80000005; bit31 of leaf0x80000001 supplies3DNow and leaves0x80000002..4 supply brand text. Intel/fallback descriptions use old family labels; some MMX decisions test output POINTER rather than value. Optional MHz measurement requires TSC output: Sleep100ms, sample low32 RDTSC around
// busy wait for timeGetTime+100, retry on low32 wrap; signed arithmetic rounds delta with833333 then divides/multiplies by1666667 and divides100000. Priority APIs receive NULL process/thread handles and their results are unchecked. No description capacity, modern feature decoding or uniform success return.
unsigned int __cdecl rf_system_query_legacy_cpu_info(
        unsigned int *a1,
        _DWORD *a2,
        _DWORD *a3,
        _DWORD *a4,
        _DWORD *a5,
        char *Buffer,
        int *a7)
{
  unsigned int v7; // kr00_4
  unsigned int v8; // kr04_4
  unsigned int result; // eax
  char v43; // dl
  char *v44; // [esp+1Ch] [ebp-94h]
  char *v45; // [esp+20h] [ebp-90h]
  int nPriority; // [esp+28h] [ebp-88h]
  DWORD Time; // [esp+2Ch] [ebp-84h]
  DWORD dwPriorityClass; // [esp+30h] [ebp-80h]
  unsigned int v49; // [esp+38h] [ebp-78h]
  unsigned int timestamp_counter; // [esp+44h] [ebp-6Ch]
  _DWORD v51[17]; // [esp+48h] [ebp-68h] BYREF
  char String1[4]; // [esp+8Ch] [ebp-24h] BYREF
  int v53; // [esp+90h] [ebp-20h]
  int v54; // [esp+94h] [ebp-1Ch]
  int v55; // [esp+98h] [ebp-18h]
  unsigned int v56; // [esp+A0h] [ebp-10h]
  int v57; // [esp+A4h] [ebp-Ch]
  int v58; // [esp+A8h] [ebp-8h]
  int v59; // [esp+ACh] [ebp-4h]

  v57 = 1;
  *a1 = 0;
  *a2 = 0;
  *a3 = 0;
  *a5 = 0;
  *a4 = 0;
  if ( a7 )
    *a7 = 0;
  v58 = 0;
  *(_DWORD *)String1 = 0;
  v53 = 0;
  v54 = 0;
  v55 = 0;
  v7 = __readeflags();
  __writeeflags(v7 ^ 0x200000);
  v8 = __readeflags();
  if ( v7 != v8 )
  {
    _EAX = 0;
    __asm { cpuid }
    v58 = _EAX;
    *(_DWORD *)String1 = _EBX;
    v53 = _EDX;
    v54 = _ECX;
    _EAX = 1;
    __asm { cpuid }
    v56 = _EAX;
    v59 = _EDX;
  }
  else
  {
    v56 = 1024;
    v59 = 0;
  }
  *a1 = (v56 >> 8) & 0xF;
  result = (unsigned int)a1;
  if ( (int)*a1 >= 5 )
  {
    if ( (v59 & 0x10) != 0 )
      *a5 = 1;
    if ( ((unsigned int)&unk_800000 & v59) == 0 )
      *a2 = 0;
    if ( v57 )
      *a2 = 1;
    else
      *a2 = 0;
    if ( (int)*a1 > 5 && ((unsigned int)&unk_2000000 & v59) != 0 )
      *a4 = 1;
    if ( !_stricmp(String1, "AuthenticAMD") )
    {
      _EAX = 0x80000000;
      __asm { cpuid }
      v56 = result;
      if ( result >= 0x80000005 )
      {
        _EAX = -2147483647;
        __asm { cpuid }
        v56 = result;
        v59 = _EDX;
        if ( _EDX < 0 )
        {
          result = (unsigned int)a3;
          *a3 = 1;
        }
        if ( Buffer )
        {
          memset(v51, 0, 0x40u);
          _EAX = -2147483646;
          __asm { cpuid }
          v51[0] = _EAX;
          v51[1] = _EBX;
          v51[2] = _ECX;
          v51[3] = _EDX;
          _EAX = -2147483645;
          __asm { cpuid }
          v51[4] = _EAX;
          v51[5] = _EBX;
          v51[6] = _ECX;
          v51[7] = _EDX;
          _EAX = -2147483644;
          __asm { cpuid }
          v51[8] = _EAX;
          v51[9] = _EBX;
          v51[10] = _ECX;
          v51[11] = _EDX;
          v45 = (char *)v51;
          v44 = Buffer;
          do
          {
            v43 = *v45;
            *v44 = *v45;
            result = (unsigned int)++v45;
            ++v44;
          }
          while ( v43 );
        }
      }
      else if ( Buffer )
      {
        if ( a2 )
          result = sprintf(Buffer, "AMD-K%d, MMX:%s", *a1, (const char *)&off_642224);
        else
          result = sprintf(Buffer, "AMD-K%d, MMX:%s", *a1, "No");
      }
    }
    else
    {
      result = _stricmp(String1, "GenuineIntel");
      if ( result )
      {
        if ( Buffer )
        {
          if ( *a2 )
            result = sprintf(Buffer, "%d86 w/ MMX Compatible", *a1);
          else
            result = sprintf(Buffer, "%d86 Compatible", *a1);
        }
      }
      else if ( Buffer )
      {
        if ( *a1 == 5 )
        {
          result = sprintf(Buffer, "Intel Pentium");
          if ( a2 )
          {
            result = 539981600;
            strcat(Buffer, " w/ MMX");
          }
        }
        else if ( *a1 == 6 )
        {
          if ( *a4 )
          {
            result = sprintf(Buffer, "Intel Pentium III");
          }
          else if ( a2 )
          {
            result = sprintf(Buffer, "Intel Pentium II w/ MMX");
          }
          else
          {
            result = sprintf(Buffer, "Intel Pentium Pro");
          }
        }
        else
        {
          result = sprintf(Buffer, "Intel i%d86", *a1);
        }
      }
    }
    if ( a7 )
    {
      *a7 = 0;
      if ( *a5 )
      {
        dwPriorityClass = GetPriorityClass(nullptr);
        nPriority = GetThreadPriority(nullptr);
        SetPriorityClass(nullptr, 0x100u);
        SetThreadPriority(nullptr, 15);
        Sleep(0x64u);
        do
        {
          Time = timeGetTime();
          timestamp_counter = rf_cpu_read_timestamp_counter();
          while ( timeGetTime() < Time + 100 )
            ;
          v49 = rf_cpu_read_timestamp_counter();
          timeGetTime();
        }
        while ( timestamp_counter > v49 );
        *a7 = 1666667 * ((int)(v49 - timestamp_counter + 833333) / 1666667) / 100000;
        SetPriorityClass(nullptr, dwPriorityClass);
        return SetThreadPriority(nullptr, nPriority);
      }
    }
  }
  else
  {
    *a1 = 4;
    if ( Buffer )
      return sprintf(Buffer, "Not Pentium Compatible");
  }
  return result;
}

