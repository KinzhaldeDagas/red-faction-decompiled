// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EC9D0 rf_fpgun_cancel_transition_hook_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Five-byte empty cdecl hook. Both native callers push one player pointer and pop four bytes. The callers perform the pending-transition cleanup themselves; this hook reads neither argument nor state and has no initialized return value.
void __cdecl rf_fpgun_cancel_transition_hook_noop(int unused_player)
{
  ;
}

