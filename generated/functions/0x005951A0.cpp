// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005951A0 rf_system_format_local_date_strdate
// UNREALRED VERIFIED [transfer-scene-20261028]: Single buffer argument; forwards directly to CRT _strdate and returns its pointer. Caller supplies writable storage for the CRT date string, no size argument or error handling here.
char *__cdecl rf_system_format_local_date_strdate(char *Buffer)
{
  return _strdate(Buffer);
}

