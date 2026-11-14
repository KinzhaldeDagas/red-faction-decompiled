// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049E4A0 rf_multiplayer_hud_update_target_notice
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): cdecl(candidate player orNULL). Uses shared RFString77FE58, showBYTE77FE4D, transitionBYTE77FE4E, directionBYTE66291B, teamDWORD77FE54,
// acquire deadline77FF18 and loss deadline77FE6C. Candidate with empty stored name: copies player RFString+8, arms acquire100ms, clears show; does NOT update team in this branch.
// Same case-insensitive name: acquire elapsed any nonzero ->show1,transition1,direction1,team=zeroextended player BYTE48; otherwise show0. Different name while transition!=0 does
// nothing. Otherwise if !show OR direction!=0, replaces name/arms100/show0/updates team; show!=0 AND direction0 instead starts transition1 without replacing name. NULL candidate
// during transition does nothing. Else arm loss300ms if unarmed; if show!=0, elapsed ->transition1, not elapsed ->show0. If show0, empties name and resets acquire, but does not reset
// loss timer. Native bytes49E511..523 have no ordinary entry-flow predecessor and are not used to invent a further normal branch. No team filtering, alpha mutation, player lifetime
// retention or normalized status return.
int __cdecl rf_multiplayer_hud_update_target_notice(int a1)
{
  int result; // eax

  if ( a1 )
  {
    if ( rf_string_equals_case_insensitive((int)dword_77FE58, (char *)&byte_63A406) )
    {
      rf_string_assign_from_object(dword_77FE58, a1 + 8);
      result = rf_replicator_arm_milliseconds(dword_77FF18, 100);
      unk_77FE4D = 0;
    }
    else if ( rf_string_object_equals_case_insensitive((int)dword_77FE58, a1 + 8) )
    {
      result = rf_replicator_has_elapsed(dword_77FF18);
      if ( (_BYTE)result )
      {
        unk_77FE4D = 1;
        byte_77FE4E[0] = 1;
        byte_66291B = 1;
        unk_77FE54 = *(unsigned __int8 *)(a1 + 48);
      }
      else
      {
        unk_77FE4D = 0;
      }
    }
    else
    {
      result = byte_77FE4E[0];
      if ( !byte_77FE4E[0] )
      {
        if ( !unk_77FE4D || byte_66291B )
        {
          rf_string_assign_from_object(dword_77FE58, a1 + 8);
          result = rf_replicator_arm_milliseconds(dword_77FF18, 100);
          unk_77FE4D = 0;
          unk_77FE54 = *(unsigned __int8 *)(a1 + 48);
        }
        else
        {
          byte_77FE4E[0] = 1;
        }
      }
    }
  }
  else
  {
    result = byte_77FE4E[0];
    if ( !byte_77FE4E[0] )
    {
      if ( !rf_replicator_is_armed(&unk_77FE6C) )
        rf_replicator_arm_milliseconds(&unk_77FE6C, 300);
      if ( unk_77FE4D )
      {
        result = rf_replicator_has_elapsed(&unk_77FE6C);
        if ( (_BYTE)result )
          byte_77FE4E[0] = 1;
        else
          unk_77FE4D = 0;
      }
      else
      {
        rf_string_assign_from_cstr(dword_77FE58, (char *)&byte_63A405);
        return (int)rf_replicator_reset(dword_77FF18);
      }
    }
  }
  return result;
}

