// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00463050 rf_browser_start_discovery
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg;native callers sometimes pass two ignored sentinel words. Any nonzero trackerActive6F51A2 ->return without work. Else clear cancel6F51A1,arm UIhold57DC1000. LAN
// checkbox6F5DB8 nonzero ->begin refresh461C60. Online:arm shared send deadline5334 offset0,release browser arrays,set displayselection0/rawselection-1;attempt importing each
// favorite BEFORE any reallocation,so importer primaryNULL guard rejects them after normal release. Initialize tracker;FULL EAX==0 shows error modal but still sends fixed10 control
// delegate and sets trackerActive=1. Both sources rebuild indices. Does not reset scroll directly or abort after tracker-init failure;favorite reinsertion after tracker completion is
// separate463290.
void rf_browser_start_discovery()
{
  int i; // [esp+8h] [ebp-4h]

  if ( !unk_6F51A2 )
  {
    unk_6F51A1 = 0;
    rf_clock_deadline_set_wrapped_offset(&dword_6F57DC, 1000);
    if ( byte_6F5DB8[0] )
    {
      rf_browser_begin_refresh_existing_rows();
    }
    else
    {
      rf_clock_deadline_set_wrapped_offset(&dword_6F5334, 0);
      rf_browser_release_record_and_index_arrays();
      unk_6F52E0 = 0;
      dword_661F9C = -1;
      for ( i = 0; i < dword_6F52EC; ++i )
        rf_browser_import_cache100(unk_6F52E8 + 100 * i, 1);
      if ( !rf_tracker_initialize_host_templates_and_pool() )
        rf_ui_show_ok_modal(unk_88E138, unk_88E23C, 0, 0);
      rf_network_control_send_fixed10_when_active();
      unk_6F51A2 = 1;
    }
    rf_browser_rebuild_filtered_sorted_row_indices();
  }
}

