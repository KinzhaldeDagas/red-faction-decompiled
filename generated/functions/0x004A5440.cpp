// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A5440 rf_multiplayer_left_game_reason_text
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(raw BYTE reason), returns borrowed C-string pointer. Default88E1F8 unknown;2=>88E1FC kicked,4=>88E200 incompatible,5=>88E1D4 between levels,6=>88E220 timeout,7=>literal You
// do not have selected level. Other bytes including1/3 default; native MOVZX means values128..255 are unsigned. Case7 takes literal branch unconditionally rather than localization
// fallback88D434. No mode/authority guard or allocation; jump-table bytes verified.
const char *__cdecl rf_multiplayer_left_game_reason_text(char a1)
{
  const char *v2; // [esp+1Ch] [ebp-4h]

  v2 = (const char *)unk_88E1F8;
  switch ( a1 )
  {
    case 2:
      v2 = (const char *)unk_88E1FC;
      break;
    case 4:
      v2 = (const char *)unk_88E200;
      break;
    case 5:
      v2 = (const char *)unk_88E1D4;
      break;
    case 6:
      v2 = (const char *)unk_88E220;
      break;
    case 7:
      v2 = "You do not have the level the server has selected.";
      break;
    default:
      return v2;
  }
  return v2;
}

