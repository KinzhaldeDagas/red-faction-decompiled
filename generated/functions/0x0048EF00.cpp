// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048EF00 rf_multiplayer_character_caches_release
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl no arguments. Signed-loop i<multiplayer_character_count. For each pointer704BE0[i],native calls character_cache_release_record_wrapper(pointer,EXTRA stack0),cleans8; verified
// wrapper reads only first argument and delegates full resource release. Then clears slotNULL. No slotNULL guard,duplicate pointer suppression or count reset; cache release semantics
// delegated. Count<=0 makes no calls/clears and EAX is incidental; normal positive loop EAX=count. Called by multiplayer runtime teardown.
int rf_multiplayer_character_caches_release()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_multiplayer_character_count; ++i )
  {
    rf_character_cache_release_record_wrapper(unk_704BE0[i]);
    unk_704BE0[i] = 0;
    result = i + 1;
  }
  return result;
}

