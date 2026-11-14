// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B4D0 rf_level_name_matches_game_mode_prefix
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl(candidateCstring,rawIndex),bool AL. Read pointer661EA8+4*index without index bounds;scan that prefix fully toNUL,then
// _strnicmp(candidate,prefix,prefixLength)==0. Original PE slots0..2 are "dm","ctf","dm"; no delimiter,extension,full-name equality or filename canonicalization. Thus any candidate
// beginning selected prefix matches regardless following bytes. No NULL check on either string or own runtime/mode validation. Adjacent slot3 points "ServerName",not proof of another
// supported mode. Called by rules parser and multiplayer level-list filter45CD00.
bool __cdecl rf_level_name_matches_game_mode_prefix(char *String1, int a2)
{
  return _strnicmp(String1, (&off_661EA8)[a2], strlen((&off_661EA8)[a2])) == 0;
}

