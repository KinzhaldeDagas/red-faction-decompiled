// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0660 rf_client_state_sync_arm_eight_second_timer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg wrapper. Unconditionally call existing4B0640 to arm shared replicator7B25EC for8000ms and preserve delegate EAX. No runtime, peer-state, queue
// or authority admission; no packet send or distinct timer.
int rf_client_state_sync_arm_eight_second_timer()
{
  return rf_replication_timer7B25EC_arm_8s();
}

