// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057CF00 rf_path_stat64i32_adapter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl filename and caller stat output. Directly returns CRT _stat64i32 result. No path building, allocation, status normalization, error translation or output initialization in wrapper.
int __cdecl rf_path_stat64i32_adapter(char *FileName, struct _stat64i32 *Stat)
{
  return _stat64i32(FileName, Stat);
}

