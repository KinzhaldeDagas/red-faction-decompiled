// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C69A __strdate_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) below sets errnoE and calls
// invalid_parameter(NULL,NULL,NULL,0,0); stated error returns require that callback to return. Cdecl(buffer,unsignedsize),errno-style0/E. NULLbuffer/size0 invalid22/22; otherwise
// FIRST buffer[0]=0. Size<9 invalid34/34. GetLocalTime into SYSTEMTIME, no status return to check; render fixed ASCII MM/DD/YY,NUL at8 from WORDmonth/day and year%100. No
// locale/date-field validation, allocation, own lock or timezone lookup through CRT globals; OS supplies local time. Success changes only9bytes and does not explicitly clear
// errno/doserrno.
errno_t __cdecl _strdate_s(char *Buffer, size_t SizeInBytes)
{
  int *v2; // eax
  errno_t v3; // esi
  int v5; // edx
  int wMonth; // eax
  int wDay; // edi
  int v8; // [esp-4h] [ebp-1Ch]
  struct _SYSTEMTIME SystemTime; // [esp+8h] [ebp-10h] BYREF

  if ( !Buffer || !SizeInBytes )
  {
    v2 = _errno();
    v8 = 22;
LABEL_4:
    v3 = v8;
    *v2 = v8;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return v3;
  }
  *Buffer = 0;
  if ( SizeInBytes < 9 )
  {
    v2 = _errno();
    v8 = 34;
    goto LABEL_4;
  }
  GetLocalTime(&SystemTime);
  v5 = SystemTime.wYear % 100;
  wMonth = SystemTime.wMonth;
  wDay = SystemTime.wDay;
  Buffer[5] = 47;
  Buffer[2] = 47;
  Buffer[8] = 0;
  *Buffer = wMonth / 10 + 48;
  Buffer[1] = wMonth % 10 + 48;
  Buffer[3] = wDay / 10 + 48;
  Buffer[4] = wDay % 10 + 48;
  Buffer[6] = v5 / 10 + 48;
  Buffer[7] = v5 % 10 + 48;
  return 0;
}

