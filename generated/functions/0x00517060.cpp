// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517060 rf_world_resolve_cached_room
// UNREALRED VERIFIED [trigger-airlock-20261022] Cached room resolution retains the prior room unless movement crossing logic requests another owner; with no prior room it falls back to532BA0. Full native cached movement and dynamically rebuilt geometry ownership remain outside the current authored-face airlock adapter.
// UNREALRED VERIFIED [combat-particle-contact-20261104]: No prior room calls532BA0(end). With supplied room, compares start/end squared distance tozero; zero movement or5170E0(world,0,start,end) miss retains supplied room; a crossing reruns532BA0(end). Effect/emitter caller resolves before randomized particle radius offset and copies room to allocation; a point-bounds lookup on each particle is not this contract.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Thiscall world,priorRoom,startXYZ,endXYZ,UNUSEDlastDWORD RET16. Seedlocalresult=priorRoom. IfpriorRoomNULL callcdecl532BA0(world,end) andsaveEAX. Else computeF32squaredDistance(start,end) viahelper;ONLYORDERED>0 then5170E0(world,0,start,end) returningnonzero triggers532BA0(world,end),otherwisekeeppriorRoom. Zero/NaNmovementkeepspriorRoom. LASTstackDWORDunread. ReturnEAXcached/newroompointeronEVERYpath at5170D7,notvoid;noincomingST0parameter. Correctingreturnexposesroomuseat52E70A andothercallers. No pointervalidation, referencecountorcachewrite; onlycalleequeriesmaychangetheirqueryscratch. FouractualstackargsandECXverifiedfromrawcalls/RET16; priorsemanticcommentsretained.
void *__thiscall rf_world_resolve_cached_room(void *this, void *a2, const float *a3, const float *a4, int a5)
{
  void *v7; // [esp+4h] [ebp-4h]

  v7 = a2;
  if ( !a2 || rf_vector_distance_squared(a3, a4) > 0.0 && sub_5170E0((int)this, 0, (float *)a3, (int)a4) )
    return (void *)sub_532BA0((float *)this, (float *)a4);
  return v7;
}

