// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048D4A0 rf_banlist_append_unique_text
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl text Cstring; NULL no-op. Scans sentinel704C5C list for exact case-insensitive text equality; existing spelling/canonical address equivalence is not normalized.
// Allocates32-byte node, safely returns on allocationNULL. Node inline text starts0, nextDWORD24,prevDWORD28. Initializes self links, copies entire source including NUL WITHOUT
// length bound, then appends tail via old704C78 and sentinel. More than23 visible characters can overwrite link storage; caller loader separately filters<=23 but this routine itself
// performs no validation/length cap. No pattern matching for duplicate suppression, disk export or network action.
void __cdecl rf_banlist_append_unique_text(char *String1)
{
  char v1; // dl
  _BYTE *v2; // [esp+8h] [ebp-14h]
  char *v3; // [esp+Ch] [ebp-10h]
  char *String2; // [esp+14h] [ebp-8h]
  _DWORD *v5; // [esp+18h] [ebp-4h]

  if ( String1 )
  {
    for ( String2 = (char *)unk_704C74; String2 != (char *)&unk_704C5C; String2 = *((char **)String2 + 6) )
    {
      if ( !_stricmp(String1, String2) )
        return;
    }
    v5 = operator new(0x20u);
    if ( v5 )
    {
      v5[6] = v5;
      v5[7] = v5;
      v3 = String1;
      v2 = v5;
      do
      {
        v1 = *v3;
        *v2++ = *v3++;
      }
      while ( v1 );
      v5[7] = unk_704C78;
      v5[6] = &unk_704C5C;
      *(_DWORD *)(unk_704C78 + 24) = v5;
      unk_704C78 = v5;
    }
  }
}

