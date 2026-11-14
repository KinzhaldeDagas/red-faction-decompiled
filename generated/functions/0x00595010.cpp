// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595010 rf_console_command_system_info
// UNREALRED VERIFIED [system-progress-20261028]: If console execution flag0x1809818 set, constructs2048-byte backed output object, calls0x594C40 with benchmark enabled, prints text through0x56DD50, destroys output object. If help flag0x1809814 set, prints Shows system info. May execute both branches. No arguments or explicit result; benchmark may block for roughly1second plus CPU measurement.
void rf_console_command_system_info()
{
  char *data; // eax
  int v1[513]; // [esp+4h] [ebp-82Ch] BYREF
  const char *v2[6]; // [esp+80Ch] [ebp-24h] BYREF
  int v3; // [esp+82Ch] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_text_log_buffer_construct(v2, (int)v1, 2048, 0);
    v3 = 0;
    rf_system_append_legacy_info_report(v2, 1, 1u);
    data = (char *)rf_text_log_buffer_get_data(v2);
    rf_console_output_append_text_lines(data, nullptr);
    v3 = -1;
    rf_text_log_buffer_destroy_storage((int)v2);
  }
  if ( dword_1809814 )
    rf_console_output_append_text_lines("Shows system info", nullptr);
}

