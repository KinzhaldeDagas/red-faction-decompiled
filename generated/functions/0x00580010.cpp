// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580010 rf_world_room_packets_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend187CC9C==102 forwards three stack DWORD arguments to verified dynamic-light additive pass. Other backends no action,return backend value;active return incidental from callee,not general success predicate.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Backend187CC9C==102 forwards worldReceiver,roomPointerArray,count to5E7890 complete BASE+DECAL+PROJECTED-LIGHT draw,not just additive lighting. Unsupported backend no draw. Sole observed caller5208DD ignores EAX;callee provides no defined result,signature corrected tovoid. No local state save/restore,capacity checks or geometry work.
void __cdecl rf_world_room_packets_backend_wrapper(void *a1, void *const *a2, int a3)
{
  if ( dword_187CC9C == 102 )
    rf_world_room_packets_draw_base_decals_and_lights(a1, a2, a3);
}

