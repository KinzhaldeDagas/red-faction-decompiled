// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004163C0 rf_clutter_render_registered_clocks
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Noargs. Signed loop0..<globalcount666B78,reads runtimeUIDs from666AE0,resolves each via clutter-only resolver and calls416420 fornonNULL. StaleUID skipped,notremoved. Wrapper has NO own32-capacity check or classflag recheck;normal builder414680 populates first32 clutter classes with flag0x100 in listorder. Does not reset count/time or stop after failed draw. No list/input allocation or defined application returnvalue.
void rf_clutter_render_registered_clocks()
{
  int i; // [esp+0h] [ebp-8h]
  int v1; // [esp+4h] [ebp-4h]

  for ( i = 0; i < dword_666B78; ++i )
  {
    v1 = rf_clutter_find_by_uid(unk_666AE0[i]);
    if ( v1 )
      rf_clutter_render_three_clock_hands(v1);
  }
}

