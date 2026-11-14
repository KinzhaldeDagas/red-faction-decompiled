// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6190 rf_exception_report_list_modules
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Writes the module-list header, queries page size, and walks virtual addresses using page indices up to 4*(0x40000000/pageSize). Advances by RegionSize/pageSize after successful nonempty VirtualQuery, or 0x10000/pageSize on failure/zero region. For committed regions (MEM_COMMIT=0x1000), reports an AllocationBase only when greater than the last reported base, avoiding repeated regions of a module. Calls the per-module writer, which rejects non-PE mappings. Returned loop index is incidental. Uses original 32-bit address/page arithmetic.
unsigned int __cdecl rf_exception_report_list_modules(HANDLE hFile)
{
  unsigned int result; // eax
  struct _MEMORY_BASIC_INFORMATION Buffer; // [esp+0h] [ebp-50h] BYREF
  HMODULE hModule; // [esp+1Ch] [ebp-34h]
  DWORD dwPageSize; // [esp+20h] [ebp-30h]
  unsigned int v5; // [esp+24h] [ebp-2Ch]
  struct _SYSTEM_INFO SystemInfo; // [esp+28h] [ebp-28h] BYREF
  DWORD v7; // [esp+4Ch] [ebp-4h]

  rf_exception_report_writef(hFile, "\r\n\tModule list: names, addresses, sizes, time stamps and file times:\r\n");
  GetSystemInfo(&SystemInfo);
  dwPageSize = SystemInfo.dwPageSize;
  v7 = 4 * (0x40000000 / SystemInfo.dwPageSize);
  v5 = 0;
  hModule = nullptr;
  while ( 1 )
  {
    result = v5;
    if ( v5 >= v7 )
      break;
    if ( VirtualQuery((LPCVOID)(dwPageSize * v5), &Buffer, 0x1Cu) )
    {
      if ( Buffer.RegionSize )
      {
        v5 += Buffer.RegionSize / dwPageSize;
        if ( Buffer.State == 4096 && Buffer.AllocationBase > hModule )
        {
          hModule = (HMODULE)Buffer.AllocationBase;
          rf_exception_report_write_module(hFile, (HMODULE)Buffer.AllocationBase);
        }
      }
      else
      {
        v5 += 0x10000 / dwPageSize;
      }
    }
    else
    {
      v5 += 0x10000 / dwPageSize;
    }
  }
  return result;
}

