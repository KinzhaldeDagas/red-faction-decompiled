// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00568F70 rf_sound_update_listener_and_instances_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl three stack arguments forwarded unchanged to568D20 listener/instance update,then plainRET; no additional policy,state writes or success result. Does not interpret an ECX receiver.
// UNREALRED VERIFIED (2026-11-11; native split-caller and complete wrapper ABI refinement): Existing verified3-argument ABI confirmed from complete native body: forwards only
// stack+4/+8/+12 to568D20 then RET. Split caller4AE550 pushes six words and cleans24 bytes: first pos/zeroVelocity/matrix followed by second pos/zeroVelocity/matrix. This wrapper
// ignores trailing three words; no dual-listener mixing or second-camera read in wrapper. Keep correct3-argument prototype; caller extra arguments alone do not justify six-argument
// retyping.
void __cdecl rf_sound_update_listener_and_instances_adapter(float *a1, float *a2, float *a3)
{
  rf_sound_update_listener_and_instances(a1, a2, a3);
}

