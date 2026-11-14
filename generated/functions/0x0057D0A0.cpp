// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D0A0 rf_path_get_current_directory_adapter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl destination and signed size. Direct CRT _getcwd(destination,size) adapter, returns its pointer/NULL result. Does not allocate its own scratch, normalize path or force termination on failure.
char *__cdecl rf_path_get_current_directory_adapter(char *destination, int size)
{
  return _getcwd(destination, size);
}

