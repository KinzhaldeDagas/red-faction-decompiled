// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4920 rf_object_find_by_uid
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): cdecl signed32 UID. EXACT-1 returnsNULL. Otherwise indexes DWORD map7B1538 by LOW16 UID, reads handle; handle EXACT-1
// returnsNULL, else object_resolve_handle(handle). Ignores high16 bits except the initial full-DWORD-1 sentinel; no map-index limit or generation/full-UID comparison in own body.
// Initializer4A8330 clears only1024 map DWORDs, while lookup admits all65536 low16 indices; do not infer a safe65536-entry initialized map from the mask. Final live-handle admission
// belongs to resolver. No map write, allocation or network role gate.
int __cdecl rf_object_find_by_uid(int a1)
{
  int v2; // [esp+4h] [ebp-4h]

  if ( a1 == -1 )
    return 0;
  v2 = unk_7B1538[(unsigned __int16)a1];
  if ( v2 == -1 )
    return 0;
  else
    return rf_object_resolve_handle(v2);
}

