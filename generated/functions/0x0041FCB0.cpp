// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041FCB0 rf_console_jump_height_command
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): No-argument void console callback. Global1809818 ANY nonzero: parse56F950(requiredMask0x10,preserveCase0), ignore flags return, copy parsed
// FLOAT180A400 to persistent height681E28 FIRST. Then x87 load current gravity FLOAT662E18, multiply DOUBLE2.0, multiply stored height, round product to FLOAT32 local before passing
// FLOAT to40CFF0. Sqrt wrapper ultimately40D010 returns FLOAT32-rounded sqrt throughST0; store that to persistent681E1C. No sign,finite,zero-gravity or result check; negative/NaN
// product is delegated to native sqrt environment, and height has already committed. No extra intermediate FLOAT store between gravity*2 and multiplyheight. If global1809818==0, only
// when global1809AB8 nonzero construct/print "jump height = "+current681E28 formatted fixed2 decimal places+newline, with normal/SEH string cleanup. Otherwise no action. Parsing may
// nonlocally abort before own height store; no player/entity lookup, action/sound cleanup, deadline, impulse application or independent success return.
void rf_console_jump_height_command()
{
  const char *v0; // eax
  void *v1; // [esp+Ch] [ebp-28h]
  float v2; // [esp+14h] [ebp-20h]
  int v3[2]; // [esp+18h] [ebp-1Ch] BYREF
  _DWORD v4[2]; // [esp+20h] [ebp-14h] BYREF
  int v5; // [esp+30h] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(16, 0);
    unk_681E28 = flt_180A400;
    v2 = rf_physics_gravity_acceleration * 2.0 * flt_180A400;
    unk_681E1C = rf_sqrt_float(v2);
  }
  else if ( unk_1809AB8 )
  {
    rf_string_construct_from_cstr(v4, "jump height = ");
    v5 = 0;
    v1 = rf_string_format_float_fixed_precision(v3, unk_681E28, 2);
    LOBYTE(v5) = 1;
    rf_string_append_object_in_place(v4, (int)v1);
    LOBYTE(v5) = 0;
    rf_string_destroy_buffer(v3);
    rf_string_append_cstr_in_place(v4, (int)"\n");
    v0 = rf_string_object_c_str_or_empty(v4);
    rf_console_output_append_text_lines(v0, nullptr);
    v5 = -1;
    rf_string_destroy_buffer(v4);
  }
}

