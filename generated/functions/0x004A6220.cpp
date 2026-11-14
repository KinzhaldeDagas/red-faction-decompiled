// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6220 rf_multiplayer_log_open_if_enabled_stub
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): No arguments. Sets ECX7B1534 and calls constant-return-false AL stub4A6760; MOVZX AL then branch makes the ENTIRE log-opening path unreachable in
// this compiled binary. Normal call performs no username/path/time/file operation and does not change log handle7B1530. Retained dormant branch zeroes1024-byte directory buffer,
// calls GetUserNameA with advertised capacity127 (native local username area68 bytes), copies loose-directory index0 unbounded, appends original backslash+NUL if last directory byte
// differs. Gets64-bit CRT time/localtime, strftime max63 with %a%b%d_%I%M, sprintf filename %s%s_%s.txt into local1028, fopen wt ->7B1530; success emits banner and stores LOW32
// current time into Time2 then662BE0. No own API-result, bounded concatenation, existing-file/old-handle or localtime-null guards on dormant branch. Existing FILE* return type is
// incidental/path-dependent, not a promise that return is the opened handle.
FILE *rf_multiplayer_log_open_if_enabled_stub()
{
  FILE *result; // eax
  struct tm *v1; // eax
  char v2; // [esp+7h] [ebp-8EDh]
  _WORD *v3; // [esp+8h] [ebp-8ECh]
  const char *v4; // [esp+18h] [ebp-8DCh] BYREF
  char v5; // [esp+1Ch] [ebp-8D8h] BYREF
  CHAR v6[1023]; // [esp+1Dh] [ebp-8D7h] BYREF
  CHAR Buffer[68]; // [esp+41Ch] [ebp-4D8h] BYREF
  DWORD pcbBuffer; // [esp+460h] [ebp-494h] BYREF
  __time64_t Time; // [esp+464h] [ebp-490h] BYREF
  char v10[128]; // [esp+46Ch] [ebp-488h] BYREF
  char FileName[1028]; // [esp+4ECh] [ebp-408h] BYREF

  result = (FILE *)(unsigned __int8)constant_return_false_al_4A6760();
  if ( (_BYTE)result )
  {
    v5 = 0;
    memset(v6, 0, sizeof(v6));
    pcbBuffer = 127;
    GetUserNameA(Buffer, &pcbBuffer);
    rf_vfile_copy_loose_directory_cstring_unbounded(0, &v5);
    v4 = &v5;
    v4 += strlen(v4) + 1;
    if ( *((_BYTE *)&v4 + v4 - v6 + 3) != 92 )
    {
      v3 = (_WORD *)((char *)&v4 + 3);
      do
      {
        v2 = *((_BYTE *)v3 + 1);
        v3 = (_WORD *)((char *)v3 + 1);
      }
      while ( v2 );
      *v3 = 92;
    }
    Time = rf_crt_time64_forward(nullptr);
    v1 = rf_crt_localtime64_forward(&Time);
    strftime(v10, 0x3Fu, "%a%b%d_%I%M", v1);
    sprintf(FileName, "%s%s_%s.txt", &v5, Buffer, v10);
    result = fopen(FileName, "wt");
    MEMORY[0x7B1530] = result;
    if ( result )
    {
      rf_multiplayer_log_open_banner();
      LODWORD(Time2) = rf_crt_time64_forward(nullptr);
      dword_662BE0 = Time2;
      return (FILE *)Time2;
    }
  }
  return result;
}

