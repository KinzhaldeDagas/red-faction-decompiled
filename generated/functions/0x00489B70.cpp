// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00489B70 rf_mover_debug_draw_all
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl no arguments. Traverses common mover sentinel704610 from first70489C, calling debug_draw_keys for each record in linked order and advancing nextDWORD652. Stops only at
// sentinel; empty list makes no draw call. No per-object visibility/enable filter, NULL/cycle protection or list snapshot; follows next after drawing. Does not traverse separate
// moving-solid sentinel704940. EAX incidental, not mover count.
int rf_mover_debug_draw_all()
{
  int result; // eax
  _DWORD *i; // [esp+0h] [ebp-4h]

  result = unk_70489C;
  for ( i = (_DWORD *)unk_70489C; i != (_DWORD *)&unk_704610; i = (_DWORD *)i[163] )
    result = rf_mover_debug_draw_keys(i);
  return result;
}

