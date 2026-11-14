// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B1240 rf_multiplayer_game_flag200_is_set
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. Test global ruleflags mask200; return normalized bool in AL only (upperEAX retains masked value). No runtime/authority/mode admission, mutation
// or semantic flag-name inference beyond mask.
bool rf_multiplayer_game_flag200_is_set()
{
  return (rf_multiplayer_game_flags & 0x200) != 0;
}

