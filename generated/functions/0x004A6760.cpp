// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6760 constant_return_false_al_4A6760
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Native body saves incoming ECX only in private stack local, XOR AL,AL, returns; no argument reads used in result, calls or global writes. Always returns AL0 while upper EAX is not initialized. Repeated startup callers set different option-related ECX values but none affect result. Do not reinterpret this compiled stub as the working boolean-option getter rf_command_line_bool_option_is_enabled. Existing library classification retained because this generic body alone does not establish original source ownership.
char constant_return_false_al_4A6760()
{
  return 0;
}

