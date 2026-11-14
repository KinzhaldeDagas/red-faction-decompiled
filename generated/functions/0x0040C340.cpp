// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040C340 sub_40C340
// UNREALRED VERIFIED [ai-set-mode-event-20260826]: Association prelude used by Set_AI_Mode when the direct entity's numeric mode at owner +0x520 equals 13. It resolves the identifier at the AI owner's +0x200, runs the verified reciprocal detach path, handles the separate AI-block +0x284 == 13 branch, and finally writes numeric mode 1 to the resolved associated entity. These numeric modes are intentionally not assigned unverified semantic names.
int __cdecl sub_40C340(int *a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-4h]

  result = rf_entity_resolve_handle(*(_DWORD *)(*a1 + 512));
  v2 = result;
  if ( result )
  {
    rf_entity_try_detach_with_safe_exit(*a1);
    if ( a1[161] == 13 )
      rf_ai_numeric_mode_write(a1, 2, -1, -1);
    else
      sub_40A2A0(a1);
    return rf_ai_numeric_mode_write((_DWORD *)(v2 + 672), 1, -1, -1);
  }
  return result;
}

