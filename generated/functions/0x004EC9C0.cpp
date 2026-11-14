// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EC9C0 rf_fpgun_player_weapon_hook_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Five-byte empty cdecl hook: push ebp; mov ebp,esp; pop ebp; ret. Native death-transition caller pushes player and weapon ID and pops eight bytes. Both arguments are unused; no side effects or initialized return value.
void __cdecl rf_fpgun_player_weapon_hook_noop(int unused_player, int unused_weapon)
{
  ;
}

