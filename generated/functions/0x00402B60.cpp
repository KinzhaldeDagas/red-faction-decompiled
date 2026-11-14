// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402B60 rf_ai_seek_any_waypoint_list
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): False CRT __fputchar_1/library identification corrected: one cdecl AI block forwarded
// to402950(block,ADDRESS630F75). Original byte at630F75 isNUL, so request is EMPTY STRING; prefix predicate admits every named waypoint list, including unrelated categories; delegate
// still collects at most32 matches. Exactly two stack args and8-byte cleanup. No direct inventory change/guard or independent result; EAX incidental void-delegate value. Do not
// invent an item category for padding bytes after literal ammo.
int __cdecl rf_ai_seek_any_waypoint_list(int Character)
{
  int result; // eax

  sub_402950((int *)Character, (char *)byte_630F75);
  return result;
}

