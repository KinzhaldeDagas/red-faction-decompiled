// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C850 rf_vfile_group_access_level_decrement_and_format_notice
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl no args. Decrements global DWORD189CE94, sprintf formats Group file access lowered to level %d. plus LF into shared buffer18CD828, returns formatter character count. No lower bound or matching-increment requirement, no print/send here and no file access checks in this body.
int __cdecl rf_vfile_group_access_level_decrement_and_format_notice()
{
  return sprintf(&unk_18CD828, "Group file access lowered to level %d.\n", --dword_189CE94);
}

