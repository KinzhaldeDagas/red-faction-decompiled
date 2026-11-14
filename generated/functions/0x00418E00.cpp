// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00418E00 rf_disabled_physical_debris_legacy_factory_return_zero
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Normal entry installs transient SEH, executes XOR EAX,EAX at0x418E28, then unconditional JMP0x4190C2 and restores SEH/frame before plain RET. Always returns0 with no allocation, solid ownership change, list insertion or application global mutation. Large legacy construction body remains in existing chunks but is unreachable from normal entry; do not infer effects or argument ABI from that dead body.
int rf_disabled_physical_debris_legacy_factory_return_zero()
{
  return 0;
}

