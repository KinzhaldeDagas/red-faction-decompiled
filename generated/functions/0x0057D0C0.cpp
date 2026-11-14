// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D0C0 rf_path_change_drive_bool
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl CRT numeric drive (A=1 etc). Calls _chdrive, returns ALtrue iff result0. No range validation, drive-letter conversion or current-directory restoration here.
bool __cdecl rf_path_change_drive_bool(int Drive)
{
  return _chdrive(Drive) == 0;
}

