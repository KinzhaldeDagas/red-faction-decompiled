// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BC90 rf_input_get_scan_code_state_byte
// UNREALRED VERIFIED [system-progress-20261028]: Returns BYTE at0x193B560+signed index. No bounds validation,mutation,normalization or event dequeue. Window procedure uses indices56 and184 to suppress selected default handling.
char __cdecl rf_input_get_scan_code_state_byte(int a1)
{
  return byte_193B560[a1];
}

