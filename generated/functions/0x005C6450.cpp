// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6450 rf_exception_format_local_filetime
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Arguments are output character pointer and FILETIME passed BY VALUE (two DWORDs). Converts UTC FILETIME to local FILETIME in its argument copy, then to DOS date/time. Writes M/D/YYYY HH:MM:SS using DOS fields; seconds have two-second resolution. Either conversion failure writes an empty string. Returns formatter length on success or failed API BOOL zero on failure; no destination capacity argument.
int __cdecl rf_exception_format_local_filetime(LPSTR a1, FILETIME FileTime)
{
  int result; // eax
  WORD FatDate; // [esp+0h] [ebp-8h] BYREF
  WORD FatTime; // [esp+4h] [ebp-4h] BYREF

  result = FileTimeToLocalFileTime(&FileTime, &FileTime);
  if ( result )
  {
    result = FileTimeToDosDateTime(&FileTime, &FatDate, &FatTime);
    if ( result )
      return wsprintfA(
               a1,
               "%d/%d/%d %02d:%02d:%02d",
               (FatDate / 32) & 0xF,
               FatDate & 0x1F,
               FatDate / 512 + 1980,
               FatTime / 2048,
               (FatTime / 32) & 0x3F,
               2 * (FatTime & 0x1F));
  }
  *a1 = 0;
  return result;
}

