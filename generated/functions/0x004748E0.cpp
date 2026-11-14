// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004748E0 rf_item_show_local_pickup_message
// UNREALRED VERIFIED [item-pickups-20261028]: Only for entity==global0x681E38 and local-player-entry count<=1. Selects localized item-definition pickup strings: normal single+20/plural+24, weapon-and-ammo single+28/plural+32. Plural path requires quantity>1 and available plural normal or W&A string. Formats into global0x18CD828, using260-byte temporary for format templates, then0x44B4B0. Missing normal single+20 exits in singular branch; some W&A missing-template paths still call display with prior global buffer contents. No bounds checks on sprintf and no general fallback guarantee.
void __cdecl rf_item_show_local_pickup_message(int a1, int a2, int a3, char a4)
{
  char Buffer[260]; // [esp+0h] [ebp-108h] BYREF

  if ( a1 == dword_681E38 && rf_local_player_entry_count <= 1 )
  {
    if ( a3 > 1 && (*(_DWORD *)(a2 + 24) || a4 && *(_DWORD *)(a2 + 32)) )
    {
      if ( a4 || !*(_DWORD *)(a2 + 24) )
      {
        if ( a4 )
        {
          if ( *(_DWORD *)(a2 + 32) )
          {
            sprintf(Buffer, "%s", **(const char ***)(a2 + 32));
            sprintf(&unk_18CD828, Buffer, a3);
          }
        }
      }
      else
      {
        sprintf(Buffer, "%s", **(const char ***)(a2 + 24));
        sprintf(&unk_18CD828, Buffer, a3);
      }
    }
    else
    {
      if ( !*(_DWORD *)(a2 + 20) )
        return;
      if ( a4 || !*(_DWORD *)(a2 + 20) )
      {
        if ( a4 && *(_DWORD *)(a2 + 28) )
        {
          sprintf(Buffer, "%s", **(const char ***)(a2 + 28));
          sprintf(&unk_18CD828, Buffer, a3);
        }
      }
      else
      {
        sprintf(&unk_18CD828, "%s", **(const char ***)(a2 + 20));
      }
    }
    rf_hud_message_enqueue_expand_tokens_and_rearm_head(&unk_18CD828, 0, 0, nullptr);
  }
}

