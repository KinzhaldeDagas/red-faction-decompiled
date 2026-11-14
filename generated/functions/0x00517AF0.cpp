// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517AF0 rf_liquid_room_contains_point
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall room,point3f pointer,RET4. ReturnAL0 immediately if roomBYTE388==0 without touching point. Else compare point.Y4 <= room.minY12+liquidDepth392; sum stays in x87 without intermediate F32 store. Ordered equality admitted,unorderedNaN rejected(TEST AH41/JP). No X/Z bounds,room/portal containment,positive depth,liquid material,collision eligibility or enabled valueEXACT1 check: any nonzero enableBYTE passes and depth may be0/negative. Does not transform coordinates or write room/point.
bool __thiscall rf_liquid_room_contains_point(int this, int a2)
{
  return *(_BYTE *)(this + 388) && *(float *)(a2 + 4) <= *(float *)(this + 12) + *(float *)(this + 392);
}

