// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F140 rf_cstring_find_first_substring
// UNREALRED VERIFIED [system-progress-20261028]: Direct CRT strstr wrapper(string,substring),returns first case-sensitive match or null. No allocation,null guard or length bound.
char *__cdecl rf_cstring_find_first_substring(char *Str, char *SubStr)
{
  return strstr(Str, SubStr);
}

