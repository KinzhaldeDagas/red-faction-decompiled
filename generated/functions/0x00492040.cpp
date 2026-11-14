// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00492040 rf_scoreboard_build_sorted_player_snapshots
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl(destination block,source circular player head,signed count),returns destination COPY corresponding to local player orNULL. Count<1 returnsNULL without touching destination.
// Otherwise initializes destination next0/prev4 as sentinel; first copied player atdest+4612,subsequent physical slots dest+4612*(i+1). Uses runtime-state ASSIGNMENT4953A0,so
// destination embedded RFStrings must already be constructed; no allocation or constructor here. Relinks only copied next/prev.
// Insertion-sort list descending by SIGNED WORD at[playerDWORD44]+2. New score<existing advances; equality stops and inserts BEFORE existing,so ties reverse source order. Uses shared
// score pointer copied44,not an independent score value snapshot. Assumes source list/count consistent; after wrapping source next becomesNULL but loop still trusts count and can
// dereferenceNULL. No destination capacity,count cap,sourceNULL,score-pointer guard or sort of source records themselves. Tracks local-player copy by source-pointer
// equality,returnsNULL if absent. Net4608 and other pointer fields remain shallow copies; nested RFStrings use assignment.
int ***__cdecl rf_scoreboard_build_sorted_player_snapshots(int ***a1, _DWORD *a2, int a3)
{
  _DWORD *v4; // [esp+0h] [ebp-24h]
  _DWORD *v5; // [esp+4h] [ebp-20h]
  int j; // [esp+8h] [ebp-1Ch]
  int ***v7; // [esp+Ch] [ebp-18h]
  int v8; // [esp+14h] [ebp-10h]
  _DWORD *v9; // [esp+18h] [ebp-Ch]
  int i; // [esp+1Ch] [ebp-8h]
  int *v11; // [esp+20h] [ebp-4h]
  int *v12; // [esp+20h] [ebp-4h]

  if ( a3 < 1 )
    return nullptr;
  v8 = 1;
  v7 = nullptr;
  *a1 = (int **)a1;
  a1[1] = (int **)a1;
  v11 = (int *)(a1 + 1153);
  rf_player_copy_runtime_state(a1 + 1153, (int)a2);
  if ( a2 == (_DWORD *)rf_local_fpgun_player )
    v7 = a1 + 1153;
  *v11 = (int)*a1;
  (*a1)[1] = v11;
  *a1 = (int **)v11;
  a1[1154] = (int **)a1;
  if ( (_DWORD *)*a2 == a2 )
    v5 = nullptr;
  else
    v5 = (_DWORD *)*a2;
  v9 = v5;
  for ( i = 1; i < a3; ++i )
  {
    v12 = (int *)*a1;
    for ( j = 0; j < v8 && *(__int16 *)(v9[11] + 2) < *(__int16 *)(v12[11] + 2); ++j )
      v12 = (int *)*v12;
    rf_player_copy_runtime_state(&a1[1153 * i + 1153], (int)v9);
    *(_DWORD *)v12[1] = &a1[1153 * i + 1153];
    a1[1153 * i + 1154] = (int **)v12[1];
    v12[1] = (int)&a1[1153 * i + 1153];
    a1[1153 * i + 1153] = (int **)v12;
    if ( v9 == (_DWORD *)rf_local_fpgun_player )
      v7 = &a1[1153 * i + 1153];
    if ( (_DWORD *)*v9 == a2 )
      v4 = nullptr;
    else
      v4 = (_DWORD *)*v9;
    v9 = v4;
    ++v8;
  }
  return v7;
}

