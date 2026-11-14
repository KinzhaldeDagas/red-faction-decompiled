// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043D030 rf_entity_info_destroy_owned_strings
// [UnrealRed physical spheres 2026-11-12; verified ASM] EntityInfo class-definition destructor used by62EB90 atexit vector destructor75*1514; cachearray wrappers CEC/E30 and sourceB68 use no-op shared destructors. Lifetime of definitions is distinct from rendered model wrappers/individual body/audio owner.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall ECX required EntityInfo receiver, no stack arguments, void; TWO native chunks total811 bytes
// including EH cleanup thunks. Normal destruction order: RFString5068; fixed10 records at3968, stride108, through6066BD reverse indices9..0 and416DB0 callback; no-op member
// destructors3632,3308,2920; RFString1860; no-op members1840,1804,1728,1692,1656,496,480,468,456,444; then RFStrings260,56,48,32,24,16,8,0. Skin callback destroys ALL12 strings
// atrecord+12+8*i in reverse, then name0, irrespective active count; class profile count3964 is not consulted. String destruction releases owned buffers/clears pointer while
// retaining extent; no-op members do not free/reset their array counts/storage. No containing EntityInfo allocation delete, count/capacity gate or model/body/audio teardown. Main
// body installs FS exception frame and updates state22 down to-1. PE-backed unwind map658980 has23 entries(nextState=i-1, action): state0..7 strings0,8,16,24,32,48,56,260;
// states8..17 corresponding no-op offsets444,456,468,480,496,1656,1692,1728,1804,1840; state18 string1860; states19..21 no-ops2920,3308,3632; state22 same10-record skin destructor.
// Tail chunk622EF0..62303F implements these thunks, array cleanup, cookie check and CxxFrameHandler3 dispatcher, not an extra normal fall-through path. Array iterator handles
// remaining reverse cleanup on exception; already-processed members are not rolled back. Existing definition-lifetime comment retained.
void __thiscall rf_entity_info_destroy_owned_strings(char *this)
{
  rf_string_destroy_buffer(this + 5068);
  `eh vector destructor iterator'(
    this + 3968,
    0x6Cu,
    10,
    (void (__thiscall *)(void *))rf_clutter_skin108_destroy_strings);
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_string_destroy_buffer(this + 1860);
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_shared_noop_destructor_4580d0();
  rf_string_destroy_buffer(this + 260);
  rf_string_destroy_buffer(this + 56);
  rf_string_destroy_buffer(this + 48);
  rf_string_destroy_buffer(this + 32);
  rf_string_destroy_buffer(this + 24);
  rf_string_destroy_buffer(this + 16);
  rf_string_destroy_buffer(this + 8);
  rf_string_destroy_buffer(this);
}

