// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057C350 rf_vfile_unregister_root_pointers_only
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, filename/drive helpers, directory error paths, intrusive enumeration lists, VFile construction/unlink and15-bit hash arithmetic): Cdecl signed root id. Clears root and extension pointers at1897490+12*id and1897494+12*id, returns byte offset12*id in EAX. Does not free interned strings, remove existing loose-lookup nodes or clear per-root flags at+8. No id range/negative/special-id validation. Clearing an intermediate id also affects collector57CB70, which stops at first invalid root rather than skipping holes.
int __cdecl rf_vfile_unregister_root_pointers_only(int root_id)
{
  dword_1897490[3 * root_id] = 0;
  dword_1897494[3 * root_id] = 0;
  return 12 * root_id;
}

