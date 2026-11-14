// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E590 rf_registry_write_dword
// UNREALRED VERIFIED [registry-config-20261028]: Arguments optional section,value name,DWORD value passed on stack at+16. Calls raw writer type4(REG_DWORD),address of value,4bytes. Returns0/-1. Decompiled variadic signature is an artifact of taking stack argument address; body writes one fixed DWORD and performs no varargs traversal.
int rf_registry_write_dword(char *String1, LPCSTR lpValueName, ...)
{
  va_list Data; // [esp+10h] [ebp+10h] BYREF

  va_start(Data, lpValueName);
  return rf_registry_write_raw_value(String1, lpValueName, 4u, (BYTE *)Data, 4u);
}

