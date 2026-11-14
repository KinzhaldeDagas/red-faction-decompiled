// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412660 rf_ai_route_pose_members_destroy
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Native void thiscall ECX dual-pose aggregate, no stack args/plainRET; old saved no-argument cdecl integer signature omitted
// actual ECX receiver. Calls4126C0 nav-array member destructor on aggregate+152 first, then aggregate+28. No aggregate deallocation or whole-object memset. MSVC SEH state0->-1 with
// original657ED4 map and622350 tail destroys remaining+28 member when first cleanup unwinds. Return registers incidental; no pointer guards or boolean result.
void __thiscall rf_ai_route_pose_members_destroy(void *self)
{
  rf_nav_node_destroy_array_members((int)self + 152);
  rf_nav_node_destroy_array_members((int)self + 28);
}

