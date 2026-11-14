// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B5420 rf_replication_collect_all_remote_sample_ids
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(outIDBytes,outSampleWords). First walks circular player list counting nonlocal entries with resolved entity; caps returned signed count to32
// AFTER traversal. Second independently walks ALL qualifying nonlocal players and writes net BYTE20 plus motion-buffer WORD1324 into supplied parallel arrays using uncapped counter.
// No loop bound tied to capped count, net/buffer null checks, state/team/death/range filtering or output capacity. Returns capped FIRST-pass count, not actual second-pass writes;
// list changes between passes not reconciled. Caller4A8390 stores return into local motion-buffer count2300.
int __cdecl rf_replication_collect_all_remote_sample_ids(int a1, int a2)
{
  _DWORD *v3; // [esp+0h] [ebp-1Ch]
  _DWORD *v4; // [esp+4h] [ebp-18h]
  int v5; // [esp+8h] [ebp-14h]
  int v6; // [esp+10h] [ebp-Ch]
  _DWORD *i; // [esp+14h] [ebp-8h]
  _DWORD *j; // [esp+14h] [ebp-8h]
  int v9; // [esp+18h] [ebp-4h]

  v9 = 0;
  for ( i = (_DWORD *)dword_87C324; i; i = v4 )
  {
    if ( i != (_DWORD *)rf_local_fpgun_player && rf_entity_resolve_handle(i[5]) )
      ++v9;
    if ( *i == dword_87C324 )
      v4 = nullptr;
    else
      v4 = (_DWORD *)*i;
  }
  if ( v9 > 32 )
    v9 = 32;
  v6 = 0;
  for ( j = (_DWORD *)dword_87C324; j; j = v3 )
  {
    if ( j != (_DWORD *)rf_local_fpgun_player )
    {
      v5 = rf_entity_resolve_handle(j[5]);
      if ( v5 )
      {
        *(_BYTE *)(v6 + a1) = *(_BYTE *)(j[1152] + 20);
        *(_WORD *)(a2 + 2 * v6++) = *(_WORD *)(*(_DWORD *)(v5 + 632) + 1324);
      }
    }
    if ( *j == dword_87C324 )
      v3 = nullptr;
    else
      v3 = (_DWORD *)*j;
  }
  return v9;
}

