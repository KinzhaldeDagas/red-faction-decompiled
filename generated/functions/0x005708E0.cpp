// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005708E0 rf_fatal_error_show_message_and_exit
// UNREALRED VERIFIED [registry-config-20261028]: Arguments source-file string,line,error-message string. Unbounded sprintf into1048-byte stack text with error/file/line,appends fixed critical-error and OK-to-exit text,calls0x5708D0,MessageBoxA(NULL,text,Error!,0x12000),then exit(1). No return,recovery callback or exception throw. Does not cap input lengths. Registry root parser uses this for unsupported root names.
void __cdecl __noreturn rf_fatal_error_show_message_and_exit(const char *a1, int a2, const char *a3)
{
  char *v3; // edi
  char *v5; // [esp+10h] [ebp-424h] BYREF
  CHAR Text[1048]; // [esp+14h] [ebp-420h] BYREF
  int v7; // [esp+430h] [ebp-4h]

  sprintf(Text, "Error: %s\nFile: %s - Line: %d\n\n", a3, a1, a2);
  v5 = (char *)&v5 + 3;
  while ( *++v5 )
    ;
  v3 = v5;
  qmemcpy(v5, "A critical error has occurred and the program cannot continue.\nPress OK to exit the program\n", 0x5Cu);
  v3[92] = aACriticalError[92];
  rf_fatal_error_noop_lifecycle_adapter_5708d0();
  MessageBoxA(nullptr, Text, "Error!", 0x12000u);
  v7 = 2;
  exit(1);
}

