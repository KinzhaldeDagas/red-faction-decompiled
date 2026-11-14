// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEED0 rf_splitscreen_assign_level_and_start_parameter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Cdecl(levelName C-string,parameter DWORD). Store raw parameter to global7B25D4 BEFORE constructing two owned8-byte RFStrings: level from input, save-name from
// original verified empty NUL63B455. Pass16 bytes byvalue to level_transition_assign_level_and_save_strings, caller ADD ESP16; delegate owns values, SEH cleans partially built
// temporary on failure. No level validation, NULL input check, runtime/mode gate, actual load/panel request or split-count mutation in this routine. Global parameter is not rolled
// back on construction/transition failure; its broader numeric meaning is not established here.
void __cdecl rf_splitscreen_assign_level_and_start_parameter(char *Source, int a2)
{
  int v2[2]; // [esp-8h] [ebp-34h] BYREF
  int v3[5]; // [esp+0h] [ebp-2Ch] BYREF
  _DWORD *v4; // [esp+14h] [ebp-18h]
  int *v5; // [esp+18h] [ebp-14h]
  void *v6; // [esp+1Ch] [ebp-10h]
  int v7; // [esp+28h] [ebp-4h]

  unk_7B25D4 = a2;
  v6 = v3;
  v4 = rf_string_construct_from_cstr(v3, (char *)byte_63B455);
  v3[4] = (int)v4;
  v7 = 0;
  v5 = v2;
  v3[3] = (int)rf_string_construct_from_cstr(v2, Source);
  v7 = -1;
  rf_level_transition_assign_level_and_save_strings(v2[0], (char *)v2[1], v3[0], (char *)v3[1]);
}

