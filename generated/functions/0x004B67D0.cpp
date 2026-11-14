// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B67D0 rf_download_configure_received_transfer
// UNREALRED VERIFIED [file-transfer-20261028]: Receive-offer callback taking slot. Copies slot name to temporary string; case-insensitive match with global requested filename0x6FC31C stores slot in0x7B4DE4 and sets transfer path selector from0x88E430. Other names use selector0x88E428 and enable auto-release0x8000. Destroys temporary string. Does not start or cancel transfer itself.
void __cdecl rf_download_configure_received_transfer(int a1)
{
  _DWORD v1[2]; // [esp+4h] [ebp-14h] BYREF
  int v2; // [esp+14h] [ebp-4h]

  rf_string_construct_empty(v1);
  v2 = 0;
  rf_file_transfer_copy_slot_name(a1, v1);
  if ( rf_string_object_equals_case_insensitive((int)unk_6FC31C, (int)v1) )
  {
    dword_7B4DE4 = a1;
    rf_file_transfer_set_path_selector(dword_88E430, a1);
  }
  else
  {
    rf_file_transfer_set_path_selector(unk_88E428, a1);
    rf_file_transfer_enable_auto_release(a1);
  }
  v2 = -1;
  rf_string_destroy_buffer(v1);
}

