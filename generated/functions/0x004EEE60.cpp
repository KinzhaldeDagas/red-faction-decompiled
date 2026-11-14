// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EEE60 rf_fplegs_destroy_model
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Recovered original19-byte closed function4EEE60..4EEE73; no current code callers. Calls model destroy adapter on global663038, pops one argument, returns void. Does not clear model handle, animation handles or transition state and has no own NULL guard.
void __cdecl rf_fplegs_destroy_model()
{
  rf_model_handle_destroy_cdecl_adapter((_DWORD *)dword_663038);
}

