// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BBF50 sub_4BBF50
// UNREALRED VERIFIED [trigger-use-20261021] Writes incoming friendliness code to common+0x1F8 and invalidates target handle+0x560. This writer and RFL loader4811C0 establish the semantic identity of the field compared against1/2 by auto Use admission40DB70.
// UNREALRED VERIFIED [ai-script-target-clear-20261029] Set_Friendliness writes common+0x1F8, then for entity type directly stores -1 at entity+0x560 (AI+0x2C0). It does not call40BA80 and does not apply that setter owner/player-only guards. Keep this forced invalidation distinct from guarded Goto clear requests.
BOOL __cdecl sub_4BBF50(int a1, int a2)
{
  BOOL result; // eax

  *(_DWORD *)(a1 + 504) = a2;
  result = rf_object_is_entity(a1);
  if ( result )
    *(_DWORD *)(a1 + 1376) = -1;
  return result;
}

