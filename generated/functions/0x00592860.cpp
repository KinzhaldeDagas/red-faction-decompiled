// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592860 rf_vfile_loose_lookup_prepend_node_return_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Cdecl name and root id. Allocates12-byte node, hashes raw case-sensitive name592660, prepends node to bucket1BA1F00 BEFORE duplicating string; node rootId+0,ownedName+4,next+8. _strdup result stored+4 and returned in EAX, NOT node pointer. No duplicate detection, allocation checks or root validation. Failed strdup leaves a published node with NULL name; destruction592920 separately frees name/node. Does not increment auxiliary counter1BA1EF8.
char *__cdecl rf_vfile_loose_lookup_prepend_node_return_name(char *Source, int a2)
{
  int v2; // eax
  char *result; // eax
  _DWORD *v4; // [esp+4h] [ebp-8h]

  v4 = operator new(0xCu);
  v2 = rf_vfile_loose_name_hash15(Source);
  v4[2] = dword_1BA1F00[v2];
  dword_1BA1F00[v2] = (int)v4;
  *v4 = a2;
  result = _strdup(Source);
  v4[1] = result;
  return result;
}

