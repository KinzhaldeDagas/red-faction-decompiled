// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00592830 rf_vfile_loose_lookup_find_or_insert_mixed_return
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Cdecl name and root id. Existing exact-case name5925C0 returns NODE pointer and leaves original root id unchanged (first registered duplicate wins). Missing name delegates insertion592860, whose EAX is duplicated NAME pointer rather than node. Thus return has branch-dependent meaning, not uniform node handle/status. No lowercase conversion; enumeration592700 lowercases before calling. Does not validate root id or update auxiliary registration count here.
char *__cdecl rf_vfile_loose_lookup_find_or_insert_mixed_return(char *Source, int a2)
{
  char *result; // eax

  result = (char *)rf_vfile_loose_lookup_find_exact_name_node(Source);
  if ( !result )
    return rf_vfile_loose_lookup_prepend_node_return_name(Source, a2);
  return result;
}

