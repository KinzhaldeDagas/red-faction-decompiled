// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A2A0 sub_40A2A0
// UNREALRED VERIFIED [ai-authored-startup-20261028] Restores saved mode/secondary via native writers. If saved mode is 4 and saved list AI+0x4A8 is -1, writes mode 2 and returns WITHOUT a secondary-state write. If saved mode is 4 with a list, calls 0x434070 using saved list name and flags AI+0x4AC; -1 return leaves current mode/secondary unchanged. Successful admission or any non-4 saved mode writes saved mode then saved secondary. Subsequent class-bit-dependent random idle deadline is separate. Missing list is not a failed route to an existing list.
// UNREALRED VERIFIED [ai-goto-completion-20261028] For reuse after Goto arrival, caller0x409950 has already written secondary0 and reset the route. Saved mode4 with missing list only overwrites current mode2; it must preserve that secondary0. A saved existing-list route failure leaves both current fields unchanged; route-free adapters must report pending/incomplete instead of claiming restored mode4.
// UNREALRED VERIFIED [combat-reaction-20261111]: Saved-state restoration is ordered and partial: savedmode4/list-1 writes mode2 only; an existing list calls434070 and returns on-1 without saved mode/secondary writes (434070 itself has prefix state writes). Other/admitted states write savedmode then savedsecondary. Class+724 bit800000/currentmode2/random>0.5 optional AI+41C deadline remains separate.
// UNREALRED VERIFIED [combat-reaction-target-wait-20261111]: Timer ownership clarification: AI+41C is EMBEDDED ROUTE+134 because route startsAI+2E8. The ambient/currentmode2/unitRandom>0.5 branch arms this shared route wait deadline inclusive[0,2000]; it is NOT Entity+138C idle-animation variation. Do not map it onto a host idle animation cooldown.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] After saved-state restore, ambient class AND restored currentmode2 samples567730; draw>0.5 arms route+134/AI+41C inclusive0..2000ms via55EFF0 (second shared draw). Strict >0.5; no draw if class/mode predicate false. Current-mode writer and saved-state ownership remain distinct. Host unrepresented route-wait timer must stay explicit after represented mode/predicate prefixes.
// UNREALRED VERIFIED [combat-native-ai-wait-correction-20261111] Corrected only our immediately preceding ambient route wait range transcription using40A37A push7D0 and40A37F push0: inclusive0..2000ms. Existing earlier verified native comment already had correct bounds. No production consumer used the erroneous text.
void __cdecl sub_40A2A0(int *a1)
{
  char *v1; // eax
  int v2; // [esp-4h] [ebp-4h]

  if ( a1[161] != 4 )
    goto LABEL_5;
  if ( a1[298] == -1 )
  {
    rf_ai_numeric_mode_write(a1, 2, -1, -1);
    return;
  }
  v2 = a1[299];
  v1 = (char *)rf_string_object_c_str_or_empty(&unk_700480[131 * a1[298]]);
  if ( sub_434070(*(_DWORD *)(*a1 + 44), v1, v2) != -1 )
  {
LABEL_5:
    rf_ai_numeric_mode_write(a1, a1[161], -1, -1);
    rf_ai_secondary_state_write((int)a1, a1[174]);
    if ( ((unsigned int)&unk_800000 & *(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1828)) != 0
      && a1[160] == 2
      && sub_567730() > 0.5 )
    {
      rf_timestamp_arm_random_inclusive_milliseconds(a1 + 263, 0, 2000);
    }
  }
}

