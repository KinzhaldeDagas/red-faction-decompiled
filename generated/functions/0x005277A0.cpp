// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005277A0 rf_renderer_light_release
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl handle,modeBYTE void. Resolve unchecked, decrement record signed DWORD88 (native wrap); if result<=0 increment serial, call coverage(record,rawmode) iff categoryBYTE77 nonzero OR mode==EXACT1. Then set type8=0, splice prev.next/next.prev, clear record next/prev, decrement renderer object count. Counter>0 retains record with no serial increment/coverage. ALWAYS invalidate active list afterward, even when retained. Mode2 withcategory0 skips coverage (not any-nonzero test), though categorynonzero forwards any mode. No handle/type/double-release guard or heap delete; payload and category remain. Constructors here start counter0, first release yields-1 and removes.
void __cdecl rf_renderer_light_release(int a1, char a2)
{
  int *v2; // [esp+0h] [ebp-4h]

  v2 = rf_renderer_light_resolve_handle(a1);
  if ( --v2[22] <= 0 )
  {
    ++rf_renderer_light_change_serial;
    if ( *((_BYTE *)v2 + 77) || a2 == 1 )
      rf_light_refresh_receiver_coverage((int)v2, a2);
    v2[2] = 0;
    *(_DWORD *)v2[1] = *v2;
    *(_DWORD *)(*v2 + 4) = v2[1];
    *v2 = 0;
    v2[1] = 0;
    --rf_renderer_object_count;
  }
  rf_light_invalidate_active_world_list();
}

