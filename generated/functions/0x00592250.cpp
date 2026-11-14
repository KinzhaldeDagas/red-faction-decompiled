// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592250 rf_vfile_optical_path_stat_adapter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Cdecl filename and stat output. Directly returns CRT _stat64i32 result without translating status, allocating output or changing path. Used by optical-media path resolver592270, distinct duplicate wrapper from57CF00.
int __cdecl rf_vfile_optical_path_stat_adapter(char *FileName, struct _stat64i32 *Stat)
{
  return _stat64i32(FileName, Stat);
}

