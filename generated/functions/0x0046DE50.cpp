// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046DE50 rf_persona_history_remaining_layout_height
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): No-argument signed height sum for history viewoffset6F899C. Starts entry index=newestIndex-viewoffset; loops i=viewoffset while i<fresh historyCount. Before lookup any
// negative index is replaced with EXACT79 (not index+80), then index decrements after each entry. Null entry returns-1 immediately; otherwise adds MOVSX signed WORD entry+0x106.
// Empty loop returns0. No offset normalization, positive-count precondition, height clamp or overflow handling.
int rf_persona_history_remaining_layout_height()
{
  int v1; // [esp+0h] [ebp-10h]
  rf_persona_history_entry *v2; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]
  int index; // [esp+Ch] [ebp-4h]

  v1 = 0;
  index = rf_persona_history_get_newest_index() - unk_6F899C;
  for ( i = unk_6F899C; i < rf_persona_history_get_count(); ++i )
  {
    if ( index < 0 )
      index = 79;
    v2 = rf_persona_history_entry_at(index);
    if ( !v2 )
      return -1;
    v1 += v2->layout_height;
    --index;
  }
  return v1;
}

