// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049BBF0 sub_49BBF0
// UNREALRED VERIFIED [lan-killfeed-20261028] Validates selected multiplayer character index against rf_multiplayer_character_count; lazily resolves entities.tbl definition name "multi_female" with0x431680, then compares that index to pc_multi.tbl record+8 (stride0x140), populated by $EntityAnimType:. This pronoun choice is not an entities.tbl gender flag or the $EntityType: record+4 field. Invalid selected index returns false.
bool __cdecl sub_49BBF0(int a1)
{
  if ( a1 < 0 || a1 >= rf_multiplayer_character_count )
    return 0;
  if ( dword_662910 == -1 )
    dword_662910 = sub_431680("multi_female");
  return unk_77D768[80 * a1] == dword_662910;
}

