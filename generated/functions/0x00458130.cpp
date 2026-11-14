// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458130 rf_frontend_help_handle_input_event
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl raw eventDWORD. Wrapped unsigned(event-1)>208 exits; otherwise full209-byte selector table4581B8 maps into4targets at4581A8. Original PE tables: event1
// calls4464A0 deferred stack pop;200/201/203 decrement DWORD6F2998 with32-bit wrap then set1 iff result sign negative;205/208/209 increment with32-bit wrap then signed>=2 sets0. All
// other events do nothing. Valid0/1 page indices cycle, but arbitrary invalid values/INT_MIN wrap are not fully normalized. No sound, rendering, key rebinding, direct game input or
// callback here; result incidental.
void __cdecl rf_frontend_help_handle_input_event(int a1)
{
  switch ( a1 )
  {
    case 1:
      rf_ui_request_panel_stack_pop();
      break;
    case 200:
    case 201:
    case 203:
      if ( --dword_6F2998 < 0 )
        dword_6F2998 = 1;
      break;
    case 205:
    case 208:
    case 209:
      if ( ++dword_6F2998 >= 2 )
        dword_6F2998 = 0;
      break;
    default:
      return;
  }
}

