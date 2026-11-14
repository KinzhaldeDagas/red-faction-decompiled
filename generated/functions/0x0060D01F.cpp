// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060D01F __getenv_helper_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(name), borrowed value pointer/NULL, no own
// lock. If envInitialized DWORD2022F88==0 ->NULL even existing environ. If narrowenv2021360 NULL and wideenv2021368 exists, call wtomb_environ; require status0 and newly nonNULL
// narrowenv. Name NULL checked ONLYafter conversion, silently NULL without own errno/invalid callback. strlen(name); scan NUL-terminated char** until NULL: require
// strlen(entry)>nameLen,entry[nameLen]==equals,mbsnbicoll(entry,name,nameLen)==0, then return entry+nameLen+1. Locale-aware case-insensitive byte-prefix collation, not ASCII strcmp.
// Empty name allowed and may match leading equals entries. No name-equals rejection, copying or lifetime pinning.
const char *__cdecl _getenv_helper_nolock(char *Str)
{
  const char **v1; // esi
  size_t v3; // edi

  v1 = (const char **)unk_2021360;
  if ( !unk_2022F88 )
    return nullptr;
  if ( unk_2021360 || unk_2021368 && !__wtomb_environ() && (v1 = (const char **)unk_2021360) != nullptr )
  {
    if ( Str )
    {
      v3 = strlen(Str);
      while ( *v1 )
      {
        if ( strlen(*v1) > v3
          && (*v1)[v3] == 61
          && !_mbsnbicoll((const unsigned __int8 *)*v1, (const unsigned __int8 *)Str, v3) )
        {
          return &(*v1)[v3 + 1];
        }
        ++v1;
      }
    }
  }
  return nullptr;
}

