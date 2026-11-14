// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E4C30 rf_vehicle_cockpit_reset_shared_animation_latch
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): No-argument void body clears ONLY global BYTE87C6B4, then returns without initialized EAX. Used from local-player startup/reset loops to permit another fixed0.25 animation advance in jeep seat0. No camera node, material/model, per-player or VFX-instance clearing.
void rf_vehicle_cockpit_reset_shared_animation_latch()
{
  unk_87C6B4 = 0;
}

