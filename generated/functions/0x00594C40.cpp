// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00594C40 rf_system_append_legacy_info_report
// UNREALRED VERIFIED [system-progress-20261028]: Arguments string-output object,unused second argument,benchmark byte. Queries0x594770 and appends CPU type/speed and legacy extension tags. GlobalMemoryStatus total physical RAM is rounded to nearest4MiB by4*((bytes+0x200000)>>22) and printed as MB. Nonzero benchmark allocates TWO4MiB buffers, measures about1second using unsigned timeGetTime deadline and QPC. Each iteration copies ONLY0x40000 bytes (rep movsd ECX=0x10000), not4MiB. Computes ticksPerIteration=(end-start)/iterations and prints frequency/ticksPerIteration with label RAM Speed MB/s; value is iterations/sec without byte conversion. No zero-iteration, zero-tick, allocation/API failure or timer-wrap handling in this body. Frees both buffers. Return path is incidental byte or formatting result.
char *__cdecl rf_system_append_legacy_info_report(const char **a1, int a2, unsigned __int8 a3)
{
  char *result; // eax
  char *v5; // [esp+Ch] [ebp-52Ch]
  char *v7; // [esp+14h] [ebp-524h]
  char *v9; // [esp+1Ch] [ebp-51Ch]
  char *v11; // [esp+24h] [ebp-514h]
  void *v12; // [esp+38h] [ebp-500h]
  DWORD v13; // [esp+3Ch] [ebp-4FCh]
  LARGE_INTEGER v14; // [esp+40h] [ebp-4F8h] BYREF
  void *v15; // [esp+4Ch] [ebp-4ECh]
  __int64 v16; // [esp+50h] [ebp-4E8h]
  char v17[4]; // [esp+5Ch] [ebp-4DCh]
  LARGE_INTEGER Frequency; // [esp+60h] [ebp-4D8h] BYREF
  _DWORD v19[3]; // [esp+6Ch] [ebp-4CCh] BYREF
  int v20; // [esp+78h] [ebp-4C0h] BYREF
  int v21; // [esp+7Ch] [ebp-4BCh] BYREF
  char v22[128]; // [esp+80h] [ebp-4B8h] BYREF
  char v23[1024]; // [esp+100h] [ebp-438h] BYREF
  int v24; // [esp+504h] [ebp-34h] BYREF
  char v25[4]; // [esp+508h] [ebp-30h] BYREF
  SIZE_T v26; // [esp+50Ch] [ebp-2Ch]
  struct _MEMORYSTATUS Buffer; // [esp+510h] [ebp-28h] BYREF
  int v28; // [esp+530h] [ebp-8h] BYREF
  int v29; // [esp+534h] [ebp-4h] BYREF

  memset(v22, 0, sizeof(v22));
  rf_system_query_legacy_cpu_info((unsigned int *)&v29, &v24, &v21, &v28, &v20, v22, (int *)v25);
  rf_text_log_buffer_append_printf_unbounded(a1, "CPU Type: %s\n", v22);
  rf_text_log_buffer_append_printf_unbounded(a1, "CPU Speed: %d Mhz\n", *(_DWORD *)v25);
  v23[0] = 0;
  if ( v29 > 5 )
  {
    v11 = &v22[127];
    while ( *++v11 )
      ;
    strcpy(v11, "[PPro] ");
  }
  if ( v24 )
  {
    v9 = &v22[127];
    while ( *++v9 )
      ;
    strcpy(v9, "[MMX] ");
  }
  if ( v21 )
  {
    v7 = &v22[127];
    while ( *++v7 )
      ;
    strcpy(v7, "[3DNow] ");
  }
  if ( v28 )
  {
    v5 = &v22[127];
    while ( *++v5 )
      ;
    strcpy(v5, "[Katmai] ");
  }
  rf_text_log_buffer_append_printf_unbounded(a1, "CPU Extensions: %s\n", v23);
  Buffer.dwLength = 32;
  GlobalMemoryStatus(&Buffer);
  v26 = 4 * ((Buffer.dwTotalPhys + 0x200000) >> 22);
  sprintf(v23, "%d MB", v26);
  rf_text_log_buffer_append_printf_unbounded(a1, "Total RAM: %s\n", v23);
  result = (char *)a3;
  if ( a3 )
  {
    v15 = operator new(0x400000u);
    v12 = operator new(0x400000u);
    QueryPerformanceCounter((LARGE_INTEGER *)&v19[1]);
    v19[0] = 0;
    v13 = timeGetTime() + 1000;
    while ( timeGetTime() < v13 )
    {
      qmemcpy(v15, v12, 0x40000u);
      ++v19[0];
    }
    QueryPerformanceCounter(&v14);
    QueryPerformanceFrequency(&Frequency);
    operator delete(v15);
    operator delete(v12);
    v16 = (v14.QuadPart - *(_QWORD *)&v19[1]) / v19[0];
    *(_DWORD *)v17 = Frequency.QuadPart / v16;
    return rf_text_log_buffer_append_printf_unbounded(a1, "RAM Speed: %d MB/s\n", *(_DWORD *)v17);
  }
  return result;
}

