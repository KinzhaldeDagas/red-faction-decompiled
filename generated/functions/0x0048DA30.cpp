// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048DA30 rf_banlist_export_and_destroy_nodes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl no arguments. Invokes banlist_export_text_file BEFORE deletion and ignores export result. Iterates nodes from704C74 to sentinel704C5C,saves next24 BEFORE unlink/free. Repairs
// prev.next/next.prev,zeros own24/28,raw operator-deletes node,advances saved next. Empty list still exports. Does not free static sentinel, alter unrelated multiplayer state or
// retain nodes on export failure. Ordinary well-formed drain restores sentinel self-links through unlink operations; no explicit list-corruption guard. Return EAX is final
// sentinel.next artifact,not Boolean/export status.
int rf_banlist_export_and_destroy_nodes()
{
  int result; // eax
  int i; // [esp+4h] [ebp-8h]
  int v2; // [esp+8h] [ebp-4h]

  rf_banlist_export_text_file();
  for ( i = unk_704C74; ; i = v2 )
  {
    result = *(_DWORD *)(i + 24);
    v2 = result;
    if ( (_UNKNOWN *)i == &unk_704C5C )
      break;
    *(_DWORD *)(*(_DWORD *)(i + 28) + 24) = *(_DWORD *)(i + 24);
    *(_DWORD *)(*(_DWORD *)(i + 24) + 28) = *(_DWORD *)(i + 28);
    *(_DWORD *)(i + 24) = 0;
    *(_DWORD *)(i + 28) = 0;
    operator delete((void *)i);
  }
  return result;
}

