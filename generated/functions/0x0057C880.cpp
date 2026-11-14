// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C880 rf_enumerate_files_sorted
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl two-DWORD intrusive list sentinel output, root id, pattern, flags byte, optional callback. Initializes empty circular sentinel, builds256-byte loose path, enumerates direct nondirectories. Each accepted entry allocates56-byte node: next0,prev4,name8[40],flags48,time32 at52. Flag4 keeps extension; otherwise last-dot stripping57C440 uses84-byte scratch before truncation (can overflow scratch). Name truncated to39 bytes plus forcedNUL. Node flags mask0x2 for readonly,mask0x4 for archive; timestamp is LOW DWORD of file-write time. Callback receives transient stack node before links initialized; low-byte false skips allocation. Flag1 inserts ascending case-insensitive name (new equal names
// precede existing equals); else flag2 inserts descending SIGNED32 timestamp (equal times keep prior order); flag1 wins when both set. Neither bit means enumeration order. Output owns heap nodes, no prior-list cleanup, no allocation NULL guard, no VPP enumeration. Returns findclose result or-1 for initial find failure, NOT node count; empty output remains self-linked sentinel.
int __cdecl rf_enumerate_files_sorted(
        const char **a1,
        int a2,
        const char *a3,
        char a4,
        unsigned __int8 (__cdecl *a5)(char *))
{
  int result; // eax
  char v6[84]; // [esp+Ch] [ebp-2C8h] BYREF
  char *v7; // [esp+60h] [ebp-274h]
  struct _finddata64i32_t FindData; // [esp+64h] [ebp-270h] BYREF
  intptr_t FindHandle; // [esp+190h] [ebp-144h]
  char v10[56]; // [esp+194h] [ebp-140h] BYREF
  char FileName[256]; // [esp+1CCh] [ebp-108h] BYREF
  const char *i; // [esp+2D0h] [ebp-4h]

  *a1 = (const char *)a1;
  a1[1] = (const char *)a1;
  i = nullptr;
  rf_vfile_build_loose_path(a2, a3, FileName);
  result = _findfirst64i32(FileName, &FindData);
  FindHandle = result;
  if ( result != -1 )
  {
    do
    {
      if ( (FindData.attrib & 0x10) == 0 )
      {
        if ( (a4 & 4) != 0 )
        {
          strncpy(&v10[8], FindData.name, 0x27u);
        }
        else
        {
          rf_path_copy_without_last_extension(v6, FindData.name);
          strncpy(&v10[8], v6, 0x27u);
        }
        v10[47] = 0;
        *(_DWORD *)&v10[52] = FindData.time_write;
        *(_DWORD *)&v10[48] = 0;
        if ( (FindData.attrib & 1) != 0 )
          *(_DWORD *)&v10[48] |= 2u;
        if ( (FindData.attrib & 0x20) != 0 )
          *(_DWORD *)&v10[48] |= 4u;
        if ( !a5 || a5(v10) )
        {
          v7 = (char *)operator new(0x38u);
          qmemcpy(v7, v10, 0x38u);
          if ( *a1 != (const char *)a1 && (a4 & 3) != 0 )
          {
            if ( (a4 & 1) != 0 )
            {
              for ( i = *a1; i != (const char *)a1 && _stricmp(i + 8, v7 + 8) < 0; i = *(const char **)i )
                ;
            }
            else
            {
              for ( i = *a1; i != (const char *)a1 && *((_DWORD *)i + 13) >= *((_DWORD *)v7 + 13); i = *(const char **)i )
                ;
            }
            if ( i == (const char *)a1 )
            {
              *((_DWORD *)v7 + 1) = a1[1];
              *(_DWORD *)v7 = a1;
              *(_DWORD *)a1[1] = v7;
              a1[1] = v7;
            }
            else
            {
              **((_DWORD **)i + 1) = v7;
              *((_DWORD *)v7 + 1) = *((_DWORD *)i + 1);
              *((_DWORD *)i + 1) = v7;
              *(_DWORD *)v7 = i;
            }
          }
          else
          {
            *((_DWORD *)v7 + 1) = a1[1];
            *(_DWORD *)v7 = a1;
            *(_DWORD *)a1[1] = v7;
            a1[1] = v7;
          }
        }
      }
    }
    while ( !_findnext64i32(FindHandle, &FindData) );
    return _findclose(FindHandle);
  }
  return result;
}

